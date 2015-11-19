public class Account
{
	private int _number;
	private float _balance;
	
	float get_balance()
	{
		return _balance;
	}
	
	void set_balance(float pNewBalance)
	{
		_balance = pNewBalance;
	}
	
	int get_number()
	{
		return _number;
	}
	
	public Account(int pAccountNumber, float pBalance)
	{
		_number = pAccountNumber;
		_balance = pBalance;
	}
}
