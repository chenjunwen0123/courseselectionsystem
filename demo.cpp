#include<fstream>
#include<iostream> 
#include<cstdio>
#include<vector>
#include<string.h>
#include<algorithm>
#include<time.h> 


using namespace std;
vector <int> empty;   //���õĶ���ѧ�Ŵ���� 
vector <int> empty_CourseNum;
int savecount = 0;
class Student{       //ѧ�� 	
	public:
		static int count;
		int id;           //ѧ�� 
		string name;      //���� 
		string faculty;   //Ժϵ 
		string gender;    //�Ա� 
		int age;          //���� 
		
		Student(){}  
		Student(string _name,string _faculty,string _gender,int _age):
				name(_name),faculty(_faculty),gender(_gender),age(_age){
				if(empty.size() == 0){
					id = ++count;
				}else{
					int size = empty.size();
					id = empty[size - 1];
					empty.erase(empty.begin() + size - 1);
				}
		}
		
		Student(const Student & sam){
			id = sam.id;
			name = sam.name;
			faculty = sam.faculty;
			gender = sam.gender;
			age = sam.age;
		}
		
		~Student(){}
		
		friend ostream & operator<<(ostream & os, const Student& stud){
			string str_id = to_string(stud.id);
			while(str_id.size() < 4){
				str_id = "0" + str_id;
			}
			os << "ѧ�ţ�"<<str_id<<endl
			   << "������"<<stud.name<<endl
			   << "�Ա�"<<stud.gender<<endl
			   << "���䣺"<<stud.age<<endl
			   << "Ժϵ��"<<stud.faculty<<endl;
			return os; 
		}
				
		
};
int Student::count = 0;
class Course{       //�γ� 
	public:
		static int count;
		int Course_Num;
		string Course_Name;
		string Prior_Course;
		int Credit;
		
		Course(){}
		Course(string _name,string _pri,int _credit):Course_Name(_name),Prior_Course(_pri),Credit(_credit){

			if(empty_CourseNum.size() == 0)
				Course_Num = ++count; 
			else{
				int size = empty_CourseNum.size();
				Course_Num = empty_CourseNum[size - 1];
				empty_CourseNum.erase(empty_CourseNum.begin() + size - 1);
			}
		} 
		
		Course(const Course & c){
			Course_Num = c.Course_Num;
			Course_Name = c.Course_Name;
			Prior_Course = c.Prior_Course;
			Credit = c.Credit;
		}
		~Course(){}		
		
		friend ostream & operator<< (ostream & os, const Course &course){
			os << "�γ̱�ţ�"<<course.Course_Num<<endl
			   << "�γ����֣�"<<course.Course_Name<<endl
			   << "���пγ̣�"<<course.Prior_Course<<endl
			   << "ѧ�֣�"<<course.Credit<<endl; 
			return os; 			
		}
		
}; 
int Course::count = 0;
vector <Course>  cor;  	//�γ̱�
class Point{        //ѧ���Ŀγ�ѧϰ��� 
	public:
		int id;
		int num;    // �γ̺� 
		double score;  // ����/ѧ�� 
		Point(){}
		Point(int _id,int _num,double _score ):id(_id),num(_num),score(_score){}
		~Point(){};
		friend ostream &operator<< (ostream &os, const Point &point){
			int credit; 
			for(Course p:cor)
				if(p.Course_Num == point.num)
					credit = p.Credit;
			os << "ѧ����ţ�"<<point.id<<endl
			   << "�γ̱�ţ�"<<point.num<<endl
			   << "ѧ���ɼ���"<<point.score<<" / "<<credit<<endl;
			return os; 				
		}
		
};

vector <Student> stu;    			//ѧ���� 
vector <Point>   poi;               //�ɼ��� 

/*ѧ�������*/
Student inStu(){				    //����ѧ����Ϣ 
	string name,faculty,gender;
	int age;
	
	cout<<"������ѧ��������"; 
	cin>>name;
	cout<<"����������Ժϵ��"; 
	cin>>faculty;
	cout<<"������ѧ���Ա�";
	cin>>gender;
	cout<<"������ѧ�����䣺";
	cin>>age;


	Student test(name,faculty,gender,age);
	return test;
}
void query_Stu(){          			//��ѧ��  ,methon: 1.ѧ��ƥ�� 2.����ƥ�� 3.�Ա�ƥ�� 4.Ժϵƥ�� 
	cout<<"**********************"<<endl;
	cout<<"*   ��ѡ���ѯ����   *"<<endl
		<<"*     1.ѧ��ƥ��     *"<<endl
		<<"*     2.����ƥ��     *"<<endl
		<<"*     3.�Ա�ƥ��     *"<<endl
		<<"*     4.Ժϵƥ��     *"<<endl
		<<"**********************"<<endl;
	int method;
	string ans;
	cin>>method;
	cout<<"����ƥ��ֵ:";
	cin>>ans;
	
	switch(method){ 
		case 1:
			for(Student prop:stu){
				if(prop.id == atoi(ans.c_str()))
					cout<<prop<<endl;
			}
			break;
		case 2:
			for(Student prop:stu){
				if(prop.name == ans){
					cout<<prop<<endl;
				}
			}			
			break;
		case 3:
			for(Student prop:stu){
				if(prop.gender == ans){
					cout<<prop<<endl;
				}
			}			
			break;
		case 4:
			for(Student prop:stu){
				if(prop.faculty == ans){
					cout<<prop<<endl;
				}
			}	
			break;
	}
} 
Student * queryStu_byID(int id){
	for(int i = 0;i < stu.size(); ++i){
		if(stu[i].id == id)
			return &stu[i];
	}
}
void del_Stu(int id){           	//ͨ��idɾ��ѧ�� 
	for(int i = 0;i<stu.size();++i)
		if(stu[i].id== id)
		{
			stu.erase(stu.begin() + i);
			empty.push_back(id);
			cout<<"ɾ�����"<<endl;
			//ɾ��ѧ���ɼ� 
			for(int j = 0;j<poi.size();++j){
				if(poi[j].id == id){
					poi.erase(poi.begin() + j);
				}
			}			
		}

} 
void edit_Stu(){               		//ͨ��id�޸�ѧ����Ϣ 
	int id;
	cout<<"��������޸�ѧ����ѧ�ţ�";
	cin>>id;
	Student * p = queryStu_byID(id);
	
	cout<<"1.�޸�����  2.�޸�Ժϵ"<<endl;
	int choice;
	string temp;
	cin>>choice;
	cout<<"��ϣ������Ϊ��";
	cin>>temp;
	switch(choice){
		case 1:
			p->name = temp;
			break;
		case 2:
			p->faculty = temp;
			break;
	}
	cout<<"�������"<<endl; 
}

/*�γ̱����*/
void inCor(){						//�����γ���Ϣ 
	int credit;
	string name,prior;
	
	cout<<"�¿γ�����";
	cin>>name;
	cout<<"���пγ̣�";
	cin>>prior;
	cout<<"ѧ�֣�";
	cin>>credit;
	Course test(name,prior,credit);
	cor.push_back(test);
	cout<<"��ӳɹ�"<<endl;
}
void query_Course(){         		//���ݿγ̱�Ų�γ� 
	int num;
	cout<<"���������ѯ�γ̵Ŀγ̱��:";
	cin>>num;
	int i;
	for(i =0;i<cor.size();++i){
		if(cor[i].Course_Num == num){
			cout<<cor[i]<<endl;
			cout<<"��ѯ�ɹ�"<<endl;
			break;
		}
	}
	if( i == cor.size()){
		cout<<"δ���ҵ�����"<<endl;
	} 
	
} 
void edit_Course(){         		//�޸Ŀγ���Ϣ 
	int num;
	cout<<"��������޸Ŀγ̵Ŀγ̱�ţ�";
	cin>>num; 
	for(Course prop:cor){
		if(prop.Course_Num == num){
			
			cout<<"1.�޸Ŀγ�����  2.�޸��ȵ��γ� 3.�޸�ѧ��"<<endl;
			int choice;
			cin>>choice;
			
			if(choice == 3){
				int p;
				cin>>p;
				prop.Credit = p;
			}else{
				string temp;
				cin>>temp;
				if(choice == 1)
					prop.Course_Name = temp;
				else
					prop.Prior_Course = temp;
			}
			cout<<"�޸ĳɹ�"<<endl; 
			break;
		}
	}
	
} 
void del_Course(){         			//ɾ���γ���Ϣ 
	cout<<"�������ɾ���γ̵Ŀγ̱��:";
	int num;
	cin>>num;
	for(int i = 0; i < cor.size();++i){
		if(cor[i].Course_Num == num){
			cor.erase(cor.begin() + i);
			empty_CourseNum.push_back(num);
			for(int j = 0;j<poi.size();++j){         //�γ̶�Ӧ�ĳɼ�Ҳɾ�� 
				if(poi[j].num == num){
					poi.erase(poi.begin() + j);
				}
			}
			break;
		}
	}
} 

/*�ɼ������*/
void inPoint(){                     //����ɼ� 
	cout<<"��������ѧ�ţ��γ̱�����Ӧ�ɼ����ÿո����:";
	int id,num,score;
	cin>>id>>num>>score; 
	
	for(Student st:stu){          //��id�Ƿ���� 
		if(st.id == id){          
			for(Course les:cor){  //�ҿγ̺��Ƿ���� 
				if(les.Course_Num == num){
					while(les.Credit < score){      //�ɼ�����ѧ�� 
						cout<<"�ɼ�������󣨴��ڸÿγ�ѧ�֣������������룺";
						cin>>score;							
					}
						Point p(id,num,score);
						poi.push_back(p);
					return;
				}
			}
			cout<<"error:�Ҳ�����ؿγ�"<<endl;
		}
	} 
	cout<<"error:û�и�ѧ������Ϣ"<<endl; 
}
void del_Score(){   				//ɾ���ɼ� 
	int id,num;
	cout<<"����������Ҫɾ���Ķ���� ѧ����γ̱�ţ��ÿո������";
	cin>>id>>num;
	for(int i = 0;i<poi.size();++i){
		if(poi[i].id == id && poi[i].num == num){
			poi.erase(poi.begin() + i);
			cout<<"ɾ���ɹ���"<<endl;
			break;
		}
	}
}
void edit_Score(){    				//���ĳɼ� 
	int id,num;
	cout<<"����������Ҫ���ĵĶ���� ѧ����γ̱�ţ��ÿո������";
	cin>>id>>num;
	for(int i = 0;i<poi.size();++i){
		if(poi[i].id == id && poi[i].num == num){
			double newScore;
			cout<<"������ѧ��Ϊ "<<id<<" ��ѧ���γ̱��Ϊ "<<num<<" ���³ɼ���"; 
			cin>>newScore;
			poi[i].score = newScore;
			return;
		}
	}
	
	cout<<"�鲻�������Ϣ���������������Ƿ����"<<endl;
}	
bool scorelistRule(const Point &p1, const Point &p2){
	return p1.score > p2.score;
}
void swap(int &a,int &b){
	int temp = a;
	a = b;
	b = temp;
}
void query_Score(){     							//��ɼ� 
	int id,num,choice;
	cout<<"**********************"<<endl;
	cout<<"*   ��ѡ���ѯ����   *"<<endl
		<<"*  1.�γ̳ɼ�������  *"<<endl
		<<"*  2.ѧ�����γ̳ɼ�  *"<<endl
		<<"*  3.ѧ��ȫ�γ̳ɼ�  *"<<endl
		<<"*     4.���гɼ�     *"<<endl
		<<"**********************"<<endl;
	cin>>choice;	
	vector<Point> target;	
	switch(choice){
		case 1:			
			int courseNum,count;
			cout<<"���������ѯ�γ̵Ŀγ̱�ţ�";
			cin>>courseNum;		
			for(int i = 0; i < poi.size() ; ++i){
				if(poi[i].num == courseNum)
					target.push_back(poi[i]);	
			}
			sort(target.begin(),target.end(),scorelistRule);
			for(int j = target.size(),rank = 1;j > 0; --j,++rank){
				cout<<"��"<<rank<<"λ:"<<endl<<target[j]<<endl;
			} 
			break;
		case 2:
			int tmp;
			cout<<"������ѧ����id:"; 
			cin>>id;
			cout<<"�������ѯ�Ŀγ�:";
			cin>>num;
			for(int i = 0;i<poi.size();++i){
				if(poi[i].id == id && poi[i].num == num){
					cout<<poi[i]<<endl; 
					tmp = i;
					break;
				}
			}
			cout<<"��ѯ���"<<endl;
			if(tmp == poi.size())
				cout<<"�鲻�������Ϣ���������������Ƿ����"<<endl;
			
			break;
		case 3:
			cout<<"����ѧ����id:";
			cin>>id;
			for(int i =0;i<poi.size();++i){
				if(poi[i].id == id){
					cout<<"�γ̱�ţ�"<<poi[i].num<<"  �ɼ���"<<poi[i].score<<endl; 
				}					
			}
			cout<<"��ѯ��ϣ�"<<endl;
			break;
		case 4:
			for(int i = 0;i<poi.size();++i){
				cout<<poi[i]<<endl;
			}
			cout<<"����Ϊ���гɼ�"<<poi.size()<<endl;
			break;
	}
}

/*�ļ�����*/
int read_to_stu(int m){             	 		//��ȡѧ������ 
	ifstream fin("student.txt");
	if(!fin){
		cout<<"��ȡѧ����Ϣʧ��"<<endl;
		return 0;
	}
	int size = stu.size();
	for(int i = 0; i < m; ++i){
//		Student test("temp","temp","temp",0);
//		stu.push_back(test);	 
		if(size == 0){
			int id,age;
			string name,gender,faculty;
			fin >> id >> name >> gender >> age >> faculty;
			Student test(name,faculty,gender,age);
			stu.push_back(test);
			stu[i].id == id;
		}else
			fin >> stu[i].id >> stu[i].name >> stu[i].gender >> stu[i].age >> stu[i].faculty;
	}
	
	fin.close();
	cout<<"��ȡѧ����Ϣ���"<<endl;
	return 1;
	
}
bool stuCpRule(const Student&a1,const Student&a2) {return a1.id < a2.id;}
void save_to_stu(int m){             			//д��ѧ������ 
	sort(stu.begin(),stu.end(),stuCpRule);
	ofstream fout("student.txt");  //�����ļ� 
	if (!fout){
		cout << "����ѧ������ʧ��\n";
		return;
	}
	for (int i = 0; i < m; i++){
		fout << stu[i].id << " " << stu[i].name << " " << stu[i].gender << " "
			 << stu[i].age << " " << stu[i].faculty<<"\n";
	}
 	cout<<"�ɹ�����ѧ����Ϣ"<<endl;
	fout.close();
}

int read_to_cor(int n){              			//��ȡ�γ̵��� 
	ifstream incourse("course.txt");
	if(!incourse){
		cout<<"��ȡ�γ���Ϣʧ��"<<endl;
		return 0;
	}
	int size = cor.size();
	for(int i = 0;i < n;++i){
		if(size == 0){
			string name,prior;
			int num,credit;
			incourse >> num >> name >> prior >> credit;
			Course test(name,prior,credit);
			cor.push_back(test);
			cor[i].Course_Num = num;
		}else
			incourse >> cor[i].Course_Num >> cor[i].Course_Name >> cor[i].Prior_Course >> cor[i].Credit;
	}
	
	incourse.close();
	cout<<"��ȡ�γ���Ϣ���"<<endl;
	return 1;
}
bool corCpRule(const Course&a1,const Course&a2) {return a1.Course_Num < a2.Course_Num;}
void save_to_cor(int n){              			//д��γ̵��� 
	sort(cor.begin(),cor.end(),corCpRule);   //�γ̰��γ̺��������� 
	ofstream to_course("course.txt");
	if(!to_course){
		cout<<"����γ���Ϣʧ��"<<endl;
		return;
	}else{
		for(int i =0;i < n; ++i){
			to_course << cor[i].Course_Num << " " << cor[i].Course_Name << " " 
					  << cor[i].Prior_Course << " " << cor[i].Credit <<"\n";
		}
	}
	cout<<"�ɹ�����γ���Ϣ"<<endl;
	to_course.close();
}

int read_to_poi(int p){      					//��ȡ�ɼ����� 
	ifstream inscore("score.txt");
	if(!inscore){
		cout<<"��ȡ�ɼ���Ϣʧ��"<<endl;
		return 0;
	}
	int size = poi.size();
	for(int i = 0;i < p;++i){
		if(size == 0){
			int id,num,score;
			inscore >>	id >> num >> score;
			Point test(id,num,score);
			poi.push_back(test);
		}else{
			inscore >>	poi[i].id >> poi[i].num >> poi[i].score;
		}
	}
	
	inscore.close();
	cout<<"��ȡ�ɼ���Ϣ���"<<endl;
	return 1;
}
bool scoreCpRule(const Point &p1,const Point &p2){
	if(p1.id == p2.id)
		return p2.num < p1.num;
	else
		return p1.id < p2.id;
}
int save_to_poi(int p){      					//д��ɼ����� 
	sort(poi.begin(),poi.end(),scoreCpRule);
	cout<<"�ɼ�����ɹ�"<<endl;
	ofstream fout("score.txt");  //�����ļ� 
	if (!fout){
		cout << "����ѧ���ɼ�ʧ��\n";
		return 0;
	}
	for (int i = 0; i < p; i++){
		fout << poi[i].id << " " << poi[i].num << " " << poi[i].score <<"\n";
	}
 	cout<<"�ɹ�����ѧ���ɼ�"<<endl;
	fout.close();
	return 1;
}

void output_setting(){							//��� ��ѧ��������Ϣ �տγ�������Ϣ  ѧ������ �γ�����  �ɼ� 
	cout<<"-------------"<<endl;
	ofstream setting("setting.txt");
	if(!setting)
		cout<<"��������ʧ��"<<endl;
	
	setting <<"empty_size:"<< empty.size()<<endl;                       		//��ѧ�� 
	for(int i:empty){
		setting<<i<<" ";
	}
	setting<<endl;
	setting<<"empty_course_size:"<< empty_CourseNum.size()<<endl;             //�տγ̱�� 
	for(int j:empty_CourseNum){
		setting<<j<<" ";
	}
	
	setting<<endl<<endl;	
	setting<< "Student_Count:" << stu.size() << endl <<
			  "Course_Count:"<< cor.size() << endl << 
			  "Score_num:"   << poi.size() << endl;         //ѧ������,�γ��������ɼ����� 
	cout<<"�������óɹ�"<<endl; 
	cout<<"-------------"<<endl;
}
int input_setting(int &m,int &n,int &p){      	//m��������ѧ������     n�������տγ�����    p�������ճɼ� 
		cout<<"----------------"<<endl;
		ifstream setting("setting.txt");
		if(!setting){
			cout<<"��ȡ����ʧ��"<<endl;
			return 0;
		}
		
		int size1,size2;
		char temp[20];
		for(int i = 0;i<11;++i){
			setting >> temp[i];
		}
   
		setting >> size1;

		
		for(int i =0;i<size1;++i){
 			int index;
 			setting >> index;
 			empty.push_back(index);
 			cout<<"empty["<<i<<"] = "<<empty[i]<<endl;
		}
		for(int i =0;i<18;++i){
			setting >>  temp[i];
		}
		setting >> size2;
		for(int i = 0;i<size2;++i){
 			int index;
 			setting >> index;
 			empty_CourseNum.push_back(index);
 			cout<<"empty_CourseNum["<<i<<"] = "<<empty_CourseNum[i]<<endl;
		}
		
		for(int i =0;i<14;++i){
			setting >> temp[i];
		}
		
		setting >> m;      //����ѧ������ 
		cout <<"ѧ������("<<m<<")��ȡ���"<<endl;
		
		for(int i =0;i<13;++i){
			setting >> temp[i]; 
		}
		setting >> n;     //���տγ�����
		cout <<"�γ�����("<<n<<")��ȡ���"<<endl;
		
		for(int i =0;i<10;++i){
			setting >> temp[i];
		}
		setting >> p;     //���ճɼ����� 
		cout <<"�ɼ�����("<<p<<")��ȡ���"<<endl; 
		
		cout<<"----------------"<<endl<<endl;
		return 1; 		

}


/*�˵���ʾ*/
void main_menu();        //����
void randinit();//���� 
void Student_Menu(){
	while(true){
		cout<<"**********************"<<endl
			<<"*     ѧ������     *"<<endl
			<<"*-- -- -- -- -- -- --*"<<endl 
			<<"*     1.��Ϣ��ѯ     *"<<endl
			<<"*     2.��Ϣ���     *"<<endl
			<<"*     3.��Ϣ�޸�     *"<<endl
			<<"*     4.��Ϣɾ��     *"<<endl
			<<"*     5.�������˵�   *"<<endl
			<<"*     6.��������ѧ�� *"<<endl
			<<"**********************"<<endl;

		int choice;
		int emptysize = empty.size();
		cin>>choice;
		switch(choice){
			case 1:
				query_Stu();
				break;
			case 2:						
					stu.push_back(inStu());
				break;
			case 3:
				edit_Stu();
				break;
			case 4:
				cout<<"����������ɾ����ѧ����ѧ�ţ�";
				int id; 
				cin>>id;
				del_Stu(id);
				break;
			case 5:
				main_menu();
				break;
			case 6:
				for(Student sample:stu)
					cout<<sample<<endl;
		}
	}
} 
void Course_Menu(){
	while(true){
		cout<<"**********************"<<endl
			<<"*     �γ̱���     *"<<endl
			<<"*-- -- -- -- -- -- --*"<<endl 
			<<"*     1.�γ̲�ѯ     *"<<endl
			<<"*     2.�γ����     *"<<endl
			<<"*     3.�γ��޸�     *"<<endl
			<<"*     4.�γ�ɾ��     *"<<endl
			<<"*     5.�������˵�   *"<<endl
			<<"*     6.�������пγ� *"<<endl
			<<"**********************"<<endl;
		int c;
		cin>>c;
		switch(c){
			case 1:
				query_Course();
				break;
			case 2:		
				inCor();
				break;
			case 3:
				edit_Stu();
				break;
			case 4:
				del_Course();
				break;
			case 5:
				main_menu();
				break;
			case 6:
				for(int i =0;i<cor.size();++i)
					cout<<cor[i]<<endl;	
		}		
	}
}
void Score_Menu(){
	while(true){
		cout<<"**********************"<<endl
			<<"*     �ɼ�����     *"<<endl
			<<"*-- -- -- -- -- -- --*"<<endl 
			<<"*     1.�ɼ���ѯ     *"<<endl
			<<"*     2.�ɼ��޸�     *"<<endl
			<<"*     3.�ɼ����     *"<<endl
			<<"*     4.�ɼ�ɾ��     *"<<endl
			<<"*     5.�������˵�   *"<<endl
			<<"**********************"<<endl; 
		int choice;
		cin>>choice; 
		switch(choice){
			case 1:
				query_Score();
				break;
			case 2:		
				edit_Score();
				break;
			case 3:
				inPoint();
				break;
			case 4:
				del_Score();
				break;
			case 5:
				main_menu();
				break;	
		}	
	}
}
void main_menu(){
	cout<<"**********************"<<endl;
	cout<<"*  ѡ����Ҫ�����ı�  *"<<endl
		<<"*== == == == == == ==*"<<endl
		<<"*        P S         *"<<endl
		<<"*    �ޱ������ݵ�    *"<<endl
		<<"* ���������ʼ������ *"<<endl
		<<"*�б�������ʱ���ȶ�ȡ*"<<endl
		<<"*== == == == == == ==*"<<endl 
		<<"*     1.ѧ����Ϣ     *"<<endl
		<<"*     2.�γ���Ϣ     *"<<endl
		<<"*     3.�ɼ���Ϣ     *"<<endl
		<<"*-- -- -- -- -- -- --*"<<endl
		<<"*     4.��ȡ����     *"<<endl
		<<"*     5.�����޸�     *"<<endl
		<<"*     6.�����ʼ��   *"<<endl
		<<"**********************"<<endl;
	
	int choice;
	cout<<"����˵�������";
	cin>>choice;
	switch(choice){
		case 1:
			Student_Menu();
			break;
		case 2:
			Course_Menu();
			break;
		case 3:
			Score_Menu();
			break;
		case 4:
			int m,n,p;
			input_setting(m,n,p);
			read_to_stu(m);
			read_to_cor(n);
			read_to_poi(p);
			main_menu();
			break;
		case 5:
			save_to_stu(stu.size());
			save_to_cor(cor.size());
			save_to_poi(poi.size());
			output_setting();
			break;
		case 6:
			randinit();
			break;
		default:
			cout<<"��������ȷ������ֵ"<<endl;
			main_menu();
			break; 
	}
}
void randinit(){
	int size1,size2,size3,tmp1,tmp2;
	cout<<"�����ʼ����ѧ���������γ���, �ɼ���.�ÿո����:";
	cin >> size1 >> size2 >> size3;
	tmp1 = size1;
	tmp2 = size2;
	srand(time(0));    //��ʼ���������
	
	while(size1--){     //��ʼ��ѧ�� 
		string name,faculty,gender;
		int age = rand()%8 + 18;;
		for(int i = 0;i < 8; ++ i){
			name +=rand()% ('z'-'A' + 1) + 'A';
		}
		for(int i = 0;i < 8; ++ i){
			faculty +=rand()% ('Z'-'A' + 1) + 'A';
		}
		gender = (rand()%10 >= 5)? "male" : "female";
		Student temp(name,faculty,gender,age);
		stu.push_back(temp);
	}
	cout<<"**********************"<<endl
		<<"* ѧ���б��ʼ���ɹ� *"<<endl;
		
	
	while(size2--){    //��ʼ���γ� 
		string course_name,prior_name;
		int credit = rand()%5 + 1;
		for(int i = 0;i < 8; ++ i){
			course_name +=rand()% ('Z'-'A' + 1) + 'A';
		}
		for(int i = 0;i < 8; ++ i){
			prior_name +=rand()% ('Z'-'A' + 1) + 'A';
		}
		
		Course temp(course_name,prior_name,credit);
		cor.push_back(temp);
	}
	cout<<"* �γ��б��ʼ���ɹ� *"<<endl;
	
	int id,num,cre;
	double score;
	while(size3--){
		id = rand()%tmp1 + 1;
		num = rand()%tmp2 + 1; 
		for(Course les:cor){
			if(les.Course_Num == num)
				 cre = les.Credit;
		}
		double denum = rand()%10;
		score = denum / 10 + rand()%cre;
		Point temp(id,num,score);
		poi.push_back(temp);
	}
	cout<<"* �ɼ��б��ʼ���ɹ� *"<<endl;
	cout<<"**********************"<<endl<<endl;
	sort(poi.begin(),poi.end(),scoreCpRule);
	main_menu(); 
} 

int main(){	
	main_menu();
	return 0;
}
