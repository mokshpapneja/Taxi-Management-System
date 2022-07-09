

#include <iostream>
#include <bits/stdc++.h>
#include <fstream>

using namespace std;


class driver{
public:
	int dId;
	string dName;
	int hrs;
	float totaldpay;
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
private:
	//driver D;
	//int hrs;
	//float pay;
public:
    float pay=0.0;
    driver D;
    int hrs;
	trip(int h){
		hrs=h;
		pay=0;
	}
	trip(driver &d,int h)
	{D=d;
	hrs=hrs;
	pay=0;}


};

vector<driver> emp;//A global list of employees
vector<trip> trips;
float BasePrice=100.0;
float conv=120;
float dr=0.4;
float ctrevenue=0.0;
fstream femp("employee.txt",ios::in | ios::out| ios::trunc );


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

void calculatePay(trip &T)
{T.pay=BasePrice+(T.hrs*conv);
 T.D.totaldpay+=dr*T.pay;
 cout<<"toatl driver pay for current driver"<<T.D.totaldpay;
 ctrevenue+=(1-dr)*T.pay;}

int main(){

	Queue qu;bool exists=false;int count=0;
	while(true){
		cout<<"0. Load Drivers.\n1. Add driver into employee list\n2. Add driver to queue \n3. Allot driver to customer\n4. Remove driver from employee list.\n5. List drivers in emp list\n6. List drivers in queue.\n7. Driver ID returned.\n8. Exit \n";
		int x;
		cin>>x;
		switch(x){
			case 0:{
				    std::fstream fs{ "employee.txt" };
                    std::string s;
                    while (fs)
                    {
                        std::getline(fs, s); // read each line into a string
                        std::cout << s << '\n';
                    }
				    break;

			}
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
	        	QNode* D = qu.deQueue();exists=false;trip t(D->data,0);trips.push_back(t);
	        	cout<<"Driver with ID " <<(D->data).dId <<" and name "<<(D->data).dName<<" removed from queue and alloted customer."<<endl;
	        calculatePay(t);}
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
					cout<<"These are your employee drivers displayed in format(ID,NAME,No. of seconds worked today,Available):\n";
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

				case 7:{
					cout<<"Enter driver ID that has returned :"<<endl;
	        int drId;
	        cin>>drId;
					exists=false;
					int i;
					for(i=0;i<trips.size();i++){
						if(drId==(trips[i].D).dId){
							exists=true;
							break;
						}
					}
					if(exists){
						cout<<"Driver with ID "<<drId<<" has returned.";
						// (trips[i].D).hrs=stop-start;
						// trips.remove(i);

					}
					else{
						cout<<"This driver wasn't on a trip.";
					}
				}
				case 8:{
					exit(1);
				}


					default:{
					cout<<"Unexpected argument."<<endl;
				}




		}
	}
}
