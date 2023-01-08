#include<iostream>
#include<cmath>
#include<cstring>
#include<time.h>
#include<Windows.h>//for text/background coloring
using namespace std;


//initalization data
int N,X,C,R,V;
int min_speed = 1, max_speed = 6;
double p = 1,p1 = 1, p2 = 1,ptemp = 1;
int T,T1,T3;

//to store the state of different users
struct user{
   int state;
   int x,y;   
   bool mask;
};

//prototypes
char BasicalInput();
void SetColorAndBackground(int,int);
void DataOutput();
void distance(int* ,int,user[]);
char LatterInput();
void AddInput(user []); 
 
//direction array
int direction[2][4] = {
	{-1,1,0,0},
	{0,0,-1,1}
};

int main(){
//set basical variables
    char choice;
    choice = BasicalInput(); 
    srand(time(0));
    user u[N+5];
    const int length = X+5;
    int area[length][length] = {0};

//initalize users' status and location    
    for(int i = 1;i <= N;i++){
    	u[i].mask = false;
    	u[i].x = rand()%X+1;
    	u[i].y = rand()%X+1;
    	if(area[u[i].x][u[i].y] != 0){
    		i--;
    		continue;
		}
        if(i <= R){
		    u[i].state = 1;
		    area[u[i].x][u[i].y] = 1;
		}
		
    	else if ((i > R)&&(i <= R+V)){
		    u[i].state = 2;
		    area[u[i].x][u[i].y] = 2;
		}
    	else {
		    u[i].state = 3;
		    area[u[i].x][u[i].y] = 3;
		}
    	
	}

  //for the additional functions
	AddInput(u);

//The first output    
  //to display thr graph
    if(choice != '2'){
    	cout << endl;
    	cout << "The initialization grph is as follows: " << endl;
    	for(int i = 1;i <= X;i++){
	    	for(int j = 1;j <= X;j++){
	    		if(area[i][j] == 1){
	    			SetColorAndBackground(7,4);
	    			cout <<" ";
				}
				else if(area[i][j] == 2){
	    			SetColorAndBackground(7,2);
	    			cout << " ";
				}
				else if((area[i][j] == 3)){
	    			SetColorAndBackground(7,6);
	    			cout << " ";
				}
				else{
					SetColorAndBackground(4,7);
	    			cout << " ";
				}
			}
			SetColorAndBackground(7,0);
		    cout << endl;
	    } 
	}

  //to display the data
	if(choice != '1'){
		cout << endl;
    	cout << "The initialization data is as follows: " << endl;
    	DataOutput();
	}

//for the subsequent input and output updates
    int time;
    char choice2;
    do{
    	choice2 =  LatterInput();
    	if(choice2 == '1'){
    		
    		cout << endl;
    		cout << "The users randomly walk, or walk along straight lines (The speed we set is between 1 and 6 meter every minute, you can set it by yourself )" << endl;
    		cout << endl;
    		cout << "After how long time(minute(s)) do you want to see the change: ";
			cin >> time;
			bool flag2 = false; 
	    		
	    		 
    		for(int j = 1;j <= N;j++){
    		  //"straight" can dicide randomly walk or walk along straight lines 
    			int straight = rand()%2;
    			int dir = rand()%4;
    			for(int i = 1;i <= time;i++){
    		        distance(&area[0][0],N,u);
    			    int temp1 = u[j].x,temp2 = u[j].y;
    			    area[u[j].x][u[j].y]= 0;
	    			do{
	
	    				bool flag2 = false;
	    				u[j].x = temp1;
	    				u[j].y = temp2;
	                 
					 //for walk along straight lines   
					    if(straight == 0) dir = rand()%4;
					    
					  //for randomly walk
						else{
							if(dir == 1 || dir == 0){
								dir = rand()%2;
							}
							else{
								dir = rand()%2+2;
							}
						}	
					  //"step" defaults to 1~6, which can be adjusted by additional functions					
					    int step = rand()%(max_speed-min_speed+1)+min_speed;
					    u[j].x += (direction[0][dir])*step;
					    u[j].y += (direction[1][dir])*step;
					    if(area[u[j].x][u[j].y] == 0){
					        area[u[j].x][u[j].y]= u[j].state;
					        flag2 = true;
					    }			
						
					  //in case the users don't cross the line    
	                   if(!(((u[j].x < 1)|| (u[j].y > X )|| (u[j].y < 1))||(!flag2))) break;
					}while(true);
    				
			    }
		    }
        
		  //to update the number of the contagious users
            R = 0;
			for(int i = 1;i <= N;i++){
				if(u[i].state == 1){
					R++;
					area[u[i].x][u[i].y] = 1;
				}
			}

	  //for the subsequent output
          //to display thr graph
			if(choice != '2'){
				cout << endl;
		    	cout << "The next grph is as follows: " << endl;
		    	for(int i = 1;i <= X;i++){
			    	for(int j = 1;j <= X;j++){
			    		if(area[i][j] == 1){
			
			    			SetColorAndBackground(7,4);
			    			cout <<" ";
						}
						else if(area[i][j] == 2){
			    			SetColorAndBackground(7,2);
			    			cout << " ";
						}
						else if((area[i][j] == 3)){
			    			SetColorAndBackground(7,6);
			    			cout << " ";
						}
						else{
							SetColorAndBackground(4,7);
			    			cout << " ";
						}
					}
				SetColorAndBackground(7,0);
				cout << endl;
			    } 
			}

		  //to display thr data
			if(choice != '1'){
				cout << endl;
    	        cout << "The next data is as follows: " << endl;
    	        DataOutput();
			}
	    }
	    else{
	    	cout << endl;
	    	cout <<" Welcome to use our simulator next time!!! " << endl;
	    	break;
		}

	  //to terminate this program
		if(R+V == N){
			cout << "Oh no! Anyone who hasn't been vaccinated has been infected." << endl;
			cout << endl;
			cout << " Welcome to use our simulator next time!!! " << endl;
			break;
		}
	}while(true);

    return 0;
}

//to remind the scientists to enter the basic information of the simulator
char BasicalInput(){
	cout << "Welcome to use our simulator!!!" << endl;
	cout << endl;
  //the basic menu 
	cout << "What function do you want?" << endl;
	cout << "(1) Graph display " << endl;
	cout << "(2) Data display" << endl;
	cout << "(3) Both" << endl;
	cout << endl;
  //the choice	
	char input1[1000];
    cout << "Please enter your choice (1,2 or 3): ";
    cin >> input1;
    
  //when the scientist enters a false answer  
    while(((input1[0] <'1')||(input1[0] >'3'))||(strlen(input1) > 1)){
    	cout << endl;
	    cout << "Error! Please enter your choice (1,2 or 3) again: ";
        cin >> input1;
    }
    cout << endl;
    cout << "input panel: " << endl;
    
  //N
	cout << "Please enter the number of users: ";
    cin >> N;  
    cout <<endl;
  
  //X
    cout << "Reminder: because of the limitation of screen size,  the input value of the \"distance(meters) when two users move closer, the virus can transmit to another user\" should no more than 700" << endl;
    cout << endl;
    
    cout <<"Please enter the side length(meters) of the area which the users can move: ";
    cin >> X;
    
	while(X > 700){
		cout << endl;
		cout << "Sorry! Please enter a number which is no more than 700!" << endl;
		cout <<"Please enter the side length(meters) of the area which the users can move: ";
		cin >> X;
	}

  //C
    cout << "Please enter the distance(meters) when two users move closer, the virus can transmit to another user: ";
    cin >> C;
    
  //R
    cout << "Please enter the number of contagious users: ";
    cin >> R;
  //V
    cout << "Please enter the number of vaccinated users: ";
    cin >> V;
  //when the number of users is wrong
    if(R+V > N){
    	cout << "Sorry! the sum of contagious and vaccinated users are bigger than the number of users! " << endl;
    	cout << "Please enter the data again." << endl;
    	cout << endl;
    	cout << endl;
    	input1[0] = BasicalInput(); 
	}
	return input1[0];
}

//to set different color of the graph display
void SetColorAndBackground(int ForgC,int BackC){
	WORD wColor = ((BackC & 0x0F) << 4)+(ForgC & 0x0F);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),wColor);
	return;
}

//to display the related data
void DataOutput(){
	cout << endl;
	cout << "The number of users: ";
	cout << N << endl;
	cout << "The number of contagious users: ";
	cout << R << endl;
	cout << "The number of vaccinated users: ";
	cout << V << endl; 
	return;
}

//to make the users infect when they are too close to the contagious users
void distance(int *ptr ,int n,user u[]){
	int distance1;
	bool flag = false;
	while(!flag){
		flag = true;
	    for(int i = 1;i <= n;i++){
	    	for(int j = i+1;j <= n;j++){
	    	//to compute the distance
	    		distance1 = sqrt(pow(u[i].x-u[j].x,2)+pow(u[i].y-u[j].y,2));
	    		if((distance1 <= C)&&(u[i].state != 2)&&(u[j].state != 2)){
	    			if((u[i].state == 1&&u[j].state == 3)||(u[j].state == 1&&u[i].state == 3)){
	    			
					// some of the parameters are used for the other functions
	    				if(u[i].mask == true&& u[j].mask==true) p = p2;
	    				else if(u[i].mask == true || u[j].mask==true) p = p1;
	    				p = p*1000000;
	    				int k = rand()%999999+1;
	    				if(k <= p){
						    u[j].state = 1;
						    u[i].state = 1;
						    flag = false; 
					    }
					}
				}
				p = ptemp;
			}
		}
    }
    return; 
}

//to ask if the user want to continue after each cycle
char LatterInput(){
	cout << endl;
	cout << endl;
	cout <<" What do you want to do next? " << endl;
	cout << "(1) Observing the next change of the graph or the data" << endl;
	cout << "(2) Abandoning this simulation" << endl;
	cout << endl;
	char input1[1000];
    cout << "Please enter your choice (1 or 2): ";
    cin >> input1;
    while(((input1[0] <'1')||(input1[0] >'2'))||(strlen(input1) > 1)){
    	cout << endl;
	    cout << "Sorry! Please enter your choice (1 or 2) again: ";
        cin >> input1;
    }
	return input1[0];
}

//to enter the data of the additional functions
void AddInput(user u[]){
	cout << endl;
	char answer;
	cout << " Do you want to add other variables(y or n)? ";
	cin >> answer;
	bool choice[10];
	char choose[10];
	for(int i = 0;i < 5;i++){
		choice[i] = false;
	}
	if(tolower(answer) == 'y'){
		
	    cout << endl;
	    
	//the additional menu
	    cout << "(1) Walking speed" << endl; 
	    cout << "(2) Possibility of virus transmission within " << C << " meters" << endl;
	    cout << "(3) The number of users wearing masks" << endl;
	    cout << "......" << endl;
	    cout << "We are still developing other functions" << endl;
	    do{
			cout << endl;
		    cout << "What variables do you want(If you want to choose more than one answer, like choosing (1), (2) and (3), you should input 123 )? ";
	        cin >> choose;
	        int len = strlen(choose);
	        bool flag = false;
	        for(int i = 0;i < len;i++){
	        	if(choose[i]-48 > 3 || choose[i]-48 < 0){
	        		cout << endl;
	        		cout << " Error! Please enter you choice again." << endl;
	        		flag = true;
	        		break;
				}
				else{
					choice[choose[i]-49] = true;
				}
			}
			if(!flag) break;
			    
	    }while(true);
	    
    }
    
  //for the choice 1, (1) Walking speed
    if(choice[0]){
    	cout << endl;
		cout << "Now, the minimum speed is " << min_speed << ", the maximum speed is " << max_speed << endl;
    	cout << "Reminder: If the maximum speed is too high, the simulator may break down." << endl;
    	do{cout << "Please enter the minimum speed(meter/minute): ";
    	cin >> min_speed;
    	cout << "Please enter the maximum speed(meter/minute): ";
    	cin >> max_speed;
    	if(max_speed >= min_speed){
    		break;
		}
		cout << "Sorry! The maximum speed you input is less than the minimum speed. Please enter the data again." << endl;
		cout << endl;
	    }while(true);	
	}
	
  //for the choice 2, (2) Possibility of virus tranmission within C meters
	if(choice[1]){
		do{
			cout << endl;
			cout << "Please enter the possibility of virus transmission within " << C << " meters(a decimal from 0 to 1, not a fraction): ";
			cin >> p;
			if(p <= 1 && p >= 0 ){
	    		break;
			}
			cout << "Sorry! Your possibility is not between 0 and 1, please enter the data again." << endl;
			cout << endl;
	    }while(true);
	    ptemp = p;
	}
	
  //for the choice 3, (3) The number of users wearing masks
	if(choice[2]){
		
		do{
			
		  //for the total number of users wearing masks
			cout << endl;
			cout << "There are now " << N << " users. " << endl;
			cout << "Please enter the total number of users wearing masks: ";
			cin >> T;
			if(T > N){
				do{
					cout << endl;
					cout << "Sorry! This number is too large, please enter the number of contagious users wearing masks again: ";
					cin >> T;
				}while(T1 > N);
			}
			
		  //for the number of contagious users wearing masks
			cout << endl;
			cout << "There are now " << C << " contagious users. " << endl;
			cout << "Please enter the number of contagious users wearing masks:  ";
			cin >> T1;
			if(T1 > C){
				do{
					cout << endl;
					cout << "Sorry! This number is too large, please enter the number of contagious users wearing masks again: ";
					cin >> T1;
				}while(T1 > C);
			}
			for(int i = 1;i <= T1;i++){
				int ran = rand()%C+1;
				if(u[ran].mask == true){
		    		i--;
		    		continue;
				}
				u[ran].mask = true; 
			}
			cout << endl;
			cout << "There are now " << N-C-R << " users who are neither vaccinated nor contagious. " << endl;
			cout << "Please enter the number of users who are neither vaccinated nor contagious wearing masks:  ";
			cin >> T3;
		 	if(T3 > N-C-R){
			do{
				cout << endl;
				cout << "Sorry! This number is too large, please enter the number of users who are neither vaccinated nor contagious wearing masks again: ";
				cin >> T3;
			}while(T3 > N-C-R);
			}
			for(int i = 1;i <= T3;i++){
				int ran = rand()%(N-C-R)+C+R+1;
				if(u[ran].mask == true){
		    		i--;
		    		continue;
				}
				u[ran].mask = true; 
			}
			if(T-T1-T3 > V){
				cout << endl;
				cout << "Sorry! The number of vaccinated users who wear masks is too large, please enter again." << endl;
			}
		}while(T-T1-T3 > V);
		
	  //two related possibilities 
		do{
			cout << endl;
			cout << "Please enter the possibility of virus tranmission if one side takes a mask(a decimal from 0 to 1, not a fraction): ";
			cin >> p1;
			if(p1 <= 1 && p1 >= 0 ){
		    		break;
				}
				cout << "Sorry! Your possibility is not between 0 and 1, please enter the data again." << endl;
				cout << endl;
	    }while(true);
	    do{
			cout << endl;
			cout << "Please enter the possibility of virus tranmission if both sides take a mask(a decimal from 0 to 1, not a fraction): ";
			cin >> p2;
			if(p2 <= 1 && p2 >= 0 ){
		    		break;
				}
				cout << "Sorry! Your possibility is not between 0 and 1, please enter the data again." << endl;
				cout << endl;
	    }while(true);
		
	}
	return;
}
