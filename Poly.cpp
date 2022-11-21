#include "Poly.h"
#include <iostream>
#include <vector>
#include <math.h>

using namespace std;
Poly::Poly(){}

Poly::Poly(float number){
    power.push_back(0);
    coef.resize(coef.size()+1);
    coef[0]=number;
}

Poly::~Poly(){
    coef.clear();
    power.clear();
}

Poly &Poly::operator=(Poly const &other){
    if(this != &other){
        coef.clear();
        power.clear();
        coef.resize(other.coef.size());
        power.resize(other.power.size());
        for( int i = 0; i < (int)other.power.size(); i++ ){
            coef[i] = other.coef[i];
            power[i] = other.power[i];
        }
    }
    return *this;
}

Poly::Poly(Poly const &other){
    coef.resize(other.coef.size());
    power.resize(other.power.size());
    for( int i = 0; i < (int)other.power.size(); i++ ){
        coef[i] = other.coef[i];
        power[i] = other.power[i];
    }
}

ostream &operator<<(ostream &os, Poly const &poly){
    int i = 0;
    os<<endl;
    for(; i<(int)poly.power.size() - 1; i++){
        if(poly.coef[i] == 0){
        }
        else if(poly.power[i] != 0){
            os<<poly.coef[i]<<"x^"<<poly.power[i]<<" + "; 
        }
        else{
            os<<poly.coef[i]<< " + "; 
        }
    }
    if(poly.power[i] != 0){
        os<<poly.coef[i]<<"x^"<<poly.power[i]; 
    }
    else{
        os<<poly.coef[i]; 
    }
    return os;
}

float &Poly::operator[](unsigned int pos){
    power.push_back(pos);
    coef.resize(coef.size()+1);
    sortPowers(); 
    return coef[findIndex(pos)];
}

float Poly::operator[](unsigned int pos) const{
    return coef[findIndex(pos)];
}

int Poly::findIndex(float number) const{
    for(int i = 0; i < (int)power.size(); i++){
        if(power[i] == number){
            return i;
        }
    }
    return 0;
}

Poly& Poly::sortPowers(){
    for(int i = 0; i < (int)power.size(); i++){
        for(int j = 0; j < (int)power.size() - 1; j++){
            if(power[j] < power[j + 1]){
                swap(power[j], power[j+1]);
                swap(coef[j], coef[j+1]);
            }
        }
    }
    return *this;
}

Poly operator+(Poly first, Poly second){
    int firstsize = first.power.size();
    
    for(int i = 0; i < (int)second.power.size(); i++){
        first.power.push_back(second.power[i]);
        first.coef.push_back(second.coef[i]);
    }

    for(int i = 0; i < firstsize; i++){
        for(int j = firstsize; j < (int)first.power.size(); j++){
            if(first.power[i] == first.power[j]){
                first.coef[i] += first.coef[j];
                first.coef.erase(first.coef.begin()+j);
                first.power.erase(first.power.begin()+j);
            }
        }
    }

    first.sortPowers();
    return first;
}

Poly operator-(Poly first, Poly second){
    int firstsize = first.power.size();
    
    for(int i = 0; i < (int)second.power.size(); i++){
        first.power.push_back(second.power[i]);
        first.coef.push_back(-1 * second.coef[i]);
    }

    for(int i = 0; i < firstsize; i++){
        for(int j = firstsize; j < (int)first.power.size(); j++){
            if(first.power[i] == first.power[j]){
                first.coef[i] += first.coef[j];
                first.coef.erase(first.coef.begin()+j);
                first.power.erase(first.power.begin()+j);
            }
        }
    }

    first.sortPowers();
    return first;
}

Poly operator*(Poly first, Poly second){
    Poly newPoly;
    newPoly.power.resize(first.power.size()+second.power.size());
    newPoly.coef.resize(first.coef.size()+second.coef.size());
    for (int i = 0; i < (int)first.power.size(); i++) {
        for (int j = 0; j < (int)second.power.size(); j++) {
            int pow = second.power[j] + first.power[i];
            newPoly.power[second.power[j] + first.power[i]-1] = pow;
            newPoly.coef[newPoly.findIndex(pow)] += second.coef[j] * first.coef[i];
        } 
    }
    newPoly.sortPowers();
    return newPoly;
}

Poly operator-(Poly poly){
    for (int i = 0; i < (int)poly.coef.size(); i++) {
        poly.coef[i] *= (-1);
    }
    return poly;
}

float Poly::operator()(const float& point) const
{
	float answer = 0;
	if (coef.size() == 0)
		return answer;
	else {
		answer = coef[coef.size() - 1];
		for (int i = coef.size()- 2; i >= 0; i--) {
			answer = answer + pow(point, power[i]) * coef[i];
		}
	}
	return answer;
}