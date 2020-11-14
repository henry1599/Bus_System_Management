#include <sstream>
#include <vector>
#include <algorithm>
#include <string>
#include <iostream>
#include <iomanip>
#include <assert.h>
#include <type_traits>
#include <map>
using namespace std;
#define MAX_INT 1e5
// END: STUDENT ANSWER



int N; // số chuyến tối đa của mỗi tuyến trong suốt quá trình
/* Note: 
    * You change anything in this answer 
    * such that your implementation must have BusSystem class with method query.
    * This query method should return the output of each instruction
*/

class Bus
{
private:
    string LP;      // License plate
    string ID;       // Rout ID
    int CASE;       // = 0 : Outgoing bus
                    // = 1 : Return bus
    int TIME_A;       // Time start
    int TIME_B;       // Time stop
    int TIME;         // current considerable time
    bool is_on_way; // Check if Bus is on way or not
    friend class BusSystem;

public:
    Bus()
    {
        this->ID = "";
        this->LP = "";
        this->CASE = 0;
        this->TIME_A = 0;
        this->TIME_B = 0;
        this->TIME = 0;
        this->is_on_way = 0;
    }
    Bus(string _bus_CODE, string _bus_LP, int _bus_CASE, int _bus_TIME_A, int _bus_TIME_B, int _bus_TIME, bool _bus_is_on_way)
    {
        this->ID = _bus_CODE;
        this->LP = _bus_LP;
        this->CASE = _bus_CASE;
        this->TIME_A = _bus_TIME_A;
        this->TIME_B = _bus_TIME_B;
        this->TIME = _bus_TIME;
        this->is_on_way = _bus_is_on_way;
    }
    friend ostream &operator<<(ostream &os, const Bus &data)
    {
        os << data.ID << " | " << data.LP << " | " << data.CASE << " | " << data.TIME_A << " | "  << data.TIME_B << " | " << data.TIME << " | " << data.is_on_way;
        return os;
    }
    Bus &operator=(const Bus &data)
    {
        this->ID = data.ID;
        this->CASE = data.CASE;
        this->is_on_way = data.is_on_way;
        this->LP = data.LP;
        this->TIME_A = data.TIME_A;
        this->TIME_B = data.TIME_B;
        this->TIME = data.TIME;
        return *this;
    }
    bool operator!=(const Bus &data)
    {
        return (this->ID != data.ID) ||
               (this->CASE != data.CASE) ||
               (this->LP != data.LP) ||
               (this->is_on_way != data.is_on_way) ||
               (this->TIME_A != data.TIME_A)  ||
               (this->TIME_B != data.TIME_B) ||
               (this->TIME != data.TIME);
    }
    bool operator==(const Bus &data)
    {
        return (this->ID == data.ID) &&
               (this->CASE == data.CASE) &&
               (this->LP == data.LP) &&
               (this->is_on_way == data.is_on_way) &&
               (this->TIME_A == data.TIME_A) &&
               (this->TIME_B == data.TIME_B) &&
               (this->TIME == data.TIME);
    }
};

class BusSystem
{
private:
    map<string , vector<Bus>> System;

public:
    BusSystem(){}
    ~BusSystem(){}
     
    string query(string instruction);
    vector<string> Split_Command(string instructor);
    bool is_valid(vector<string> result, string instruction);
    void Initial_Setup(int _N);
    int INS(string _ID, string _LP, int _time_A, int _time_B, int _CASE = 0);
    int DEL(string _ID, int _time_A, int _time_B);
    int CS(string _ID, int _time, int _CASE);
    int CE(string _ID, int _time, int _CASE);
    string GS(string _ID, int _time, int _CASE);
    string GE(string _ID, int _time, int _CASE);
    void print();
    void input();
};

vector<string> BusSystem::Split_Command(string instructor)
{
    string delimiter = " ";
    string post_instructor = instructor;
    vector<string> Storage;

    size_t pos = 0;
    string token;
    while ((pos = instructor.find(delimiter)) != string::npos)
    {
        token = instructor.substr(0, pos);
        Storage.push_back(token);
        instructor.erase(0, pos + delimiter.length());
    }
    Storage.push_back(instructor);
    return Storage;
}

int BusSystem::INS(string _ID, string _LP, int _time_A, int _time_B, int _CASE)
{
    if (_time_A == -1 || _time_B == -1)
        return -1;
    // Create new Iterator name after my name :)))
    // To find whether the "_ID" is in the current System or not
    map<string , vector<Bus>>::iterator Henry;
    // Find the "_ID" in the System
    // If found : Henry will point to that "_ID" in the System
    // Otherwise, Henry points to the end() of the System
    Henry = this->System.find(_ID);
    if (Henry->second.size() == N)
        return -1;
    if (Henry == this->System.end()) // Not found the ID
    {
        // Create new bus to insert into map
        Bus myBus = Bus(_ID, _LP, _CASE, _time_A, _time_B, 0, false);
        // Create new vector to insert into map
        vector<Bus> newVec;
        // insert new ID of the routes as well as a new empty vector
        this->System.insert({_ID,newVec});
        Henry = this->System.find(_ID);
        // Push_back new Bus into the vector at the ID which has been inserted
        Henry->second.push_back(myBus);
        // Return the current buses in the rout ID
        // In this case it is going to be 1, apparently
        return 1;
    }
    else // Found the ID
    {
        // Create new bus to insert into map
        Bus myBus = Bus(_ID, _LP, _CASE, _time_A, _time_B, 0, false);
        // Check if the new bus has already been existed in the System or not
        bool isExist = false;
        // Check if the new bus's outgoing time is valid in case it has already existed in the System
        bool is_Valid_Same_LP = false;
        bool is_Valid_Same_ID = true;
        // Checking time !!!
        for (vector<Bus>::iterator it_bus = Henry->second.begin(); it_bus != Henry->second.end(); it_bus++)
        {
            if (it_bus->LP == _LP) // if new bus has already been existed
            {
                isExist = true;
                int time_end_prev = it_bus->TIME_B;
                int time_start_next = _time_A;
                // Debug message
                // cout << "PREV : " << time_end_prev << " | NEXT : " << time_start_next << endl;
                // end message
                if (time_start_next > time_end_prev)
                {
                    is_Valid_Same_LP = true;
                    break;
                }
            }
            if (it_bus->TIME_A == _time_A && it_bus->CASE == _CASE)
            {
                is_Valid_Same_ID = false;
            }
            
        }
        if (!isExist) // if new bus not Exist : push that in System
        { 
            if (is_Valid_Same_ID)
            {
                Henry->second.push_back(myBus);
            }
            else
            {
                // Debug message
                // cout << "#...Cannot push ! (the same start time)   " << endl;
                // end message
                return -1;
            }
        }
        else
        {
            if (is_Valid_Same_LP)
            {
                Henry->second.push_back(myBus);
            }
            else
            {
                // Debug message
                // cout << "#...Push ! (valid time)   " << endl;
                // End message
                return -1;
            }
        }
        // Return the current buses in the rout ID
        // In this case it will return the current Bus in the vector rout which has the key "_ID"
        // Henry is pointing to "ID"
        return Henry->second.size();
    }
    
}

int BusSystem::DEL(string _ID, int _time_A, int _time_B)
{
    map<string, vector<Bus>>::iterator Henry = this->System.find(_ID);
    if (_time_B < _time_A && _time_B != -1 && _time_A != -1)
        return 0;
    if (Henry == this->System.end()) // Not found the route
        return 0;
    else // Found the route 
    {
        if (_time_A == -1 && _time_B == -1)
        {
            int result = Henry->second.size();
            Henry->second.clear();
            return result;
        }
        else
        {
            int count_delete_bus = 0;
            for (vector<Bus>::iterator it_bus = Henry->second.begin(); it_bus != Henry->second.end(); it_bus++)
            {
                if (_time_A != -1 && _time_B != -1)
                {
                    if (_time_A <= it_bus->TIME_A && it_bus->TIME_A <= _time_B)
                    {
                        Henry->second.erase(it_bus);
                        it_bus--;
                        count_delete_bus++;
                    }
                }
                else if (_time_A != -1 && _time_B == -1)
                {
                    if (_time_A == it_bus->TIME_A)
                    {
                        Henry->second.erase(it_bus);
                        it_bus--;
                        count_delete_bus++;
                    }
                }
            }
            return count_delete_bus;
        }
    }
}

int BusSystem::CS(string _ID, int _time, int _CASE)
{
    map<string, vector<Bus>>::iterator Henry = this->System.find(_ID);
    if (Henry == this->System.end())
        return 0;
    else
    {
        int count_active_bus = 0;
        for (vector<Bus>::iterator it_bus = Henry->second.begin(); it_bus != Henry->second.end(); it_bus++)
        {
            if (_CASE == -1) // bidirection
            {
                count_active_bus += (it_bus->TIME_A < _time && _time < it_bus->TIME_B) ? 1 : 0;
            }
            else // one-way direction
            {
                count_active_bus += (it_bus->TIME_A < _time && _time < it_bus->TIME_B && it_bus->CASE == _CASE) ? 1 : 0;
            }
        }
        return count_active_bus;
    }
}

int BusSystem::CE(string _ID, int _time, int _CASE)
{
    map<string, vector<Bus>>::iterator Henry = this->System.find(_ID);
    if (Henry == this->System.end())
        return -1;
    else
    {
        int count_number_bus_not_start = 0;
        for (vector<Bus>::iterator it_bus = Henry->second.begin(); it_bus != Henry->second.end(); it_bus++)
        {
            if (_CASE == -1)
            {
                count_number_bus_not_start += (_time < it_bus->TIME_A) ? 1 : 0;
            }
            else
            {
                count_number_bus_not_start += (_time < it_bus->TIME_A && it_bus->CASE == _CASE) ? 1 : 0;
            }
        }
        int count_number_bus_on_way = this->CS(_ID, _time, _CASE) == -1 ? 0 : this->CS(_ID, _time, _CASE);
        // Debug message
        // cout << "ON way : " << count_number_bus_on_way << endl 
        //      << "not Start : " << count_number_bus_not_start << endl;
        // End message
        int count_number_bus = 0;
        for (vector<Bus>::iterator it_bus = Henry->second.begin(); it_bus != Henry->second.end(); it_bus++)
        {
            count_number_bus += (it_bus->CASE == _CASE) ? 1 : 0;
        }
        return (count_number_bus - count_number_bus_not_start - count_number_bus_on_way) > 0 ? 
               (count_number_bus - count_number_bus_not_start - count_number_bus_on_way) : 0;
    }
}

string BusSystem::GS(string _ID, int _time, int _CASE)
{
    map<string, vector<Bus>>::iterator Henry = this->System.find(_ID);
    if (Henry == this->System.end())
        return "-1";
    else
    {
        if (_CASE != -1)
        {
            int Delta_time = MAX_INT;
            string result_LP = "";
            for (vector<Bus>::iterator it_bus = Henry->second.begin(); it_bus != Henry->second.end(); it_bus++)
            {
                if (it_bus->CASE == _CASE)
                {
                    int min = _time - it_bus->TIME_A > 0 ? _time - it_bus->TIME_A : MAX_INT;
                    if (Delta_time > min)
                    {
                        Delta_time = min;
                        result_LP = it_bus->LP;
                    }
                }
            }
            if (result_LP == "")
                result_LP = "-1";
            return result_LP;
        }
        else
        {
            int Delta_time_Outgoing = MAX_INT;
            int Delta_time_Return = MAX_INT;
            string result_LP_Outgoing = "";
            string result_LP_Return = "";
            string result_LP = "";
            for (vector<Bus>::iterator it_bus = Henry->second.begin(); it_bus != Henry->second.end(); it_bus++)
            {
                if (it_bus->CASE == 0)
                {
                    int min = _time - it_bus->TIME_A > 0 ? _time - it_bus->TIME_A : MAX_INT;
                    if (Delta_time_Outgoing > min)
                    {
                        Delta_time_Outgoing = min;
                        result_LP_Outgoing = it_bus->LP;
                    }
                }
            }
            for (vector<Bus>::iterator it_bus = Henry->second.begin(); it_bus != Henry->second.end(); it_bus++)
            {
                if (it_bus->CASE == 1)
                {
                    int min = _time - it_bus->TIME_A > 0 ? _time - it_bus->TIME_A : MAX_INT;
                    if (Delta_time_Return > min)
                    {
                        Delta_time_Return = min;
                        result_LP_Return = it_bus->LP;
                    }
                }
            }
            if (Delta_time_Outgoing == Delta_time_Return)
                return result_LP_Outgoing;
            else
            {
                string result_LP = Delta_time_Outgoing > Delta_time_Return ? result_LP_Return : result_LP_Outgoing;
                if (result_LP == "")
                    result_LP = "-1";
                return result_LP;
            }
        }
    }    
}

string BusSystem::GE(string _ID, int _time, int _CASE)
{
    map<string, vector<Bus>>::iterator Henry = this->System.find(_ID);
    if (Henry == this->System.end())
        return 0;
    else
    {
        if (_CASE != -1) // one direction
        {
            int Delta_time = MAX_INT;
            int Base_time_start = -MAX_INT;
            string result_LP = "";
            // Find min Delta time
            for (vector<Bus>::iterator it_bus = Henry->second.begin(); it_bus != Henry->second.end(); it_bus++)
            {
                if (it_bus->CASE == _CASE)
                {
                    int min = _time - it_bus->TIME_B > 0 ? _time - it_bus->TIME_B : MAX_INT;
                    if (Delta_time > min)
                    {
                        Delta_time = min;
                    }
                }
            }
            // Find suitable bus
            for (vector<Bus>::iterator it_bus = Henry->second.begin(); it_bus != Henry->second.end(); it_bus++)
            {
                if (it_bus->CASE == _CASE)
                {
                    if (_time - it_bus->TIME_B == Delta_time)
                    {
                        if (Base_time_start < it_bus->TIME_A)
                        {
                            Base_time_start = it_bus->TIME_A;
                            result_LP = it_bus->LP;
                        }
                    }
                }
            }
            if (result_LP == "")
                result_LP = "-1";
            return result_LP;
        }
        else // bidirection
        {
            int Delta_time_Outgoing = MAX_INT;
            int Delta_time_Return = MAX_INT;
            int Base_time_start_Outgoing = -MAX_INT;
            int Base_time_start_Return = -MAX_INT;
            string result_LP_Outgoing = "";
            string result_LP_Return = "";
            string result_LP = "";
            // Find min Delta time
            for (vector<Bus>::iterator it_bus = Henry->second.begin(); it_bus != Henry->second.end(); it_bus++)
            {
                if (it_bus->CASE == 0)
                {
                    int min = _time - it_bus->TIME_B > 0 ? _time - it_bus->TIME_B : MAX_INT;
                    if (Delta_time_Outgoing > min)
                    {
                        Delta_time_Outgoing = min;
                    }
                }
            }
            // Find suitable bus
            for (vector<Bus>::iterator it_bus = Henry->second.begin(); it_bus != Henry->second.end(); it_bus++)
            {
                if (it_bus->CASE == 0)
                {
                    if (_time - it_bus->TIME_B == Delta_time_Outgoing)
                    {
                        if (Base_time_start_Outgoing < it_bus->TIME_A)
                        {
                            Base_time_start_Outgoing = it_bus->TIME_A;
                            result_LP_Outgoing = it_bus->LP;
                        }
                    }
                }
            }
            // Find min Delta time
            for (vector<Bus>::iterator it_bus = Henry->second.begin(); it_bus != Henry->second.end(); it_bus++)
            {
                if (it_bus->CASE == 1)
                {
                    int min = _time - it_bus->TIME_B > 0 ? _time - it_bus->TIME_B : MAX_INT;
                    if (Delta_time_Return > min)
                    {
                        Delta_time_Return = min;
                    }
                }
            }
            // Find suitable bus
            for (vector<Bus>::iterator it_bus = Henry->second.begin(); it_bus != Henry->second.end(); it_bus++)
            {
                if (it_bus->CASE == 1)
                {
                    if (_time - it_bus->TIME_B == Delta_time_Return)
                    {
                        if (Base_time_start_Return < it_bus->TIME_A)
                        {
                            Base_time_start_Return = it_bus->TIME_A;
                            result_LP_Return = it_bus->LP;
                        }
                    }
                }
            }
            if (Delta_time_Outgoing == Delta_time_Return)
            {
                if (result_LP_Outgoing == "")
                    result_LP_Outgoing = "-1";
                return result_LP_Outgoing;
            }
            else
            {
                string result_LP = Delta_time_Outgoing > Delta_time_Return ? result_LP_Return : result_LP_Outgoing;
                if (result_LP == "")
                    result_LP = "-1";
                return result_LP;
            }
        }
    }    
}

void BusSystem::print()
{
    if (this->System.empty())
    {
        cout << "The System is currently empty" << endl;
    }
    else 
    {
        cout << "---------------------------------------------------------------------------" << endl;
        cout << "|" << setw(8) << "Route" << setw(3) 
             << "|" << setw(16) << "License Plate" << setw(3) 
             << "|" << setw(7) << "Case" << setw(3)
             << "|" << setw(17) << "Departure time" << setw(3) 
             << "|" << setw(11) << "End time" << setw(3) << "|" << endl
             << "---------------------------------------------------------------------------" << endl;
        for (auto i : this->System)
        {
            for (vector<Bus>::iterator Mouse = i.second.begin(); Mouse != i.second.end(); Mouse++)
            {
                cout << "|" << setw(6) << Mouse->ID << setw(5) 
                     << "|" << setw(14) << Mouse->LP << setw(5) 
                     << "|" << setw(5) << Mouse->CASE << setw(5)
                     << "|" << setw(12) << Mouse->TIME_A << setw(8)
                     << "|" << setw(9) << Mouse->TIME_B << setw(5) << "|" << endl;
            }
        }
        cout << "---------------------------------------------------------------------------" << endl;
    }
}

void BusSystem::input()
{
    cout << "Press 'x' anytime to exit" << endl;
    cout << "Press 'p' anytime to print the table" << endl;
    while (true)
    {
        string result = "";
        cout << ">>> ";
        getline(cin, result, '\n');
        if (result == "x" || result == "X")
            break;
        if (result == "p" || result == "P")
            this->print();
        this->query(result);
    }
}

string BusSystem::query(string instruction)
{
    // TODO: Your implementation
    if (instruction[0] == ' ' || instruction[instruction.length() - 1] == ' ') 
        return "-1";
   // Read command
    string Command = this->Split_Command(instruction).at(0);
    // Check valid command
    if (Command != "SQ" && Command != "INS" && Command != "DEL" && Command != "CS" && Command != "CE" && Command != "GS" && Command != "GE")
        return "-1";
    // Valid command
    // Handle each situation
    if (Command == "SQ")
    {
        N = stoi(this->Split_Command(instruction).at(1));
        return "1";
    }
    else if (Command == "INS")
    {
        string _ID = "";
        string _LP = "";
        string _CASE = "";
        string _time_A = "";
        string _time_B = "";
        vector<string> Result = this->Split_Command(instruction);
        if (Result.size() < 3)
            return "-1";
        unsigned int i = 1;
        if (i < Result.size())
        {
            _ID = Result.at(i);
            i++;
        }
        if (i < Result.size())
        {
            _LP = Result.at(i);
            i++;
        }
        if (i < Result.size())
        {
            _CASE = Result.at(i);
            i++;
        }
        if (i < Result.size())
        {
            _time_A = Result.at(i);
            i++;
        }
        if (i < Result.size())
        {
            _time_B = Result.at(i);
            i++;
        }
        if (i < Result.size()) 
            return "-1";
        
        // Check valid values
        // Check if Case exist or not
        // if not, assign -1 to case
        if (_CASE.size() != 1)
        {
            _time_B = _time_A;
            _time_A = _CASE;
            _CASE = "0";
        }
        try
        {
            stoi(_time_A);
            stoi(_time_B);
            stoi(_CASE);
        }
        catch (...)
        {
            return "-1";
        }
        // Check time
        if (_time_A == "") return "-1";
        if (_time_B == "") return "-1";
        if (to_string(stoi(_time_A)) != _time_A) return "-1";
        if (to_string(stoi(_time_B)) != _time_B) return "-1";
        // Debug message
        // Only turn on when debugging
        // cout << "---- INS ----" << endl
        //      << "CODE   : " << _ID << endl
        //      << "LP     : " << _LP << endl
        //      << "CASE   : " << _CASE << endl
        //      << "Time A : " << _time_A<< endl
        //      << "Time B : " << _time_B << endl
        //      << "Result >>> ";
        // End debug message

        // Test to catch the exception about stoi function
        return to_string(this->INS(_ID,
                                   _LP,
                                   stoi(_time_A),
                                   stoi(_time_B),
                                   stoi(_CASE)));
        // return "-1";
    }
    else if (Command == "DEL")
    {
        string _ID = "";
        string _TIME_A = "";
        string _TIME_B = "";
        string _Initial_TIME = "";
        vector<string> Result = this->Split_Command(instruction);
        if (Result.size() < 2)
            return "-1";
        unsigned int i = 1;
        if (i < Result.size())
        {
            _ID = Result.at(i);
            i++;
        }
        if (i < Result.size())
        {
            _TIME_A = Result.at(i);
            i++;
        }
        if (i < Result.size())
        {
            _TIME_B = Result.at(i);
            i++;
        }
        if (i < Result.size())
            return "-1";
        if (_TIME_A == "")
            _TIME_A = "-1";
        if (_TIME_B == "")
            _TIME_B = "-1";
        try 
        {
            stoi(_TIME_A);
            stoi(_TIME_B);
        }
        catch(...)
        {
            return "-1";
        }
        // Debug message
        // Only turn on when debugging
        // cout << "---- DEL ----" << endl
        //      << "CODE   : " << _ID << endl
        //      << "TIME A : " << _TIME_A << endl
        //      << "TIME B : " << _TIME_B << endl
        //      << "Result >>> ";
        // End message
        return to_string(this->DEL(_ID, stoi(_TIME_A), stoi(_TIME_B)));
    }
    else if (Command == "CS")
    {
        string _ID = "";
        string _TIME = "";
        string _CASE = "";
        vector<string> Result = this->Split_Command(instruction);
        if (Result.size() < 3)
            return "-1";
        unsigned int i = 1;
        if (i < Result.size())
        {
            _ID = Result.at(i);
            i++;
        }
        if (i < Result.size())
        {
            _TIME = Result.at(i);
            i++;
        }
        if (i < Result.size())
        {
            _CASE = Result.at(i);
            i++;
        }
        if (i < Result.size())
        {
            return "-1";
        }
        if (_CASE.size() != 1)
        {
            _CASE = "-1";
        }
        try 
        {
            stoi(_TIME);
            stoi(_CASE);
        }
        catch(...)
        {
            return "-1";
        }
        //Debug message
        // cout << "---- CS ----" << endl
        //      << "CODE   : " << _ID << endl  
        //      << "TIME   : " << _TIME << endl
        //      << "CASE   : " << _CASE << endl
        //      << "Result >>> ";
        // end message
        return to_string(this->CS(_ID,stoi(_TIME),stoi(_CASE)));
    }
    else if (Command == "CE")
    {
        string _ID = "";
        string _TIME = "";
        string _CASE = "";
        vector<string> Result = this->Split_Command(instruction);
        if (Result.size() < 3)
            return "-1";
        unsigned int i = 1;
        if (i < Result.size())
        {
            _ID = Result.at(i);
            i++;
        }
        if (i < Result.size())
        {
            _TIME = Result.at(i);
            i++;
        }
        if (i < Result.size())
        {
            _CASE = Result.at(i);
            i++;
        }
        if (i < Result.size())
        {
            return "-1";
        }
        if (_CASE.size() != 1)
        {
            _CASE = "-1";
        }
        try 
        {
            stoi(_TIME);
            stoi(_CASE);
        }
        catch(...)
        {
            return "-1";
        }
        //Debug message
        // cout << "---- CE ----" << endl
        //      << "CODE   : " << _ID << endl  
        //      << "TIME   : " << _TIME << endl
        //      << "CASE   : " << _CASE << endl
        //      << "Result >>> ";
        // end message
        return to_string(this->CE(_ID,stoi(_TIME),stoi(_CASE)));
    }
    else if (Command == "GS")
    {
        string _ID = "";
        string _TIME = "";
        string _CASE = "";
        vector<string> Result = this->Split_Command(instruction);
        if (Result.size() < 3)
            return "-1";
        unsigned int i = 1;
        if (i < Result.size())
        {
            _ID = Result.at(i);
            i++;
        }
        if (i < Result.size())
        {
            _TIME = Result.at(i);
            i++;
        }
        if (i < Result.size())
        {
            _CASE = Result.at(i);
            i++;
        }
        if (i < Result.size())
        {
            return "-1";
        }
        if (_CASE.size() != 1)
        {
            _CASE = "-1";
        }
        try 
        {
            stoi(_TIME);
            stoi(_CASE);
        }
        catch(...)
        {
            return "-1";
        }
        //Debug message
        // cout << "----GS ----" << endl
        //      << "CODE   : " << _ID << endl  
        //      << "TIME   : " << _TIME << endl
        //      << "CASE   : " << _CASE << endl
        //      << "Result >>> ";
        // end message
        return this->GS(_ID,stoi(_TIME),stoi(_CASE));
    }
    else if (Command == "GE")
    {
        string _ID = "";
        string _TIME = "";
        string _CASE = "";
        vector<string> Result = this->Split_Command(instruction);
        if (Result.size() < 3)
            return "-1";
        unsigned int i = 1;
        if (i < Result.size())
        {
            _ID = Result.at(i);
            i++;
        }
        if (i < Result.size())
        {
            _TIME = Result.at(i);
            i++;
        }
        if (i < Result.size())
        {
            _CASE = Result.at(i);
            i++;
        }
        if (i < Result.size())
        {
            return "-1";
        }
        if (_CASE.size() != 1)
        {
            _CASE = "-1";
        }
        try 
        {
            stoi(_TIME);
            stoi(_CASE);
        }
        catch(...)
        {
            return "-1";
        }
        //Debug message
        // cout << "----GE ----" << endl
        //      << "CODE   : " << _ID << endl  
        //      << "TIME   : " << _TIME << endl
        //      << "CASE   : " << _CASE << endl
        //      << "Result >>> ";
        // end message
        return this->GE(_ID,stoi(_TIME),stoi(_CASE));
    }
    else return "-1";
    return "-1";
}

// Check input string
/*
 * 1. Check the space at the beginning and the end
 * 2. Check if the time_A and time_B contains character
 * 3. Check valid case input (not [Case], but Case)
 * 4. Check the right order of each element in the input string
 * */
int main()
{
    BusSystem *bs = new BusSystem();
    bs->query("SQ 10");
    bs->query("INS A12B 5D-23342 1235 5678");
    bs->query("INS B23A 31RE-555 0 1235 9121");
    bs->query("INS C400 54D143-111 0 12778 21001");
    bs->query("INS D33 14C2-738 121 912");
    bs->query("INS A12B 51D2-3244 1 1235 5655");
    bs->query("INS B23A 32C-66563 657 9121");
    bs->query("INS 43A 51D6-89191 0 277 1100");
    bs->query("INS D43 AD-738 5699 9121");
    bs->query("INS A12 50D-23342 1 1235 5678");
    bs->query("INS B23 32C-55555 0 1235 9121");
    bs->query("INS C4 54D1-89391 0 1277 2100");
    bs->query("INS D43 44C2-73847 1299 9121");
    bs->query("INS A1 51DA-23244 1 1211 5655");
    bs->query("INS B23 32C-66563 657 912");
    bs->query("INS 43A 51D6-89191 0 277 1100"); 
    bs->query("INS D43 AD-738 5699 9121");
    bs->query("INS 50 50D1-23342 1 1235 5678");
    bs->query("INS 50 32C1-55555 0 1235 9121");
    bs->query("INS 50 54D1-89391 0 1277 2100");
    bs->query("INS 50 44C2-73847 1 1299 9121");
    bs->query("INS 50 50D1-23342 1234 5678");
    bs->query("INS 50 50D1-23342 1234 5679");
    bs->query("INS 50 59A3-18965 1244 1754");
    bs->query("INS 50 54B3-18365 1245 1754");
    bs->query("INS 33 54F1-21076 1 1232 1345");
    bs->query("INS 33 51B5-22451 0 1235 1412");
    bs->print();
    // bs->query("DEL 50");
    // bs->query("DEL A12B");
    // bs->query("DEL D43");
    // bs->print();
}
