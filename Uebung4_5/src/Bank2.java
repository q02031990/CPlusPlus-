import java.util.ArrayList;
import java.util.concurrent.ArrayBlockingQueue;

public class Bank2 implements Runnable
{
	private ArrayList<Account> _accounts = new ArrayList<Account>();
	private ArrayBlockingQueue<Transaction> _transactions;
	
	public Bank2(ArrayBlockingQueue pTransactionQueue)
	{
		_transactions = pTransactionQueue;
	}
	
	public synchronized void run()
	{
		while(true)
		{
			if(!_transactions.isEmpty())
			{
				Transaction transaction;
				try
				{
					transaction = _transactions.take();
					
					Account foundAccount = null;
					
					for (Account account : _accounts) {
						if(account.get_number() == transaction.get_accountNumber())
						{
							foundAccount = account;
							break;
						}
					}
					_accounts.remove(foundAccount);
					
					foundAccount.set_balance(foundAccount.get_balance() + transaction.get_balanceChange());
					
					_accounts.add(foundAccount);
					System.out.println(foundAccount.get_number() + ":" + foundAccount.get_balance() + "(" + transaction.get_balanceChange() + ")");
				}
				catch (InterruptedException e)
				{
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
			}
		}
	}
	
	public void AddAccount(Account pNewAccount)
	{
		_accounts.add(pNewAccount);
	}
	
	public void AddTransaction(Transaction pTransaction)
	{
		_transactions.add(pTransaction);
	}
}
