#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <iostream>
#include <string>
#include <bits/stdc++.h>
#include <sstream>
#include <fstream>
#include <vector>
using namespace std;
/////////////////////////////////////////////////////////// only touch here. All else works.//
string helper(string a){
    string result = "That word was not found.";
    vector<string> values;
 istringstream f(a);
    string line;
    string key;
    cout << "Enter word to search for: ";
    cin >> key;    
    string buffer;
    int count = 0;
while (getline(f, line)) {
      buffer = line;
      istringstream ff(buffer);
      string line2;
      //cout << buffer << endl;
      while(getline(ff, line2, ' ')){
      	transform(line2.begin(), line2.end(), line2.begin(), ::tolower);
        if(key == line2){
          ++count;
        }
      }
      if (count > 0){
        values.push_back(buffer);
        count = 0;
      }
      }
      sort(values.begin(),values.end());
      if (values.size() == 0){
        return result;
      }
      result = "";
    for (int i = 0; i < values.size(); ++i){
        result = result + values.at(i) + '\n';
    }
    return result;
}
////////////////////////////////////////////////////////////////////////////////////////////
int main(void)
{
    int sv[2]; /* the pair of socket descriptors */
    int buf; /* for data exchange between processes */
    string contents;
    string childContents;
    string childAns;
    string parentAns;
    ///////////////////////////////This takes file contents and puts them in a string.
    string line;
    string fileToFind;
    cout << "Enter the file path: ";
    cin >> fileToFind;
    ifstream myfile (fileToFind); ////////// Change file to whatever you would like the program to search in (as long as it is a text file, of course) 
    if (myfile.is_open()){
        while (getline(myfile,line)){
            contents = contents + "\n" + line;
        }
        myfile.close();
    } else {
        cout << "Unable to open file.";
    }
    /////////////////////////////////////////////////////////////////////////////////////
    if (socketpair(AF_UNIX, SOCK_STREAM, 0, sv) == -1) {
        perror("socketpair");
        exit(1);
    }
        //cout << contents << endl;
    if (!fork()) {  /////////////////////////////// child ////////////////////////////
            read(sv[1], &buf, 4);
            int childSizeCon = buf;
            //cout << "Child read " << buf << " from parent." << endl;
      int tmpp;
            for (int i = 0; i < childSizeCon; ++i){
             read(sv[1], &buf, 4);
        tmpp = buf;
        childContents = childContents + (char)tmpp;
            }
      //cout << "Inside of child: " << childContents << endl;

      childAns = helper(childContents); ////// this takes in the string and returns a string with the values discovered 
                                        ////// and alphabetically ordered and sets it equal to childAns.
      int sizeResult = childAns.size();

      write(sv[1], &sizeResult, 4);
      //cout << "Child wrote " << sizeResult << " to parent." << endl;
      int tmp2;
      for (int i = 0; i < sizeResult; ++i){
        tmp2 = childAns.at(i);
        write(sv[1], &tmp2, 4);
      }
        
    } else { /* parent *///////////////////////////////////// parent ///////////////////////////
       int sizeCon = contents.size();
       write(sv[0], &sizeCon, 4); // writes the size of the string to the parent
       //cout << "Parent wrote " << sizeCon << " to child." << endl;
       int tmp;
       for (int i = 0; i < sizeCon; ++i){ // sends each character over in ASCII code
        tmp = contents.at(i);
        write(sv[0], &tmp, 4);
       }
        read(sv[0], &buf, 4);
       //cout << "Parent read " << buf << " from child." << endl;
       int tmp3 = buf;
       for (int i = 0; i < tmp3; ++i){
        read(sv[0], &buf, 4);
        parentAns = parentAns + char(buf);
       }
       cout << parentAns << endl; // parentAns is what will hold the value that 'helper' returns.
        wait(NULL); /* wait for child to die */
    }

    return 0;
}