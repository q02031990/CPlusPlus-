public class Model implements IModel
{
	private String _measurePlace;
	private int _current;
	private int _voltage;
	private float _power;
	
	public Model()
	{
		
	}
	
	public void CalcPower()
	{
		_power = _current * _voltage;
	}

	public String get_measurePlace() {
		return _measurePlace;
	}

	public void set_measurePlace(String _measurePlace) {
		this._measurePlace = _measurePlace;
		CalcPower();
	}

	public int get_current() {
		return _current;
	}

	public void set_current(int _current) {
		this._current = _current;
		CalcPower();
	}

	public int get_voltage() {
		return _voltage;
	}

	public void set_voltage(int _voltage) {
		this._voltage = _voltage;
		CalcPower();
	}

	public float get_power() {
		return _power;
	}
}
