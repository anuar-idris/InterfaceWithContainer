// InterfaceWithContainer.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <iostream>
#include <vector>

//Interface Class, to suit polymorphism
//Based on principle, works on Interface, not with implementation
class IAnimal
{
public:
    virtual void movement() = 0;

};

//Create a subclass with a contract with IAnimal
class Dog : public IAnimal
{
public:
    void movement()
    {
        std::cout << "Jumping with 4 legs!\n";
    };
};

//Create another subclass with a contract with IAnimal
class Duck : public IAnimal
{
public:
    void movement()
    {
        std::cout << "Gliding with 2 legs!\n";
    };
};

//MyNumber is a class with container of Animal
//which is a Composite class?
class MyCompositeClass
{
public:
    //Constructor
    MyCompositeClass(const std::initializer_list<IAnimal*>& v) {
        for (auto itm : v) {
            mVec.push_back(itm);
        }
    }

    //Method
    void Movement() {
        for (auto itm : mVec) {
            itm->movement();
        }
    }

    void DeleteVector() {
        //if the pointer is created inside the class, then it is worth to do like below
        //for (auto itm : mVec)
        //{
        //    delete itm;
        //}
        mVec.clear();
    }

    //Attributes
private:
    std::vector<IAnimal*> mVec;
};

int main()
{
    //method to detect memory leaks. If we are not sure which is the exit
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    std::cout << "Hello World!\n";

    //implement initialization list based on Lambda type
    Dog m_Dog;
    Duck m_Duck;

    //Create pointer here
    IAnimal *a1 = new Dog; 
    IAnimal *a2 = new Duck;

    //Kludge implementation to allow for auto deallocation when this main function out of the scope    
    //std::shared_ptr<IAnimal> smart_a1(a1);
    //std::shared_ptr<IAnimal> smart_a2(a2);    

    //create initialization list, consisted of pointer above
    auto iter = { a1,a2 };

    MyCompositeClass m = { iter };
    m.Movement();       // 1 2 3 4
    m.DeleteVector();   //last point before MycompositeClass goes out of scope, clear the vector.Basically no need since it is an object and it will be deleted by program.

    //since pointer a1 and a2 was created here, it will need to be deleted here to, just before out of scope.
    delete a1;
    delete a2;

    //method to detect memory leaks. Only if we certain only one exit
    //_CrtDumpMemoryLeaks();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
