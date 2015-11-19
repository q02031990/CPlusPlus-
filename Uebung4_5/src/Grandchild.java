import java.util.concurrent.locks.ReentrantLock;

import java.util.concurrent.locks.ReentrantLock;

public class Grandchild extends Thread
{
	private Bank _bank;
	private String _name;
	private int _sleepTime;
	private int _accountNumber;
	
	private static ReentrantLock _lock = new ReentrantLock();
	
	public Grandchild(Bank pBank, String pName, int pSleepTime, int pAccountNumber)
	{
		_bank = pBank;
		_name = pName;
		_sleepTime = pSleepTime;
		_accountNumber = pAccountNumber;
	}
	
	public void run()
	{
		while(true)
		{
			try
			{
				_lock.lock();
				{
					_bank.transfer(0, Math.random() * 50.0, _accountNumber);
				}
				_lock.unlock();
			}
			catch(IllegalArgumentException e)
			{
				try
				{
					this.wait();Thread.sleep(1000);
				}
				catch (InterruptedException e1)
				{
					e1.printStackTrace();
				}
			}
			
			try
			{
				Thread.sleep(_sleepTime);
			}
			catch (InterruptedException e)
			{
				e.printStackTrace();
			}
		}
	}
}
