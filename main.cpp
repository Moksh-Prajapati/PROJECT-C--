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
    //for registration
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
  
    //for login
    bool loginUser(string &loggedUser)
    {
    string username, password;
    cout << "\n Login \n";

    cout <<"Enter Username:";
    cin >> username;

    cout<<"Enter Password:";
    cin>>password;

    ifstream file("login.txt");
    string u,p;

        while (file>>u>>p) {
            if (u==username && p==password) {
                loggedUser=username;
                cout<<"Login successful!\n";
                return true;
            }
        }

        cout << "Invalid credentials!\n";
        return false;
    }
};
