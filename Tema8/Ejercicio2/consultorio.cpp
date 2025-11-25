#pragma once

#include <string>

#include <unordered_map>
#include <map>

#include <stdexcept>

struct fecha {
	int dia, hora, minuto;

	bool operator<(const fecha& other) const {
		if (dia != other.dia) return dia < other.dia;
		if (hora != other.hora) return hora < other.hora;
		return minuto < other.minuto;
	}
};

using medico = std::string;
using paciente = std::string;

using pacientes = std::map<fecha, paciente>;

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
			throw std::invalid_argument("Medico no encontrado");
		}
		else if (!(*it).second.insert({ f, p }).second) {
			throw std::invalid_argument("Fecha ocupada");
		}
	}
	paciente siguientePaciente(medico m) {
		auto it = medicos.find(m);

		if (it == medicos.end()) {
			throw std::invalid_argument("Medico no encontrado");
		}
		else if ((*it).second.empty()) {
			throw std::invalid_argument("No hay pacientes");
		}
		else {
			return (*(*it).second.begin()).second; // Devuelvo el paciente con menor fecha
		}
	}
	void atiendeConsulta(medico m) {
		auto it = medicos.find(m);

		if (it == medicos.end()) {
			throw std::invalid_argument("Medico no encontrado");
		}
		else if ((*it).second.empty()) {
			throw std::invalid_argument("No hay pacientes");
		}
		else {
			(*it).second.erase((*it).second.begin()); // borro el paciente con menor fecha
		}
	}
	std::vector<paciente> listaPacientes(medico m, fecha fecha) {
		std::vector<paciente> v;
		int dia = fecha.dia;

		auto it = medicos.find(m);

		if (it == medicos.end()) {
			throw std::invalid_argument("Medico no encontrado");
		}
		else {
			for (auto it2 = (*it).second.begin(); (*it2).first.dia == dia; it++) {
				v.push_back((*it2).second);
			}
		}

		return v;
	}
};

