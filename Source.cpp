#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <functional>
#include <vector>
#include <sstream>
#include <iterator>
#include <set>
#include <cmath>
#include <unordered_map>
#include <memory>
#include <stack> 

using namespace std;

const char* TOO_CHAOTIC = "Too chaotic";

int TotalBribes(vector<int>& q)
{
    int bribes = 0;
    int totalBribes = 0;
    int aux = 0;

    for (int i = 0; i < q.size()-1; i++)
    {
        if (q[i] > q[i + 1])
        {
            bribes++;
            aux = q[i];
            q[i] = q[i + 1];
            q[i + 1] = aux;
            if (bribes == 3)
            {
                printf("%s\n", TOO_CHAOTIC);
                totalBribes = -1;
                break;
            }
        }
        else
        {
            totalBribes+=bribes;
            bribes = 0;
        }
    }
    if (totalBribes == -1)
    {
        return totalBribes;
    }
    else
    {
        return totalBribes+bribes;
    }
}

void minimumBribes(vector<int> q)
{
    int totalBribes = 0;
    while ((!is_sorted(q.begin(), q.end())) & (totalBribes != -1))
    {
        totalBribes += TotalBribes(q);
    }
    if (totalBribes != -1)
    {
        printf("%d\n", totalBribes);
    }
}

long repeatedString(string s, long n)
{
    long aOccurrencies = 0;
    long aExtra = 0;
    long timesS = n / s.length();
    long extraChar = n % s.length();

    for (long i = 0; i < s.length(); i++)
    {
        if (s[i] == 'a')
        {
            aOccurrencies++;
            if (i < extraChar)
            {
                aExtra++;
            }
        }
    }

    aOccurrencies = aOccurrencies * timesS + aExtra;
    return aOccurrencies;
}

int minimumSwaps(vector<int> A)
{
    int swaps = 0;
    vector <bool> rightPos;

    for (int i = 0; i < A.size(); i++)
    {
        rightPos.push_back(false);
    }

    while (!is_sorted(A.begin(), A.end()))
    {
        for (int i = 0; i < A.size() - 1; i++)
        {
            int realPos = A[i] - 1;

            if (i != realPos)
            {
                if (!rightPos[i])
                {
                    int aux;

                    aux = A[realPos];
                    A[realPos] = A[i];
                    A[i] = aux;
                    rightPos[realPos] = true;
                    swaps++;
                }
            }
            else
            {
                rightPos[realPos] = true;
            }
        }
    }
    return swaps;
}

long arrayManipulation(int n, vector<vector<int>> queries)
{
    long maxValue = -1;
    int a, b, k;
    long sum = 0;
    vector <int> A;

    for (int i = 0; i < n; i++)
    {
        A.push_back(0);
    }

    for (int i = 0; i < queries.size(); i++)
    {
        a = queries[i][0];
        b = queries[i][1];
        k = queries[i][2];

        A[a-1] += k;

        if ((b) < n)
        {
            A[b] -= k;
        }
    }

    for (int j = 0; j < n; j++)
    {
        sum += A[j];

        if (maxValue < sum)
        {
            maxValue = sum;
        }
    }

    return maxValue;
}

void Swap(vector<int> &arr, int i, int j)
{
    int aux = arr[i];
    arr[i] = arr[j];
    arr[j] = aux;
}

void BubbleSort(vector<int> &a) 
{
    int numSwaps = 0;

    for (int i = 0; i < a.size(); i++)
    {
        for (int j = 0; j < a.size()-1; j++)
        {
            if (a[j] > a[j + 1])
            {
                Swap(a, j, j+1);
                numSwaps++;
            }
        }
    }

    int firstElement = a[0];
    int lastElement = a[(a.size())-1];

    printf("Array is sorted in %d swaps.\nFirst Element: %d\nLast Element: %d\n", numSwaps, firstElement, lastElement);
}

int Partition(vector<int> &toysList, int low, int high)
{
    int pivotValue = toysList[high];
    int i = low - 1;

    for (int j = low; j <= high - 1; j++)
    { 
        if (toysList[j] < pivotValue)
        {
            i++;
            Swap(toysList, i, j);
        }
    }
    int newPivotIndex = i + 1;
    Swap(toysList, newPivotIndex, high);

    return newPivotIndex;
}
void QuickSort(vector<int> &toysList, int low, int high)
{
    if (low < high)
    {
        int pivot = Partition(toysList, low, high);

        QuickSort(toysList, low, pivot-1);
        QuickSort(toysList, pivot+1, high);
    }
}

int MaximumToys(vector<int> toysList, int k)
{
    int pricesListSize = toysList.size();

    // Bubble Sort O n2
    //for (int i = 0; i < pricesListSize; i++)
    //{
    //    for (int j = 0; j < pricesListSize -1; j++)
    //    {
    //        if (prices[j] > prices[j + 1])
    //        {
    //            Swap(prices, j, j+1);
    //        }
    //    }
    //}

    // Quick Sort O n - Lineal

    QuickSort(toysList, 0, pricesListSize -1);

    int sum = 0;
    int toys = 0;

    for (int i = 0; i < pricesListSize; i++)
    {
        if (sum + toysList[i] <= k)
        {
            toys++;
            sum += toysList[i];
        }
        else
        {
            break;
        }
    }

    return toys;
}

class TextInput {
private:
    char x;

public:
    static string input;
    // constructor to initialize type
    TextInput() : x('-') {}

    // declare virtual function
    string getValue() {
        return input;
    }
    // declare virtual function
    virtual void add(char x) {
        input.push_back(x);
    }
};

string TextInput::input;

class NumericInput : public TextInput {
private:
    char x;

public:
    // constructor to initialize type
    NumericInput() : x('-') {}

    void add(char x) override {
        if (!isalpha(x))
        input.push_back(x);
    }
};

class FunctionCache
{
    class Parameters
    {
    public:
        Parameters(int first, int second)
        {
            this->first = first;
            this->second = second;
        }

        int first;
        int second;
    };

public:
    FunctionCache(std::function<int(int, int)> function) : function(function) {}

    int calculate(int first, int second)
    {
        auto args = make_shared<Parameters>(first, second);
        auto it = calculations.find(args);
        if (it != calculations.end())
            return it->second;

        int calculation = function(first, second);
        calculations[args] = calculation;
        return calculation;
    }

private:
    std::unordered_map<std::shared_ptr<Parameters>, int> calculations;
    std::function<int(int, int)> function;
};

int modulo(int a, int b)
{
    std::cout << "Function modulo has been called.\n";
    return a % b;
}

class WindowManager
{
private:
    std::vector<std::string> windows;

public:

    void open(const std::string windowName)
    {
        windows.push_back(windowName);
    }

    void close(const std::string windowName)
    {
        for (int i = 0; i < windows.size(); i++)
        {
            if (windows[i] == windowName)
                windows[i] = "0";
        }
    }

    std::string getTopWindow()
    {
        if (windows[windows.size() - 1] == "0")
        {
            for (int i = windows.size() - 1; i <= 0; i--)
            {
                if (windows[i] != "0")
                    return windows[i];
            }
        }
        else
            return windows[windows.size() - 1];
    }
};

int CerosEnBinario(int decimal) {
    int remainder, product = 1;
    vector<int> binary;

    while (decimal != 0) 
    {
        remainder = decimal % 2;
        binary.push_back(remainder);
        decimal = decimal / 2;
        product *= 10;
    }
    reverse(binary.begin(), binary.end());

    int count = 0;
    int maxCount = 0;
    int binarySize = binary.size();

    for (int i = 0; i < binarySize; i++)
    {
        if (binary[i] == 0)
        {
            count++;
        }
        else
        {
            if (maxCount < count)
            {
                maxCount = count;
            }
            count = 0;
        }
    }
    return maxCount;
}

vector<int> MoveArrayPosition(vector<int> array, int k)
{
    vector<int> newArray;
    const int arraySize = array.size();

    for (int i = 0; i < arraySize; i++)
    {
        int newPosition = i + k -1;

        if (newPosition < arraySize)
        {
            newArray.push_back(array[newPosition]);
        }
        else
        {
            int otherPos = newPosition - (arraySize - 1);
            newArray.push_back(array[otherPos-1]);
        }
    }
    return newArray;
}

void PrintArray(vector<int> array)
{
    printf("Array [ ");
    for (int i = 0; i < array.size(); i++)
    {
        printf("%d ", array[i]);
    }
    printf("]");
}

int main()
{
    vector <int> arr{ 1,2,3,4};
    int k = 4;

    vector<int> newArray = MoveArrayPosition(arr, k);
    PrintArray(newArray);

   /* int decimal = 6;
    printf("RESPUESTA: %d",CerosEnBinario(decimal));*/

    //WindowManager wm;
    //wm.open("Calculator");
    //wm.open("Browser");
    //wm.open("Player");
    //wm.close("Browser");
    //std::cout << wm.getTopWindow();

/*
    FunctionCache cache(modulo);

    // Function modulo should be called.
    std::cout << cache.calculate(5, 2) << std::endl;

    // Function modulo should be called.
    std::cout << cache.calculate(7, 4) << std::endl;

    // Function modulo shouldn't be called because we have already made a call with arguments (5, 2)!
    std::cout << cache.calculate(5, 2) << std::endl;
    */
    //----1----
    //
    //string s = "a";
    //long n = 10000000000;
    //printf("n: %ld \n", n);
    //long result = repeatedString(s, n);
    //
    //cout << result << "\n";
    //
    //---------

   // //----2---- 
   //  
   // int t,n;
   //  
   // //Opening the file
   // ifstream inputfile("Bribes.txt");
   //
   // if (!inputfile.is_open())
   //     cout << "Error opening file";
   //
   // inputfile >> t;
   //
   // for (int i = 0; i < t; i++)
   // {
   //     inputfile >> n;
   //     vector <int> q;
   //     for (int i = 0; i < n; i++)
   //     {
   //         int value;
   //         inputfile >> value;
   //         q.push_back(value);
   //      }
   //     minimumBribes(q);
   // }
   ////---------

    // //----Minimum Swaps----
    //vector <int> arr{ 7,1,3,2,4,5,6 };
    //printf("%d", minimumSwaps(arr));
    ////---------

//
//    //----Array Manipulation----
//
//    //Opening the file
//    ifstream inputfile("ArrayManipulation.txt");
// 
//    int n, m;
//
//    if (!inputfile.is_open())
//        cout << "Error opening file";
// 
//    inputfile >> n;
//    inputfile >> m;
// 
//    vector<vector<int>> queries(m);
//
//    for (int i = 0; i < m; i++)
//    {
//        queries[i].resize(3);
//
//        int a,b,k;
//        inputfile >> a;
//        inputfile >> b;
//        inputfile >> k;
//        queries[i][0] = a;
//        queries[i][1] = b;
//        queries[i][2] = k;
//    }
//
//    long result = arrayManipulation(n, queries);
//
//    cout << result << "\n";
//  // ---------
//

    // //----Bubble Sort----
    //vector <int> arr{ 3,2,1};
    //BubbleSort(arr);
    ////---------
    //

    ////----MaximumToys Sort----
    //vector <int> arr{1,12,5,111,200,1000,10};
    //int k = 50;
    //
    //printf("%d", MaximumToys(arr, k));
    ////---------
    //
   
   /* //----Set----
    // empty set container
    set<string> Names;

    std::vector<std::string> names1 = { "Ava", "Emma", "Olivia" };
    std::vector<std::string> names2 = { "Olivia", "Sophia", "Emma" };

    for (int i = 0; i < names1.size(); i++)
    {
        Names.insert(names1[i]);
    }

    for (int i = 0; i < names2.size(); i++)
    {
        Names.insert(names2[i]);
    }

    vector<string> result(Names.begin(), Names.end());
    cout << "Names:";
    for (int i = 0; i < result.size(); i++)
    {
        cout << result[i];
    }
    cout << endl;*/

    //// insert elements in random order
    //s1.insert(40);
    //s1.insert(30);
    //s1.insert(60);
    //s1.insert(20);
    //s1.insert(50);
    //
    //// only one 50 will be added to the set
    //s1.insert(50);
    //s1.insert(10);
    //
    //// printing set s1
    //set<int, greater<int> >::iterator itr;
    //cout << "\nThe set s1 is : \n";
    //for (itr = s1.begin(); itr != s1.end(); itr++) {
    //    cout << *itr << " ";
    //}
    //cout << endl;

//
    //// assigning the elements from s1 to s2
    //set<int> s2(s1.begin(), s1.end());
    //
    //// print all elements of the set s2
    //cout << "\nThe set s2 after assign from s1 is : \n";
    //for (itr = s2.begin(); itr != s2.end(); itr++) {
    //    cout << *itr << " ";
    //}
    //cout << endl;
//
    //// remove all elements up to 30 in s2
    //cout << "\ns2 after removal of elements less than 30 "
    //    ":\n";
    //s2.erase(s2.begin(), s2.find(30));
    //for (itr = s2.begin(); itr != s2.end(); itr++) {
    //    cout << *itr << " ";
    //}
//
    //// remove element with value 50 in s2
    //int num;
    //num = s2.erase(50);
    //cout << "\ns2.erase(50) : ";
    //cout << num << " removed\n";
    //for (itr = s2.begin(); itr != s2.end(); itr++) {
    //    cout << *itr << " ";
    //}
//
    //cout << endl;
//
    //// lower bound and upper bound for set s1
    //cout << "s1.lower_bound(40) : \n"
    //    << *s1.lower_bound(40) << endl;
    //cout << "s1.upper_bound(40) : \n"
    //    << *s1.upper_bound(40) << endl;
//
    //// lower bound and upper bound for set s2
    //cout << "s2.lower_bound(40) :\n"
    //    << *s2.lower_bound(40) << endl;
    //cout << "s2.upper_bound(40) : \n"
    //    << *s2.upper_bound(40) << endl;
/*
    //-----Quadratic ecuation-----
    float a, b, c, x1, x2, discriminant, realPart, imaginaryPart;
    //cout << "Enter coefficients a, b and c: ";
   // cin >> a >> b >> c;
    a = 2;
    b = 10;
    c = 8;
    discriminant = b * b - 4 * a * c;

    if (discriminant > 0) {
        x1 = (-b + sqrt(discriminant)) / (2 * a);
        x2 = (-b - sqrt(discriminant)) / (2 * a);
        cout << "Roots are real and different." << endl;
        cout << "x1 = " << x1 << endl;
        cout << "x2 = " << x2 << endl;
    }

    else if (discriminant == 0) {
        cout << "Roots are real and same." << endl;
        x1 = -b / (2 * a);
        cout << "x1 = x2 =" << x1 << endl;
    }

    else {
        realPart = -b / (2 * a);
        imaginaryPart = sqrt(-discriminant) / (2 * a);
        cout << "Roots are complex and different." << endl;
        cout << "x1 = " << realPart << "+" << imaginaryPart << "i" << endl;
        cout << "x2 = " << realPart << "-" << imaginaryPart << "i" << endl;
    }

    //------VIRTUAL------
    TextInput* input = new TextInput();
    input->add('1');
    input->add('a');
    input->add('0');
    std::cout << input->getValue();
*/

    return 0;
 }