#include <iostream>
#include<string>
#include<map>
#include<vector>
#include<algorithm>
#include <sstream>
#include<stdexcept>
#include<iomanip>
#include<set>

using namespace std;

class Date {
public:
    int GetYear() const;
    int GetMonth() const;
    int GetDay() const;
    void AddYear(int a);
    void AddMonth(int a);
    void AddDay(int a);

    friend istream& operator>>(istream& str, Date& val);  
    Date& operator=(const string& rhs);
    
private:
    int Year;
    int Month;
    int Day;
};

bool operator==(const Date& lhs, const Date& rhs);
bool operator<(const Date& lhs, const Date& rhs);

class Database {
public:
    
    void AddEvent(const Date& date, const string& event);
    bool DeleteEvent(const Date& date, const string& event);
    int  DeleteDate(const Date& date);
    void Find(const Date& date) const;
    void Print() const;

private:
    map<Date,set<string>> Ev;
    
};
bool PrErrorDate(const string& a) {
    stringstream str(a);
    int t1, t2, t3;
    char e1, e2;
   
    if (!str.eof()) {
        str >> t1 >> e1 >> t2 >> e2 >> t3;
        if ((!str) || (e1 != '-') || (e2 != '-') || (!str.eof())) {
            cout << "Wrong date format: " + a << endl;
            return false;
        }
        else if ((t2 <= 0) || (t2 >= 13)) {
            string error = "Month value is invalid: " + to_string(t2);
            cout << error << endl;
            return false;
        }
        else if ((t3 <= 0) || (t3 >= 32)) {
            string error = "Day value is invalid: " + to_string(t3);
            cout << error << endl;
            return false;
        }
        else return true;
    }
    return false;

}



int main() {
    Database db;

    string command;
    while (getline(cin, command)) {
        stringstream ss(command);
        string com;
        ss >> com;
        
         if (com == "Add"){
             string a;
             Date b;
             ss >> a;
             if (PrErrorDate(a)) {
                 b = a;
                 string c;
                 ss >> c;

                 db.AddEvent(b, c);
             }
         }
         else if (com == "Del") {
             string a;
             Date b;
             ss >> a;
             if (PrErrorDate(a)) {
                 b = a;
                 string c;
                 ss >> c;

                 if (c == "")
                     db.DeleteDate(b);
                 else
                     db.DeleteEvent(b, c);
             }
         }
         else if (com == "Find") {
             string a;
             Date b;
             ss >> a;
             if (PrErrorDate(a)) {
                 b = a;
                 db.Find(b);
             }
         }
         else if (com == "Print") {
             db.Print();
         }
         else if (com == ""){
             
         }
         else {
             cout << "Unknown command: " << com << endl;
         }
        
    }

    return 0;
}
/*Функционал класса дат*/
int Date::GetYear() const {
    return Year;
}
int Date::GetMonth() const {
    return Month;
}
int Date::GetDay() const {
    return Day;
}
void Date::AddYear(int a) {
    Year = a;
}
void Date::AddMonth(int a) {
    Month = a;
}
void Date::AddDay(int a) {
    Day = a;
}
 istream& operator>>(istream& str, Date& val) {
    if (str) {
        int a, b, c;
        str >> a;
        str.ignore(1);
        str >> b;
        str.ignore(1);
        str >> c;
        val.Day = c;
        val.Month = b;
        val.Year = a;
    }
    return str;
}

Date& Date::operator=(const string& rhs) {

    stringstream str(rhs);
    str >> *this;
    return *this;
}

/*Дополнительные операторы класса дат*/
bool operator==(const Date& lhs, const Date& rhs) {
    if ((lhs.GetYear() == rhs.GetYear()) && (lhs.GetMonth() == rhs.GetMonth()) && (lhs.GetDay() == rhs.GetDay()))
        return true;
}

bool operator<(const Date& lhs, const Date& rhs) {

    if (lhs.GetYear() != rhs.GetYear()) {
        return lhs.GetYear() < rhs.GetYear();
    }
    if (lhs.GetMonth() != rhs.GetMonth()) {
        return lhs.GetMonth() < rhs.GetMonth();
    }
    if (lhs.GetDay() != rhs.GetDay()) {
        return lhs.GetDay() < rhs.GetDay();
    }
    return false;
}

/*Функционал базы данных*/
void Database::AddEvent(const Date& date, const string& event) {
    Ev[date];
    Ev.at(date).insert(event);
}

bool Database::DeleteEvent(const Date& date, const string& event) {
   Ev[date];
   if (Ev.at(date).count(event)){
            cout << "Deleted successfully" << endl;
            Ev.at(date).erase(event);
            return true;
    }
   else {
       cout << "Event not found" << endl;
       return false;
   }
}
int  Database::DeleteDate(const Date& date) {
    int N;
    Ev[date];
    N = Ev.at(date).size();
    Ev.erase(date);
    cout << "Deleted " << N << " events" << endl;
    return N;
}

void Database::Find(const Date& date) const {
    if (Ev.count(date) != 0)
        for (auto i = Ev.at(date).begin(); i!= Ev.at(date).end(); i++) {
            cout << *i << endl;
        }

}

void Database::Print() const {
    
    for (auto iter: Ev) {
        for (string i: iter.second) {
            cout << setfill('0');
            cout << setw(4) << iter.first.GetYear() << '-' << setw(2) <<
                iter.first.GetMonth() << '-'
                << setw(2) << iter.first.GetDay() << ' ';
            cout << i;
            cout << endl;
        }
    }
}