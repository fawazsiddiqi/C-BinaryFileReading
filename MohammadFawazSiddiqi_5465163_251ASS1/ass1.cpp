/************************
 * CSCI251 - Ass1
 * Mohammad Fawaz Siddiqi - 5465163
 * ass1.cpp - Contains function definitions for student records database
 ************************/
#include <iostream>
#include <fstream>
#include "ass1.h"
using namespace std;

// ============== Constants ==========================================

const char cTextFileName[]   = "ass1.txt";
const char cBinaryFileName[] = "ass1.dat";
const int cMaxRecs = 100;
const int cMaxChars = 30;
const int cMaxSubjects = 8;

// ============= User Defined types ==================================

enum StatusType{eEnrolled,eProvisional,eWithdrawn};
struct SubjectType{ char Code[8]; StatusType Status; int Mark;};

struct StudentRecord{
    long StudentNo;
    char FirstName[cMaxChars];
    char LastName[cMaxChars];
    int NumSubjects;
    SubjectType Subjects[cMaxSubjects];
};


// ============= Global Data =========================================

StudentRecord gRecs[cMaxRecs];
int gNumRecs=0;


// ============= Private Function Prototypes =========================
//prototypes for the functions involed within the program
void PrintRecord(int i);
int FindRecord(long StudentNum);
bool ReadTextFile();
bool WriteTextFile();
bool ReadBinaryFile();
bool WriteBinaryFile();
void WriteBinaryRecord(int Pos);
// ============= Public Function Definitions =========================

void ReadFile()
{
    ReadBinaryFile();   //read binary file to read the binary file
    WriteBinaryFile();  //write binary file
}

void DisplayRecord()
{   long StudentNo;
    cout << "Enter Student Number :";
    cin >> StudentNo;   //reads the student number
    int i = FindRecord(StudentNo);  //function which checks if the student record exists returns -1 if not found
    if(i == -1)
    {
        cout << "Sorry, Record not found." <<endl;
    }
    else
    {
        PrintRecord(i);  //prints the record if the student number is found
    }
}

void SaveFile() //function to save the file
{
    ofstream write;
    write.open(cTextFileName);  //opens the file
    if (write.fail()) {         //validation to check if the file has opened or not
        cout <<"Cant find text data file!" <<endl;
        exit(1);
    }
    for (int i =0; i<gNumRecs; i++) {       //for loop to iterate through gRecs student record array
        write << gRecs[i].StudentNo <<endl; //writes the student number
        write << gRecs[i].FirstName <<" ";  //writes first name of student
        write << gRecs[i].LastName <<endl;  //writes last name
        write << gRecs[i].NumSubjects << endl; //writes the number of subjects for the student
        
        for(int j =0; j<gRecs[i].NumSubjects; j++){ //for loop to write the subject code, status and marks with trespect to the number of subjects
            write << gRecs[i].Subjects[j].Code << " ";      //reads the subject codes for a particular student
            write << gRecs[i].Subjects[j].Status << " ";    //reads the status of the student in that subject
            write << gRecs[i].Subjects[j].Mark <<endl;      //reads the marks of the student in that subject
        }
        write << endl;
        
    }
    write.close();
    cout << gNumRecs << " Records Saved" <<endl; //Displays number of records
}

void UpdateRecord()
{   long StudentNo;
    char sub[8];
    char optn;
    int m;
    int statusSel;
    cout << "Enter Student Number :" <<endl;
    cin >> StudentNo;               //reads the student number
    int i = FindRecord(StudentNo);  //function which checks if the student record exists returns -1 if not found
    if(i == -1)
    {
        cout << "Record not found!" <<endl;
    }
    else
    {
        PrintRecord(i);     //initates the print record function
        cout << "Please enter subject code" <<endl;
        cin >> sub;
        
        for (int j =0; j<gRecs[i].NumSubjects; j++) {
            
            if (strcmp(gRecs[i].Subjects[j].Code,sub) == 0) {   //compares entered value in sub with the subject codes
                cout << "Select status or mark (s/m) :" <<endl;
                cin  >> optn;   //a switch case control variable in order to control the options in a switch case
                switch(optn)    //switch case to assign new statusType or new marks
                {
                    case 's':
                        cout << "Select new status :" <<endl;
                        cout << "0: " << "eEnrolled" <<endl;
                        cout << "1: " << "eProvisional" <<endl;
                        cout << "2: " << "eWithdrawn" <<endl;
                        cin  >> statusSel;      //a switch case control variable in order to control the options in a switch case
                        switch (statusSel) {    //switch case to uodate statusType
                            case 0:
                                gRecs[i].Subjects[j].Status = eEnrolled;
                                break;
                            case 1:
                                gRecs[i].Subjects[j].Status = eProvisional;
                                break;
                            case 2:
                                gRecs[i].Subjects[j].Status = eWithdrawn;
                                break;
                        }
                        break;
                    case 'm':
                        cout << "Enter the marks" <<endl;
                        cin  >> m;
                        gRecs[i].Subjects[j].Mark = m;
                        break;
                }
                
            }
            else{
                cout << "Subject code not found" <<endl;
            }
        }
        PrintRecord(i);
    }
    
}


// ============= Private Function Definitions =========================

void PrintRecord(int i) //prints records i on screen
{ // Prints record i on screen
    cout << gRecs[i].StudentNo <<endl;
    cout << gRecs[i].FirstName << " ";
    cout << gRecs[i].LastName <<endl;
    cout << gRecs[i].NumSubjects<<endl;
    
    for (int j =0; j < gRecs[i].NumSubjects; j++) //for loop to  the subject code, status and marks with trespect to the number of subjects
    {
        cout << gRecs[i].Subjects[j].Code<< " ";
        if(gRecs[i].Subjects[j].Status == 0){
            cout << "eEnrolled ";
        }
        else if (gRecs[i].Subjects[j].Status == 1){
            cout << "eProvisional ";
        }
        else{
            cout << "eWithdrawn ";
        }
        
        cout << gRecs[i].Subjects[j].Mark <<endl;
    }
    
}

int FindRecord(long StudentNo)  //finds record and if found returns the index else -1
{
    
    for (int i = 0; i < gNumRecs; i++){
        if (gRecs[i].StudentNo == StudentNo)
            return i;
    }
    return -1;
}

bool ReadTextFile(){            //reads text file
    int temp;
    int i = 0;
    ifstream readText;
    readText.open(cTextFileName);   //opens file
    if(readText.fail()){            //checks if file opened
        cout << "Cant find text data file" << endl;
        return false;
    }
    readText >> gRecs[i].StudentNo; //reads student number
    while(!readText.eof()) { //while it is not enf of file
        
        readText >> gRecs[i].FirstName;
        readText >> gRecs[i].LastName;
        readText >> gRecs[i].NumSubjects;
        
        for (int j = 0; j < gRecs[i].NumSubjects; j++){
            readText >>gRecs[i].Subjects[j].Code;
            readText >> temp;
            switch(temp){
                case 0: gRecs[i].Subjects[j].Status = eEnrolled;
                    break;
                case 1: gRecs[i].Subjects[j].Status = eProvisional;
                    break;
                default: gRecs[i].Subjects[j].Status = eWithdrawn;
                    break;
            }
            
            readText >> gRecs[i].Subjects[j].Mark;
            
        }
        i++;
        readText >> gRecs[i].StudentNo;
    }
    
    gNumRecs = i;
    readText.close();
    cout << gNumRecs << " records read" << endl;
    return true;
}

bool WriteTextFile(){ //writes to text file
    ofstream write;
    write.open(cTextFileName);
    
    if (write.fail()) {
        cout <<"Cant find text data file" <<endl;
        return false;
    }
    for (int i =0; i<gNumRecs; i++) {   //iterates through gRecs and writes to text file
        write << gRecs[i].StudentNo <<endl;
        write << gRecs[i].FirstName <<" ";
        write << gRecs[i].LastName <<endl;
        write << gRecs[i].NumSubjects << endl;
        
        for(int j =0; j<gRecs[i].NumSubjects; j++){
            write << gRecs[i].Subjects[j].Code << " ";
            write << gRecs[i].Subjects[j].Status << " ";
            write << gRecs[i].Subjects[j].Mark <<endl;
        }
        write << endl;
        
    }
    write.close();
    cout << gNumRecs << " Records Saved" <<endl;
    return true;
    }

bool ReadBinaryFile()                   //reads binary data from file to gRecs[] array
{
    ifstream readBin;
    readBin.open(cBinaryFileName, ios::in | ios::binary); //opens binary with input mode
    int j=0;
    if(!readBin)
    {
        cout << "Can't open Binary File, reading from text file" << endl;
        ReadTextFile();
        return false;
    }
    readBin.read((char*)&gNumRecs,sizeof(int));         //reads the number of records through gNumRecs
    while(!readBin.eof())
    {
        readBin.read((char*)&gRecs[j].StudentNo,sizeof(int));   //reads student number and size of student number in integer
        readBin.read(reinterpret_cast<char *> (&gRecs[j].FirstName),sizeof(gRecs[j].FirstName)); //reads student first name and gets its size
        readBin.read(reinterpret_cast<char *> (&gRecs[j].LastName),sizeof(gRecs[j].LastName));
        readBin.read((char*)&gRecs[j].NumSubjects,sizeof(int));
        for (int i = 0; i < gRecs[j].NumSubjects; i++)
        {
            readBin.read((char*)&gRecs[j].Subjects[i].Code,sizeof(SubjectType));
            readBin.read((char*)&gRecs[j].Subjects[i].Status,sizeof(SubjectType));
            readBin.read((char*)&gRecs[j].Subjects[i].Mark,sizeof(SubjectType));
        }
        j++;
    }
    readBin.close();
    return true;
    
}
bool WriteBinaryFile() //writes binary data from gRecs[] to file
{
    ofstream writeBin;
    writeBin.open(cBinaryFileName, ios::out | ios::binary);     //opens binary with output mode
    if(!writeBin)
    {
        cout << "Can't open Binary File, writing to text file" << endl;
        WriteTextFile();
        return false;
    }
    int k=0;
    writeBin.write((char*)&gNumRecs,sizeof(int));               //reads the number of records through gNumRecs
    while(k < gNumRecs)
    {
        writeBin.write((char*)&gRecs[k].StudentNo,sizeof(int)); //write student number and size of student number in integer
        writeBin.write(reinterpret_cast<char *> (&gRecs[k].FirstName),sizeof(gRecs[k].FirstName));//writes student first name and gets its size
        writeBin.write(reinterpret_cast<char *> (&gRecs[k].LastName),sizeof(gRecs[k].LastName));
        writeBin.write((char*)&gRecs[k].NumSubjects,sizeof(int));
        for (int i = 0; i < gRecs[k].NumSubjects; i++)
        {
            writeBin.write((char*)&gRecs[k].Subjects[i].Code,sizeof(SubjectType));
            writeBin.write((char*)&gRecs[k].Subjects[i].Status,sizeof(SubjectType));
            writeBin.write((char*)&gRecs[k].Subjects[i].Mark,sizeof(SubjectType));
        }
        k++;
    }
    writeBin.close();
    return true;
}

void WriteBinaryRecord(int Pos){
    ofstream myFile;
    myFile.open(cBinaryFileName, ios::out | ios::binary);
    
    
    
    }

