#ifndef PHENOTYPE_H
#define PHENOTYPE_H

#include <cmath>
#include <vector>
#include "chphenotype.hpp"

//RECONSIDER size_t?
template<class T, size_t size, class Ttraits> class phenotype {
    T pdata[size]; //phenotype data
public:
    phenotype(const T& a); //make phenotype using a single element, copied to fill pdata
    phenotype(); //make phenotype with random data
    phenotype(const phenotype<T, size, Ttraits>& rhs);
    phenotype(const std::vector<T>& data); //make phenotype from given data
    phenotype<T, size, Ttraits>& operator=(const phenotype<T, size, Ttraits>& rhs);
    int fitness(const phenotype<T, size, Ttraits>& rhs) const;
    char& operator[](const size_t& index);
    const char& operator[](const size_t& index) const;
    void mutate(const size_t max_percent);
    phenotype<T, size, Ttraits> mix(const phenotype<T, size, Ttraits>& rhs);//TO BE IMPLEMENTED
};

template<class T, size_t size, class Ttraits> inline phenotype<T, size, Ttraits>::phenotype(const phenotype<T, size, Ttraits>& rhs) {
    operator=(rhs);
}

template<class T, size_t size, class Ttraits> phenotype<T, size, Ttraits>::phenotype(const T& a) {
    for(size_t i=0; i<size; i++) {
        pdata[i] = a;
    }
}

template<class T, size_t size, class Ttraits> phenotype<T, size, Ttraits>::phenotype() {
    for(size_t i=0; i<size; i++) {
        pdata[i] = Ttraits::random();
    }
}

//MAY NEED MORE CARE
template<class T, size_t size, class Ttraits> phenotype<T, size, Ttraits>::phenotype(const std::vector<T>& data) {
    for(int i=0; i<size; i++) {
        pdata[i] = data.at(i);
    }
}

template<class T, size_t size, class Ttraits> inline char& phenotype<T, size, Ttraits>::operator[](const size_t& index) {
    //CHECK BOUNDS
    //ADD EXCEPTION
    return pdata[index];
}

template<class T, size_t size, class Ttraits> inline const char& phenotype<T, size, Ttraits>::operator[](const size_t& index) const {
    //CHECK BOUNDS
    //ADD EXCEPTION
    return pdata[index];
}


template<class T, size_t size, class Ttraits> int phenotype<T, size, Ttraits>::fitness(const phenotype<T, size, Ttraits>& rhs) const {
    size_t fitness = 0;
    for(int i=0; i<size; i++) {
        fitness += abs(rhs[i] - pdata[i]);
    }
    return fitness;
}

template<class T, size_t size, class Ttraits> phenotype<T, size, Ttraits>& phenotype<T, size, Ttraits>::operator=(const phenotype<T, size, Ttraits>& rhs) {
    if(this==&rhs) return *this;
    for(size_t i=0; i<size; i++) {
       pdata[i] = rhs[i];
    }
    return *this;
}

template<class T, size_t size, class Ttraits> void phenotype<T, size, Ttraits>::mutate(const size_t& max_percent) {
    size_t mutate_count = floor(float(rand()%max_percent)/100*size);
    for(size_t i=0; i<mutate_count; i++) {
        phen[rand()%size] = Ttraits::random();
    }
}

#endif