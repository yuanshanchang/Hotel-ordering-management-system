#include<iostream>
#include<fstream>
#include<cstring>
#include<string>
#include<vector>
#include "Menu.h"
#include "User.h"
using namespace std;
fstream fout;

vector<Order>order;
vector<Menu>menu;

void seviceForSeller();
void seviceForBuyer();
//�ж������������������/���ҷ�Χ
int main()
{
	string n;
	bool success = 0;
	cout<<setw(55)<<"��ӭ��������������ѡ��������Ĳ���"<<endl;
	cout<<"          ----------------------------------------------------------"<<endl;
	//1Ϊ��ң�2Ϊ���ң�3Ϊ�˳�ϵͳ 
	cout<<right;
	cout<<endl<<setw(25)<<"1 ���˲���"<<setw(15)<<"2.���Ҳ���"<<setw(15)<<"3.�˳�"<<endl;
	while(cin>>n)
	{
		order.clear();
		menu.clear();
		if(n == "3") break;
		//����������� 
		if(n != "1" && n != "2")
		{
		    cout<<endl<<"Invalid number!Please input again :"<<endl;
			cout<<endl<<setw(25)<<"1 ����"<<setw(15)<<"2 �̼�"<<setw(15)<<"3 �˳�"<<endl;
			continue;
		}
		if(n == "1") seviceForBuyer();
		else seviceForSeller();
		cout<<right;
		cout<<endl<<setw(25)<<"1 ����"<<setw(15)<<"2 �̼�"<<setw(15)<<"3 �˳�"<<endl;
	}
	return 0;
}

//���ڶ�ȡ�ļ��еĲ˵� 
Menu inputMenu()
{
	Menu iMenu;
	string dishID,dishName;
	double price = -1;
	fout>>dishID;
	if(dishID == " " || dishID == "\n"){
		iMenu.setDishID("-1");
		return iMenu;
	}
	fout>>dishName>>price;
	if(price < 0 || price > 100000){
		iMenu.setDishID("-1");
		return iMenu;
	}
	iMenu.setDishID(dishID);
	iMenu.setDishName(dishName);
	iMenu.setPrice(price);
	return iMenu;
}

//���ڶ�ȡ�ļ��еĶ��� 
Order inputOrder()
{
	string dishID,dishName,name,adress,phone;
	double price = -1;
	int year,month,day,hour,modify,num;
	fout>>dishID;
	if(dishID == " " || dishID == "\n")
	{
		Order iOrder;
		iOrder.setDishID("-1");
		return iOrder;
	}
	fout>>dishName>>price>>num>>name>>adress>>phone;
	if(price < 0 || price > 100000){
		Order iOrder;
		iOrder.setDishID("-1");
		return iOrder;
	}
	fout>>year>>month>>day>>hour>>modify;
	Date date(year,month,day,hour);
	Order iOrder(dishName,dishID,price,name,adress,phone,date);
	iOrder.setnum(num);
	if(!modify) iOrder.setModify();
	return iOrder;
}

//���� 
void seviceForSeller()
{
	Seller iSeller;
	Order iOrder;
	Menu iMenu;
	//��֤���� 
	string password;
	fout.open("password.txt");
	if(fout.fail())
	{
		cout<<endl<<"�ļ���ȡʧ��!"<<endl;
		return;
	}
	fout>>password;
	fout.close();
	iSeller.setPassword(password);
	cout<<endl<<"��������������֤��� :";
	string str;
	int num = 5;
	cin>>str;
	while(num-- && str != iSeller.getPassword())
	{
		cout<<endl<<"�������\n������һ��: ";
		cin>>str;
	}
	if(num <= 0)
	{
		cout<<endl<<"���Ѵ����������"<<endl;
		return;
	}
	//1Ϊ���Ӳ˵���2Ϊɾ���˵���3Ϊ��ѯ������4Ϊȷ�϶�����5Ϊ�������룬6.�������˵� 
	cout<<endl<<"��ѡ�����Ĳ���"<<endl;
	cout<<left;
    cout<<endl<<"           "<<setw(30)<<"1. ����"<<setw(20)<<"2. ɾ��"<<endl;
	cout<<"           "<<setw(30)<<"3. ��ѯ"<<setw(20)<<"4.ȷ�϶���"<<endl;
	cout<<"           "<<setw(30)<<"5.�޸�����"<<setw(20)<< "6.����"<<endl;
	cout << "           " << setw(30) << "7.���ز˵�" << endl;

	string choice;
	while(cin>>choice)
	{
		if(choice == "7")
		{
			system("cls");
			return;
		}
		//����������� 
		if(choice != "1" && choice != "2" && choice != "3" && choice != "4" && choice != "5"&& choice != "6")
	    {
		    cout<<endl<<"�������"<<endl;
			cout << endl << "           " << setw(30) << "1. ����" << setw(20) << "2. ɾ��" << endl;
			cout << "           " << setw(30) << "3. ��ѯ" << setw(20) << "4.ȷ�϶���" << endl;
			cout << "           " << setw(30) << "5.�޸�����" << setw(20) << "6.����" << endl;
			cout << "           " << setw(30) << "7.���ز˵�" << endl;
			continue;
	    }
	    //���ļ���ȡ�Գ�ʼ���˵���Ϣ�Ͷ�����Ϣ 
		order.clear();
		fout.open("order.txt",ios::in);
		if(fout.fail())
		{
			cout<<endl<<"�ļ���ȡʧ��!"<<endl;
			break;
		}
		while(!fout.eof())
		{
			iOrder = inputOrder();
			if(iOrder.getDishID() == "-1") break;
			order.push_back(iOrder);
		}
		fout.close();
		menu.clear();
		fout.open("menu.txt",ios::in);
		if(fout.fail())
		{
			cout<<endl<<"�ļ���ȡʧ��!"<<endl;
			break;
		}
		while(!fout.eof())
		{
			iMenu = inputMenu();
			if(iMenu.getDishID() == "-1") break;
			menu.push_back(iMenu);
		}
		fout.close();
		//choice
		if (choice == "1")
			iSeller.appendMenu(menu);
		else if (choice == "2")
			iSeller.cancelMenu(menu);
		else if (choice == "6")
			iSeller.sortMenu(menu);
		else if(choice == "3")
			iSeller.inquireOrder(order);
		else if(choice == "4")
			iSeller.modifyOrder(order);
		else
		{
            //�޸����� 
			string str1,str2;
			cout<<right;
			cout<<endl<<setw(35)<<"1 ȷ�ϼ����޸�"<<setw(20)<<"2 ����"<<endl;
			while(cin>>str1)
			{
				if(str1 == "2") break; 
				//����������� 
				if(str1 != "1")
				{
					cout<<"�������!"<<endl;
					cout<<endl<<setw(35)<<"1 ��������"<<setw(20)<<"2 ����"<<endl;
					continue;
				}
				cout<<"���������� ������ : ";
				cin>>str1;
				if(str1 == iSeller.getPassword()) break;
				else 
				{
					cout<<right;
					cout<<endl<<"Wrong!"<<endl;
				    cout<<endl<<setw(35)<<"1 ��������"<<setw(20)<<"2 ����"<<endl;
				}
			}
			if(str1 == "2")
			{
				cout<<left;
				cout<<endl<<"           "<<setw(30)<<"1. ����"<<setw(20)<<"2. ɾ��"<<endl;
	           cout<<"           "<<setw(30)<<"3. ��ѯ"<<setw(20)<<"4.ȷ�϶���"<<endl;
	           cout<<"           "<<setw(30)<<"5.�޸�����"<<setw(20)<< "6.����"<<endl;
			   cout << "           " << setw(30) << "7.���ز˵�" << endl;

				continue;
			}
			cout<<endl<<"���������� ������ : ";
			cin>>str1;
			cout<<endl<<"ȷ������ :";
			cin>>str2;
			//���������������һ�������޸����룬д���ļ� 
			if(str1 == str2 ){
				fout.open("password.txt",ios::out);
	            if(fout.fail())
	            {
		             cout<<endl<<"�ļ���ȡʧ��!"<<endl;
		             return;
	            }
	            fout<<str1;
	            fout.close();
				iSeller.setPassword(str1);
				cout<<endl<<"������³ɹ�"<<endl;
			}
			else 
			{
			    cout<<endl<<"���������벻ͬ"<<endl;
			}
		}
		cout<<left;
cout<<endl<<"           "<<setw(30)<<"1. ����"<<setw(20)<<"2. ɾ��"<<endl;
cout<<"           "<<setw(30)<<"3. ��ѯ"<<setw(20)<<"4.ȷ�϶���"<<endl;
	   cout<<"           "<<setw(30)<<"5.�޸�����"<<setw(20)<< "6.����"<<endl;
	   cout << "           " << setw(30) << "7.���ز˵�" << endl;

	}
	/*if(choice == "6")
	{
	    return;
	}*/
}

//����
void seviceForBuyer()
{
	Buyer ibuyer;
	Menu iMenu;
    Order iOrder;
	string n;
	// 1Ϊ��ˣ�2Ϊ��ѯ������3Ϊ�޸Ķ��� ��46.�������˵� 
	cout<<left;
	cout << endl << "��ѡ����Ĳ���:" << endl;
	cout << endl << "           " << setw(20) << "1. ����" << setw(20) << "2. ��ѯ" << endl;
	cout << "           " << setw(20) << "3. ȡ������" << setw(20) << "4.�������˵�" << endl;
	cin>>n;
    while(n!="4")
	{
        //����������� 
	    if(n != "1" && n != "2" && n!= "3" )
		{
			cout<<endl<<"����������"<<endl;
			cin>>n;
			continue;
		}
		//���ļ���ȡ�Գ�ʼ���˵���Ϣ�Ͷ�����Ϣ 
		order.clear();
		fout.open("order.txt",ios::in);
		if(fout.fail())
		{
			cout<<endl<<"�ļ���ȡʧ��!"<<endl;
			break;
		}
		while(!fout.eof())
		{
			iOrder = inputOrder();
			if(iOrder.getDishID() == "-1") break;
			order.push_back(iOrder);
		}
		fout.close();
		menu.clear();
		fout.open("menu.txt",ios::in);
		if(fout.fail())
		{
			cout<<endl<<"�ļ���ȡʧ��!"<<endl;
			break;
		}
		while(!fout.eof())
		{
			iMenu = inputMenu();
			if(iMenu.getDishID() == "-1") break;
			menu.push_back(iMenu);
		}
		fout.close();
		if(n=="1")
		ibuyer.bookOrder(menu,order);
		else if(n=="2")
			ibuyer.inquireOrder(order);
		else if(n=="3")
		    ibuyer.modifyOrder(order);
		cout<<left;
		cout<<endl<<"��ѡ����Ĳ���:"<<endl;
		cout<<endl<<"           "<<setw(20)<<"1. ����"<<setw(20)<<"2. ��ѯ"<<endl;
	    cout<<"           "<<setw(20)<<"3. ȡ��"<<setw(20)<<"4.�������˵�"<<endl;
		cin>>n;
	}
	if (n == "4")
	{
		system("cls");
		return;
	}
}
