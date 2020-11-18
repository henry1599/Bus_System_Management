#include <sstream>
#include <vector>
#include <algorithm>
#include <string>
#include <iostream>
#include <windows.h>
#include <assert.h>
#include <type_traits>
#include <iomanip>
#include <map>
using namespace std;
#define MAX_INT 1e5
// END: STUDENT ANSWER



unsigned long long int N; // Maximum trip in each route of the system
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
    BusSystem()
    {
        for (map<string , vector<Bus>>::iterator Mouse = this->System.begin(); Mouse != this->System.end(); Mouse++)
        {
            Mouse->second.resize(0);
        }
    }
    ~BusSystem()
    {
        this->System.clear();
    }
     
    /* Pre : a string as an instruction, whatever string
     * Post : a string satisfied the requirement
     * */
    string query(string instruction);
    /* Pre : the initial instruction as a string, whatever string
     * Post : a vector string contains each element of the input instruction
     * */
    vector<string> Split_Command(string instructor);
    /* Pre : - all parameter must be positive numbers
     *       - _time_A_1 <= _time_B_1 <= _time_A_2 <= _time_B_2
     * Post : - True : [_time_A_1 , _time_B_1] overlaps with [_time_A_2 , _time_B_2]
     *        - False : [_time_A_1 , _time_B_1] does not overlap with [_time_A_2 , _time_B_2] 
     * */
    bool is_overlap(int _time_A_1, int _time_B_1, int _time_A_2, int _time_B_2);
    /* Pre : 
     * - standard _ID and _LP (satisfied the requirement)
     * - _time_A <= _time_B && _time_A, _time_B > 0
     * - _CASE = {0,1} (optional parameter)
     * Post : 
     * - 1 : if successfully push a new bus into the System
     * - 0 : if cannot push a new bus into System due to several reasons mentioned in requirement
     * */
    int INS(string _ID, string _LP, int _time_A, int _time_B, int _CASE = 0);
    /* Pre : 
     * - standard _ID (satisfied the requirement)
     * - _time_A <= _time_B && _time_A, _time_B > 0 (optional variables)
     * Post :
     * - <number> : the number of deleted buses
     * */
    int DEL(string _ID, int _time_A, int _time_B);
    /* Pre : 
     * - standard _ID (satisfied the requirement)
     * - _time > 0 (optional variable)
     * - _CASE = {0,1} (optional variable)
     * Post : 
     * - <number> : the number of buses started but have not stopped yet at the considered time <time>
     * */
    int CS(string _ID, int _time, int _CASE);
    /* Pre : 
     * - standard _ID (satisfied the requirement)
     * - _time > 0 (optional vaiable)
     * - _CASE = {0,1} (optional variable)
     * Post :
     * - <number> : the number of buses have already stopped at the considered time <time>
     * */
    int CE(string _ID, int _time, int _CASE);
    /* Pre : 
     * - standard _ID (satisfied requirement)
     * - _time > 0 (optional variable)
     * - _CASE = {0,1} (optional variable)
     * Post : 
     * - <LP> : the License plate of A BUS which departure time is greater than considered time <time>
     * */
    string GS(string _ID, int _time, int _CASE);
    /* Pre : 
     * - standard _ID (satisfied requirement)
     * - _time > 0 (optional variable)
     * - _CASE = {0,1} (optional variable)
     * Post : 
     * - <LP> : the License plate of A BUS which stop time is greater than considered time <time>
     * */
    string GE(string _ID, int _time, int _CASE);
    /* Pre : 
     * - does not have any parameters 
     * Post : 
     * - A table show all information of the System (ID, LP, CASE, TIME_A, TIME_B)
     * */
    void print();
    void input(BusSystem *bs);
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

bool BusSystem::is_overlap(int _time_A_1, int _time_B_1, int _time_A_2, int _time_B_2)
{
    if (_time_B_2 < _time_A_1)
        return false;
    else
        return true;
}

int BusSystem::INS(string _ID, string _LP, int _time_A, int _time_B, int _CASE)
{
    // Create new Iterator name after my name :)))
    // To find whether the "_ID" is in the current System or not
    map<string , vector<Bus>>::iterator Henry;
    // Find the "_ID" in the System
    // If found : Henry will point to that "_ID" in the System
    // Otherwise, Henry points to the end() of the System
    Henry = this->System.find(_ID);
    if (N == 0)
        return -1;
    if (Henry->second.size() == N)
        return -1;
    if (Henry == this->System.end()) // Not found the ID
    {
        // Create new bus to insert into map
        Bus myBus = Bus(_ID, _LP, _CASE, _time_A, _time_B, 0, false);
        // Create new vector to insert into map
        vector<Bus> newVec;
        newVec.resize(0);
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
                // Debug message
                // cout << "PREV : " << time_end_prev << " | NEXT : " << time_start_next << endl;
                // end message
                if (!this->is_overlap(_time_A,_time_B, it_bus->TIME_A, it_bus->TIME_B))
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
        return -1;
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
        int count_bus_stop = 0;
        for (vector<Bus>::iterator Mouse = Henry->second.begin(); Mouse != Henry->second.end(); Mouse++)
        {
            if (Mouse->TIME_B < _time)
            {
                count_bus_stop++;
            }
        }
        return count_bus_stop;
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
                    int min = _time - it_bus->TIME_A >= 0 ? _time - it_bus->TIME_A : MAX_INT;
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
                    int min = _time - it_bus->TIME_A >= 0 ? _time - it_bus->TIME_A : MAX_INT;
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
                    int min = _time - it_bus->TIME_A >= 0 ? _time - it_bus->TIME_A : MAX_INT;
                    if (Delta_time_Return > min)
                    {
                        Delta_time_Return = min;
                        result_LP_Return = it_bus->LP;
                    }
                }
            }
            if (Delta_time_Outgoing == Delta_time_Return)
                return result_LP_Outgoing == "" ? "-1" : result_LP_Outgoing;
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
        return "-1";
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

void BusSystem::input(BusSystem *bs)
{
    cout << "Press 'x' anytime to exit" << endl;
    cout << "Press 'p' anytime to print the table" << endl;
    cout << "Press 'c' anytime to clear the console" << endl;
    while (true)
    {
        string result = "";
        cout << ">>> ";
        getline(cin, result, '\n');
        if (result == "x" || result == "X")
            break;
        if (result == "p" || result == "P")
        {
            bs->print();
        }
        if (result == "c" || result == "C")
        {
            system("cls");
            cout << "Press 'x' anytime to exit" << endl;
            cout << "Press 'p' anytime to print the table" << endl;
            cout << "Press 'c' anytime to clear the console" << endl;
        }
        if (result == "") continue;
        bs->query(result);
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
        if (Result.size() != 5 && Result.size() != 6)
            return "-1";
        bool is_CASE = Result.size() == 5 ? false : true;
        if (is_CASE) // CASE exists
        {
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
            if (_CASE != "1" && _CASE != "0")
            {
                return "-1";
            }
        }
        else // CASE does not exist
        {
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
                _time_A = Result.at(i);
                i++;
            }
            if (i < Result.size())
            {
                _time_B = Result.at(i);
                i++;
            }
            _CASE = "0";
        }
        
        if (_LP.size() > 10)
            return "-1";
        if (_ID.size() > 5)
            return "-1";
        
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
        while (_time_A[0] == '0')
        {
            _time_A.erase(_time_A.begin());
        }
        while (_time_B[0] == '0')
        {
            _time_B.erase(_time_B.begin());
        }
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

// Check input string, particularly INS instruction
/*
 * 1. Check the space at the beginning and the end
 * 2. Check if the time_A and time_B contains character
 * 3. Check valid case input (not [Case], but Case)
 * 4. Check the right order of each element in the input string
 * */
#define Out cout
int main()
{
    BusSystem *bs = new BusSystem();
    // Out << bs->query("SQ 1") << endl;
    // Out << bs->query("INS 50 50D1-23341 1234 5678") << endl;
    // Out << bs->query("INS 50 50A1-53246 1235 5689") << endl;
    bs->input(bs);
}
