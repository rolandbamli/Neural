#include <iostream>
#include <cmath>
#include <ctime>
#include <cstdlib>

float A[101];

void neuron()
{
  int a = 1;

  for(int i = 2; i <= 100; i++)
    if(A[i] > 0.0)
    {
      if(i - a > 1)
      {
        float x = A[i] - A[a];
        int n = i - a - 1;
        x = x/n;

        for(int j = a + 1; j < i; j++)
        {
          float tmp = A[a] + (j - a)*x;

          if(A[j] == 0)
            A[j] = tmp;
          else
            A[j] = (A[j] + tmp)/2.0;
        }
      }

      a = i;
    }
}

int main()
{
  std::cout << "Test for guessing the square root of numbers\n";

  for(int i = 0; i < 100; i++)
    A[i] = 0.0;

  A[1] = 1;
  A[100] = 10;

  for(int k = 0; k < 3; k++)
  {
    std::srand(std::time(NULL) + k);
    std::cout << "Input: 1, ";

    for(int i = 0; i < 10; i++)
    {
      int n;
      do
      {
        n = std::rand()%99 + 1;
      } while((int)sqrt(n)*sqrt(n) == n);

      A[n] = std::sqrt(n);
      std::cout << n << ", ";
    }

    std::cout << "100\n";

    neuron();
  }

  for(int i = 1; i < 100; i++)
    A[i] = std::abs(A[i]);

  std::cout << "\nTest:\n";
  for(int i = 2; i < 10; i++)
    std::cout << i*i << " : " << A[i*i] << "\n";

  return 0;
}
