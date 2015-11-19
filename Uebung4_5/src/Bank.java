import java.util.HashMap;

public class Bank
{	
	//Properties _balances = new Properties();
	private HashMap<Integer, Double> _balances = new HashMap<Integer, Double>();
	
	public void createAccount(int pOwner)
	{
		_balances.put(pOwner, 0.0);
	}
	
	public void transfer(int pAsInput, double pAmount, int pOwner) throws IllegalArgumentException
	{		
		if(pAsInput == 0)
		{
			//Auszahlung
			transferOut(pAmount, pOwner);
		}
		else if(pAsInput == 1)
		{
			//Einzahlung
			transferIn(pAmount, pOwner);
		}
		else
			throw new IllegalArgumentException();
		
		System.out.println(_balances.get(pOwner));
	}
	
	private synchronized void transferIn(double pAmount, int pOwner)
	{		
		double val = _balances.get(pOwner);
		val += pAmount;
		_balances.put(pOwner, val);
	}
	
	private synchronized void transferOut(double pAmount, int pOwner) throws IllegalArgumentException
	{
		double val = _balances.get(pOwner);
		val -= pAmount;
		
		if(val<0)
			throw new IllegalArgumentException();
		
		_balances.put(pOwner, val);
	}
}
