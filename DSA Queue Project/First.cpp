

#include <iostream>
#include <bits/stdc++.h>
#include <chrono>
#include <fstream>

using namespace std;





//Driver Class
class driver{
public:
	int dId;//Driver ID
	string dName;//Driver Name
	int hrs=0;//Driver time
	float totaldpay=0;//Total driver pay
	bool inQueue;//Id driver in the queue or not?
	driver(){};
	driver(int a,string b,int c,bool d){//Parametrised Constructor
		dId=a;
		dName=b;
		hrs=c;
		inQueue=d;
	}


};






//Trip Class
class trip{
friend class driver;
public:
	std::chrono::time_point<std::chrono::high_resolution_clock> s,e;//Saves time point variable
	driver D;//Driver on the trip
	double hrs;//Time taken
	float pay;//Payment on the trip

	trip();
	trip(driver &dr,int h,float p){
		D = dr;
		hrs =h;
		pay =p;
	}

	void start(){
		 s = std::chrono::high_resolution_clock::now();//s stores time at which driver is alloted to customer
	}
	void end(){
		 e = std::chrono::high_resolution_clock::now();//e stores time at which trip ends
	}


};


vector<driver> emp;//A global list of employees
vector<trip> trips;//Global List of trips
float BasePrice=100.0;//BAse price of every trip
float conv=0.033;//Per second rate
float dr=0.4;//Driver ratio 40% --> Can be changed
float ctrevenue=0.0;//Company revenue initially





//Queue Implementation
struct QNode {//Node of Linked list
    driver data;
    QNode* next;
    QNode(driver d)
    {
        data = d;
        next = NULL;
    }
};

struct Queue {//Direct Queue Implementation
    QNode *front, *rear;//Front and rear pointers in queue
    Queue()
    {
        front = rear = NULL;//No element in queue initially
    }

    void enQueue(driver x)//Add driver to queue
    {
        QNode* temp = new QNode(x) ;//Create temperory new node

        // If queue is empty, then
        // new node is front and rear both
        if (rear == NULL) {
            front = rear = temp;
            return;
        }

        // Add the new node at
        // the end of queue and change rear
        rear->next = temp;
        rear = temp;
    }

    // Function to remove
    // a key from given queue q
    QNode* deQueue()
    {
        //If queue is empty, return NULL.
        if (front == NULL)
            return NULL;

        // Store previous front and
        // move front one node ahead
        QNode* temp = front;
        front = front->next;

        // If front becomes NULL, then
        // change rear also as NULL
        if (front == NULL)
            rear = NULL;

        return temp;
    }

		void Listdrivers(){//Helps to provide list of drivers in queue
			QNode* temp = front;
			while(temp!=NULL){
				cout<<(temp->data).dId<<"\t"<<(temp->data).dName<<"\n";
				temp=temp->next;
			}
		}


		bool isin(int n){//Is driver in queue?
			QNode* temp=front;
			while(temp!=NULL){
				if((temp->data).dId==n){return true;}
				temp=temp->next;
			}
			return false;
		}
};


//Checks if driver is even in employee list
bool drExists(int drId){bool exists=false;for (int i=0;i<emp.size();i++){if(emp[i].dId==drId){exists=true;break;}} return exists;}


//Calculates Payment of driver and company
void calculatePay(trip &T)
{T.pay=BasePrice+(T.hrs*conv);//Payment = Base + ( Time*Rate )
 T.D.totaldpay+=dr*T.pay;//Part of the trip payment for the driver
 cout<<"Total driver pay for current driver "<<T.D.totaldpay<<endl;
 ctrevenue+=(1-dr)*T.pay;}//Company revenue



int main(){//Main function

	Queue qu;//Making the Queue
	bool exists=false;
	int count=0;//Total driver count
	while(true){//Infinite loop
		cout<<"0. Load Drivers.\n1. Add driver into employee list\n2. Add driver to queue \n3. Allot driver to customer\n4. Remove driver from employee list.\n5. List drivers in emp list\n6. List drivers in queue.\n7. Driver ID returned.\n8. Exit and get Total Revenue. \n";
		int x;
		cin>>x;
		switch(x){
			case 0:{
				    ifstream fs("employee.txt",ios::out);//Opening the file as ios::out-->for reading the file
            string s;
                    while (getline(fs,s))//Reading file line by line
                    {
											istringstream ss(s);//input string stream created
											string word;
											ss >> word;//Stores id in word
											int x=stoi(word);
											ss>>word;//Stores Name in word
											string y=word;
											ss>>word;//Stores time in word
											int z=stoi(word);

											driver* DR=new driver(x,y,z,false);//Created driver object wiht these parameters
											emp.push_back(*DR);//Adds driver to employee list
											count++;
                    }
						fs.close();
				    break;

			}
			case 1:{
	        string dName;//Asks for name
	        cout<<"Enter driver name: ";
	        cin>>dName;
	        driver d = driver(count,dName,0,false);//New driver object
					count++;
	        emp.push_back(d);//Adds driver object to emp list
	        break;
				}
	        case 2:{

	        cout<<"Enter driver ID:";//Give ID of driver that is to be added into the queue
	        int drId;
	        cin>>drId;
					int i;
	        for (i=0;i<emp.size();i++){if(emp[i].dId==drId){exists=true;break;}}//Checks Id is in emp list.
					bool is=false;//If driver already in queue
					is=qu.isin(drId);//Checking duplicate driver in queue
	        if(exists&&(!is)){//Id driver in emplyee list and not in queue
	        	qu.enQueue(emp[i]);//Adds driver to queue
						emp[i].inQueue=true;//Driver is in queue so that attribute is true.
						exists=false;
	        }
					else if(is){cout<<"Driver already in queue corresponding to this driver ID."<<endl;}//Driver already in queue
	        else{
	        	cout<<"Driver doesn't exist corresponding to this driver ID."<<endl;//Driver not in employee list
	        }
	        break;
				}

	        case 3:{
						if(qu.front==NULL){exists=false;}//If no driver in queue
						else{exists=true;}
	        if(exists){//Driver in queue
	        	QNode* D = qu.deQueue();//Removes driver from queue

						exists=false;
						trip t(D->data,0,0);//trip object made
						trips.push_back(t);//Adds trip to trips vector
						trips[trips.size()-1].start();//Starts timer for the trip recently added.
	        	cout<<"Driver with ID " <<(D->data).dId <<" and name "<<(D->data).dName<<" removed from queue and alloted customer."<<endl;
						D->data.inQueue=false;
	        }
	        else{
	        	cout<<"No driver exists in the queue we are really sorry."<<endl;//No driver in Queue
	        }
					break;
				}
					case 4:{
					cout<<"Enter driver ID:"<<endl;//Takes ID
	        int drId;
	        cin>>drId;
					exists=drExists(drId);//Checks if driver ID exists in employee list
					if(exists){
						for(int i=0;i<emp.size();i++){
							if(drId==emp[i].dId){emp.erase(emp.begin()+i);break;}//Erases that driver of that ID.
						}
						cout<<"Driver removed as an employee!\n";
					}
					else{
						cout<<"Driver doesn't exist corresponding to this driver ID."<<endl;
					}
					break;
				}
				case 5:{//Display drivers in employee list
					cout<<"These are your employee drivers displayed in format(ID,NAME,Pay,No. of seconds worked today,Available):\n";
					for(int i=0;i<emp.size();i++){
						cout<<emp[i].dId<<"\t"<<emp[i].dName<<"\t"<<emp[i].totaldpay<<"\t"<<emp[i].hrs<<"\t"<<emp[i].inQueue<<"\n";
					}
					cout<<"DONE\n";
					break;
				}
				case 6:{//List drivers in queue
					cout<<"Drivers in queue are:\n";
					qu.Listdrivers();
					cout<<"DONE for queue\n";
					break;
				}

				case 7:{//Driver return from a trip
					int did;
					cout<<"Enter Driver ID of returning driver"<<endl;
					cin>>did;//Enter driver ID
					exists = false;
					int i,j;
					for(i=0;i<trips.size();i++){//Check if the driver was on a trip or not?
					if(did == ((trips[i].D).dId)){
						exists = true;
						break;
					}
				}
				for(j=0;j<emp.size();j++){//Getting driver that was on that trip
					if(emp[j].dId==did){break;}
				}
				if(exists){cout<<"Driver with the ID "<<did<<" has finished a trip\n";}
				else{"This driver was not on a trip ";}

				trips[i].end();//Stores end of the trip time stamp in trip attributes.

				auto dur = trips[i].e - trips[i].s;//Finds duration of the trip
				auto elapsed = std::chrono::duration_cast<std::chrono::duration<double>>(dur);//Converts duration in duration double format
				trips[i].hrs = elapsed.count();//Stores double value in trips time attribute.
				emp[j].hrs +=  trips[i].hrs;//Stores double value in driver's time attribute.
				cout<<"Trip was of  "<<elapsed.count()<<" seconds\n"<<endl;
				if(emp[j].hrs<28800){//Checks if driver now has less than  hrs of work today
					qu.enQueue(trips[i].D);//Adds driver back to queue
					trips[i].D.inQueue=true;
					cout<<"Driver is added to back to queue.\n";
				}
				else{cout<<"Driver has exceeded 8 hours of working time and cannot be added back to queue."<<endl;}
				calculatePay(trips[i]);//Calculates trip payment attributes

				emp[j].totaldpay+=trips[i].D.totaldpay;//Stores trip payment into emplyee pay attribute.
				(trips[i].D).dId=-1;//Indication that trip has ended
				break;
				}
				case 8:{
					ofstream fs("employee.txt",ios::out|ios::in|ios::trunc);//Open file for write operation
					for(int i=0;i<emp.size();i++){
						fs<<emp[i].dId<<" "<<emp[i].dName<<" "<<0<<endl;//
					}
					fs.close();
					cout<<"\nTotal Revenue: "<<ctrevenue;//Displays total revenue

					exit(1);
				}


					default:{
					cout<<"Unexpected argument."<<endl;
				}




		}
	}
}
