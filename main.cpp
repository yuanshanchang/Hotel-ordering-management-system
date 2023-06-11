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
//判断情况，初步引导至买/卖家范围
int main()
{
	string n;
	bool success = 0;
	cout<<setw(55)<<"欢迎来到本餐厅，请选择您所需的操作"<<endl;
	cout<<"          ----------------------------------------------------------"<<endl;
	//1为买家，2为卖家，3为退出系统 
	cout<<right;
	cout<<endl<<setw(25)<<"1 客人操作"<<setw(15)<<"2.卖家操作"<<setw(15)<<"3.退出"<<endl;
	while(cin>>n)
	{
		order.clear();
		menu.clear();
		if(n == "3") break;
		//处理错误输入 
		if(n != "1" && n != "2")
		{
		    cout<<endl<<"Invalid number!Please input again :"<<endl;
			cout<<endl<<setw(25)<<"1 客人"<<setw(15)<<"2 商家"<<setw(15)<<"3 退出"<<endl;
			continue;
		}
		if(n == "1") seviceForBuyer();
		else seviceForSeller();
		cout<<right;
		cout<<endl<<setw(25)<<"1 客人"<<setw(15)<<"2 商家"<<setw(15)<<"3 退出"<<endl;
	}
	return 0;
}

//用于读取文件中的菜单 
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

//用于读取文件中的订单 
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

//卖家 
void seviceForSeller()
{
	Seller iSeller;
	Order iOrder;
	Menu iMenu;
	//验证密码 
	string password;
	fout.open("password.txt");
	if(fout.fail())
	{
		cout<<endl<<"文件读取失败!"<<endl;
		return;
	}
	fout>>password;
	fout.close();
	iSeller.setPassword(password);
	cout<<endl<<"请输入密码以验证身份 :";
	string str;
	int num = 5;
	cin>>str;
	while(num-- && str != iSeller.getPassword())
	{
		cout<<endl<<"密码错误\n请再试一次: ";
		cin>>str;
	}
	if(num <= 0)
	{
		cout<<endl<<"您已错误输入五次"<<endl;
		return;
	}
	//1为增加菜单，2为删除菜单，3为查询订单，4为确认订单，5为设置密码，6.返回主菜单 
	cout<<endl<<"请选择您的操作"<<endl;
	cout<<left;
    cout<<endl<<"           "<<setw(30)<<"1. 新增"<<setw(20)<<"2. 删除"<<endl;
	cout<<"           "<<setw(30)<<"3. 查询"<<setw(20)<<"4.确认订单"<<endl;
	cout<<"           "<<setw(30)<<"5.修改密码"<<setw(20)<< "6.排序"<<endl;
	cout << "           " << setw(30) << "7.返回菜单" << endl;

	string choice;
	while(cin>>choice)
	{
		if(choice == "7")
		{
			system("cls");
			return;
		}
		//处理错误输入 
		if(choice != "1" && choice != "2" && choice != "3" && choice != "4" && choice != "5"&& choice != "6")
	    {
		    cout<<endl<<"输入错误"<<endl;
			cout << endl << "           " << setw(30) << "1. 新增" << setw(20) << "2. 删除" << endl;
			cout << "           " << setw(30) << "3. 查询" << setw(20) << "4.确认订单" << endl;
			cout << "           " << setw(30) << "5.修改密码" << setw(20) << "6.排序" << endl;
			cout << "           " << setw(30) << "7.返回菜单" << endl;
			continue;
	    }
	    //从文件读取以初始化菜单信息和订单信息 
		order.clear();
		fout.open("order.txt",ios::in);
		if(fout.fail())
		{
			cout<<endl<<"文件读取失败!"<<endl;
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
			cout<<endl<<"文件读取失败!"<<endl;
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
            //修改密码 
			string str1,str2;
			cout<<right;
			cout<<endl<<setw(35)<<"1 确认继续修改"<<setw(20)<<"2 返回"<<endl;
			while(cin>>str1)
			{
				if(str1 == "2") break; 
				//处理错误输入 
				if(str1 != "1")
				{
					cout<<"输入错误!"<<endl;
					cout<<endl<<setw(35)<<"1 继续操作"<<setw(20)<<"2 返回"<<endl;
					continue;
				}
				cout<<"请输入您的 旧密码 : ";
				cin>>str1;
				if(str1 == iSeller.getPassword()) break;
				else 
				{
					cout<<right;
					cout<<endl<<"Wrong!"<<endl;
				    cout<<endl<<setw(35)<<"1 继续操作"<<setw(20)<<"2 返回"<<endl;
				}
			}
			if(str1 == "2")
			{
				cout<<left;
				cout<<endl<<"           "<<setw(30)<<"1. 新增"<<setw(20)<<"2. 删除"<<endl;
	           cout<<"           "<<setw(30)<<"3. 查询"<<setw(20)<<"4.确认订单"<<endl;
	           cout<<"           "<<setw(30)<<"5.修改密码"<<setw(20)<< "6.排序"<<endl;
			   cout << "           " << setw(30) << "7.返回菜单" << endl;

				continue;
			}
			cout<<endl<<"请输入您的 新密码 : ";
			cin>>str1;
			cout<<endl<<"确认密码 :";
			cin>>str2;
			//两次输入的新密码一样，则修改密码，写入文件 
			if(str1 == str2 ){
				fout.open("password.txt",ios::out);
	            if(fout.fail())
	            {
		             cout<<endl<<"文件读取失败!"<<endl;
		             return;
	            }
	            fout<<str1;
	            fout.close();
				iSeller.setPassword(str1);
				cout<<endl<<"密码更新成功"<<endl;
			}
			else 
			{
			    cout<<endl<<"两次新密码不同"<<endl;
			}
		}
		cout<<left;
cout<<endl<<"           "<<setw(30)<<"1. 新增"<<setw(20)<<"2. 删除"<<endl;
cout<<"           "<<setw(30)<<"3. 查询"<<setw(20)<<"4.确认订单"<<endl;
	   cout<<"           "<<setw(30)<<"5.修改密码"<<setw(20)<< "6.排序"<<endl;
	   cout << "           " << setw(30) << "7.返回菜单" << endl;

	}
	/*if(choice == "6")
	{
	    return;
	}*/
}

//卖家
void seviceForBuyer()
{
	Buyer ibuyer;
	Menu iMenu;
    Order iOrder;
	string n;
	// 1为点菜，2为查询订单，3为修改订单 ，46.返回主菜单 
	cout<<left;
	cout << endl << "请选择你的操作:" << endl;
	cout << endl << "           " << setw(20) << "1. 订餐" << setw(20) << "2. 查询" << endl;
	cout << "           " << setw(20) << "3. 取消订单" << setw(20) << "4.返回主菜单" << endl;
	cin>>n;
    while(n!="4")
	{
        //处理错误输入 
	    if(n != "1" && n != "2" && n!= "3" )
		{
			cout<<endl<<"请重新输入"<<endl;
			cin>>n;
			continue;
		}
		//从文件读取以初始化菜单信息和订单信息 
		order.clear();
		fout.open("order.txt",ios::in);
		if(fout.fail())
		{
			cout<<endl<<"文件读取失败!"<<endl;
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
			cout<<endl<<"文件读取失败!"<<endl;
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
		cout<<endl<<"请选择你的操作:"<<endl;
		cout<<endl<<"           "<<setw(20)<<"1. 订餐"<<setw(20)<<"2. 查询"<<endl;
	    cout<<"           "<<setw(20)<<"3. 取消"<<setw(20)<<"4.返回主菜单"<<endl;
		cin>>n;
	}
	if (n == "4")
	{
		system("cls");
		return;
	}
}
