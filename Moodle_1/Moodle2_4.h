#ifndef TEMPERATURA_H_
#define TEMPERATURA_H_

class Temperatura{
	private:
		float tem_kelvin;
	public:
		Temperatura(float = 1);
		void setTempKelvin(float);
		void setTempFahrenheit(float);
		void setTempCelsius(float);
		void muestra_Kelvin();
		void muestra_Fahrenheit();
		void muestra_Celsius();
};

#endif