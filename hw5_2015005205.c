#include "types.h"
#include "defs.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"
#include "x86.h"
#include "traps.h"
#include "spinlock.h"

// Interrupt descriptor table (shared by all CPUs).
struct gatedesc idt[256];
extern uint vectors[];  // in vectors.S: array of 256 entry pointers
struct spinlock tickslock;
uint ticks;

void
tvinit(void)
{
  int i;

  for(i = 0; i < 256; i++)
    SETGATE(idt[i], 0, SEG_KCODE<<3, vectors[i], 0);
  SETGATE(idt[T_SYSCALL], 1, SEG_KCODE<<3, vectors[T_SYSCALL], DPL_USER);

  initlock(&tickslock, "time");
}

void
idtinit(void)
{
  lidt(idt, sizeof(idt));
}

//PAGEBREAK: 41
void
trap(struct trapframe *tf)
{
  if(tf->trapno == T_SYSCALL){
    if(myproc()->killed)
      exit();
    myproc()->tf = tf;
    syscall();
    if(myproc()->killed)
      exit();
    return;
  }

  switch(tf->trapno){
  case T_IRQ0 + IRQ_TIMER:
    if(cpuid() == 0){
      acquire(&tickslock);
      ticks++;
      wakeup(&ticks);
      release(&tickslock);
    }
    //매 tick마다 하드웨어가 발생시키는 인터럽트를 T_IRQ0 + IRQ_TIMER 케이스에서 처리된다.
    //alarmtest code...
	if(myproc() != 0 && (tf->cs & 3) == 3){//프로세서가 실행 중이고, 유저프로세스에서 발생한 타이머 인터럽트일 때 알람 tick을 처리한다.
        //tf->cs == 3이면 유저모드
		myproc()->countticks++;
		if(myproc()->countticks == myproc()->alarmticks){
            //주어진 tick만큼 tick이 발생했을 때 myproc()->alarmhandler에 들어있는 periodic를 실행한다.
            // 커널 모드에서 유저함수를 사용해야하는 결과가 나온다.
            //따라서 유저스택영역에 유저영역에서 현재 보고있던 주소를 저장해준다.
            //그후 유저영역으로 돌아갔을 때 실행해야하는 주소에 alarmhandler함수주소를 넣어준다.
            //인터럽트를 처리하고 유저영역으로 돌아가서 alarmhandler함수를 실행한 뒤 유저스택의 리턴값을 보고 다시 .을 프린트하는 일을 진행한다.
			tf->esp-=4;//유저스택에 새로운 값을 저장할 공간 생성
			*((uint *)(tf->esp)) = tf->eip;//유저스택에 유저영역에서 현재보고있는 주소를 저장
			tf->eip = (uint)myproc()->alarmhandler;//현재봐야하는 주소를 alarmhandler함수 주소로 저장
			myproc()->countticks = 0;//다시 tick을 카운트하기 위해 0으로 초기화
		}
	}
    
	lapiceoi();
    break;
  case T_IRQ0 + IRQ_IDE:
    ideintr();
    lapiceoi();
    break;
  case T_IRQ0 + IRQ_IDE+1:
    // Bochs generates spurious IDE1 interrupts.
    break;
  case T_IRQ0 + IRQ_KBD:
    kbdintr();
    lapiceoi();
    break;
  case T_IRQ0 + IRQ_COM1:
    uartintr();
    lapiceoi();
    break;
  case T_IRQ0 + 7:
  case T_IRQ0 + IRQ_SPURIOUS:
    cprintf("cpu%d: spurious interrupt at %x:%x\n",
            cpuid(), tf->cs, tf->eip);
    lapiceoi();
    break;

  //PAGEBREAK: 13
  default:
    if(myproc() == 0 || (tf->cs&3) == 0){
      // In kernel, it must be our mistake.
      cprintf("unexpected trap %d from cpu %d eip %x (cr2=0x%x)\n",
              tf->trapno, cpuid(), tf->eip, rcr2());
      panic("trap");
    }
    // In user space, assume process misbehaved.
    cprintf("pid %d %s: trap %d err %d on cpu %d "
            "eip 0x%x addr 0x%x--kill proc\n",
            myproc()->pid, myproc()->name, tf->trapno,
            tf->err, cpuid(), tf->eip, rcr2());
    myproc()->killed = 1;
  }

  // Force process exit if it has been killed and is in user space.
  // (If it is still executing in the kernel, let it keep running
  // until it gets to the regular system call return.)
  if(myproc() && myproc()->killed && (tf->cs&3) == DPL_USER)
    exit();

  // Force process to give up CPU on clock tick.
  // If interrupts were on while locks held, would need to check nlock.
  if(myproc() && myproc()->state == RUNNING &&
     tf->trapno == T_IRQ0+IRQ_TIMER)
    yield();

  // Check if the process has been killed since we yielded
  if(myproc() && myproc()->killed && (tf->cs&3) == DPL_USER)
    exit();
}
