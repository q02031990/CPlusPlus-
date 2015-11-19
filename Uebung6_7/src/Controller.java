import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.Observable;
import java.util.Observer;

public class Controller extends Observable implements ActionListener
{
	IModel _model;
	IView _view1;
	IView _view2;	
	
	@Override
	public synchronized void addObserver(Observer arg0) {
		// TODO Auto-generated method stub
		super.addObserver(arg0);
	}
	
	public void actionPerformed(ActionEvent arg0) {
		//Modelldaten aktualisieren
		
		//Views über Veränderung informieren
		//setChanged
		this.setChanged();
		//notifyObservers
		this.notifyObservers();
	}
}
