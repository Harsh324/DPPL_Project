#include<iostream>
#include<cstddef>

using namespace std;

namespace Memory
{
    enum Choice
    {
        first = 1,
        Best = 2,
        Next = 3
    };

    struct Node
    {
        Node* Next;
        Node* Prev;

        int Size;

        int Flag;

        void *Location;
    };



    class First_Fit
    {
        public:
            Node* Node1 = NULL;
            Node* head;

            size_t SIZE;

        public:
            First_Fit(Node* Head, size_t Req_size)
            {
                this->Node1 = Head;
                this->SIZE = Req_size;
                this->head = Head;
            }

            Node* Apply_Strategy()
            {
                while(true)
                {
                    if((Node1->Flag == 0) && Node1->Size >= this->SIZE)
                        return Node1;
                    Node1 = Node1->Next;

                    if(Node1 == head)
                        break;
                }
                /*
                while(Node1->Next != this->head)
                {
                    if((Node1->Flag == 0) && Node1->Size >= this->SIZE)
                        return Node1;
                    Node1 = Node1->Next;
                }*/
                return NULL;
            }
    
    };

    class Next_Fit
    {
        public:
            Node* Node1 = NULL;
            Node* next;

            size_t SIZE;

        public:
            Next_Fit(Node* Next, size_t Req_size)
            {
                this->Node1 = Next;
                this->SIZE = Req_size;
                this->next = Next;
            }

            Node* Apply_Strategy()
            {
                while(true)
                {
                    if((next->Flag == 0) && next->Size >= this->SIZE)
                        return next;
                    next = next->Next;
                    if(next == this->Node1)
                        break;
                }
                /*
                while(this->next->Next != this->Node1)
                {
                    if((this->next->Flag == 0) && this->next->Size >= this->SIZE)
                        return this->next;
                }*/
                return NULL;
            }
    };

    class Best_Fit
    {
        public:
            Node* Node1 = NULL;
            Node* head = NULL;
            Node* BEST = NULL;

            size_t SIZE;

        public:
            Best_Fit(Node* Head, size_t Req_size)
            {
                //cout<<"In Best_Fit Constructor"<<endl;
                this->Node1 = Head;
                this->SIZE = Req_size;
                this->head = Head;
            }

            Node* Apply_Strategy()
            {
                //cout<<"Flag"<<endl;
                //cout<<this->Node1<<endl;
                //cout<<this->head<<endl;

                while(true)
                {
                    //cout<<"Trying Best While loop"<<endl;
                    if((Node1->Flag == 0) && (Node1->Size >= this->SIZE))
                    {
                        if(!BEST || (Node1->Size < BEST->Size))
                            BEST = Node1;
                    }
                    Node1 = Node1->Next;
                    if(Node1 == this->head)
                    {
                        //cout<<"Breaking"<<endl;
                        break;
                    }
                }
                /*
                while(Node1->Next != this->head)
                {
                    cout<<"Trying Best While loop"<<endl;
                    if((Node1->Flag == 0) && (Node1->Size >= this->SIZE))
                    {
                        if(BEST == NULL || (Node1->Size < BEST->Size))
                            BEST = Node1;
                    }
                    Node1 = Node1->Next;
                }*/
                return BEST;
            }
    };


    
    class Memory_Management
    {
        Choice choice;
        void* Memory_block = NULL;

        Node* Head = NULL;
        Node* Next = NULL;

        size_t Total_size;

        public:

            Memory_Management(Choice Ch, size_t Size)
            {
                //cout<<"Memory Constructor created "<<endl;

                this->choice = Ch;
                this->Total_size = Size;

                if(NULL != Head)
                    free(Head);
                if(NULL != Memory_block)
                    free(Memory_block);


                //Assigning the memory block
                Memory_block = malloc(this->Total_size);
                //cout<<"Memory_block = "<<Memory_block<<endl;

                //Assiging the memory to Head Node
                Head = (Node*)malloc(sizeof(Node));
                //cout<<"Head = "<<Head<<endl;
                Head->Location = this->Memory_block;
                Head->Size = this->Total_size;
                Head->Flag = 0;
                Next = Head;

                Head->Next = Head;
                Head->Prev = Head;
                //cout<<"1 : "<<Head<<endl;
                //cout<<"2 : "<<Next<<endl;
                //cout<<"Memory Block of Size : "<<Size<<" is Created"<<endl;
            }


            void* Allocate(size_t size)
            {
                this->Print_Linked_List(this->Head);
                cout<<"\nTrying to Allcoate memory for size : "<<size<<endl;
                Node* Block = NULL;

                if(this->choice == first)
                {
                    First_Fit Strat = First_Fit(this->Head, size);
                    Block = Strat.Apply_Strategy();
                    //cout<<"Applying the First Fit Strategy"<<endl;
                }

                else if(this->choice == Best)
                {
                    //cout<<"Printing Head in Allocate"<<endl;
                    //this->Print_Linked_List(this->Head);
                    Best_Fit Strat = Best_Fit(this->Head, size);
                    Block = Strat.Apply_Strategy();
                    cout<<"\nApplying the Best Fit Strategy"<<endl;
                }

                else
                {
                    Next_Fit Strat = Next_Fit(this->Next, size);
                    Block = Strat.Apply_Strategy();
                    //cout<<"Applying the Next Fit Strategy"<<endl;
                }

                //cout<<Block->Size<<endl;
                //cout<<size<<endl;


                if(Block->Size > size)
                {
                    // New node created
                    //cout<<"Inside Allcoate If"<<endl;
                    Node* New = (Node*)malloc(sizeof(Node));

                    // Insertion of new node
                    New ->Next = Block->Next;
                    New->Next->Prev = New;
                    New->Prev = Block;
                    Block->Next = New;

                    New->Size = (Block->Size - size);
                    New->Flag = 0;
                    New->Location = (int*)Block->Location + size;
                    Block->Size = size;
                    //cout<<"! New "<<New<<endl;
                    //cout<<"! Block "<<Block<<endl;
                    //this->Print_Node(Block);
                    //this->Print_Node(New);
                    
                }
                else
                {
                    //cout<<"In Else"<<endl;
                    this->Next = Block->Next;
                }

                Block->Flag = 1;
                cout<<"\nBlock of Size "<<size<<" is Created "<<endl;
                //this->Print_Node(Block);
                //cout<<this->Head->Size<<" , "<<this->Head->Location<<endl;
                //this->Print_Linked_List(this->Head);
                
                return Block->Location;
            }

            void Deallocate(void* node)
            {
                cout<<"Memory Block is deleted"<<endl;
                this->Print_Linked_List(this->Head);
                Node* Pointer = this->Head;
                while(Pointer->Next != this->Head)
                {
                    if(Pointer->Location == node)
                        break;
                    Pointer = Pointer->Next;
                }

                Pointer->Flag = 0;

                if(Head != Pointer && (Pointer->Prev->Flag == 0))
                {
                    Node* Node1 = Pointer->Prev;
                    Node1->Next = Pointer->Next;
                    Node1->Next->Prev = Node1;
                    Node1->Size += Pointer->Size;

                    if(Pointer == this->Next)
                        this->Next = Node1;

                    free(Pointer);
                    Pointer = Node1;
                }

                if(Head != Pointer->Next && (Pointer->Next->Flag == 0))
                {
                    Node* Node2 = Pointer->Next;
                    Pointer->Next = Node2->Next;
                    Pointer->Next->Prev = Pointer;
                    Pointer->Size += Node2->Size;
                    
                    if(this->Next == Node2)
                        this->Next = Pointer;
                    
                    free(Node2);
                }
            }

            void Print_Linked_List(Node* Head)
            {
                cout<<"Printing the Linked List"<<endl;
                int Count = 1;
                while(true)
                {
                    cout<<Count<<". (Size : "<<Head->Size<<" , Flag : "<<Head->Flag<<" , Memory_Block : "<<Head->Location<<" )"<<endl;
                    Head = Head->Next;
                    if(Head == this->Head)
                        break;
                    Count++;
                }
            }

            void Print_Node(Node* node)
            {
                cout<<"\nPrinting the node"<<endl;
                cout<<"(Size : "<<Head->Size<<" , Flag : "<<Head->Flag<<" , Memory_Block : "<<Head->Location<<" )"<<endl;

            }

            
            // void print_memory() 
            // {
            //     /* Iterate over memory list */
            //     Node* head = this->Head;
            //     cout<<head<<endl;
            //     cout<<head->Next<<endl;
            //     while(head->Next != this->Head)
            //     {
            //         printf("\tBlock %p,\tsize %d,\t%s\n", head->Location, head->Size, head->Flag);
            //         printf("\n");
            //         head = head->Next;
            //     }
            // }
            
    };








}