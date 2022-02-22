#include<fstream>
#include<iostream> 
#include<cstdio>
#include<vector>
#include<string.h>
#include<algorithm>
#include<time.h> 


using namespace std;
vector <int> empty;   //闲置的二手学号储存地 
vector <int> empty_CourseNum;
int savecount = 0;
class Student{       //学生 	
	public:
		static int count;
		int id;           //学号 
		string name;      //姓名 
		string faculty;   //院系 
		string gender;    //性别 
		int age;          //年龄 
		
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
			os << "学号："<<str_id<<endl
			   << "姓名："<<stud.name<<endl
			   << "性别："<<stud.gender<<endl
			   << "年龄："<<stud.age<<endl
			   << "院系："<<stud.faculty<<endl;
			return os; 
		}
				
		
};
int Student::count = 0;
class Course{       //课程 
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
			os << "课程编号："<<course.Course_Num<<endl
			   << "课程名字："<<course.Course_Name<<endl
			   << "先行课程："<<course.Prior_Course<<endl
			   << "学分："<<course.Credit<<endl; 
			return os; 			
		}
		
}; 
int Course::count = 0;
vector <Course>  cor;  	//课程表
class Point{        //学生的课程学习情况 
	public:
		int id;
		int num;    // 课程号 
		double score;  // 分数/学分 
		Point(){}
		Point(int _id,int _num,double _score ):id(_id),num(_num),score(_score){}
		~Point(){};
		friend ostream &operator<< (ostream &os, const Point &point){
			int credit; 
			for(Course p:cor)
				if(p.Course_Num == point.num)
					credit = p.Credit;
			os << "学生编号："<<point.id<<endl
			   << "课程编号："<<point.num<<endl
			   << "学生成绩："<<point.score<<" / "<<credit<<endl;
			return os; 				
		}
		
};

vector <Student> stu;    			//学生表 
vector <Point>   poi;               //成绩表 

/*学生表操作*/
Student inStu(){				    //新增学生信息 
	string name,faculty,gender;
	int age;
	
	cout<<"请输入学生姓名："; 
	cin>>name;
	cout<<"请输入所属院系："; 
	cin>>faculty;
	cout<<"请输入学生性别：";
	cin>>gender;
	cout<<"请输入学生年龄：";
	cin>>age;


	Student test(name,faculty,gender,age);
	return test;
}
void query_Stu(){          			//查学生  ,methon: 1.学号匹配 2.名字匹配 3.性别匹配 4.院系匹配 
	cout<<"**********************"<<endl;
	cout<<"*   请选择查询条件   *"<<endl
		<<"*     1.学号匹配     *"<<endl
		<<"*     2.名字匹配     *"<<endl
		<<"*     3.性别匹配     *"<<endl
		<<"*     4.院系匹配     *"<<endl
		<<"**********************"<<endl;
	int method;
	string ans;
	cin>>method;
	cout<<"输入匹配值:";
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
void del_Stu(int id){           	//通过id删除学生 
	for(int i = 0;i<stu.size();++i)
		if(stu[i].id== id)
		{
			stu.erase(stu.begin() + i);
			empty.push_back(id);
			cout<<"删除完毕"<<endl;
			//删除学生成绩 
			for(int j = 0;j<poi.size();++j){
				if(poi[j].id == id){
					poi.erase(poi.begin() + j);
				}
			}			
		}

} 
void edit_Stu(){               		//通过id修改学生信息 
	int id;
	cout<<"请输入待修改学生的学号：";
	cin>>id;
	Student * p = queryStu_byID(id);
	
	cout<<"1.修改名字  2.修改院系"<<endl;
	int choice;
	string temp;
	cin>>choice;
	cout<<"你希望更改为：";
	cin>>temp;
	switch(choice){
		case 1:
			p->name = temp;
			break;
		case 2:
			p->faculty = temp;
			break;
	}
	cout<<"修正完毕"<<endl; 
}

/*课程表操作*/
void inCor(){						//新增课程信息 
	int credit;
	string name,prior;
	
	cout<<"新课程名：";
	cin>>name;
	cout<<"先行课程：";
	cin>>prior;
	cout<<"学分：";
	cin>>credit;
	Course test(name,prior,credit);
	cor.push_back(test);
	cout<<"添加成功"<<endl;
}
void query_Course(){         		//根据课程编号查课程 
	int num;
	cout<<"请输入待查询课程的课程编号:";
	cin>>num;
	int i;
	for(i =0;i<cor.size();++i){
		if(cor[i].Course_Num == num){
			cout<<cor[i]<<endl;
			cout<<"查询成功"<<endl;
			break;
		}
	}
	if( i == cor.size()){
		cout<<"未能找到对象"<<endl;
	} 
	
} 
void edit_Course(){         		//修改课程信息 
	int num;
	cout<<"请输入待修改课程的课程编号：";
	cin>>num; 
	for(Course prop:cor){
		if(prop.Course_Num == num){
			
			cout<<"1.修改课程名字  2.修改先导课程 3.修改学分"<<endl;
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
			cout<<"修改成功"<<endl; 
			break;
		}
	}
	
} 
void del_Course(){         			//删除课程信息 
	cout<<"请输入待删除课程的课程编号:";
	int num;
	cin>>num;
	for(int i = 0; i < cor.size();++i){
		if(cor[i].Course_Num == num){
			cor.erase(cor.begin() + i);
			empty_CourseNum.push_back(num);
			for(int j = 0;j<poi.size();++j){         //课程对应的成绩也删除 
				if(poi[j].num == num){
					poi.erase(poi.begin() + j);
				}
			}
			break;
		}
	}
} 

/*成绩表操作*/
void inPoint(){                     //输入成绩 
	cout<<"依次输入学号，课程编号与对应成绩，用空格隔开:";
	int id,num,score;
	cin>>id>>num>>score; 
	
	for(Student st:stu){          //找id是否存在 
		if(st.id == id){          
			for(Course les:cor){  //找课程号是否存在 
				if(les.Course_Num == num){
					while(les.Credit < score){      //成绩大于学分 
						cout<<"成绩输入错误（大于该课程学分），请重新输入：";
						cin>>score;							
					}
						Point p(id,num,score);
						poi.push_back(p);
					return;
				}
			}
			cout<<"error:找不到相关课程"<<endl;
		}
	} 
	cout<<"error:没有该学生的信息"<<endl; 
}
void del_Score(){   				//删除成绩 
	int id,num;
	cout<<"请输入你需要删除的对象的 学号与课程编号，用空格隔开：";
	cin>>id>>num;
	for(int i = 0;i<poi.size();++i){
		if(poi[i].id == id && poi[i].num == num){
			poi.erase(poi.begin() + i);
			cout<<"删除成功！"<<endl;
			break;
		}
	}
}
void edit_Score(){    				//更改成绩 
	int id,num;
	cout<<"请输入你需要更改的对象的 学号与课程编号，用空格隔开：";
	cin>>id>>num;
	for(int i = 0;i<poi.size();++i){
		if(poi[i].id == id && poi[i].num == num){
			double newScore;
			cout<<"请输入学号为 "<<id<<" 的学生课程编号为 "<<num<<" 的新成绩："; 
			cin>>newScore;
			poi[i].score = newScore;
			return;
		}
	}
	
	cout<<"查不到相关信息！请检查搜索索引是否错误！"<<endl;
}	
bool scorelistRule(const Point &p1, const Point &p2){
	return p1.score > p2.score;
}
void swap(int &a,int &b){
	int temp = a;
	a = b;
	b = temp;
}
void query_Score(){     							//查成绩 
	int id,num,choice;
	cout<<"**********************"<<endl;
	cout<<"*   请选择查询索引   *"<<endl
		<<"*  1.课程成绩及排名  *"<<endl
		<<"*  2.学生单课程成绩  *"<<endl
		<<"*  3.学生全课程成绩  *"<<endl
		<<"*     4.所有成绩     *"<<endl
		<<"**********************"<<endl;
	cin>>choice;	
	vector<Point> target;	
	switch(choice){
		case 1:			
			int courseNum,count;
			cout<<"请输入待查询课程的课程编号：";
			cin>>courseNum;		
			for(int i = 0; i < poi.size() ; ++i){
				if(poi[i].num == courseNum)
					target.push_back(poi[i]);	
			}
			sort(target.begin(),target.end(),scorelistRule);
			for(int j = target.size(),rank = 1;j > 0; --j,++rank){
				cout<<"第"<<rank<<"位:"<<endl<<target[j]<<endl;
			} 
			break;
		case 2:
			int tmp;
			cout<<"请输入学生的id:"; 
			cin>>id;
			cout<<"请输入查询的课程:";
			cin>>num;
			for(int i = 0;i<poi.size();++i){
				if(poi[i].id == id && poi[i].num == num){
					cout<<poi[i]<<endl; 
					tmp = i;
					break;
				}
			}
			cout<<"查询完毕"<<endl;
			if(tmp == poi.size())
				cout<<"查不到相关信息！请检查搜索索引是否错误！"<<endl;
			
			break;
		case 3:
			cout<<"输入学生的id:";
			cin>>id;
			for(int i =0;i<poi.size();++i){
				if(poi[i].id == id){
					cout<<"课程编号："<<poi[i].num<<"  成绩："<<poi[i].score<<endl; 
				}					
			}
			cout<<"查询完毕！"<<endl;
			break;
		case 4:
			for(int i = 0;i<poi.size();++i){
				cout<<poi[i]<<endl;
			}
			cout<<"以上为所有成绩"<<poi.size()<<endl;
			break;
	}
}

/*文件操作*/
int read_to_stu(int m){             	 		//读取学生档案 
	ifstream fin("student.txt");
	if(!fin){
		cout<<"读取学生信息失败"<<endl;
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
	cout<<"读取学生信息完成"<<endl;
	return 1;
	
}
bool stuCpRule(const Student&a1,const Student&a2) {return a1.id < a2.id;}
void save_to_stu(int m){             			//写入学生档案 
	sort(stu.begin(),stu.end(),stuCpRule);
	ofstream fout("student.txt");  //创建文件 
	if (!fout){
		cout << "保存学生档案失败\n";
		return;
	}
	for (int i = 0; i < m; i++){
		fout << stu[i].id << " " << stu[i].name << " " << stu[i].gender << " "
			 << stu[i].age << " " << stu[i].faculty<<"\n";
	}
 	cout<<"成功保存学生信息"<<endl;
	fout.close();
}

int read_to_cor(int n){              			//读取课程档案 
	ifstream incourse("course.txt");
	if(!incourse){
		cout<<"读取课程信息失败"<<endl;
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
	cout<<"读取课程信息完成"<<endl;
	return 1;
}
bool corCpRule(const Course&a1,const Course&a2) {return a1.Course_Num < a2.Course_Num;}
void save_to_cor(int n){              			//写入课程档案 
	sort(cor.begin(),cor.end(),corCpRule);   //课程按课程号排序后存入 
	ofstream to_course("course.txt");
	if(!to_course){
		cout<<"保存课程信息失败"<<endl;
		return;
	}else{
		for(int i =0;i < n; ++i){
			to_course << cor[i].Course_Num << " " << cor[i].Course_Name << " " 
					  << cor[i].Prior_Course << " " << cor[i].Credit <<"\n";
		}
	}
	cout<<"成功保存课程信息"<<endl;
	to_course.close();
}

int read_to_poi(int p){      					//读取成绩档案 
	ifstream inscore("score.txt");
	if(!inscore){
		cout<<"读取成绩信息失败"<<endl;
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
	cout<<"读取成绩信息完成"<<endl;
	return 1;
}
bool scoreCpRule(const Point &p1,const Point &p2){
	if(p1.id == p2.id)
		return p2.num < p1.num;
	else
		return p1.id < p2.id;
}
int save_to_poi(int p){      					//写入成绩档案 
	sort(poi.begin(),poi.end(),scoreCpRule);
	cout<<"成绩排序成功"<<endl;
	ofstream fout("score.txt");  //创建文件 
	if (!fout){
		cout << "保存学生成绩失败\n";
		return 0;
	}
	for (int i = 0; i < p; i++){
		fout << poi[i].id << " " << poi[i].num << " " << poi[i].score <<"\n";
	}
 	cout<<"成功保存学生成绩"<<endl;
	fout.close();
	return 1;
}

void output_setting(){							//输出 空学号数组信息 空课程数组信息  学生数量 课程数量  成绩 
	cout<<"-------------"<<endl;
	ofstream setting("setting.txt");
	if(!setting)
		cout<<"创建配置失败"<<endl;
	
	setting <<"empty_size:"<< empty.size()<<endl;                       		//空学号 
	for(int i:empty){
		setting<<i<<" ";
	}
	setting<<endl;
	setting<<"empty_course_size:"<< empty_CourseNum.size()<<endl;             //空课程编号 
	for(int j:empty_CourseNum){
		setting<<j<<" ";
	}
	
	setting<<endl<<endl;	
	setting<< "Student_Count:" << stu.size() << endl <<
			  "Course_Count:"<< cor.size() << endl << 
			  "Score_num:"   << poi.size() << endl;         //学生数量,课程数量，成绩数量 
	cout<<"保存设置成功"<<endl; 
	cout<<"-------------"<<endl;
}
int input_setting(int &m,int &n,int &p){      	//m用来接收学生数量     n用来接收课程数量    p用来接收成绩 
		cout<<"----------------"<<endl;
		ifstream setting("setting.txt");
		if(!setting){
			cout<<"读取设置失败"<<endl;
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
		
		setting >> m;      //接收学生数量 
		cout <<"学生数量("<<m<<")读取完成"<<endl;
		
		for(int i =0;i<13;++i){
			setting >> temp[i]; 
		}
		setting >> n;     //接收课程数量
		cout <<"课程数量("<<n<<")读取完成"<<endl;
		
		for(int i =0;i<10;++i){
			setting >> temp[i];
		}
		setting >> p;     //接收成绩数量 
		cout <<"成绩数量("<<p<<")读取完成"<<endl; 
		
		cout<<"----------------"<<endl<<endl;
		return 1; 		

}


/*菜单显示*/
void main_menu();        //声明
void randinit();//声明 
void Student_Menu(){
	while(true){
		cout<<"**********************"<<endl
			<<"*     学生表功能     *"<<endl
			<<"*-- -- -- -- -- -- --*"<<endl 
			<<"*     1.信息查询     *"<<endl
			<<"*     2.信息添加     *"<<endl
			<<"*     3.信息修改     *"<<endl
			<<"*     4.信息删除     *"<<endl
			<<"*     5.返回主菜单   *"<<endl
			<<"*     6.返回所有学生 *"<<endl
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
				cout<<"请输入你想删除的学生的学号：";
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
			<<"*     课程表功能     *"<<endl
			<<"*-- -- -- -- -- -- --*"<<endl 
			<<"*     1.课程查询     *"<<endl
			<<"*     2.课程添加     *"<<endl
			<<"*     3.课程修改     *"<<endl
			<<"*     4.课程删除     *"<<endl
			<<"*     5.返回主菜单   *"<<endl
			<<"*     6.返回所有课程 *"<<endl
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
			<<"*     成绩表功能     *"<<endl
			<<"*-- -- -- -- -- -- --*"<<endl 
			<<"*     1.成绩查询     *"<<endl
			<<"*     2.成绩修改     *"<<endl
			<<"*     3.成绩添加     *"<<endl
			<<"*     4.成绩删除     *"<<endl
			<<"*     5.返回主菜单   *"<<endl
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
	cout<<"*  选择需要操作的表  *"<<endl
		<<"*== == == == == == ==*"<<endl
		<<"*        P S         *"<<endl
		<<"*    无本地数据的    *"<<endl
		<<"* 可先随机初始化数据 *"<<endl
		<<"*有本地数据时可先读取*"<<endl
		<<"*== == == == == == ==*"<<endl 
		<<"*     1.学生信息     *"<<endl
		<<"*     2.课程信息     *"<<endl
		<<"*     3.成绩信息     *"<<endl
		<<"*-- -- -- -- -- -- --*"<<endl
		<<"*     4.读取数据     *"<<endl
		<<"*     5.保存修改     *"<<endl
		<<"*     6.随机初始化   *"<<endl
		<<"**********************"<<endl;
	
	int choice;
	cout<<"输入菜单索引：";
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
			cout<<"请输入正确的索引值"<<endl;
			main_menu();
			break; 
	}
}
void randinit(){
	int size1,size2,size3,tmp1,tmp2;
	cout<<"输入初始化的学生人数，课程数, 成绩数.用空格隔开:";
	cin >> size1 >> size2 >> size3;
	tmp1 = size1;
	tmp2 = size2;
	srand(time(0));    //初始化随机种子
	
	while(size1--){     //初始化学生 
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
		<<"* 学生列表初始化成功 *"<<endl;
		
	
	while(size2--){    //初始化课程 
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
	cout<<"* 课程列表初始化成功 *"<<endl;
	
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
	cout<<"* 成绩列表初始化成功 *"<<endl;
	cout<<"**********************"<<endl<<endl;
	sort(poi.begin(),poi.end(),scoreCpRule);
	main_menu(); 
} 

int main(){	
	main_menu();
	return 0;
}
