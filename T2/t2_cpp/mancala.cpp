#include <iostream>
#include <vector>
#include <emscripten/emscripten.h>

extern "C"
{
    int EMSCRIPTEN_KEEPALIVE mancala_result(int flag, int *seq, int size)
    {

        int board[2][6];
        int score[2] = {0};
        for (int i = 0; i < 2; ++i)
        {
            for (int j = 0; j < 6; ++j)
            {
                board[i][j] = 4;
            }
        }
        int currentPlayer = flag - 1;
        for (int i = 0; i < size; ++i)
        {
            int player = (seq[i] / 10) - 1;
            int hole = seq[i] % 10 - 1;
            if (player != currentPlayer || board[player][hole] == 0 || hole < 0 || hole >= 6)
            {
                return 30000 + i;
            }
            int stones = board[player][hole];
            board[player][hole] = 0;
            int index = hole + 1;

            while (stones > 0)
            {
                if (index == 6)
                {
                    if (player == currentPlayer)
                    {
                        score[player]++;
                        stones--;
                    }
                    player = 1 - player;
                    index = 0;
                }
                else
                {
                    board[player][index]++;
                    stones--;
                    index++;
                }
            }
            if (player == currentPlayer && index > 0 && board[player][index - 1] == 1 && board[1 - player][6 - index] > 0)
            {
                score[player] += board[1 - player][6 - index] + 1;
                board[player][index - 1] = 0;
                board[1 - player][6 - index] = 0;
            }

            if (!(player != currentPlayer && index == 0))
            { 
                currentPlayer = 1 - currentPlayer;
            }
        }
        int sum0 = 0;
        int sum1 = 0;
        for (int i = 0; i < 6; ++i)
        {
            sum0 += board[0][i];
            sum1 += board[1][i];
        }
        if (sum0 == 0 || sum1 == 0)
        {
            return 15000 + score[flag - 1] - score[2 - flag];
        }
        else
        {
            return 20000 + score[flag - 1];
        }
    }
}
