//------------------------------------------------------------------------------
// inventory_app.cpp : base class declaration and definition
//------------------------------------------------------------------------------
#include "TwoWheeler.h"

#include <iostream>
#include <string>
#include <sstream>
#include <exception>
#include <fstream>
#include <algorithm>
#include <list>

using std::cout;
using std::string;
using std::exception;

// exception for when file fails to open
class FileOpenException : public exception
{
public:
    const char* what() { return "File could not be opened! Exiting application..."; }
};

// exception for invalid amount of data to create an instance of a TWoWheeler
class FileFormatException : public exception
{
public:
    void what() {
        cout << " <- Unable to read inventory item in this line! Continuing application...\n";
    }
};

// function prototypes
void testFileOpening(std::ifstream& _inFile);
void testFileFormat(int _tracker, std::ifstream& _inFile);
std::list<TwoWheeler> fillList();
void displayList(std::list<TwoWheeler> list);
void countItems(std::list<TwoWheeler> list);

//------------------------------------------------------------------------------
// inventory_app.cpp : base class declaration and definition
//------------------------------------------------------------------------------
int main() {
    
    
    // Opens file "inventory.txt" to get input from
    std::ifstream inFile("inventory.txt");

    // Tests if file was opened successfully
    try
    {
        testFileOpening(inFile);
    }
    catch (FileOpenException& f) {
        cout << f.what();
        return 0;
    }
    std::list<TwoWheeler> list = fillList();
   
    displayList(list);
    countItems(list);
}

//tests if file opens, returns exception if otherwise
void testFileOpening(std::ifstream& _inFile)
{
    if (_inFile.is_open()) {
        return;
    }
    else 
         throw FileOpenException();
}

//tests if line in file has enough data to make an instance of either bicycle or scooter, returns exception otherwise
void testFileFormat(int _tracker, std::ifstream& _inFile)
{
    _inFile.clear();
    _inFile.seekg(0, std::ios::beg);
   
    string instance;

    for (int i = 1; i <= _tracker; i++)
    {
        getline(_inFile, instance, '\n');
    }
    
    _inFile.clear();
    _inFile.seekg(0, std::ios::beg);
    
    std::stringstream s(instance);
    
    int count = 0;
    while (s >> instance)
        count++;
    
    if (count == 4)
    {
        return;
    }
    else 
        throw FileFormatException();
} 

// fills list with instances of two wheeler
std::list<TwoWheeler> fillList()
{
    // list being filled
    std::list<TwoWheeler> list;

    // holds data to make up eiher bike or scooter instance
    string line;
    string holder;
    string type;
    string mfr;
    string model;
    string SoH;
    int _serial;
    double _hp;
    
    // Tracks which line of the file is being used
    int tracker = 1;
    
    std::ifstream _inFile("inventory.txt");
   
    // goes through file 
    while (!_inFile.eof())
    {
        // tests each line in file to make sure has enough data for an instance of TwoWheeler
        bool valid;
        try
        {
            testFileFormat(tracker, _inFile);
            valid = true;
        }
        catch (FileFormatException& f)
        {
            valid = false;
            cout << tracker;
            f.what();
        }

        // if the line has enough data continue
        if (valid)
        {
            // tracks what "word" is being used and puts it in appropriate var
            int tracks = 1;
           
            for (int i = 1; i <= tracker; i++)
            {
                getline(_inFile, line, '\n');
            }
            
            std::istringstream s(line);
            while (s >> holder)
            {
                switch (tracks)
                {
                case 1:
                    type = holder;
                    break;
                case 2:
                    mfr = holder;
                    break;
                case 3:
                    model = holder;
                    break;
                case 4:
                    SoH = holder;
                    break;
                }
                tracks++;
            }
           
            tracks = 1;

            // makes appropriate item based on variables
            if (stoi(type) == ID_BICYCLE)
            {
                Bicycle bike;

                _serial = stoi(SoH);

                bike.setMfr(mfr);
                bike.setModel(model);
                bike.setSerial(_serial);
                list.push_back(bike);
                tracker++;
            }
            else
            {
                Scooter scooter;

                _hp = stod(SoH);

                scooter.setMfr(mfr);
                scooter.setModel(model);
                scooter.setHp(_hp);
                list.push_back(scooter);
                tracker++;
            }
            
        }
        else
        {
            tracker++;
        }     
    }
    return list;
}

void myfunction(TwoWheeler& tw)
{
    cout << tw.getID() << " " << tw.getMfr() << " " << tw.getModel() << " ";
    tw.getSoH();
    cout << '\n';
}

void displayList(std::list<TwoWheeler> list)
{
    cout << "My inventory contains:" << std::endl;

    std::for_each(list.begin(), list.end(), myfunction);
    
    return;
}

// counts number of bikes and scooters
void countItems(std::list<TwoWheeler> list)
{
    int holder = 0;
    int countBikes = 0;
    int countScooters = 0;

    for (auto it = list.begin(); it != list.end(); it++)
    {
        holder = it->getTypeId();

        if (holder == ID_BICYCLE)
        {
            countBikes++;
        }
        else
            countScooters++;
    }
    cout << "\nMy inventory has " << countBikes << " bikes and " << countScooters << " scooters.";
};