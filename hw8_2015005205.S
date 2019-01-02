	.text

/* Switch from current_thread to next_thread. Make next_thread
 * the current_thread, and set next_thread to 0.
 * Use eax as a temporary register; it is caller saved.
 */
	.globl thread_switch
thread_switch:
	/* YOUR CODE HERE */
	pushal/*x86의 8개 register들을 current_thread stack에 저장한다.*/

	movl current_thread, %eax/*eax레지스터에 current_thread의 sp를 저장한다.*/
	movl %esp, (%eax)/*current_thread의 stack에 현재esp값을 저장한다*/

	movl next_thread, %eax/*eax register에 next_thread의 stack주소를 저장한다.*/
	movl (%eax), %esp/*stack에 next_thread에서 전에 보던 esp값을 현재의 esp값으로 사용한다.*/

	movl %eax, current_thread/*eax에 저장되어있는 next_thread을 current_thread로 바꿔준다.*/
    movl $0, next_thread/*next_thread를 0으로 초기화해준다.*/

	popal/*current_thread stack에 저장되어있는 register들을 모두 복구한다.*/

	ret				/* pop return address from stack */
