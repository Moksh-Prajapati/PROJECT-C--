#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

class user {
private:
    string username;
    string password;
    string roomtype;
public:
    user(string a, string b, string c= ""){
        username=a;
        password=b;
        roomtype=c; 
    }
    string getUserName(){
        return username;
    }
    string getPassword(){
        return password;
    }   
    string getRoomType(){
        return roomtype;
    }  
};



class AuthManager{
    public:
        //for registration
        void userRegistration()
        { 
            string username , password;
            cout<< "\n Registeration Section \n"; 
            cout<<"Enter username(No Spaces):";
            cin>>username;

            cout<<"Enter password(No spaces):";
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
            cout <<"\n Login \n";

            cout <<"Enter Username:";
            cin>>username;

            cout<<"Enter Password:";
            cin>>password;

            ifstream file("login.txt");
            string u,p;

            while (file>>u>>p) {
                if (u==username && p==password) {
                    loggedUser=username;
                    cout<<"\nLogin successful!\n";
                    return true;
                }
            }

            cout << "\nInvalid credentials!\n";
            return false;
    }
};

class Manager{
    private: 
        vector<user> doubleQueue;

        int SingleRoom;
        int DoubleRoom;
        int RoomCounter;

    public:
        Manager(){
            SingleRoom=120;
            DoubleRoom=273;
            RoomCounter=1;
        }


        void Save(string RoomNumber, vector<user> users) {
            ofstream file("users.txt", ios::app);

            file <<"Room No: "<<RoomNumber<< endl;

            for (int i = 0;i<users.size();i++) {
                file << "User: " << users[i].getUserName()
                    << " | Type: " << users[i].getRoomType() << endl;
            }

            file << "----------------------\n";
            file.close();
        
        }
        // display availability
        void showAvailability() {
            cout << "\n--- Room Availability ---\n";
            cout << "Single Rooms: " << SingleRoom << endl;
            cout << "Double Rooms: " << DoubleRoom << endl;
        }

        // allocate room
        void allocateRoom(string username) {
            string type;

            cout << "Enter Room Type (single/double): ";
            cin >> type;

            user u(username, "", type);

            //Single Rooms
            if (type == "single") {
                if(SingleRoom<=0){
                    cout<<"No single rooms available"<<endl;
                    return;
                }
            

                vector<user> temp;
                temp.push_back(u);

                string RoomNumber = "S"+to_string(RoomCounter++);
                Save(RoomNumber, temp);

                SingleRoom--;

                cout <<"Single room allotted!\n";
                cout <<"Your Room Number is: "<<RoomNumber<<endl;
            }

            // DOUBLE ROOM
            else if (type=="double"){
                if (DoubleRoom<=0) {
                    cout <<"No double rooms available!\n";
                    return;
                }

                doubleQueue.push_back(u);

                if (doubleQueue.size()==2){
                    string RoomNumber="D"+to_string(RoomCounter++);

                    cout<<"_______________________________________"<<endl
                        << "Room allotted to "
                        << doubleQueue[0].getUserName()<<" & "
                        << doubleQueue[1].getUserName()<<endl;
                    cout <<"Room Number is: "<<RoomNumber<<endl;
                    
                    Save(RoomNumber, doubleQueue);
                    
                    doubleQueue.clear();
                    DoubleRoom--;
                }
                else {
                    cout <<"Waiting for another user...\n";
                }
            }

            else {
                cout << "Invalid type!\n";
            }

        }
        void viewBookings() {
            ifstream file("users.txt");

            if (!file) {
                cout << "No booking records found!\n";
                return;
            }

            string line;
            cout << "\n----- All Bookings -----\n";
            while (getline(file, line)) {
                cout << line << endl;
            }
            file.close();
        }
        
};

    void Booking(AuthManager auth, Manager manager, string loggedUser);
    void Login(AuthManager auth, Manager manager);

void Login(AuthManager auth,Manager manager){
    int choice;
    bool end;
    string loggedUser;

    cout << "===== Hostel Management System =====\n";

    // LOGIN / REGISTER LOOP
    do {
        cout<<"____________________________________________________________________________";
        cout << "\n1. Register\n2. Login\n3. Exit\nChoice: ";
        cin >> choice;

        // if (choice == 1) {
        //     auth.userRegistration();
        // }
        // else if (choice == 2) {
        //     if (auth.loginUser(loggedUser)) break;
        // }
        switch(choice){
        case 1:
            auth.userRegistration();
            break;

        case 2:
            if(auth.loginUser(loggedUser)){
                Booking(auth,manager,loggedUser);
            }
            break;
        case 3:
            cout<<"Exiting....\n";
            exit(0);

            break;
            
        default:
            cout<< "Invalid choice! Try again.\n";
    }

    } while(choice!=-1);
}

void Booking(AuthManager auth,Manager manager,string loggedUser){
    
    int choice;
    do{
            cout<<"____________________________________________________________________________";
            cout<<"\n1. Book Room\n2. Check Availability\n3. View Bookings\n0. Exit\nChoice: ";
            cin>>choice;

            switch(choice){
                case 1:
                    manager.allocateRoom(loggedUser);
                    break;

                case 2:
                    manager.showAvailability();
                    break;

                case 3:
                    manager.viewBookings();
                    break;

                case 0:
                    cout<<"Exiting...\n";
                    Login(auth,manager);
                    return;

                default:
                    cout<<"Invalid choice\n";
            }

        } while(choice != 0);
}

int main() {

    AuthManager auth;
    Manager manager;

    int choice;
    bool end;
    string loggedUser;

    cout << "===== Hostel Management System =====\n";

    Login(auth,manager);

    // // LOGIN / REGISTER LOOP
    // do {
    //     cout<<"____________________________________________________________________________";
    //     cout << "\n1. Register\n2. Login\n3. Exit\nChoice: ";
    //     cin >> choice;

    //     // if (choice == 1) {
    //     //     auth.userRegistration();
    //     // }
    //     // else if (choice == 2) {
    //     //     if (auth.loginUser(loggedUser)) break;
    //     // }
    //     switch(choice){
    //     case 1:
    //         auth.userRegistration();
    //         break;

    //     case 2:
    //         if(auth.loginUser(loggedUser)){
    //             // exit
    //             choice=-1;  
    //         }
    //         break;
    //     case 3:
    //         cout<<"Exiting....";
    //         choice=-1;
    //         end=true;

    //         break;
            
    //     default:
    //         cout<< "Invalid choice! Try again.\n";
    // }

    // } while(choice!=-1);

    // // AFTER LOGIN
    // if(end!=true){
    //     do{
    //         cout<<"____________________________________________________________________________";
    //         cout<<"\n1. Book Room\n2. Check Availability\n3. View Bookings\n0. Exit\nChoice: ";
    //         cin>>choice;

    //         switch(choice){
    //             case 1:
    //                 manager.allocateRoom(loggedUser);
    //                 break;

    //             case 2:
    //                 manager.showAvailability();
    //                 break;

    //             case 3:
    //                 manager.viewBookings();
    //                 break;

    //             case 0:
    //                 cout<<"Exiting...\n";
    //                 break;

    //             default:
    //                 cout<<"Invalid choice\n";
    //         }

    //     } while(choice != 0);
    // }

    return 0;
}