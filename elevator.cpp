#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cstdlib>



// ASSIGNMENT:
// Provide code that simulates an elevator. You are free to use any language.
// Upload the completed project to GitHub (public) for discussion during interview.
// Document all assumptions and any features that weren’t implemented.
// The result should be an executable, or script, that can be run with the following inputs and generate the following outputs.

//            Inputs: [list of floors to visit] (e.g. elevator start=12 floor=2,9,1,32)

//            Outputs: [total travel time, floors visited in order] (e.g. 560 12,2,9,1,32)

//            Program Constants: Single floor travel time: 10


using namespace std;
// ASSUMPTIONS:

// I'm assuming that the format is as expected by the project description and follow it closely. 
// I'll also assume that the inputs only expect one input and not 1 input for the start position and 1 input for the floor array.
// I'm assuming that negative floors are valid and will be treated as below ground floors

// UNIMPLEMENTED FEATURES:

// the code only supports one input format, if the user tries to input the data as: '12 2 9 1 32' or '12\n2\n9\n1\n32' then the program wont run properly
// the code does not account for random strings to the left of our '=' delimeter, for example 'start=1 banana=14 floor=2,3,4,5' is valid and just treated as 'start=1 floor=2,3,4,5'








// Function: stringIsInteger
// Description:  Reads input string to test if it is an integer value. Valid for positive and negative integers. 
//               The function tests by comparing the converted stoi with the ammount of characters processed, held in unsigned int charProcessed           
// Inputs:
//      const string &str: passes in string by reference to test if its an integer value. Applies const so string is safe frome editing.
// Outputs:
//      bool: returns true if string is integer, false if string isnt or is null
bool stringIsInteger(const string &str){
    size_t charProcessed = 0;

    if(str.empty()){ // cant be int if its empty
        return false;
    }
    try{
        stoi(str, &charProcessed);
        return(str.size() == charProcessed);
    } catch(...){
        return false;
    }

}


// Function: readVectorInput
// Description:  Reads user input from terminal following the specific format: 'start=1 floor=2,3,4,5' and extracts desired integers into floors vector.
//               The function ends reading from terminal when the user presses Enter key.               
// Inputs:
//      None
// Outputs:
//      vector<int> floors: 1xN Vector containing a set of integers corresponding to the starting floor and desired floors for the elevator to travel to.
vector<int> readVectorInput(){
    char delim = '=';

    vector<int> floors;
    string input_raw;
    getline(cin, input_raw);

    stringstream ssIn(input_raw);
    // checks for if we actually got both start and floor
    int startAppeared = 0;
    int floorAppeared = 0;

    string input_space;

    while(ssIn >> input_space){
        int delim_pos = input_space.find(delim);

        // elevator is valid even though it doesnt have a delimiter
        if(input_space == "elevator"){
            continue;
        }

        if(delim_pos == string::npos){ 
            cerr << "Valid delimeter not found, please use \"=\" as delimiter.\n";
            return {};
        }
        
        
        string left = input_space.substr(0, delim_pos);
        string right = input_space.substr(delim_pos + 1);
        
        if(left == "start"){
            if(!stringIsInteger(right)){
                cerr << "Start input: \"" + right + "\" is invalid. Valid inputs are sinuglar integers\n";
                return {};
            }
            startAppeared = 1;
            floors.insert(floors.begin(), stoi(right));
        }   
        else if(left == "floor"){
            
            string floor;
            stringstream floor_stream(right);
            while(getline(floor_stream,floor,',')){
                if(!stringIsInteger(floor)){
                cerr << "Floor input: \"" + floor + "\" is invalid. Valid inputs are integers\n";
                    return {};
                }   
                floors.push_back(stoi(floor));
            }
            floorAppeared = 1;
        }
    }
    if (!startAppeared || !floorAppeared){
        cerr << "Start input or Floor input not found, please see desired format: elevator start=1 floor=2,3,4,5\n";
        return {};
    }
    return(floors);
}



// Function: calculateElevatorTime
// Description:  calculates the ammount of time it takes for the elevator to travel from each of the floors contained in the floors vector where it starts at the first index.               
// Inputs:
//      vector<int> floors: 1xN Vector containing a set of integers corresponding to the starting floor and desired floors for the elevator to travel to.
// Outputs:
//      int total_time: integer value containing the total ammount of time it takes for the elevator to travel through the list of floors in seconds.
int calculateElevatorTime(const vector<int> &floors){
    int time_per_floor = 10; // time to move 1 floor [s/floor]
    int total_time = 0; // total time taken to travel through list of floors [s]

    int prev_floor = floors[0]; // initialize prev_floor to first floor position
    // the first loop should be abs(floors[0] - floors[0]) = 0
    for(int curr_floor : floors){
        total_time += time_per_floor * abs(curr_floor - prev_floor); // increment the total time by ammount of time to travel from previous to current floor
        prev_floor = curr_floor; // set current floor to previous floor
    }
    return(total_time);
}
// Function: formatOutput
// Description: formats the total travel time of the elevator with the list of floors visited into a standardized output              
// Inputs:
//      vector<int> floors: 1xN Vector containing a set of integers corresponding to the starting floor and desired floors for the elevator to travel to.
//      int total_time: integer value containing the total ammount of time it takes for the elevator to travel through the list of floors in seconds.
// Outputs:
//      string output: contains contcetanted string with total elevator traveling time and the list of floors visited by the elevator.
string formatOutput(int elevator_time, const vector<int> &floors){
    
    string output;

    output = to_string(elevator_time) + " ";

    for(int i = 0; i < floors.size(); i++){

        output += to_string(floors[i]);

        if(i < floors.size() - 1){
            output += ",";
        }
    }
    return output;


}
int main( ){
    cout << "please type the starting floor and desired floors for elevator\nformat: elevator start=1 floor=2,3,4,5\n";

    vector<int> floors_input = readVectorInput(); // take in input
    if(floors_input.empty()){
        cout << "invalid input, ending...\n";
        return 1;
    }
    int elevator_time = calculateElevatorTime(floors_input); // calculate total travel time

    string output = formatOutput(elevator_time, floors_input); // format total travel time with floors traveled

    // output formatted output:
    cout << output;

    cin.get();
    cin.get();
}