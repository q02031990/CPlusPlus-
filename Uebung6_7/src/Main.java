import javax.swing.JFrame;

public class Main
{
	public static void main(String[] args)
	{
		JFrame frame = new JFrame();	
		frame.setSize(800, 600);
		
		InputView view = new InputView();
		
		frame.getContentPane().add(view);
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.setVisible(true);
	}
}
