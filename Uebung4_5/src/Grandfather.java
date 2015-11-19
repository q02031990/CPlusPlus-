import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;

public class Grandfather
{
	private Bank _bank;
	private int _accountNumber;
	private ArrayList<Grandchild> _grandChilds;
	
	public Grandfather(Bank pBank, int pAccountNumber,
			ArrayList<Grandchild> pGrandChilds) {
		_bank = pBank;
		_accountNumber = pAccountNumber;
		_grandChilds = pGrandChilds;
	}

	public void SendMoney() throws IllegalArgumentException, IOException
	{
		BufferedReader buffer=new BufferedReader(new InputStreamReader(System.in));
		
		while(true)
		{
			String line = buffer.readLine();
			try
			{
				double d = Double.parseDouble(line);
				_bank.transfer(1, d, _accountNumber);
				for(int i = 0; i<_grandChilds.size();i++)
				{
					_grandChilds.notifyAll();
				}
			}
			catch(NumberFormatException e)
			{
				break;
			}

		}
	}
	
	public void SendMoneySilent() throws IOException
	{
		BufferedReader buffer=new BufferedReader(new InputStreamReader(System.in));
		
		while(true)
		{
			String line = buffer.readLine();
			try
			{
				double d = Double.parseDouble(line);
				_bank.transfer(1, d, _accountNumber);
			}
			catch(NumberFormatException e)
			{
				break;
			}

		}
	}
}
