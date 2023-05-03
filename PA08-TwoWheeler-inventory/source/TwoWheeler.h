//------------------------------------------------------------------------------
// TwoWheeler.h : base class declaration and definition
//      - base class TwoWheeler
//      - derived classes Bicylcle, Scooter
//------------------------------------------------------------------------------
#pragma once

#include <string>
#include <iostream>
using std::string;
using std::cout;

//------------------------------------------------------------------------------
// constants : identify type of two-wheel vehicle
//------------------------------------------------------------------------------
constexpr int ID_BASE = 0;
constexpr int ID_BICYCLE = 1;
constexpr int ID_SCOOTER = 2;

//------------------------------------------------------------------------------
// TwoWheeler
//------------------------------------------------------------------------------
class TwoWheeler {
private:
    int typeId;
    string mfr;
    string model;
    int fsn = 0;
    double hp = 0;

public:
    
    // constructors
    TwoWheeler() : typeId(ID_BASE) { }
    TwoWheeler(int _typeID, string _mfr, string _model) : 
        typeId(_typeID), mfr(_mfr), model(_model) { }

    // getters
    int getTypeId() const { return typeId; }
    const string& getMfr() const { return mfr; }
    const string& getModel() const { return model; }
    const string& getID()
     {
        if (typeId == 1)
        {
            return "Bike";
        }
        else
            return "Scooter";
     }
    void getSoH() 
    { 
        if (typeId == 1)
        {
            cout << "Serial #: " << fsn;
        }
        else
            cout << "HP: " << hp;
    }

    // setters
    void setTypeID(int _id) { typeId = _id; }
    void setMfr(string _mfr) { mfr = _mfr; }
    void setModel(string _model) { model = _model; }
    void setSerial(int _fsn) { fsn = _fsn; }
    void setHp(double _hp) { hp = _hp; }
};

class Bicycle : public TwoWheeler
{
public: 
    // constructor
    Bicycle() : TwoWheeler::TwoWheeler(ID_BICYCLE, "make", "model") {  }
   
    // destructor
    ~Bicycle() {};
};

class Scooter : public TwoWheeler
{
private:
public:
    // constructor
    Scooter() : TwoWheeler::TwoWheeler(ID_SCOOTER, "make", "model") { }

    // destructor
    ~Scooter() {};
};

