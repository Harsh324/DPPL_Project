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
                while(Node1->Next != this->head)
                {
                    if((Node1->Flag == 0) && Node1->Size >= this->SIZE)
                        return Node1;
                    Node1 = Node1->Next;
                }
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
                while(this->next->Next != this->Node1)
                {
                    if((this->next->Flag == 0) && this->next->Size >= this->SIZE)
                        return this->next;
                }
                return NULL;
            }
    };

    class Best_Fit
    {
        public:
            Node* Node1 = NULL;
            Node* head;
            Node* BEST = NULL;

            size_t SIZE;

        public:
            Best_Fit(Node* Head, size_t Req_size)
            {
                this->Node1 = Head;
                this->SIZE = Req_size;
                this->head = Head;
            }

            Node* Apply_Strategy()
            {
                while(Node1->Next != this->head)
                {
                    if((Node1->Flag == 0) && (Node1->Size >= this->SIZE))
                    {
                        if(BEST == NULL || (Node1->Size < BEST->Size))
                            BEST = Node1;
                    }
                    Node1 = Node1->Next;
                }
                return BEST;
            }
    };


    //typedef struct Node Mem_Block;
    
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
            }


            void* Allocate(size_t size)
            {
                Node* Block = NULL;

                if(this->choice == first)
                {
                    First_Fit Strat = First_Fit(this->Head, size);
                    Block = Strat.Apply_Strategy();
                }

                else if(this->choice == Best)
                {
                    Best_Fit Strat = Best_Fit(this->Head, size);
                    Block = Strat.Apply_Strategy();
                }

                else
                {
                    Next_Fit Strat = Next_Fit(this->Next, size);
                    Block = Strat.Apply_Strategy();
                }


                if(Block->Size > size)
                {
                    // New node created
                    Node* New = (Node*)malloc(sizeof(Node));

                    // Insertion of new node
                    New ->Next = Block->Next;
                    New->Next->Prev = New;
                    New->Prev = Block;

                    New->Size = (Block ->Size - size);
                    New->Flag = 0;
                    New->Location = (int*)Block->Location + size;
                    Block->Size = size;
                }
                else
                    this->Next = Block->Next;

                Block->Flag = 1;
                //cout<<this->Head->Size<<" , "<<this->Head->Location<<endl;
                return Block->Location;
            }

            void Deallocate(void* node)
            {
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