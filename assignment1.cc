//***************************************************************************
//
//
//  Purpose: This program with open virtual files on /proc/ and gather
//  info about different things like os type, name,release, how many seconds
//  has been up in user mode,idle mode and the size of truing swap device.	
//
//***************************************************************************

#include <iostream>
#include <stdio.h>
#include <bits/stdc++.h>
#include <fstream>
#include <fstream>
#include <string>

using namespace std;

/**  SecondsToDayHourMinSec(int nSec) will convert the number of seconds into 
* day hour min sec.
* @param   int nSec
* @return none
*************************************************************************************************************/

void SecondsToDayHourMinSec(int nSec)
{
   int day,hour,minutes,seconds =0;
   day = nSec / (24 * 3600); //calculates number of days
   nSec = nSec % (24 * 3600);
   hour = nSec / 3600; //calculates hours
   nSec %= 3600;
   minutes = nSec / 60 ; //calculates minutes
   nSec %= 60;
   seconds = nSec; //calculates seconds
   cout << day << " " << "days " << hour  << " " << "hours " << minutes << " "
   << "minutes " << seconds << " " << "seconds " << endl;
}
/**  string getFileData(string path) will open the file path and it will
* return the content of the first line in the file
* @param   string path
* @return line 
*************************************************************************************************************/
static string getFileData(string path)
{
    ifstream fileData(path);
    string line;
    string temp = "";
    while (!fileData.eof())
    {
        getline(fileData, line);
        break;
    }
    return line;
}
/**  partA() this function with call getFileData to get info about ostype,hostname,osrelease and version
* and will output the info with complete sentences
* @param   none
* @return none
*************************************************************************************************************/
static void partA()
{
    cout<<  "\nA:Questions about turing\n";
    cout << "\t1.Turing OS type is: "  << getFileData("/proc/sys/kernel/ostype") << endl;
    cout << "\t2.Turing hostname is: " << getFileData("/proc/sys/kernel/hostname") << endl;
    cout << "\t3.Turing OS release is: " << getFileData("/proc/sys/kernel/osrelease") << endl;
    cout << "\t4.Turing version is: " << getFileData("/proc/sys/kernel/version") << endl;
    ;
}
/**  getSecondsTuring() this function will open the virtual file at /proc/uptime and it will return the 
* number of seconds Turing has been up
* @param   none
* @return value
*************************************************************************************************************/
int getSecondsTuring()
{
    ifstream finfo("/proc/uptime");
    int value;
    string line;
    string token;
    while (getline(finfo, line))
    {
        token = line.substr(0, line.find(" "));
        value = stoi(token);
        break;
    }
    return value;
}

/**  partB() this function will open the virtual file at /proc/cpuinfo it will split each line into 2 
* tokens with ":" as the splitor and it will see if first token contain processor and if it contains cpu cores
* it will increment the count everytime when it sees processor and this way we get the number of processors
* and it will return the second token on the casses when it sees cpu cores
* then it will print some answers for turing nicely formatted. 
* @param   none
* @return none
*************************************************************************************************************/

static void partB()
{
    ifstream finfo("/proc/cpuinfo");
    int count = 0;
    string line;
    string firstToken;
    string secondToken;
    string nbr_core = "";
    while (getline(finfo, line))
    {

        firstToken = line.substr(0, line.find(":"));
        secondToken = line.substr(line.find(":") + 1);
        if (firstToken.find("processor") != std::string::npos)
        {
            count++;
        }
        if (firstToken.find("cpu cores") != std::string::npos)
        {
            nbr_core = secondToken;
        }
    }
    cout << "\nB:Questions about turing's processor:\n";
    cout << "\t1.Turing has " << count << " processors( CPU cores)\n";
    cout << "\t2.Turgin has " << nbr_core << " multi-core chips\n";
    cout << "\t3.Turing has been up for " << getSecondsTuring() << " seconds" << endl;
    cout << "\t4.Turing has been up for ";
    SecondsToDayHourMinSec(getSecondsTuring());
}
/** partC() this function will answer few questions about proc 0, we start by reading info only for
* proc 0 then we split each line into 2 tokens with ":" as the splitor, than we will gather info about
* vendor_id, model name, address size ( which has a virtual and physical size) and save them in some strings
* variables, then print the finds nicely in complete senteces.
* @param   none
* @return none
*************************************************************************************************************/
static void partC()
{
    ifstream finfo("/proc/cpuinfo");
    string line;
    string vendorName;
    string modelName;
    string physicalSize;
    string virtualSize;
    string num_cpu_core;
    while (getline(finfo, line))
    {
        string firstToken;
        string secondToken;
        firstToken = line.substr(0, line.find(":"));
        secondToken = line.substr(line.find(":") + 1);
        if (firstToken.find("power management") != std::string::npos)
        {
            break;
        }
        if (firstToken.find("vendor_id") != std::string::npos)
        {
            vendorName = secondToken;
        }
        if (firstToken.find("model name") != std::string::npos)
        {
            modelName = secondToken;
        }
        //split the content you find at address sizes into 2 tokens where
        //the first token is physical size and the second one is the virtual size
        if (firstToken.find("address sizes") != std::string::npos)
        {
            physicalSize = secondToken.substr(0, secondToken.find(","));
            virtualSize = secondToken.substr(secondToken.find(",") + 1);
        }
    }
    //Nicely print info about Processor 0
    cout << "\nC.Questions about processor 0\n";
    cout << "\t1.Vendor name for processor 0 is : " << vendorName << endl;
    cout << "\t2.Model name for processor 0 is : " << modelName << endl;
    cout << "\t3.The physical address size of processor 0 is : " << physicalSize << endl;
    cout << "\t4.The virtual address size of processor 0 is : " << virtualSize<< endl;
}
/** partd() this method with open the virtual file at /proc/stat it will split each line into strings
* and it will look for the line where the first token is equl to cpu0 . on that token it wil split the 
* second token into tokens with " " as the splitor and it will add them into a vector so they can be accessed
* later and using stoi we can convert them from string to ints.
* @param   none
* @return none
*************************************************************************************************************/
static void partD()
{
    ifstream finfo("/proc/stat");
    vector<string> tokens;
    string line;
    string secondToken;
    string cpu_name;
    int sUserMode;
    int sSysMode;
    int sIdleMode;
    while (getline(finfo, line))
    {

        cpu_name = line.substr(0, line.find(" "));
        secondToken = line.substr(line.find(" ") + 1);
        if (cpu_name.find("cpu0") != std::string::npos)
        {
            stringstream check(secondToken);
            string temp;
            // tokenize the line into tokens with space as the splitor
            // then add it to the vector
            while (getline(check, temp, ' '))
            {
                tokens.push_back(temp);
            }
            sUserMode= (stoi(tokens[0]) + stoi(tokens[1]))/100;
            sSysMode = stoi(tokens[2])/100;
            sIdleMode= stoi(tokens[3])/100;
            break;
        }
    }
    //format the answers and print them out
    cout << "\nD.More questions for processor 0:\n";
    cout << "\t1.Processor 0 has been up for " << sUserMode << " seconds in user mode (including low-priority user mode).\n";
    cout << "\t2.Processor 0 has been up for " << sSysMode << " seconds in system mode.\n";
    cout << "\t3.Processor 0 has been up for " << sIdleMode << " seconds in Idle mode.\n";
    cout << "\t4.Processor 0 has been up in Idle mode for ";
    SecondsToDayHourMinSec(sIdleMode);
}
/** partE() this method will open the virtual file /proc/swap and it will try to find the line with partition
* then it will split that line into tokens and add them into a vector, then using stoi we convert the string
* into int and divide by 100 to get the size of turing swap device in MB.
* @param   none
* @return none
*************************************************************************************************************/
static void partE()
{
    ifstream finfo("/proc/swaps");
    float size;
    string line;
    vector<string> tokens;
    while (getline(finfo, line))
    {
        if (line.find("partition") != std::string::npos)
        {
            stringstream check(line);
            string intermediate;
            //split it with tab and add it to the vector
            while (getline(check, intermediate, '\t'))
            {
                tokens.push_back(intermediate);
            }
            size = stof(tokens[1]);
            break;
        }
    }


    cout << "\nE.What is the size of turing swap device in MB? " << endl;
    cout << "\t1.Size of turing swap device is " << setprecision(2) << fixed << size / 1000 << " MB\n" << endl;
}
int main()
{
    // driver program that will call methods partA,partB,partC,partD,partE
    partA();
    partB();
    partC();
    partD();
    partE();
    return 0;
}
