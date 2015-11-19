import java.awt.GridLayout;

import javax.swing.*;

public class ResultView extends JComponent implements IView
{
	GridLayout _gridLayout = new GridLayout(0,2);
	
	JLabel _uxDisplayMeasurePlaceCaption = new JLabel("Measure Place");
	JLabel _uxDisplayMeasurePlaceValue = new JLabel("-");
	
	JLabel _uxDisplayCurrentCaption = new JLabel("Current");
	JLabel _uxDisplayCurrentValue = new JLabel("-");
	
	JLabel _uxDisplayVoltageCaption = new JLabel("Voltage");
	JLabel _uxDisplayVoltageValue = new JLabel("-");
	
	JLabel _uxDisplayPowerCaption = new JLabel("Power");
	JLabel _uxDisplayPowerValue = new JLabel("-");
	
	JButton _uxSubmitReset = new JButton("Reset");
	
	public ResultView()
	{		
		this.add(_uxDisplayMeasurePlaceCaption);
		this.add(_uxDisplayMeasurePlaceValue);
		
		this.add(_uxDisplayCurrentCaption);
		this.add(_uxDisplayCurrentValue);
		
		this.add(_uxDisplayVoltageCaption);
		this.add(_uxDisplayVoltageValue);
		
		this.add(_uxDisplayPowerCaption);
		this.add(_uxDisplayPowerValue);
		
		this.add(_uxSubmitReset);
		
		this.setLayout(_gridLayout);
	}
}