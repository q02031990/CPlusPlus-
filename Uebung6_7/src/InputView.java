import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.*;

public class InputView extends JComponent implements IView
{
	GridLayout _gridLayout;
	
	JLabel _uxDisplayMeasurePlaceCaption = new JLabel("Measure Place");
	JScrollPane _uxInputMeasurePlaceScroll;
	
	JList<String> _uxInputMeasurePlace;
	
	JLabel _uxDisplayCurrentCaption = new JLabel("Current");
	JTextField _uxInputCurrent = new JTextField();
	
	JLabel _uxDisplayVoltageCaption = new JLabel("Voltage");
	JPanel _uxContainerVoltage = new JPanel();
	ButtonGroup _voltageButtonGroup = new ButtonGroup();
	JRadioButton _uxSelectionVoltage50v = new JRadioButton("50V");
	JRadioButton _uxSelectionVoltage100v = new JRadioButton("100V");
	JRadioButton _uxSelectionVoltage150v = new JRadioButton("150V");
	
	JLabel _uxDisplayPowerCaption = new JLabel("Power");
	JLabel _uxDisplayPowerValue = new JLabel("7000.0");
	
	JButton _uxSubmitCalculation = new JButton("Calculate");
	
	public InputView()
	{
		_gridLayout = new GridLayout();//(0,3,10,10);
		
		_uxInputMeasurePlaceScroll = new JScrollPane();
		String s[]={"Vorwärmen","Ofen1","Ofen2","Brennen"};
		_uxInputMeasurePlace = new JList<String>(s);
		
		_gridLayout.setColumns(2);
		_gridLayout.setRows(0);
		_gridLayout.setHgap(20);
		_gridLayout.setVgap(20);
		
		//_uxInputMeasurePlace.setSize(100,50);
		//_uxInputMeasurePlace.setLocation(50,50);
		
		_uxInputMeasurePlaceScroll.setViewportView(_uxInputMeasurePlace);
		
		//_uxDisplayMeasurePlaceCaption.setSize(100,20);
		
		this.add(_uxDisplayMeasurePlaceCaption);
		this.add(_uxInputMeasurePlaceScroll);
		
		this.add(_uxDisplayCurrentCaption);
		this.add(_uxInputCurrent);
		
		this.add(_uxDisplayVoltageCaption);
		_voltageButtonGroup.add(_uxSelectionVoltage50v);
		_voltageButtonGroup.add(_uxSelectionVoltage100v);
		_voltageButtonGroup.add(_uxSelectionVoltage150v);
		_uxContainerVoltage.add(_uxSelectionVoltage50v);
		_uxContainerVoltage.add(_uxSelectionVoltage100v);
		_uxContainerVoltage.add(_uxSelectionVoltage150v);
		
		this.add(_uxContainerVoltage);
		
		this.add(_uxDisplayPowerCaption);
		this.add(_uxDisplayPowerValue);
		
		_uxSubmitCalculation.addActionListener(new ActionListener()
		{
			public void actionPerformed(ActionEvent arg0)
			{
				double voltage = 0;
				
				if(_uxSelectionVoltage50v.isSelected())
					voltage = 50.0;
				else if(_uxSelectionVoltage100v.isSelected())
					voltage = 100.0;
				else if(_uxSelectionVoltage100v.isSelected())
					voltage = 150.0;
				
				String s = String.format("%f W\n", voltage * Double.parseDouble(_uxInputCurrent.getText()));
				
				_uxDisplayPowerValue.setText(s);
			}
		});
		
		this.add(_uxSubmitCalculation);
		
		this.setLayout(_gridLayout);
	}
}