#include <iostream>
#include <jni.h>
#include <iterator>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

void GenerateData()               //DO NOT TOUCH CODE IN THIS METHOD
{
     JavaVM *jvm;                      // Pointer to the JVM (Java Virtual Machine)
     JNIEnv *env;                      // Pointer to native interface
                                                              //================== prepare loading of Java VM ============================
     JavaVMInitArgs vm_args;                        // Initialization arguments
     JavaVMOption* options = new JavaVMOption[1];   // JVM invocation options
     options[0].optionString = (char*) "-Djava.class.path=";   // where to find java .class
     vm_args.version = JNI_VERSION_1_6;             // minimum Java version
     vm_args.nOptions = 1;                          // number of options
     vm_args.options = options;
     vm_args.ignoreUnrecognized = false;     // invalid options make the JVM init fail
                                                                          //=============== load and initialize Java VM and JNI interface =============
     jint rc = JNI_CreateJavaVM(&jvm, (void**)&env, &vm_args);  // YES !!
     delete options;    // we then no longer need the initialization options.
     if (rc != JNI_OK) {
            // TO DO: error processing...
            cin.get();
            exit(EXIT_FAILURE);
     }
     //=============== Display JVM version =======================================
     cout << "JVM load succeeded: Version ";
     jint ver = env->GetVersion();
     cout << ((ver >> 16) & 0x0f) << "." << (ver & 0x0f) << endl;

     jclass cls2 = env->FindClass("ZooFileWriter");  // try to find the class
     if (cls2 == nullptr) {
            cerr << "ERROR: class not found !";
     }
     else {                                  // if class found, continue
            cout << "Class MyTest found" << endl;
            jmethodID mid = env->GetStaticMethodID(cls2, "createZooFile", "()V");  // find method
            if (mid == nullptr)
                   cerr << "ERROR: method void createZooFile() not found !" << endl;
            else {
                   env->CallStaticVoidMethod(cls2, mid);                      // call method
                   cout << endl;
            }
     }


     jvm->DestroyJavaVM();
     cin.get();
}

void DisplayAnimals(vector<string>& data)	//	shows all animals in vector data
{
	for (int i = 0; (unsigned)i < data.size(); i++){
		cout << data[i] << endl;
	}
}

void AddAnimal(vector<string>& data)	//	adds animal to vector
{
	string trackNumber;
	int trackNumberInt;
	string animalName;
	string animalType;
	string subType;
	int eggs;
	int nursing;
	ostringstream inputData;
	string totalInput;
	char userContinue;

	cout << "Enter Tracking Number:" << endl;
	cin >> trackNumberInt;
	while (cin.fail()) // validates user input
		  {
			 cout << "ERROR -- You did not enter an integer";

			 // get rid of failure state
			 cin.clear();

			 // discard 'bad' character(s)
			 cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			 cout << "Eggs: Integer" << endl;
			 cin >> eggs;
		  }
	trackNumber = to_string(trackNumberInt);	//	turns tracking int to string to use with stringstream later

	cout << "Enter Animal Name:" << endl;
	cin.ignore();
	getline(cin, animalName);

	cout << "Is Animal a Mammal or Oviparus?" << endl;		//	gets user input as a pseudo-boolean to prevent invalid data
	cout << "(<1> for mammal, <2> for Oviparus)" << endl;
	int animalTypeBool;
	do{
		cin >> animalTypeBool;

		if (animalTypeBool != 1 && animalTypeBool != 2){	//	validates user data
			cout << "Please enter 1 or 2" << endl;
		}
	}while (animalTypeBool != 1 && animalTypeBool != 2);

	if (animalTypeBool == 1){
		animalType = "Mammal";
	}
	else{
		animalType = "Oviparus";
	}

	cout << "Sub-type: 15 characters" << endl;
	cin.ignore();
	getline(cin, subType);

	cout << "Eggs: Integer" << endl;
	cin >> eggs;
	while (cin.fail())
	  {
	     cout << "ERROR -- You did not enter an integer";

	     // get rid of failure state
	     cin.clear();

	     // discard 'bad' character(s)
	     cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	     cout << "Eggs: Integer" << endl;
	     cin >> eggs;
	  }
	cout << "Nurse: Integer" << endl;
	cin >> nursing;
	if (cin.fail())
		  {
		     cout << "ERROR -- You did not enter an integer";

		     // get rid of failure state
		     cin.clear();

		     // discard 'bad' character(s)
		     cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		  }

	//	Builds string data to insert into vector and correctly formats it
	inputData << setw(7) << setfill('0')<< trackNumber << "\t" << setw(15) << left << setfill(' ') << animalName
			<< "\t" << setw(15) << animalType << "\t" << setw(15) << subType << "\t" << setw(1) << eggs << " " << nursing;

	totalInput = inputData.str();
	cin.ignore();

	cout << "You entered:" << endl;
	cout << totalInput << endl;
	cout << "Is this correct?" << endl;
	cout << "Enter <Y> for yes";
	cin >> userContinue;
	cin.ignore();
	if (userContinue == 'Y' || userContinue == 'y'){
		data.push_back(totalInput);
		cout << "Addition successfull" << endl;
	}
	else{
		cout << "Addition abandoned" << endl;
	}
}


void RemoveAnimal(vector<string>& data)	//	removes animal from vector data
{
    cout << "Enter track number to delete:" << endl;
    string numToDelete;
    ostringstream streamNumToDelete;
    cin.clear();
    cin.ignore();						//	Clears cin cache
    getline(cin, numToDelete);			//	gets tracking number to delete and parses it into the correct format
    streamNumToDelete << setw(7) << right << setfill('0') << numToDelete;
    numToDelete = streamNumToDelete.str();

    for (int i = 0; (unsigned)i < data.size(); i++){
    	if (data[i].find(numToDelete) == 0){
    		cout << "Are you sure you want to delete this entry?" << endl;
    		cout << data[i] << endl;
    		cout << "(Enter <Y> to continue" << endl;

    		char userInput;
    		cin >> userInput;

    		if (userInput == 'Y') {
    		data.erase(data.begin() + i);
    		cout << "Animal deleted successfully." << endl;
    		}
    	}
    }
}

void LoadDataFromFile(vector<string>& data)	//	Loads data from text file into vector,
											//	clears vector data to prevent duplicate data
{
	string line;
	ifstream in("zoodata.txt");
	data.clear();
	while(getline(in,line)){
	    data.push_back(line);
	}

	cout << "Load completed" << endl;
}

void SaveDataToFile(vector<string>& data)	//	saves Vector data to txt file, erases old txt file to overwrite data
{

	ofstream outfile;
	outfile.open("zoodata.txt", std::ofstream::out | std::ofstream::trunc);

	for (int i = 0; (unsigned)i < data.size(); i++){
		outfile << data[i] << "\n";
	}

	cout << "Data saved" << endl;

}

void DisplayMenu()	//	Displays menu options
{

		cout << "Please choose from one of the following options" << endl;
		cout << "1: Load Animal Data" << endl;
		cout << "2: Generate Data" << endl;
		cout << "3: Display Animal Data" << endl;
		cout << "4: Add Record" << endl;
		cout << "5: Delete Record" << endl;
		cout << "6: Save Animal Data" << endl;
		cout << "7: Quit" << endl;

}



int main()
{
	char menuSelection;
	bool repeat = true;
	vector<string> zooData;
	string STRING;
	ifstream infile;
	infile.open("zoodata.txt");

	while(getline(infile,STRING))	//	Loads txt file into vector for temporary data storage
	  {
		 zooData.push_back(STRING);
	  }
	infile.close();

	GenerateData();

	// Take an action based on which value was selected from the menu. If not one of those, ask again.
	do {
		DisplayMenu();
		cin >> menuSelection;
		switch(menuSelection) {

			case '1':	//	Load text file into vector
				LoadDataFromFile(zooData);
				break;

			case '2':			//	Generate data from Java file, doesn't seem to
				GenerateData();	//	do anything but we were told not to touch the java data
				break;			//	and I don't understand what it's doing very well

			case '3':	//	Display all animals from vector
				DisplayAnimals(zooData);
				break;

			case '4':	//	Add animal to vector
				AddAnimal(zooData);
				repeat = true;
				break;

			case '5':	//	Delete animal from vector
				RemoveAnimal(zooData);
				repeat = true;
				break;

			case '6':	//	Save temp data in vector to txt file
				SaveDataToFile(zooData);
				repeat = true;
				break;
			case '7':	//	quit the program
				cout << "Quitting..." << endl;
				repeat = false;
				break;

			default:	//	Catch invalid input
				cout << "Please make a selection from the menu" << endl;
				repeat = true;
				break;
		}

	}while(repeat);
}
