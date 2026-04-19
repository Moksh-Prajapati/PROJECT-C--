#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class user {
private:
    string username;
    string password;
    string roomtype;
public:
    user(string a, string b, string c= "") {
        username = a;
        password = b;
        roomtype = c; 
    }
    string getusername(){
        return username;
    }
    string getpassword(){
        return password;
    }   
    string getroomtype(){
        return roomtype;
    }   
};



class manager{
    public:

    void userRegistration()
    { string username , password , roomtype;
        cout<< "\n Registeration Section \n"; 
        cout<<"Enter username:";
        cin>>username;

        cout<<"Enter password:";
        cin>>password;
        
        ofstream file("login.txt",ios::app);
        file<<username<<" "<<password<<" "<<endl;
        file.close();

        cout<<"Registration successful!"<<endl;

    } 




};