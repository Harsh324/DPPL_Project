/**
 * @file Big_int.h
 *
 * @group - 47
 *
 * @authors:
 * Aniket B Agarwal (BT20CSE001)
 * Harsh Tripathi(BT20CSE040)
 * Nilay Singh(BT20CSE071)
 * Aniket Kumar giri(BT20CSE089)
 *
 * @date 2022-02-22
 **/

#include <iostream>
using namespace std;

namespace Lib
{
    class Big_int
    {
    public:
        /**
         * @brief This method Adds two numbers , Large numbers(Big int) can be handeled by
         * this method, outputs the addition of two numbers.
         *
         * @param Num1 First number in form of string
         * @param Num2 Second number in form of input
         */
        void Add(string Num1, string Num2)
        {
            // Taking length(number of digits) of the input numbers in Len1, Len2 varible
            int Len1 = Num1.length(), Len2 = Num2.length();

            // Three ararys are declared two for each input numbers to store
            // Other array is to store Addition of the two numbers.
            int Arr1[Len1], Arr2[Len2], Arr3[max(Len1, Len2) + 1];

            int Count = 0, Sum = 0;

            // Storing the Digits of the First number in the array(Arr1)
            for (int i = Len1 - 1; i >= 0; i--)
                Arr1[Count++] = Num1[i] - '0';

            Count = 0;

            // Storing the Digits of the Second number in the array(Arr2)
            for (int i = Len2 - 1; i >= 0; i--)
                Arr2[Count++] = Num2[i] - '0';

            // Traversing throught the having less length than the other
            // and storing sum of corresponding indexes

            for (int i = 0; i < min(Len1, Len2); i++)
            {
                Sum = Sum + Arr1[i] + Arr2[i];
                if (Sum > 9)
                {
                    Arr3[i] = Sum % 10;
                    Sum = 1;
                }
                else
                {
                    Arr3[i] = Sum;
                    Sum = 0;
                }
            }
            Count = min(Len1, Len2);

            // if Length of the both array is unequal
            if (Len1 != Len2)
            {
                // if Length of array2 is more than array1
                // Traversing through remaining elements of the larger array.
                if (Len1 < Len2)
                {
                    while (Count < Len2)
                    {
                        Sum = Sum + Arr2[Count];
                        if (Sum > 9)
                        {
                            Arr3[Count] = Sum % 10;
                            Sum = 1;
                            Count++;
                        }
                        else
                        {
                            Arr3[Count] = Sum;
                            Sum = 0;
                            Count++;
                        }
                    }
                    if (Sum == 1)
                    {
                        Arr3[Count++] = 1;
                        Sum = 0;
                    }
                }
                else
                {
                    while (Count < Len1)
                    {
                        Sum = Sum + Arr1[Count];
                        if (Sum > 9)
                        {
                            Arr3[Count] = Sum % 10;
                            Sum = 1;
                            Count++;
                        }
                        else
                        {
                            Arr3[Count] = Sum;
                            Sum = 0;
                            Count++;
                        }
                    }
                    if (Sum == 1)
                    {
                        Arr3[Count++] = 1;
                        Sum = 0;
                    }
                }
            }
            // if length of the arrays are equal then this condition will be true
            else
            {
                if (Sum == 1)
                {
                    Arr3[Count++] = 1;
                    Sum = 0;
                }
            }

            // printing output of the digits of the summation
            Count--;
            int Flag = 0;
            while (Count >= 0)
            {
                if (Arr3[Count] == 0 && Flag == 0)
                {
                    if (Count == 0)
                        cout << Arr3[0];
                    Count--;
                }
                else
                {
                    cout << Arr3[Count];
                    Count--;
                    Flag = 1;
                }
            }
            cout << endl;
        }

        /**
         * @brief This method Subtracts two numbers , basicaly computes larger - smaller.
         * two numbers are provided in form of string it automatically checks for larger,
         * among them and calculates difference
         *
         * @param Num1 First number input in form of string.
         * @param Num2 Second number input in form of string.
         */
        void Sub(string Num1, string Num2)
        {
            // Taking length(number of digits) of the input numbers in Len1, Len2 varible
            int Len1 = Num1.length(), Len2 = Num2.length();

            // Three ararys are declared two for each input numbers to store
            // Other array is to store Addition of the two numbers.
            int Arr1[Len1], Arr2[Len2], Arr3[max(Len1, Len2) + 1];

            int Count = 0, Sum = 0;

            // Storing the Digits of the First number in the array(Arr1)
            for (int i = Len1 - 1; i >= 0; i--)
                Arr1[Count++] = Num1[i] - '0';

            Count = 0;

            // Storing the Digits of the Second number in the array(Arr2)
            for (int i = Len2 - 1; i >= 0; i--)
                Arr2[Count++] = Num2[i] - '0';

            // if Length of the both array is unequal
            if (Len1 != Len2)
            {
                Count = 0;

                // Thsi Flag variable will act as carry
                int Flag = 0;

                // If Num2 > Num1 the this condition will be true.
                if (Len1 < Len2)
                {
                    // Traverse till lenght of first array and compute difference digit by digit.
                    for (int i = 0; i < Len1; i++)
                    {
                        int Diff = Arr2[i] - Arr1[i] - Flag;

                        if (Diff < 0)
                        {
                            Diff = Diff + 10;
                            Flag = 1;
                        }
                        else
                            Flag = 0;
                        Arr3[Count++] = Diff;
                    }

                    // Traverse till remaining element of the larger number and store in the third array.
                    while (Count < Len2)
                    {
                        int Diff = Arr2[Count] - Flag;
                        if (Diff < 0)
                        {
                            Diff = Diff + 10;
                            Flag = 1;
                        }
                        else
                            Flag = 0;
                        Arr3[Count++] = Diff;
                    }
                }

                // If length of the Second number is smaller than the first the nthis condition will be true.
                else
                {
                    Count = 0;
                    for (int i = 0; i < Len2; i++)
                    {
                        int Diff = Arr1[i] - Arr2[i] - Flag;

                        if (Diff < 0)
                        {
                            Diff = Diff + 10;
                            Flag = 1;
                        }
                        else
                            Flag = 0;
                        Arr3[Count++] = Diff;
                    }

                    while (Count < Len1)
                    {
                        int Diff = Arr1[Count] - Flag;
                        if (Diff < 0)
                        {
                            Diff = Diff + 10;
                            Flag = 1;
                        }
                        else
                            Flag = 0;
                        Arr3[Count++] = Diff;
                    }
                }
            }

            // If two number have same number of digits the this condition holds.
            else
            {
                Count = 0;
                int Val = Num1.compare(Num2), Flag = 0;

                // If the First number is Less than Second Number
                if (Val < 0)
                {
                    for (int i = 0; i < Len2; i++)
                    {
                        int Diff = Arr2[i] - Arr1[i] - Flag;

                        if (Diff < 0)
                        {
                            Diff = Diff + 10;
                            Flag = 1;
                        }
                        else
                            Flag = 0;
                        Arr3[Count++] = Diff;
                    }
                }

                // If the Second number is Less tha First number.
                else if (Val > 0)
                {
                    for (int i = 0; i < Len1; i++)
                    {
                        int Diff = Arr1[i] - Arr2[i] - Flag;

                        if (Diff < 0)
                        {
                            Diff = Diff + 10;
                            Flag = 1;
                        }
                        else
                            Flag = 0;
                        Arr3[Count++] = Diff;
                    }
                }

                // If the Both numbers are equal.
                else
                {
                    for (int i = 0; i < Len1; i++)
                    {
                        Arr3[Count++] = Arr1[i] = Arr2[i];
                    }
                }
            }

            // printing output of the digits of the Difference of the two numbers.
            Count--;
            int Flag = 0;
            while (Count >= 0)
            {
                if (Arr3[Count] == 0 && Flag == 0)
                {
                    if (Count == 0)
                        cout << Arr3[0];
                    Count--;
                }
                else
                {
                    cout << Arr3[Count];
                    Count--;
                    Flag = 1;
                }
            }
            cout << endl;
        }
    };
}