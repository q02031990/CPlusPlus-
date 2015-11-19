public class Transaction
{
	private int _accountNumber;
	private float _balanceChange;
	
	public Transaction(int pAccountNumber, float pBalanceChange)
	{
		_accountNumber = pAccountNumber;
		_balanceChange = pBalanceChange;
	}

	public int get_accountNumber() {
		return _accountNumber;
	}

	public float get_balanceChange() {
		return _balanceChange;
	}
}
