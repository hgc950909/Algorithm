
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.Statement;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.Locale;
import java.util.Scanner;

public class BankDB {
	
	public static void main(String[] args) {
		try {
			Connection con = DriverManager.getConnection( "jdbc:mysql://localhost:3306/Bank", "root", "chlghdrb1080" );
			int command;
			String commandstring;
			Statement stmt = con.createStatement();
			ResultSet rs;
			Scanner keyboard = new Scanner(System.in);
			while(true) {
				rs = stmt.executeQuery("SELECT bank_name from bank");
				System.out.println("-------Welcome to BankDB---------\n");
				while(rs.next()) {
					System.out.println(rs.getString(1));
				}
				System.out.println("Exit");
				System.out.println("-----------------------------------");
				System.out.println("Select Menu :\n");
				commandstring = keyboard.next();
				if(commandstring.equals("Exit")) {
					System.out.println("Thank you");
					return;
				}
					while(true) {
						System.out.println("This is "+commandstring + "----------------");
						System.out.println("0. Return to previous menu");
						System.out.println("1. Manager menu");
						System.out.println("2. User menu");
						System.out.println("Select Menu : ");
						command = keyboard.nextInt();
						if(command ==0) {
							break;
						}
						switch(command) {
						case 1:
							while(true) {
								System.out.println("0. Return to previous menu");
								System.out.println("1. View Bank info");
								System.out.println("2. View user list");
								System.out.println("3. View account info");
								System.out.println("4. View trans Info");
								System.out.println("5. Create new user");
								System.out.println("6. Create new manager");
								System.out.println("7. Delete user");
								System.out.println("8. View manager list");
								System.out.println("Select Menu : ");
								int ID;
								int aID;
								command = keyboard.nextInt();
								if(command ==0) {
									break;
								}
								switch(command) {
									case 1:
										rs = stmt.executeQuery("SELECT * FROM bank WHERE bank_name = " +"'"+commandstring + "'" );
										System.out.println("-----------------------------------------------------------------------");
										System.out.println("        Bank        Managers        Users        Location        Phone");
										System.out.println("-----------------------------------------------------------------------");
										while(rs.next()) {
											System.out.printf(" %11s%15d%12d%19s%12d \n",rs.getString(1),rs.getInt(2),rs.getInt(3),rs.getString(4),rs.getInt(5));
										}
										System.out.println("-----------------------------------------------------------------------");
										break;
									case 2:
										System.out.println("-----------------------------------------------------------------------");
										System.out.println("        UserID        UserName        ManagerId        ManagerName");
										System.out.println("-----------------------------------------------------------------------");
										rs = stmt.executeQuery("SELECT u.userID, u.name, ma.managerID, ma.Mname FROM user as u, member as m, bank as b, manager as ma WHERE u.userid=m.uid and m.bname = b.bank_name and b.bank_name = " 
										+ "'"+commandstring + "'" + " and u.MID = ma.managerID");
										while(rs.next()) {
											System.out.printf(" %13d%15s%18d%19s \n",rs.getInt(1),rs.getString(2),rs.getInt(3),rs.getString(4));
										}
										System.out.println("-----------------------------------------------------------------------");
										break;
									case 3:
										System.out.println("Insert userID:");
										ID = keyboard.nextInt();
										rs= stmt.executeQuery("SELECT count(*) FROM user,member WHERE userID=UID and Bname= "+ "'"+commandstring + "'" + " and userID =" + ID);
										rs.next();
										if(rs.getInt(1)==0) {
											System.out.println("There is no user\n");
											break;
										}
										System.out.println("-------------------------------------------------------------------------");
										System.out.println("        UserID        Username        AccountID        create_date");
										System.out.println("-------------------------------------------------------------------------");
										rs = stmt.executeQuery("SELECT userID ,name, accountID, create_date FROM user,account WHERE userID =UID and userID = " + ID );
										while(rs.next()) {
											if(ID==rs.getInt(1)) {
												System.out.printf(" %13d%15s%18d%19d \n",rs.getInt(1),rs.getString(2),rs.getInt(3),rs.getInt(4));
											}
										}
										System.out.println("-------------------------------------------------------------------------");
										break;
									case 4:
										System.out.println("Insert userID:" );
										ID = keyboard.nextInt();
										rs= stmt.executeQuery("SELECT count(*) FROM user,member WHERE userID=UID and Bname= " + "'"+commandstring + "'" + " and userID =" + ID);
										rs.next();
										if(rs.getInt(1)==0) {
											System.out.println("There is no user\n");
											break;
										}
										System.out.println("Insert accountID:");
										aID= keyboard.nextInt();
										rs= stmt.executeQuery("SELECT count(*) FROM account WHERE UID = "+ ID +" and accountID = " + aID);
										rs.next();
										if(rs.getInt(1)==0) {
											System.out.println("There is no account\n");
											break;
										}
										System.out.println("-----------------------------------------------------------------------------------------------------------------------");
										System.out.println("        UserID        Username        AccountID               time        deal_money        state        balance");
										System.out.println("-----------------------------------------------------------------------------------------------------------------------");
										rs = stmt.executeQuery("SELECT userID ,name, accountID, l.time, l.deal_money,l.state,l.balance FROM user,account as a,list as l WHERE userID =a.UID and a.accountID = l.AID and userID = " 
										+ ID + " and AccountID = "+ aID + " order by l.time DESC");
										while(rs.next()) {
											if(ID==rs.getInt(1) && aID ==rs.getInt(3)) {
												System.out.printf(" %13d%15s%18d%19s%18d%12s%14d \n",rs.getInt(1),rs.getString(2),rs.getInt(3),rs.getString(4),rs.getInt(5),rs.getString(6),rs.getInt(7));
											}
										}
										System.out.println("-----------------------------------------------------------------------------------------------------------------------");
										break;
									case 5:
										System.out.println("Insert UserID:");
										ID = keyboard.nextInt();
										rs=stmt.executeQuery("SELECT count(*) FROM user WHERE userID =" + ID );
										rs.next();
										if(rs.getInt(1)>0) {
											System.out.println("There is same userID");
											break;
										}
										System.out.println("Insert UserName:");
										String name = "'"+keyboard.next()+ "'";
										System.out.println("Insert Phone:");
										int tel = keyboard.nextInt();
										System.out.println("Insert Address:");
										String ad = "'"+keyboard.next()+ "'";
										System.out.println("Insert Date:");
										int day = keyboard.nextInt();
										System.out.println("Insert sex:");
										String sex = "'"+keyboard.next()+ "'";
										System.out.println("Insert birthdate:");
										int bir = keyboard.nextInt();
										System.out.println("Insert ManagerID:");
										int MID = keyboard.nextInt();
										
										rs=stmt.executeQuery("SELECT count(*) FROM manager WHERE managerID =" + MID + " and Bname = " + "'"+commandstring + "'" );
										rs.next();
										if(rs.getInt(1)==0) {
											System.out.println("There is no manager");
											break;
										}
										stmt.executeUpdate("insert into user values ("+ID+"," +name+","+ 0 +"," + tel + "," + ad + "," + day+ "," + sex + "," + bir + "," +MID + ")");
										stmt.executeUpdate("insert into member values(" + ID + "," + "'"+commandstring + "'" + ")");
										rs=stmt.executeQuery("select users from bank where Bank_name = " + "'"+commandstring + "'" );
										rs.next();
										int users=rs.getInt(1);
										users+=1;
										stmt.executeUpdate("UPDATE bank SET users=" + users + " WHERE Bank_name = " + "'"+commandstring + "'");
										System.out.println("Complete!");
										break;
									case 6:
										System.out.println("Insert ManagerID:");
										int managerID = keyboard.nextInt();
										rs=stmt.executeQuery("SELECT count(*) FROM manager WHERE managerID =" + managerID + " and Bname = "+ "'" + commandstring + "'");
										rs.next();
										if(rs.getInt(1)>0) {
											System.out.println("There is same managerID");
											break;
										}
										System.out.println("Insert ManagerName:");
										String Mname = "'"+keyboard.next()+ "'";
										System.out.println("Insert Phone: ");
										int Mphone = keyboard.nextInt();
										System.out.println("Insert sex:");
										String Msex = "'"+keyboard.next()+ "'";
										System.out.println("Insert address:");
										String addr = "'"+keyboard.next()+ "'";
										System.out.println("Insert birthdate:");
										int Mbir = keyboard.nextInt();
										stmt.executeUpdate("insert into manager values (" + managerID + "," + Mname + ","+ Mphone + "," + Msex + "," + addr + "," + Mbir + "," + "'"+commandstring + "'" + ")");
										rs=stmt.executeQuery("select managers from bank where Bank_name = " + "'"+commandstring + "'");
										rs.next();
										int managers=rs.getInt(1);
										managers+=1;
										stmt.executeUpdate("UPDATE bank SET managers =" + managers + " WHERE Bank_name = " + "'"+commandstring + "'");
										System.out.println("Complete!");
										break;
									case 7:
										System.out.println("Insert userID: ");
										int userID =keyboard.nextInt();
										rs=stmt.executeQuery("SELECT count(*) FROM user,member WHERE  userID = UID and userID =" + userID +" and Bank_name =" + "'"+commandstring + "'");
										rs.next();
										if(rs.getInt(1)==0) {
											System.out.println("There is no user");
											System.out.println("DELETE FAIL!");
											break;
										}
										stmt.execute("SET foreign_key_checks=0");
										rs=stmt.executeQuery("SELECT accountID FROM account WHERE UID = " + userID);
										while(rs.next()) {
											int accountID = rs.getInt(1);
											stmt.executeUpdate("DELETE FROM list where AID = " + accountID);
											stmt.executeUpdate("DELETE FROM account where accountID = " + accountID); 
										}
										stmt.executeUpdate("DELETE FROM user where userID = " + userID); 
										rs=stmt.executeQuery("select users from bank where Bank_name = " + "'"+commandstring + "'");
										rs.next();
										users=rs.getInt(1);
										users-=1;
										stmt.executeUpdate("UPDATE bank SET users =" + users + " WHERE Bank_name = " + "'"+commandstring + "'");
										System.out.println("Complete!");
										stmt.execute("SET foreign_key_checks=1");
										break;
									case 8:
										System.out.println("----------------------------------------");
										System.out.println("        ManagerID        ManagerName");
										System.out.println("----------------------------------------");
										rs = stmt.executeQuery("SELECT managerID, Mname FROM manager WHERE Bname = "+ "'"+commandstring + "'" );
										while(rs.next()) {
											System.out.printf(" %13d%22s \n",rs.getInt(1),rs.getString(2));
										}
										System.out.println("-----------------------------------------");
										break;	
								}	
							}
							break;
						case 2:
							while(true) {
								System.out.println("0. Return to previous menu");
								System.out.println("1. open new account");
								System.out.println("2. Deposit");
								System.out.println("3. Withdraw");
								System.out.println("4. transfer");
								System.out.println("5. close account");
								ResultSet rs1;
								command = keyboard.nextInt();
								if(command ==0) {
									break;
								}
								switch(command) {
									case 1:
										
										System.out.println("Insert accountID:");
										int accountID = keyboard.nextInt();
										rs=stmt.executeQuery("SELECT count(*) FROM account WHERE accountID = " + accountID);
										rs.next();
										if(rs.getInt(1)!=0) {
											System.out.println("There is same user");
											System.out.println("CREATE FAIL!");
											break;
										}
										System.out.println("Insert today:");
										int aday = keyboard.nextInt();
										System.out.println("Insert your ID:");
										int UID = keyboard.nextInt();
										rs=stmt.executeQuery("SELECT count(*) FROM user,member WHERE userID = UID and Bname = "+ "'"+commandstring + "'" +" and userID =" + UID );
										rs.next();
										if(rs.getInt(1)==0) {
											System.out.println("There is no user");
											System.out.println("CREATE FAIL!");
											break;
										}
										stmt.executeUpdate("insert into account values (" + accountID + "," + 0 + "," + aday + "," + UID +")");
										rs=stmt.executeQuery("SELECT account_num FROM user WHERE userID = " + UID);
										rs.next();
										int nnum=rs.getInt(1)+1;
										stmt.executeUpdate("UPDATE user SET account_num = " + nnum + " WHERE userID = " + UID);
										System.out.println("Complete!");
										break;
									case 2:
										
										SimpleDateFormat time = new SimpleDateFormat ( "yyyyMMddHHmmss", Locale.KOREA );
									    Date now = new Date();
									    String ttime = time.format ( now );
									    System.out.println("Insert userID:" );
										int ID = keyboard.nextInt();
										rs= stmt.executeQuery("SELECT count(*) FROM user,member WHERE userID=UID and Bname= " + "'"+commandstring + "'" + " and userID =" + ID);
										rs.next();
										if(rs.getInt(1)==0) {
											System.out.println("There is no user\n");
											System.out.println("DEPOSIT FAIL!");
											break;
										}
									    System.out.println("Insert accountID:");
										accountID = keyboard.nextInt();
										rs=stmt.executeQuery("SELECT count(*),balance FROM account WHERE accountID = " + accountID + " and UID = " + ID );
										rs.next();
										if(rs.getInt(1)==0) {
											System.out.println("There is no account");
											System.out.println("DEPOSIT FAIL!");
											break;
										}
										int balance = rs.getInt(2);
										System.out.println("Insert money:");
										int money = keyboard.nextInt();
										balance+=money;
										stmt.executeUpdate("insert into list values ('" + ttime + "'," + accountID + "," + money + ", 'D'," + balance +","+ 0 +")");
										stmt.executeUpdate("UPDATE account SET balance = " + balance + " WHERE accountID = " + accountID);
										System.out.println("Complete!");
										break;
									case 3:
										  
										time = new SimpleDateFormat ( "yyyyMMddHHmmss", Locale.KOREA );
									    now = new Date();
									    ttime = time.format ( now );
									    System.out.println("Insert userID:" );
										ID = keyboard.nextInt();
										rs= stmt.executeQuery("SELECT count(*) FROM user,member WHERE userID=UID and Bname= " + "'"+commandstring + "'" + " and userID =" + ID);
										rs.next();
										if(rs.getInt(1)==0) {
											System.out.println("There is no user\n");
											System.out.println("WITHDRAW FAIL!");
											break;
										}
									    System.out.println("Insert accountID:");
										accountID = keyboard.nextInt();
										rs=stmt.executeQuery("SELECT count(*),balance FROM account WHERE accountID = " + accountID + " and UID =" + ID );
										rs.next();
										if(rs.getInt(1)==0) {
											System.out.println("There is no account");
											System.out.println("WITHDRAW FAIL!");
											break;
										}
										balance = rs.getInt(2);
										System.out.println("Insert money:");
										money = keyboard.nextInt();
										if((balance-money)<0) {
											System.out.println("Not enough money");
											System.out.println("WITHDRAW FAIL!");
											break;
										}
										balance-=money;
										stmt.executeUpdate("insert into list values ('" + ttime + "'," + accountID + "," + money + ", 'W'," + balance + "," + 0 +")");
										stmt.executeUpdate("UPDATE account SET balance =" + balance + " WHERE accountID = " + accountID);
										System.out.println("Complete!");
										break;
									case 4:
										
										time = new SimpleDateFormat ( "yyyyMMddHHmmss", Locale.KOREA );
									    now = new Date();
									    ttime = time.format ( now );
									    System.out.println("Insert userID:" );
										ID = keyboard.nextInt();
										rs= stmt.executeQuery("SELECT count(*) FROM user,member WHERE userID=UID and Bname= " + "'"+commandstring + "'" + " and userID =" + ID);
										rs.next();
										if(rs.getInt(1)==0) {
											System.out.println("There is no user\n");
											System.out.println("WITHDRAW FAIL!");
											break;
										}
									    System.out.println("Insert  destination accountID:");
										accountID = keyboard.nextInt();
										rs=stmt.executeQuery("SELECT count(*),balance FROM account WHERE accountID =" + accountID );
										rs.next();
										if(rs.getInt(1)==0) {
											System.out.println("There is no destination account");
											System.out.println("TRANSFER FAIL!");
											break;
										}
										System.out.println("Insert your accountID");
										int yourID = keyboard.nextInt();
										rs1 = stmt.executeQuery("SELECT count(*),balance FROM account WHERE accountID =" + yourID + " and UID = " + ID);
										rs1.next();
										if(rs1.getInt(1)==0) {
											System.out.println("There is no account");
											System.out.println("TRANSFER FAIL!");
											break;
										}
										int destbalance = rs.getInt(2);
										int yourbalance =rs1.getInt(2);
										System.out.println("Insert money:");
										money = keyboard.nextInt();
										if((yourbalance-money)<0) {
											System.out.println("Not enough money");
											break;
										}
										destbalance+=money;
										yourbalance-=money;
										stmt.executeUpdate("insert into list values ('" + ttime + "'," + accountID + "," + money + ", 'TR'," + destbalance + "," + yourID +")");//TR: transfer receive
										stmt.executeUpdate("insert into list values ('" + ttime + "'," + yourID + "," + money + ", 'TS'," + yourbalance + "," + accountID + ")");//TS: transfer send
										stmt.executeUpdate("UPDATE account SET balance = " + yourbalance + " WHERE accountID = " + yourID);
										stmt.executeUpdate("Update account set balance = " + destbalance + " where accountID =" + accountID);
										System.out.println("Complete!");
										break;
									case 5:
										
										System.out.println("Insert userID");
										int userID = keyboard.nextInt();
										rs=stmt.executeQuery("SELECT count(*) FROM user,member WHERE userID = UID and Bname = "+ "'"+commandstring + "'" +" and userID =" + userID );
										rs.next();
										if(rs.getInt(1)==0) {
											System.out.println("There is no user");
											System.out.println("DELETE FAIL!");
											break;
										}
										System.out.println("Insert accountID");
										int aID = keyboard.nextInt();
										rs=stmt.executeQuery("SELECT count(*) FROM account WHERE UID = " +userID + " and accountID = " +  aID);
										rs.next();
										if(rs.getInt(1)==0) {
											System.out.println("There is no account");
											System.out.println("DELETE FAIL!");
											break;
										}
										rs=stmt.executeQuery("Select balance from account where UID = " + userID + " and accountID = " + aID);
										rs.next();
										if(rs.getInt(1) != 0) {
											System.out.println("You have money in account!");
											System.out.println("DELETE FAIL!");
											break;
										}
										stmt.execute("SET foreign_key_checks=0");
										stmt.executeUpdate("DELETE from account WHERE accountID = " + aID);
										stmt.executeUpdate("DELETE from list WHERE AID = " + aID);
										rs = stmt.executeQuery("select account_num from user where userID = " + userID);
										rs.next();
										int accnum = rs.getInt(1);
										accnum-=1;
										stmt.executeUpdate("update user set account_num = " + accnum + " where userID = " + userID);
										System.out.println("Complete!");
										stmt.execute("SET foreign_key_checks=1");
										break;
								}
							}
							break;
						}
					}
			}
		}
		catch(Exception e) {
			e.printStackTrace();
		}
	}
}
