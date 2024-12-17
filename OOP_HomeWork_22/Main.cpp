#include<iostream>
#include"my_memory.hpp"


class Item {
public:
	Item() { std::cout << "Item has been created!\n"; }
	~Item() { std::cout << "Item has been deleted\n"; }
};


int main() {
	setlocale(LC_ALL, "RU");
	std::cout << "Тестирования собственного класса unique_ptr:\n";
	{
		my_std::unique_ptr<Item> p1(new Item);
		my_std::unique_ptr<Item> p2;
		std::cout << "p1 is " << (p1.isEmpty() ? "empty\n" : "not empty\n");
		std::cout << "p2 is " << (p2.isEmpty() ? "empty\n" : "not empty\n");
		std::cout << "The pointers were reversed\n";
		p2 = std::move(p1);
		std::cout << "p1 is " << (p1.isEmpty() ? "empty\n" : "not empty\n");
		std::cout << "p2 is " << (p2.isEmpty() ? "empty\n" : "not empty\n");
	}
	my_std::unique_ptr<int>p3(new int(3));
	std::cout << "Value of p3 is " << *p3 << '\n';
	std::cout << "Address of p3 is " << p3.get() << '\n';
	p3 = std::move(new int(5));
	std::cout << "Value of p3 is " << *p3 << '\n';
	std::cout << "Address of p3 is " << p3.get() << '\n';
	p3.reset();
	std::cout << "Address of p3 is " << p3.get() << '\n';
	std::cout << "*   *   *   *   *   *\n";
	std::cout << "\nТестирования собственного класса shared_ptr:\n";
	/*
	{
		my_std::shared_ptr<Item> s_p1(new Item);
		std::cout << "s_p1.use_count() = " << s_p1.use_count() << std::endl;
		std::cout << "Address of s_p1 is " << s_p1.get() << '\n';

		{
			//my_std::shared_ptr<Item> sp(s_p1);
			//std::cout << "sp.use_count() = " << sp.use_count() << std::endl;
			//std::cout << "Address of sp is " << sp.get() << '\n';

		}
	}
	std::cout << "-   -   -   -   -   -\n";

	my_std::shared_ptr<int> s_p2(new int(7));
	//my_std::shared_ptr<int> s_p3(s_p2);
	std::cout << "s_p2.use_count() = " << s_p2.use_count() << std::endl;
	//s_p3 = s_p2;
	//std::cout << "s_p3.use_count() = " << s_p3.use_count() << std::endl;*/
	{
		my_std::shared_ptr<Item> item_ptr1(new Item);
		std::cout << "item_ptr1: " << item_ptr1;
		{
			my_std::shared_ptr<Item> item_ptr2(item_ptr1);
			std::cout << "item_ptr2: " << item_ptr2;
		}
		std::cout << "item_ptr1: " << item_ptr1;
	}
	my_std::shared_ptr<int> ptr1(new int(15));
	*ptr1 = 100;
	std::cout << "ptr1 is value now: " << *ptr1 << std::endl;
	std::cout << ptr1;
	{
		std::cout << "Shared pointers ptr1, ptr2:\n";
		my_std::shared_ptr<int> ptr2 = ptr1;
		std::cout << ptr1;
		std::cout << ptr2;
		std::cout << "ptr2 is value now: " << *ptr2 << std::endl;
		{
			std::cout << "\nShared pointers ptr1, ptr2, ptr3:\n";
			my_std::shared_ptr<int> ptr3(ptr2);
			std::cout << ptr1;
			std::cout << ptr2;
			std::cout << ptr3;			
		}
		my_std::shared_ptr<int> tmp(new int(11));
		std::cout << "\nShared pointers ptr1, ptr2:\n";
		ptr2 = tmp;
		std::cout << ptr1;
		std::cout << ptr2;
	}
	std::cout << "\nShared pointers ptr1:\n";
	std::cout << ptr1;
	std::cout << "And ptr1 is value now: " << *ptr1 << std::endl;

	return 0;
}