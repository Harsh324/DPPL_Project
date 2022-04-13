#include"Memory_management.h"
#include<iostream>

using namespace std;
using namespace Memory;


int main()
{
    Memory_Management MM = Memory_Management(Best, 500);

    void* One = MM.Allocate(50);
    cout<<"\n**************************\n"<<endl;
    void* Two = MM.Allocate(100);
    cout<<"\n**************************\n"<<endl;
    //MM.print_memory();
    void* Three = MM.Allocate(40);
    cout<<"\n**************************\n"<<endl;
    //MM.print_memory();
    MM.Deallocate(Two);
    cout<<"\n**************************\n"<<endl;

    MM.Deallocate(One);

    cout<<"\n**************************\n"<<endl;


    void* Four = MM.Allocate(200);

    cout<<"\n**************************\n"<<endl;

    void * Five = MM.Allocate(100);

    cout<<"\n**************************\n"<<endl;

    MM.Deallocate(Five);

    //MM.print_memory();

}