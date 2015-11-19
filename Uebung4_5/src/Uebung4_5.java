import java.io.IOException;
import java.util.ArrayList;
import java.util.concurrent.ArrayBlockingQueue;

public class Uebung4_5
{
	public static Bank UebungBank = new Bank();
	
	public static void main(String[] args) throws IOException
	{
		//Übung Teil 1
		/*
		UebungBank.createAccount(0);
		
		Grandchild gA = new Grandchild(UebungBank, "A", 200, 0);
		Grandchild gB = new Grandchild(UebungBank, "B", 400, 0);
		Grandchild gC = new Grandchild(UebungBank, "C", 800, 0);
		
		gA.start();
		gB.start();
		gC.start();
		
		ArrayList<Grandchild> childs = new ArrayList<Grandchild>();
		childs.add(gA);
		childs.add(gB);
		childs.add(gC);
		
		Grandfather grandfather = new Grandfather(UebungBank, 0, childs);
		grandfather.SendMoney();
		//*/
		
		//Übung Teil 2
		Bank2 bank = new Bank2(new ArrayBlockingQueue<Transaction>(10000));
		bank.AddAccount(new Account(123, 50.0f));
		bank.AddAccount(new Account(246, 50.0f));
		bank.AddAccount(new Account(369, 50.0f));
		
		Thread thread = new Thread(bank);
		thread.start();
		
		for(int i = 0; i<10000; i++)
		{
			if(i%2 == 0)
				bank.AddTransaction(new Transaction(123, 1f));
			else if(i%2 == 1)
				bank.AddTransaction(new Transaction(246, 1f));
		}
		
		thread.interrupt();
	}
}
