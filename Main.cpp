#include"Memory_management.h"
#include<iostream>

using namespace std;
using namespace Memory;


int main()
{
    Memory_Management MM = Memory_Management(Best, 500);
    
    void* One = MM.Allocate(50);
    void* Two = MM.Allocate(100);
    //MM.print_memory();
    void* Three = MM.Allocate(50);
    //MM.print_memory();
    MM.Deallocate(Two);
    MM.Deallocate(One);
    void* Four = MM.Allocate(100);
    //MM.print_memory();

}