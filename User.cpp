#include<iostream>
#include<fstream>
#include<cstring>
#include<cmath>
#include<vector>
#include<string>
#include "Menu.h"
#include "User.h"
using namespace std;
fstream inout;

//����������� 
void printDate(Date date)
{
	cout<<left;
	cout<<date.getYear()<<'/'<<date.getMonth()<<'/'<<date.getDay()<<"-"<<date.getHour()<<'h';
}

//��������˵� 
void printMenu(Menu m)
{
	cout<<left;
	cout<<setw(20)<<m.getDishID()<<setw(20)<<m.getDishName()<<setw(20)<<m.getPrice()<<endl;
}


//����������� 
void printOrder(Order myOrder)
{
	cout<<left;
	cout<<setw(7)<<myOrder.getDishID()<<setw(10)<<myOrder.getDishName()<<setw(6)<<myOrder.getPrice()<<setw(4)<<myOrder.getNum();
	cout<<setw(8)<<myOrder.getCustomerName()<<setw(16)<<myOrder.getPhone()<<setw(10)<<myOrder.getAdress();
	cout << " "; printDate(myOrder.getBookDate()); cout << "  ";
	if(myOrder.getModify())
	{
		cout<<setw(10)<<"�¶���"<<endl;
	}
	else cout<<setw(10)<<"��ȷ��"<<endl;
}

//���ڽ��˵�д���ļ� 
void outputMenu(Menu &iMenu)
{
	inout<<iMenu.getDishID()<<' '<<iMenu.getDishName()<<' '<<iMenu.getPrice()<<endl;
}

//���ڽ�����д���ļ� 
void outputOrder(Order &iOrder)
{
	Date date = iOrder.getBookDate();
	int modify = iOrder.getModify()? 1:0;
	inout<<iOrder.getDishID()<<' '<<iOrder.getDishName()<<' '<<iOrder.getPrice()<<' '<<iOrder.getNum()<<endl;
	inout<<iOrder.getCustomerName()<<' '<<iOrder.getAdress()<<' '<<iOrder.getPhone()<<endl;
	inout<<date.getYear()<<' '<<date.getMonth()<<' '<<date.getDay()<<' '<<date.getHour()<<' '<<modify<<endl;
}

Buyer::Buyer()
{
	name = "no";
	adress = "no"; 
	num = 0;
}

string Buyer::getName()
{
	return name;
}

//��Ҷ��� 
void Buyer::bookOrder(vector<Menu>&myMenu,vector<Order>&order)
{
	int n,m = 0,i,year,month,day,hour,appNum = 0;
	string str;
	char ch;
	n = myMenu.size();
	num = myOrder.size();
	bool can = 1;
	//�жϲ˵��Ƿ�Ϊ�� 
	if(!n)
	{
		cout<<endl<<"Sorry! There is no dish for you to choose!"<<endl;
		return ;
	}
	cout<<left;
	cout<<endl<<"���ã��˵����� :"<<endl;
	cout<<endl<<"        "<<setw(20)<<"ID"<<setw(20)<<"ʳƷ��"<<setw(20)<<"�۸�"<<endl;
	for(i=0;i<n;++i)
	{
		cout<<"        ";
		printMenu(myMenu[i]);
	}
	//1Ϊ������2������һ�� 
	cout<<right;
	cout<<endl<<setw(30)<<"1 ��������"<<setw(20)<<"2 ����"<<endl;
	while(cin>>str)
	{
		can = 1;
		if(str == "2") break;
		cout<<"��ѡ���Ʒ�Ķ�ӦID : ";
		cin>>str;
	    for(i=0;i<n;++i)
	    {
		    if(myMenu[i].getDishID() == str)
			{
					myOrder.push_back(Order(myMenu[i],m));
					break;
			}
			//�жϸñ���Ƿ���� 
			if(i == n-1)
			{
				cout<<endl<<"���۾�!"<<endl;
			    cout<<endl<<setw(30)<<"1 ��������"<<setw(20)<<"2 ����"<<endl;
				can = 0;
			}

		}
		if(!can) continue;
		appNum ++;
		cout<<endl<<"��������Ҫ������ : ";
		cin>>m;
		myOrder[myOrder.size()-1].setnum(m);
		cout<<endl<<setw(30)<<"1 ��������"<<setw(20)<<"2 ����"<<endl;
	}
	//�ж����������˵� 
	if(appNum == 0)
	{
		cout<<endl<<"��ȡ�����"<<endl;
		return;
	}
	//��������û���Ԥ���Ĳ� 
	cout<<left;
	cout<<endl<<"���ѵ����²�Ʒ:"<<endl;
	cout<<endl<<setw(20)<<"ID"<<setw(20)<<"��Ʒ��"<<setw(20)<<"�۸�"<<endl;
	for(i=0;i<myOrder.size();++i)
	{
		printMenu(myOrder[i]);
	}
	//�жϴ�ʱ����Ƿ�Ϊ����״̬����������������������ַ���绰 
	if(name == "no"||adress == "no")
	{
	    cout<<endl<<"���������� ���� : ";
	    cin>>name;
	    cout<<endl<<"���������� ��ַ : ";
	    cin>>adress;
	    cout<<endl<<"���������� �绰���� : ";
	    cin>>phone;
		cout << endl << "����������Ҫ����λ�� : ";
		cin >> setnum;

	}
	cout<<endl<<"�����������ò�ʱ��,"<<endl;
	cout<<"�� 2023/5/2 14  : "<<endl;
	cin>>year>>ch>>month>>ch>>day>>hour;
	bookDate.setYear(year);
	bookDate.setMonth(month);
	bookDate.setDay(day);
	bookDate.setHour(hour);
	for(int i=num;i<myOrder.size();++i){
		myOrder[i].setCustomerName(name);
		myOrder[i].setAdress(adress);
		myOrder[i].setPhone(phone);
		myOrder[i].setBookDate(bookDate);
	}
	inout.open("order.txt",ios::app);
	if(inout.fail())
	{
		cout<<endl<<"�ļ���ȡʧ��!"<<endl;
		return;
	}
	for(i=num;i<myOrder.size();++i)
	{
		outputOrder(myOrder[i]);
	}
	inout.close();
	num = myOrder.size();
}

//��Ҳ�ѯ���� 
void Buyer::inquireOrder(vector<Order>&order)
{
     //�����Ƿ�Ϊ�� 
	if(name == "no"){
	    cout<<endl<<"���������� ���� : ";
	    cin>>name;
	}
	myOrder.clear();
	for(int i=0;i<order.size();++i)
	{
		if(order[i].getCustomerName() == name)
		{
			myOrder.push_back(order[i]);
		}
	}
	num = myOrder.size();
	if(num == 0)
	{
		cout<<endl<<"��δ�����κβ�Ʒ!"<<endl;
		return;
	}
	cout<<left;
	cout<<endl<<"���Ѵ����Ĳ�Ʒ���� :"<<endl; 
	cout<<endl<<setw(7)<<"ID"<<setw(10)<<"��Ʒ��"<<setw(6)<<"�۸�"<<setw(4)<<"����"<<setw(8)<<"�ͻ���";
		cout<<setw(16)<<"�绰����"<<setw(12)<<"��ַ"<<setw(15)<<"����"<<setw(10)<<"��ע"<<endl;
	for(int i=0;i<num;++i){
		printOrder(myOrder[i]);
	}
	return;
}

//���ȡ������ 
void Buyer::modifyOrder(vector<Order>&order)
{
	num = myOrder.size();
	if(num == 0)
	{
		cout<<endl<<"��δ�����κβ�Ʒ!"<<endl;
		return ;
	}
	//���������ѵ����ж��� 
	cout<<left;
	cout<<endl<<"���Ѷ����Ĳ�Ʒ����"<<endl;
	cout<<endl<<setw(7)<<"ID"<<setw(10)<<"��Ʒ��"<<setw(6)<<"�۸�"<<setw(4)<<"����"<<setw(8)<<"�ͻ���";
		cout<<setw(16)<<"�绰����"<<setw(12)<<"��ַ"<<setw(15)<<"����"<<setw(10)<<"��ע"<<endl;
	for(int i=0;i<num;++i)
	{
		printOrder(myOrder[i]);
	}
	//ѡ��1-������2-������һ�� 
	cout<<right;
	cout<<endl<<setw(30)<<"1 ��������"<<setw(20)<<"2 ����"<<endl;
	string str;
	int pos = -1,n=0;
	Order iOrder;
	int *cancleDish = new int[num+1],*cancle = new int[order.size()];
	memset(cancleDish,0,4*(num+1));
	memset(cancle,0,4*(order.size()));
	while(cin>>str)
	{
		if(str == "2") break;
		//�ж���Ч���� 
		if(str != "1"){
			cout<<endl<<"�������!"<<endl;
			cout<<endl<<setw(30)<<"1 ��������"<<setw(20)<<"2 ����"<<endl;
			continue;
		}
		cout<<endl<<"�������ƷID ";
		cin>>str;
		for(int i=0;i<num;++i)
		{
			if(myOrder[i].getDishID() == str)
			{
                //�ö����Ƿ���ȷ�� 
				if(myOrder[i].getModify()){
					cout<<endl<<"������ȡ��!"<<endl;
				    pos = i;
				    break;
				}
				else{
					cout<<endl<<"�̼���ȷ�ϣ��޷�ȡ�� !"<<endl;
					pos = -2;
					break;
				}
			}
		}
		//�鿴�������ȡ���ı���Ƿ���� 
		if(pos < 0){
			if(pos == -1)
			   cout<<endl<<"���޴˵�"<<endl;
		}
		else{
			cancleDish[pos] = 1;
			n++;
		}
		pos = -1;
		cout<<right;
		cout<<endl<<setw(30)<<"1 ��������"<<setw(20)<<"2 ����"<<endl;
	}
	//�����µĶ���д���ļ� 
	inout.open("order.txt",ios::out);
	if(inout.fail())
	{
		cout<<endl<<"�ļ���ȡʧ��!"<<endl;
		delete cancleDish;delete cancle;
		return;
	}
	for(int i=0;i<num;++i)
	{
		if(cancleDish[i]){
			for(int j=0;j<order.size();++j)
			{
				if(order[j] == myOrder[i])
				{
					cancle[j] = 1;
					break;
				}
			}
		}
	}
	for(int i=0;i<order.size();++i)
	{
		if(cancle[i]){
			continue;
		}
		outputOrder(order[i]);
	}
	inout.close();
	num -= n;
	delete cancleDish;delete cancle;
}

int Buyer::getNum()
{
	return num;
}

Seller::Seller()
{
	password = "888888";
}

void Seller::appendMenu(vector<Menu>&myMenu)
{
	cout<<endl<<"ҪΪϵͳ����µĲ�Ʒ��?  Y/N"<<endl;
	string ch;
	int k = myMenu.size();
	while(cin>>ch)
	{
        //�ж���Ч���� 
	    if(ch != "Y" && ch != "y") break;
	    cout<<endl<<"�������Ʒ���� ";
	    string str;
	    Menu iMenu;
	    double d;
	    cin>>str;
	    iMenu.setDishName(str);
	    cout<<endl<<"�������ƷID : ";
	    cin>>str;
	    iMenu.setDishID(str);
	    cout<<endl<<"�������Ʒ�۸�: ";
	    cin>>d;
	    iMenu.setPrice(d);
	    myMenu.push_back(iMenu);
		cout<<endl<<"�ѳɹ����"<<endl;
		cout<<endl<<"�Ƿ������ӣ� Y/N"<<endl;
	}
	//�������˵�д���ļ� 
	inout.open("menu.txt",ios::app);
	if(inout.fail())
	{
		cout<<endl<<"�ļ���ȡʧ��!"<<endl;
		return;
	}
	for(int i=k;i<myMenu.size();++i)
	{
		outputMenu(myMenu[i]);
	}
	inout.close();
	return;
}

void Seller::cancelMenu(vector<Menu>&myMenu)
{
	cout<<endl<<"Ҫɾ����Ʒ��? Y/N"<<endl;
	string str;
	string ch;
	Menu iMenu;
	vector<Menu>::iterator it = myMenu.begin();
	while(cin>>ch)
	{
		it = myMenu.begin();
		if(ch == "N" || ch == "n") break;
		//�ж���Ч���� 
		if(ch != "Y" && ch != "y")
		{
			cout<<endl<<"�������������"<<endl;
			cout<<endl<<"Ҫɾ����Ʒ��? Y/N"<<endl;
			continue;
		}
		//������в˵� 
		cout<<left;
	    cout<<endl<<"�˵����� :"<<endl;
	    cout<<endl<<"        "<<setw(20)<<"ID"<<setw(20)<<"��Ʒ��"<<setw(20)<<"�۸�"<<endl;
	    for(int i=0;i<myMenu.size();++i)
	    {
		    cout<<"        ";
		    printMenu(myMenu[i]);
	    }
		cout<<endl<<"��������Ҫɾ���Ĳ�ƷID: ";
		cin>>str;
		for(int i=0;i<myMenu.size();++i)
		{
			if(myMenu[i].getDishID() == str)
			{
				myMenu.erase(it+i);
				cout<<endl<<"�ѳɹ�"<<endl;
				break;
			}
			//�Ҳ����ñ�� 
			if(i == myMenu.size()-1)
			{
				cout<<endl<<"��ѯʧ��������"<<endl;
			}
		}
		cout<<endl<<"�Ƿ��������? Y/N"<<endl;
	}
	//���޸ĺ�˵�д���ļ� 
	inout.open("menu.txt",ios::out);
	if(inout.fail())
	{
		cout<<endl<<"�ļ���ȡʧ��!"<<endl;
		return;
	}
	for(int i=0;i<myMenu.size();++i)
	{
		outputMenu(myMenu[i]);
	}
	inout.close();
}

//���Ҳ�ѯ���� 
void Seller::inquireOrder(vector<Order>&order)
{
     //û�ж����������ʾ��������һ�� 
	if(order.size() == 0)
	{
		cout<<endl<<"There is no any order!"<<endl;
		return ;
	}
	cout<<left;
	cout<<endl<<"��������:"<<endl;
	cout<<endl<<setw(7)<<"ID"<<setw(10)<<"��Ʒ��"<<setw(6)<<"�۸�"<<setw(4)<<"����"<<setw(8)<<"�ͻ���";
		cout<<setw(16)<<"�绰����"<<setw(12)<<"��ַ"<<setw(15)<<"����"<<setw(10)<<"��ע"<<endl;
	for(int i=0;i<order.size();++i)
	{
		printOrder(order[i]);
	}
	return;
}

//����ȷ�϶��� 
void Seller::modifyOrder(vector<Order>&order)
{
	int *pos = new int[order.size()+1],count = 0;
	memset(pos,0,sizeof(pos));
	for(int i=0;i<order.size();++i)
	{
		if(order[i].getModify())
		{
			count++;
			pos[i] = 1;
		}
	}
	//û��δȷ�϶�������ʾ�󷵻���һ�� 
	if(count == 0)
	{
		cout<<endl<<"All order have been approved!"<<endl;
		return ;
	}
	cout<<left;
	cout<<endl<<"δȷ�϶�������: "<<endl;
	cout<<endl<<setw(7)<<"ID"<<setw(10)<<"��Ʒ��"<<setw(6)<<"�۸�"<<setw(8)<<"����"<<setw(8)<<"�ͻ���";
		cout<<setw(16)<<"�绰����"<<setw(12)<<"��ַ"<<setw(15)<<"����"<<setw(10)<<"��ע"<<endl;
	count = 0;
	for(int i=0;i<order.size();++i)
	{
		if(pos[i]&&order[i].getModify())
		{
			count++;
			cout<<count<<endl;
			printOrder(order[i]);
		}
	}
	//���ҿ�ѡ�� 1-ȫ��ȷ�� �� 2-���ȷ�� �� 3-���� 
	cout<<right;
	cout<<endl<<setw(20)<<"1.ȫ��ȷ��"<<setw(25)<<"2.���ȷ��"<<setw(20)<<"3.����"<<endl;
	string n;
	while(cin>>n)
	{
		if(n == "1" || n == "2" || n == "3") break;
		else{
			cout<<endl<<"�������!"<<endl;
			cout<<endl<<setw(20)<<"1.ȫ��ȷ��"<<setw(25)<<"2.���ȷ��"<<setw(20)<<"3.����"<<endl;
		}
	}
	if( n == "3") return;
	if(n == "1")
	{
		for(int i=0;i<order.size();++i)
		{
			if(pos[i])
				order[i].setModify();
		}
	}
	else
	{
		cout<<right;
		cout<<endl<<setw(30)<<"1 ��������"<<setw(20)<<"2 ����"<<endl;
	    int k,m;
		while(cin>>m)
		{
			if(m == 2) return;
			if(m != 1){
				cout<<endl<<"�������!"<<endl;
				return ;
			}
			cout<<endl<<"Please input the number of order:";
			cin>>m;
			//����������ȷ�� 
			if( m > count)
			{
				cout<<endl<<"There is only "<<count<<" order!"<<endl;
				cout<<endl<<"Please input again!"<<endl;
			}
			else if( m <= 0)
			{
				cout<<endl<<"The number must be positive !"<<endl;
			}
			else
			{
				k = 0;
				for(int i=0;i<order.size();++i)
				{
					if(pos[i])
					{
						k++;
						if(k == m)
						{
							order[i].setModify();
							cout<<endl<<"The order have approved!"<<endl;
						}
					}
				}
			}
			cout<<right;
			cout<<endl<<setw(30)<<"1 ��������"<<setw(20)<<"2 ����"<<endl;
		}
	}
	//���޸ĺ�Ķ���д���ļ� 
	inout.open("order.txt",ios::out);
	if(inout.fail())
	{
		cout<<endl<<"�ļ���ȡʧ��!"<<endl;
		return;
	}
	for(int i=0;i<order.size();++i)
	{
		outputOrder(order[i]);
	}
	inout.close();

}

void Seller::setPassword(string p)
{
	password = p;
}

string Seller::getPassword()
{
	return password;
}
