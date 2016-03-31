#include <stdio.h>
#include <string.h>
#include <lib_json/json_tool.h>
#include <fstream>


using namespace std;

int main(){
	ifstream json_file("dictionary.json", ifstream::binary);
	json_file >> jsonian;

	cout << jsonian<<endl;  //Printing the entire json file
	cout << jsonian["0x401153.0"]<<endl;

	return 0;
}