#include "horas.h"

Hora::Hora() : horas(), minutos(), segundos() {}
Hora::Hora(int horas, int minutos, int segundos) {
	if (horas >= 0 && horas <= 23 && minutos >= 0 && minutos <= 59 && segundos >= 0 && segundos <= 59) {
		this->horas = horas;
		this->minutos = minutos;
		this->segundos = segundos;
	}
	else {
		throw "ERROR";
	}
}

bool operator<(Hora h1, Hora h2) {
	if (h1.horas < h2.horas) {
		return true;
	}
	else if (h1.horas > h2.horas) {
		return false;
	}
	else {
		if (h1.minutos < h2.minutos) {
			return true;
		}
		else if (h1.minutos > h2.minutos) {
			return false;
		}
		else {
			if (h1.segundos < h2.segundos) {
				return true;
			}
			else {
				return false;
			}
		}
	}
}
