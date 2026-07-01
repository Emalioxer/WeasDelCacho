#include "Jugador.h"
#include <iostream>
#include <vector>
#include <utility>

class JugadorEmalioxer : public Jugador {
private:
    std::string nombreEstudiante;

public:
    JugadorEmalioxer(){
        nombreEstudiante = "Emilio Ormazabal";
    }

    std::string getNombreEstudiante() const{
        return nombreEstudiante;
    }

    JugadorEmalioxer(std::string nom = "Emalioxer") : Jugador(nom) {}

    int jugar(const std::map<std::string, Marcador>& /*marcadores*/,
              const std::vector<Actuacion>& actuacionesPosibles,
              const std::vector<int>& dados /*dados*/,
              const Anotacion& /*resultadoPrevio*/) override {
        
        // Estrategia heurística básica:
        // 1. Si existe una victoria inmediata ("dormida"), tomarla inmediatamente.
        for (size_t i = 0; i < actuacionesPosibles.size(); ++i) {
            if (actuacionesPosibles[i].accion == "dormida") {
                //std::cout << nombre << " declara DORMIDA y gana!" << std::endl;
                return i;
            }
        }

        //5. otra shit que revisa si hay weas grandes de mano :P. creo q asín no funciona esta wea aasdasjdkaf. sí ,sí funciona asín
        for(size_t i=0; i<actuacionesPosibles.size(); i++){
            if(actuacionesPosibles[i].accion=="anotar" &&
               actuacionesPosibles[i].anotacion.juego=="full"){
                return i;
               }
            else if(actuacionesPosibles[i].accion =="anotar" &&
                    actuacionesPosibles[i].anotacion.juego=="poker"){
                    return i;
               }
            else if(actuacionesPosibles[i].accion == "anotar" &&
                    actuacionesPosibles[i].anotacion.juego=="escalera"){
                    return i;
               }
            /*else if(actuacionesPosibles[i].accion == "lanzar"){
                return 30;
            }*/
        }


        std::vector<std::pair<int, int>> DEDOS;
        int c1=0, c2=0, c3=0, c4=0, c5=0, c6=0;
        //El Creador de Pibes:
        for(int i=0; i<5; i++){
            DEDOS.emplace_back(i, dados[i]);
            if(dados[i]==1) {c1++;}
            else if(dados[i]==2) {++c2;}
            else if(dados[i]==3) {c3++;}
            else if(dados[i]==4) {++c4;}
            else if(dados[i]==5) {++c5;}
            else if(dados[i]==6) {c6++;}
            //std::cout << DEDOS[i].first << ", " << DEDOS[i].second << std::endl;
        }
        std::vector<std::pair<int ,int>> weas;
        for(int i=0; i<5; i++){
            if(dados[i]==1) weas.emplace_back(c1, dados[i]);
            else if(dados[i]==2) weas.emplace_back(c2, dados[i]);
            else if(dados[i]==3) weas.emplace_back(c3, dados[i]);
            else if(dados[i]==4) weas.emplace_back(c4, dados[i]);
            else if(dados[i]==5) weas.emplace_back(c5, dados[i]);
            else if(dados[i]==6) weas.emplace_back(c6, dados[i]);
            //std::cout << weas[i].first << ", " << weas[i].second << std::endl;
        }

        //6. Lanzar si no pasa nada
        std::vector<int> aux;
        for(int j=0; j<5; j++){
            if(weas[j].first!=3) aux.push_back(DEDOS[j].first);
        }
        for(size_t i=0; i<actuacionesPosibles.size(); i++){
            if(actuacionesPosibles[i].accion == "lanzar" &&
               actuacionesPosibles[i].indiceDados == aux){
                return i;    
            }
        }

        //7. Revisa de nuevo las jugadas bacanes
        for(size_t i=0; i<actuacionesPosibles.size(); i++){
            if(actuacionesPosibles[i].accion == "anotar" &&
               actuacionesPosibles[i].anotacion.juego == "grande"){
                return i;
                }
            else if(actuacionesPosibles[i].accion == "anotar" &&
               actuacionesPosibles[i].anotacion.juego == "grande2"){
                return i;
                }
            else if(actuacionesPosibles[i].accion == "anotar" &&
               actuacionesPosibles[i].anotacion.juego == "full"){
                return i;
               }
            else if(actuacionesPosibles[i].accion == "anotar" &&
                    actuacionesPosibles[i].anotacion.juego == "poker"){
                    return i;
                }
        }

        //8. Y si todo falla
        int max = 0;
        for(size_t i=0; i<actuacionesPosibles.size(); i++){
            if(actuacionesPosibles[i].anotacion.puntos > max){
                max = actuacionesPosibles[i].anotacion.puntos;
            }
        }
        //std::cout << max<< "<-- el puntaje máximo es ese" << std::endl;

        for(size_t i=0; i<actuacionesPosibles.size(); i++){
            if(max>0 && actuacionesPosibles[i].accion == "anotar" &&
                actuacionesPosibles[i].anotacion.puntos == max){
                    return i;
                }
            else{ //aronou, dat sim kainda lol, ya'nou
                if(actuacionesPosibles[i].accion == "sobre"){
                    return i;
                }
            }
        }

        // 2. Si hay una opción para anotar una jugada de alto valor (>= 30 pts) de manera directa
        /*for (size_t i = 0; i < actuacionesPosibles.size(); ++i) {
            if (actuacionesPosibles[i].accion == "anotar" && 
                actuacionesPosibles[i].anotacion.puntos >= 15) {
                return i;
            }
        }*/

        // 4. Retorno de emergencia (último elemento disponible)
        return actuacionesPosibles.size() - 1;
    }
};