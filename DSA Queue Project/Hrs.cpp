#include <iostream>
#include <bits/stdc++.h>
#include <chrono>
using namespace std;


class driver{
public:
	int dId;
	string dName;
	int hrs;
	bool inQueue;
	driver(){};
	driver(int a,string b,int c,bool d){
		dId=a;
		dName=b;
		hrs=c;
		inQueue=d;
	}


};


class trip{
friend class driver;
public:
	std::chrono::time_point<std::chrono::high_resolution_clock> s,e;
	driver D;
	double hrs;
	float pay;

	trip();
	trip(driver dr,int h,float p){
		D = dr;
		hrs =h;
		pay =p;
	}

	void start(){
		 s = std::chrono::high_resolution_clock::now();
	}
	void end(){
		 e = std::chrono::high_resolution_clock::now();
	}


};


vector<driver> emp; //A global list of employees
vector<trip> trips;


struct QNode {
    driver data;
    QNode* next;
    QNode(driver d)
    {
        data = d;
        next = NULL;
    }
};

struct Queue {
    QNode *front, *rear;
    Queue()
    {
        front = rear = NULL;
    }

    void enQueue(driver x)
    {
        QNode* temp = new QNode(x) ;

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
        if (front == NULL)///////ISUEEEEE!!
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

		void Listdrivers(){
			QNode* temp = front;
			while(temp!=NULL){
				cout<<(temp->data).dId<<"\t"<<(temp->data).dName<<"\t"<<(temp->data).hrs<<"\t"<<(temp->data).inQueue<<"\n";
				temp=temp->next;
			}
		}
};

bool drExists(int drId){bool exists=false;for (int i=0;i<emp.size();i++){if(emp[i].dId==drId){exists=true;break;}} return exists;}

int main(){
	Queue qu;bool exists=false;int count=0;
	while(true){
		cout<<"1. Add driver into employee list\n2. Add driver to queue \n3. Allot driver to customer\n4. Remove driver from employee list.\n5. List drivers in emp list\n6. List drivers in queue.\n7. End trip for a driver.\n";
		int x;
		cin>>x;
		switch(x){
			case 1:{
	        string dName;
	        cout<<"Enter driver name: ";
	        cin>>dName;
	        driver d = driver(count,dName,0,false);count++;
	        emp.push_back(d);
	        break;
				}
	        case 2:{

	        cout<<"Enter driver ID:";
	        int drId;
	        cin>>drId;
					int i;
	        for (i=0;i<emp.size();i++){if(emp[i].dId==drId){exists=true;break;}}
	        if(exists){
	        	qu.enQueue(emp[i]);exists=false;
	        }
	        else{
	        	cout<<"Driver doesn't exist corresponding to this driver ID."<<endl;
	        }
	        break;
				}

	        case 3:{
						if(qu.front==NULL){exists=false;}
						else{exists=true;}
	        if(exists){
	        	QNode* D = qu.deQueue();exists=false;
						trip t(D->data,0,0);
						trips.push_back(t);
						trips[trips.size()-1].start();
	        	cout<<"Driver with ID " <<(D->data).dId <<" and name "<<(D->data).dName<<" removed from queue and alloted customer."<<endl;
	        }
	        else{
	        	cout<<"No driver exists in the queue we are really sorry."<<endl;
	        }
					break;
				}
					case 4:{
					cout<<"Enter driver ID:"<<endl;
	        int drId;
	        cin>>drId;
					exists=drExists(drId);
					if(exists){
						for(int i=0;i<emp.size();i++){
							if(drId==emp[i].dId){emp.erase(emp.begin()+i);break;}
						}
						cout<<"Driver removed as an employee!\n";
					}
					else{
						cout<<"Driver doesn't exist corresponding to this driver ID."<<endl;
					}
					break;
				}
				case 5:{
					cout<<"These are your employee drivers displayed in format(ID,NAME,No. of hrs worked today,Available):\n";
					for(int i=0;i<emp.size();i++){
						cout<<emp[i].dId<<"\t"<<emp[i].dName<<"\t"<<emp[i].hrs<<"\t"<<emp[i].inQueue<<"\n";
					}
					cout<<"DONE\n";
					break;
				}
				case 6:{
					cout<<"Drivers in queue are:\n";
					qu.Listdrivers();
					cout<<"DONE for queue\n";
					break;
				}

				case 7:{ //driver returns from trip
					int did;
					cout<<"Enter Driver ID of returning driver"<<endl;
					cin>>did;
					exists = false;
					int i;
					for(i=0;i<trips.size();i++){
					if(did == ((trips[i].D).dId)){
						exists = true;
						break;
					}
				}
				if(exists){cout<<"Driver with the ID "<<did<<" has finished a trip\n";}
				else{"This driver was not on a trip\n";}
				trips[i].end();
				auto dur = trips[i].e - trips[i].s;
				auto elapsed = std::chrono::duration_cast<std::chrono::duration<double>>(dur);
				// std::chrono::duration<double> elapsed = std::chrono::duration_cast<std::chrono::duration<double>>(dur);
				trips[i].hrs = elapsed.count();
				cout<<elapsed.count()<<endl;
				if(trips[i].hrs<28800){
					qu.enQueue(trips[i].D);
					cout<<"Driver added back to queue\n";
				}
				else{cout<<"Driver has exceeded 8 hours of working time"<<endl;}
				break;
			}

			case 8:{
				exit(0);
			}


				default:{
					cout<<"Unexpected argument."<<endl;
				}




		}
	}
}
