#pragma once

#include <string>

#include <unordered_map>
#include <map>
#include <vector>

#include <stdexcept>
#include <iostream>

struct fecha {
	int dia;

	struct fechaTime {
		int hora, minuto;

		
		bool operator<(const fechaTime& other) const {
			if (hora != other.hora) return hora < other.hora;
			return minuto < other.minuto;
		}
		friend std::ostream& operator<<(std::ostream& os, const fechaTime& t) {
			if (t.hora < 10) os << 0;
			os << t.hora << ":";
			if (t.minuto < 10) os << 0;
			os << t.minuto;

			return os;
		}
	} tiempo;
};

using medico = std::string;
using paciente = std::string;
using dia = int;

using pacientes = std::map<dia, std::map<fecha::fechaTime, paciente>>;

class Consultorio
{
private:
	std::unordered_map<medico, pacientes> medicos; // medico - lista de dias(lista de pacientes)
public:
	Consultorio() {}

	void nuevoMedico(medico m) {
		pacientes p;
		medicos.insert({ m, p });
	}
	void pideConsulta(paciente p, medico m, fecha f) {
		auto it = medicos.find(m);

		if (it == medicos.end()) {
			throw std::invalid_argument("Medico no existente");
		}
		else if (!(*it).second[f.dia].insert({f.tiempo, p}).second) {
			throw std::invalid_argument("Fecha ocupada");
		}
	}
	paciente siguientePaciente(medico m) {
		auto it = medicos.find(m);

		if (it == medicos.end()) {
			throw std::invalid_argument("Medico no existente");
		}
		else if ((*it).second.empty()) {
			throw std::invalid_argument("No hay pacientes");
		}
		else {
			return (*(*(*it).second.begin()).second.begin()).second; // Devuelvo el paciente con menor fecha
		}
	}
	void atiendeConsulta(medico m) {
		auto it = medicos.find(m);

		if (it == medicos.end()) {
			throw std::invalid_argument("Medico no existente");
		}
		else if ((*it).second.empty()) {
			throw std::invalid_argument("No hay pacientes");
		}
		else {
			(*(*it).second.begin()).second.erase((*(*it).second.begin()).second.begin()); // borro el paciente con menor fecha
			if ((*(*it).second.begin()).second.empty()) {
				(*it).second.erase((*it).second.begin());
			}
		}
	}
	std::vector<std::pair<fecha::fechaTime, paciente>> listaPacientes(medico m, fecha fecha) {
		std::vector<std::pair<fecha::fechaTime, paciente>> v;
		int dia = fecha.dia;

		auto it = medicos.find(m);

		if (it == medicos.end()) {
			throw std::invalid_argument("Medico no existente");
		}
		else {
			auto it2 = (*it).second.find(dia);

			if (it2 != (*it).second.end()) {
				for (auto cita : (*it).second[dia]) {
					v.push_back(cita);
				}
			}
		}
		return v;
	}
};

