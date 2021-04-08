#ifndef SUBJECT_H
#define SUBJECT_H
#include <vector>

template <typename InfoType, typename StateType>
class Observer;

template <typename InfoType, typename StateType>
class Subject {
    std::vector<Observer<InfoType, StateType> *> observers;

public:
    void attach(Observer<InfoType, StateType> *o);
    void notifyObservers();
};

template <typename InfoType, typename StateType>
void Subject<InfoType, StateType>::attach(Observer<InfoType, StateType> *o) {
    observers.emplace_back(o);
}

template <typename InfoType, typename StateType>
void Subject<InfoType, StateType>::notifyObservers() {
    for (auto &ob : observers)
        ob->notify(*this);
}

#endif
