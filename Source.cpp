#include <iostream>
#include <string>
#include <map>
#include <set>
#include <sstream>
#include <iomanip>


using namespace std;

// Реализуйте функции и методы классов и при необходимости добавьте свои

class Date {
    int day;
    int month;
    int year;

public:
    Date(int d, int m, int y) {
        day = d;
        month = m;
        year = y;
    }
    int GetYear() const {
        return year;
    }
    int GetMonth() const {
        return month;
    }
    int GetDay() const {
        return day;
    }
};

bool operator<(const Date& lhs, const Date& rhs) {
    if (lhs.GetYear() == rhs.GetYear()) {
        if (lhs.GetMonth() == rhs.GetMonth()) {
            return lhs.GetDay() < rhs.GetDay();
        }
        else return lhs.GetMonth() < rhs.GetMonth();
    }
    else return lhs.GetYear() < rhs.GetYear();
}

class Database {
    map<Date, set<string>> ev;
public:
    void AddEvent(const Date& date, const string& event) {
        ev[date].insert(event);
    }
    
    bool DeleteEvent(const Date& date, const string& event) {
        if (ev.count(date) != 0) {
            if (ev.at(date).count(event) != 0) {
                if (ev.at(date).size() == 1) ev.erase(date);
                else ev.at(date).erase(event);            
                
                return true;
            }
        }
        return false;
    }
    
    int  DeleteDate(const Date& date) {        
        if (ev.count(date) == 0) {
            return 0;
        }
        else {
            int amount = ev.at(date).size();
            ev.erase(date);
            return amount;
        }
    }
    
    void Find(const Date& date) const {
        if (ev.count(date) != 0) {
            for (auto d : ev.at(date)) {
                cout << d << endl;
            }
        }
    }

    void Print() const {       
        for (auto e : ev) {
            for (auto i : e.second) {
                cout << setw(4) << setfill('0');
                cout << e.first.GetYear();
                cout << "-";

                cout << setw(2);
                cout << e.first.GetMonth();
                cout << "-";

                cout << setw(2);
                cout << e.first.GetDay();
                cout << " " << i;
                cout << endl;
            }
        }
    }
    
};

Date InputDate(stringstream &ss) {   
    string tempDate;
    ss >> tempDate;

    stringstream sDate(tempDate);
    int day, month, year;   //Число, месяц, год    


    sDate >> year;
    if (sDate.good() == false || sDate.peek()!='-') {
        throw runtime_error("Wrong date format: "+tempDate);
    }

    sDate.ignore(1);
    sDate >> month;
    if (sDate.good() == false || sDate.peek() != '-') {
        throw runtime_error("Wrong date format: " + tempDate);
    }   

    sDate.ignore(1);
    sDate >> day;
    if (sDate.operator bool() == false || sDate.peek()!=EOF) {
        throw runtime_error("Wrong date format: " + tempDate);
    }


    if (month < 1 || month>12) {
        throw runtime_error("Month value is invalid: " + to_string(month));
    }


    if (day < 1 || day>31) {
        throw runtime_error("Day value is invalid: " + to_string(day));
    }


    return Date(day, month, year);
}

string InputEvent(stringstream& ss) {
    ss.ignore(1);
    string event;
    ss >> event;
    if (ss.operator bool() == false) {

    }
    return event;
}

int main() {
    Database db;
    string command;

    try {
        while (getline(cin, command)) {
            //Если строка оказалась пустой, переходим к следующей строке
            if (command.size() == 0) continue;

            //Из потока удобнее преобразовывать в числа значения
            stringstream ss(command);
            string operation;   //Операция


            ss >> operation;
            if (operation == "Add") {
                Date inputDate(InputDate(ss));
                string inputEvent = InputEvent(ss);                
                db.AddEvent(inputDate, inputEvent);
            }
            else if (operation == "Del") {
                Date inputDate(InputDate(ss));
                string inputEvent = InputEvent(ss);
                if (inputEvent.size() == 0) {
                    int amount = db.DeleteDate(inputDate);
                    cout << "Deleted " << amount << " events" << endl;
                    continue;
                }
                if (db.DeleteEvent(inputDate, inputEvent)) {
                    cout << "Deleted successfully" << endl;
                }
                else {
                    cout << "Event not found" << endl;
                }
            }
            else if (operation == "Find") {
                Date inputDate(InputDate(ss));
                string inputEvent = InputEvent(ss);
                db.Find(inputDate);
            }
            else if (operation == "Print") {
                db.Print();
            }
            else {
                throw runtime_error("Unknown command: " + operation);                
            }
        }        
    }
    catch (exception& ex) {
        cout << ex.what();
    }

    

    return 0;
}