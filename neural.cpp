#include <iostream>
#include <cmath>

int A[2][2][2][2][2];

void input()
{
  for(int a = 0; a < 2; a++)
    for(int b = 0; b < 2; b++)
      for(int c = 0; c < 2; c++)
        for(int d = 0; d < 2; d++)
          for(int e = 0; e < 2; e++)
          {
            int out_zero = 0, out_one = 0;

            if(A[a][b][c][d][e] == -1)
            {
              for(int i = 0; i < 2; i++)
                for(int j = 0; j < 2; j++)
                  for(int k = 0; k < 2; k++)
                    for(int l = 0; l < 2; l++)
                      for(int m = 0; m < 2; m++)
                        if(A[i][j][k][l][m] == 0 || A[i][j][k][l][m] == 1)
                        {
                          if(std::abs(i - a) + std::abs(j - b) + std::abs(k - c) + std::abs(l - d) + std::abs(m - e) == 1)
                          {
                            if(A[i][j][k][l][m] == 1)
                              out_one++;
                            else
                              out_zero++;
                          }
                        }

              if(out_one > out_zero)
                A[a][b][c][d][e] = 11;
              else if(out_zero > out_one)
                A[a][b][c][d][e] = 10;

              std::cout << a << " " << b << " " << c << " " << d << " " << e << " -> 0/1\n";
            }
            else
              std::cout << a << " " << b << " " << c << " " << d << " " << e << " -> " << A[a][b][c][d][e] << "\n";
          }
}

int main()
{
  for(int i = 0; i < 2; i++)
    for(int j = 0; j < 2; j++)
      for(int k = 0; k < 2; k++)
        for(int l = 0; l < 2; l++)
          for(int m = 0; m < 2; m++)
            if(i == 1 && j == 1 && k == 1 && l == 1 && m == 1)
              A[i][j][k][l][m] = 1;
            else if(i == 0 && j == 0 && k == 0 && l == 0 && m == 0)
              A[i][j][k][l][m] = 0;
            else
              A[i][j][k][l][m] = -1;

  int n = 0, db = 0;
  while(1)
  {
    std::cout << "\nStage " << n++ << ":\n";

    input();

    int db2 = 0;
    for(int i = 0; i < 2; i++)
      for(int j = 0; j < 2; j++)
        for(int k = 0; k < 2; k++)
          for(int l = 0; l < 2; l++)
            for(int m = 0; m < 2; m++)
            {
              if(A[i][j][k][l][m] >= 10)
                A[i][j][k][l][m] -= 10;
              if(A[i][j][k][l][m] == -1)
                db2++;
            }

    if(db == db2)
      break;
    else
      db = db2;
  }

  std::cout << "\nFinal:\n";
  input();

  return 0;
}