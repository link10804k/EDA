#pragma once
class Hora
{
private:
	int horas, minutos, segundos;
public:
	Hora();
	Hora(int horas, int minutos, int segundos);
	int GetHoras();
	int GetMins();
	int GetSegs();
	friend bool operator<(Hora h1, Hora h2);
};

