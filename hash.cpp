#include <iostream>
#include <fstream> 
#include <vector>
#include <sstream>
#include <cstdlib>
#include <iomanip>
//Guixu Li\ligui@oregonstate.edu\933948526
//Chih-hao, Feng\fengchi@oregonstate.edu\933956498
 
using namespace std;
int n_prefix = 2; //the number of prefix
int i_prefix = 1; //Show prefix the number of digits in a table
int total_size = 0; //total_size of all the data have been read.
int block_cap = 4096;
int the_cap;
int mask;
int bin_result;
int bin;
float s;
int temp_data_size;
string bin_temp;
int c = 0;
int counter;
int f_counter;
int searchwhat;
vector<vector<string> > data(2);
 
int exponential(int i)
{
	int product = 2;
	if (i == 1)
	{
		return product;
	}else{
		for (int j = 1; j < i; j++)
		{
			product *= 2;
		}
	}
	return product;
}
void create(){
	//Read File
	ifstream inFile("Employee.csv",ios::in);
	string line;//get every line strings
	vector<vector<string> > data_Array;
	while(getline(inFile,line)) 
	{	
		//get string by line
		stringstream ss(line);
		string str;
		vector<string> line_Array;
		//get string by ","
		while(getline(ss,str,','))
		{
			line_Array.push_back(str);
		}
		data_Array.push_back(line_Array);
	}
	//int temp_size;

	//Set a 2D array store Prefix and Block, <2 rows>
	int size = data_Array.size() - 1;
	for (int i = 1; i <= size ; i++)
	{
		bin_temp = data_Array[i][0];
		bin = atoi(bin_temp.c_str());
		mask = exponential(i_prefix) - 1;
		bin_result = bin & mask;
	
		if (bin_result > (n_prefix-1))
		{
			//cout<<"here"<<endl;
			int temp_i = i_prefix - 1;
			mask = exponential(temp_i) - 1;
			bin_result = bin & mask;
		}
		total_size += 8+8+data_Array[i][1].size()+data_Array[i][2].size();

		//cout<<"size is:"<<total_size<<endl;
		//cout<<"total_size: "<< total_size <<endl;
		the_cap =  n_prefix * block_cap;

		s = total_size*100/the_cap;
		//cout<<"商:"<<s<<endl;
		if (s <= 80)
		{//if less than 80%, insert safely.
			for (int z = 0; z < 4; z++)
			{	//cout<<"is here qian"<<endl;
				data[bin_result].push_back(data_Array[i][z]);
				//cout<<"is here hou"<<endl;
				c++;
				//cout<<"the counter of add function is:"<<c<<endl;
			}
		}else{
			n_prefix = n_prefix+1;
			if (n_prefix > (exponential(i_prefix)))
			{
				i_prefix = i_prefix+1;
			}

			the_cap = block_cap * n_prefix;
			//cout<<"新的总block大小："<<the_cap<<endl;
			//temp_data_size = data.size();
			//cout<<"temp_data_size is:"<<temp_data_size<<endl;
			counter = (c/4) + 1;

			//cout<<"-------------------------total count of the whole 2D array is:"<<counter<<endl;
			vector<string> useless;//keep the 2D vector the same structure
			data.resize(n_prefix,useless);
			vector<vector<string> > data_temp(n_prefix);
			//reorder
			for (int o = 1; o <= counter; o++)
			{
				//cout<<"o is:"<<o<<endl;
				//cout<<"size is:"<<size<<endl;
				bin_temp = data_Array[o][0];
				//cout<<"bin_temp:"<<bin_temp<<endl;
				bin = atoi(bin_temp.c_str());
				mask = exponential(i_prefix) - 1;
				//cout<<"mask:"<<mask<<endl;
				bin_result = bin & mask;
				//cout<<"bin_result:"<<bin_result<<endl;
                
				if (bin_result > (n_prefix-1))
				{
					//cout<<"here"<<endl;
					int temp_i = i_prefix - 1;
					mask = exponential(temp_i) - 1;
					bin_result = bin & mask;
				}
				for (int z = 0; z < 4; z++)
                {
                	//cout<<"else-for-here"<<endl;
                	//cout<<"data is"<<data_Array[o][z]<<endl;
                    data_temp[bin_result].push_back(data_Array[o][z]);
                }
                //cout<<"temp table is"<<endl;
			}
			c = c + 4;
			data = data_temp;
			}			

	}
	// cout<<"final table is"<<endl;
	// for (int u = 0; u < data.size(); u++)
	// {
	// 	for (int y = 0; y < data[u].size(); y++)
	// 	{
	// 		cout<<data[u][y]<<" ";

	// 	}
	// 	cout<<endl;
	// }
	
	//Write File
	ofstream outFile;
	outFile.open("EmployeeIndex.csv",ios::out);
	outFile<<"This is the hash index table made by Guixu Li and Chih-hao Feng"<<endl;
	outFile<<"General information is:"<<endl;
	outFile<<"The 'i' is:"<<i_prefix<<endl;
	outFile<<"The 'n'(number of blocks) is:"<<n_prefix<<endl;
	outFile<<"index"<<','<<"block"<<endl;

	for (int k = 0; k < data.size(); k++)
	{
		//outFile<<"Block:"<<n_prefix<<endl;
		
		outFile<<"index :";

		for (int i = (i_prefix-1);i>=0;i--)  
		{  
			outFile<<((k>>i)&1);  
		}  
		outFile<<',';

		for (int h = 0; h < data[k].size(); h++)
		{
			outFile<<data[k][h]<<',';
		}
		outFile<<endl;
	}


}
void search(int value){
	//cout<<"i_prefix:"<<i_prefix<<endl;
	mask = exponential(i_prefix) - 1;
	//cout<<"mask:"<<mask<<endl;
	bin_result = value & mask;
	//cout<<"bin_result:"<<bin_result<<endl;
	if (bin_result > (n_prefix-1))
	{
		//cout<<"here"<<endl;
		int temp_i = i_prefix - 1;
		mask = exponential(temp_i) - 1;
		bin_result = bin & mask;
	}
    int id = 0;
    while (1) {
        string temp = data[bin_result][id];
        int size;
        int temp_value = atoi(temp.c_str());
        size = data[bin_result].size();
        if (value == temp_value) {
            cout<<"The information of the person you search is:";
            cout<<" ID:"<<data[bin_result][id];
            cout<<" Name:"<<data[bin_result][id+1];
            cout<<" Bio:"<<data[bin_result][id+2];
            cout<<" ManagerID:"<<data[bin_result][id+3]<<endl;
            break;
        }else{
            if (id<size) {
                id += 4;
            }
            else{
                cout<<"The person you want to find is not in this database!"<<endl;
                break;
            }
        }
    }
//	if(bin_result < n_prefix){
//	cout<<"found the data in "<<bin_result<<"block"<<endl;
//	}

}
void user_interface()
{
	while(1)
	{
		cout<<"+--------------------------------------------------------+"<<endl;
		cout<<"|This is a Linear_hash_table_query_Software              |"<<endl;
		cout<<"|--------------------------------------------------------|"<<endl;
		cout<<"|!Before u choose Lookup function, u need to run C first!|"<<endl;
		cout<<"|--------------------------------------------------------|"<<endl;
		cout<<"|Enter 'C' to create hash index table                    |"<<endl;
		cout<<"|Enter 'L' to enter Lookup function                      |"<<endl;
		cout<<"|--------------------------------------------------------|"<<endl;
		cout<<"|If u want to exit the software just press 'Ctr+C'       |"<<endl;
		cout<<"+--------------------------------------------------------+"<<endl;
		char input;
		cin>>input;

		if (input == 'C')
		{
			cout<<"The letter u input is:"<<input<<". The Function is Create."<<endl;
			create();
			cout<<"++++----------------------------------------------++++"<<endl;
			cout<<"++++----------------------------------------------++++"<<endl;
			cout<<"||||You have already create a hash index table!   ||||"<<endl;
			cout<<"||||You can use 'Lookup' Function now!            ||||"<<endl;
			cout<<"++++----------------------------------------------++++"<<endl;
			cout<<"++++----------------------------------------------++++"<<endl;
			 
		}else if(input == 'L')
		{
			cout<<"The letter u input is:"<<input<<". The Function is Lookup."<<endl;
            cin>>searchwhat;
			search(searchwhat);

		}else{
			cout<<"You enter the illegal letter!!!!!!!!!!!!!!!"<<endl;
		}
	}
}
int main()
{
	user_interface();
}
