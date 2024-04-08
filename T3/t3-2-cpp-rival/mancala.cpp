
#include <emscripten/emscripten.h>
#include <iostream>
#include <climits>

const int BOARD_SIZE = 14;
const int BOARD_ANSWER_SIZE = 15;
const int OPERATOR_ANSWER_SIZE = 14;
const int DATA_BIT = 14;

bool is_game_over(const int *board)
{
    bool flag = false;
    for (int i = 0; i < 6; ++i)
    {
        if (board[i] != 0)
        {
            flag = true;
            break;
        }
    }
    if (!flag)
    {
        return true;
    }
    flag = false;
    for (int i = 7; i < 13; ++i)
    {
        if (board[i] != 0)
        {
            flag = true;
            break;
        }
    }
    return !flag;
}
// assuming the player is indeed winner.
int get_player_win_stones(const int *board, int player)
{
    int winner = 1;
    int winner_stones[2] = {board[6], board[13]};
    for (int i = 0; i < 6; ++i)
    {
        if (board[i] != 0)
        {
            winner = 2;
            break;
        }
    }
    for (int i = 0; i < 6; ++i)
    {
        winner_stones[winner - 1] += board[((2 - winner) * 7 + i)];
    }

    return winner_stones[player - 1] - winner_stones[2 - player];
}
// return next right player
int take_move(int *board, int current_player, int op, int *current_win_hole)
{
    int right_player = 0;
    int chosen_hole = 0;
    int current_stones = 0;
    int last_idx = 0, idx = 0, j = 0;
    current_player = op / 10;
    chosen_hole = op % 10 + (current_player - 1) * 7 - 1;
    current_stones = board[chosen_hole];
    current_player = op / 10;
    chosen_hole = op % 10 + (current_player - 1) * 7 - 1;
    current_stones = board[chosen_hole];
    board[chosen_hole] = 0;
    for (j = 0, idx = chosen_hole + 1; j < current_stones; ++j, idx = (idx + 1) % BOARD_SIZE)
    {
        if (idx % BOARD_SIZE == (2 - current_player) * 7 + 6)
        {
            --j;
            continue;
        }
        board[idx] += 1;
    }
    last_idx = idx > 0 ? (idx - 1) : BOARD_SIZE - 1;
    *current_win_hole = (current_player - 1) * 7 + 6;
    if (last_idx == *current_win_hole)
    {
        right_player = current_player;
    }
    else if (board[last_idx] == 1)
    {
        // win stones
        board[*current_win_hole] += board[12 - last_idx] + 1;
        board[last_idx] = board[12 - last_idx] = 0;
        right_player = 3 - current_player;
    }
    else
    {
        right_player = 3 - current_player;
    }
    return right_player;
}

int evaluate(const int board[], int flag)
{

    return board[flag == 1 ? 6 : 13] - board[flag == 1 ? 13 : 6];
}

int minimax(int board[], int depth, int flag, bool isMaximizingPlayer)
{
    int current_win_hole = 0;
    if (depth == 0)
    {
        return evaluate(board, flag);
    }
    if (is_game_over(board))
    {
        get_player_win_stones(board, flag);
    }
    if (isMaximizingPlayer)
    {
        int bestValue = INT_MIN;
        for (int i = 0; i < 6; ++i)
        {
            int pit = flag == 1 ? i : i + 7;
            if (board[pit] == 0)
                continue;

            int boardCopy[14];
            std::copy(board, board + 14, boardCopy);
            take_move(boardCopy, flag, i + 1, &current_win_hole);

            int v = minimax(boardCopy, depth - 1, flag, false);
            bestValue = std::max(bestValue, v);
        }
        return bestValue;
    }
    else
    {
        int worstValue = INT_MAX;
        for (int i = 0; i < 6; ++i)
        {
            int pit = flag == 1 ? i : i + 7;
            if (board[pit] == 0)
                continue;

            int boardCopy[14];
            std::copy(board, board + 14, boardCopy);
            take_move(boardCopy, flag, i + 1, &current_win_hole);

            int v = minimax(boardCopy, depth - 1, flag, true);
            worstValue = std::min(worstValue, v);
        }
        return worstValue;
    }
}

void init_board(int *board)
{
    for (int i = 0; i < BOARD_SIZE + 1; ++i)
    {
        if (i == 6 || i >= 13)
        {
            board[i] = 0;
        }
        else
        {
            board[i] = 4;
        }
    }
}



// false if error
bool is_operation_right(const int *board, int right_player, int cur_player, int op)
{
    if (right_player != cur_player)
    {
        return false;
    }
    if (op % 10 > 6 || op % 10 < 1)
    {
        return false;
    }
    if (board[op % 10 + (cur_player - 1) * 7 - 1] == 0)
    {
        return false;
    }
    return true;
}

// depth % 2== 1 means it's max node
// return the hole flag should select.
int alpha_beta(const int *board, int start_depth, int flag, int alpha, int beta, bool is_max_node)
{
    int pit = 0, hole = 0;
    int min_value = INT_MAX, max_value = INT_MIN;
    if (start_depth <= 0 || is_game_over(board))
    {
        return evaluate(board, flag);
    }
    if (is_max_node)
    {
        for (int i = 0; i < 6; ++i)
        {
            pit = flag == 1 ? i : i + 7;
            if (board[pit] == 0)
            {
                continue;
            }
            int board_copy[14];
            std::copy(board, board + 14, board_copy);
            take_move(board_copy, flag, i + 1, &hole);
            int v = alpha_beta(board, start_depth - 1, flag, max_value, INT_MAX, !is_max_node);
            max_value = std::max(max_value, v);
            if (v > beta)
            {
                return max_value;
            }
        }
    }
    else
    {
        for (int i = 0; i < 6; ++i)
        {
            pit = flag == 1 ? i : i + 7;
            if (board[pit] == 0)
            {
                continue;
            }
            int board_copy[14];
            std::copy(board, board + 14, board_copy);
            take_move(board_copy, flag, i + 1, &hole);
            int v = alpha_beta(board, start_depth - 1, flag, INT_MIN, min_value, !is_max_node);
            min_value = std::min(min_value, v);
            if (v < alpha)
            {
                return min_value;
            }
        }
    }

    return is_max_node ? max_value : min_value;
}

extern "C"
{

    int *EMSCRIPTEN_KEEPALIVE mancala_board(int flag, int *seq, int size)
    {
        int current_player = seq[0] / 10, right_player = seq[0] / 10, current_win_hole = 0;
        static int board[BOARD_SIZE + 1] = {0};
        init_board(board);
        for (int i = 0; i != size - 1; ++i)
        {
            current_player = right_player = take_move(board, current_player, seq[i], &current_win_hole);
        }
        current_player = flag;
        if (!is_operation_right(board, right_player, current_player, seq[size - 1]))
        {
            board[DATA_BIT] = 200 + (current_player * 2 - 3) * (48 - 2 * board[current_player == 1 ? 6 : 13]);
        }
        else
        {
            right_player = take_move(board, current_player, seq[size - 1], &current_win_hole);
            if (is_game_over(board))
            {
                board[DATA_BIT] = 200 + get_player_win_stones(board, 1);
            }
            else
            {
                board[DATA_BIT] = right_player;
            }
        }
        return board;
    }
    int EMSCRIPTEN_KEEPALIVE mancala_operator2(int flag, int *status)
    {
        int pit = 0, hole = 0;
        int alpha = INT_MIN, beta = INT_MAX;
        int max_value = INT_MIN, select_hole = 0, start_depth = 5;
        for (int i = 0; i < 6; ++i)
        {
            pit = flag == 1 ? i : i + 7;
            if (status[pit] == 0)
            {
                continue;
            }
            int board_copy[14];
            std::copy(status, status + 14, board_copy);
            take_move(board_copy, flag, i + 1, &hole);
            int v = alpha_beta(board_copy, start_depth - 1, flag, max_value, beta, false);
            if (v > max_value)
            {
                max_value = v;
                select_hole = i + 1;
            }
        }
        return select_hole + flag * 10;
    }

    int EMSCRIPTEN_KEEPALIVE mancala_operator(int flag, int *status)
    {
        int bestMove = -1;
        int bestValue = INT_MIN;
        int winner_hole = 0;
        for (int i = 0; i < 6; ++i)
        {
            int pit = flag == 1 ? i : i + 7;
            if (status[pit] == 0)
                continue; // 跳过空洞

            int boardCopy[14];
            std::copy(status, status + 14, boardCopy);
            take_move(boardCopy, flag, i + 1, &winner_hole); // 执行移动

            int moveValue = minimax(boardCopy, 5, flag, false); // 假设搜索深度为5
            if (moveValue > bestValue)
            {
                bestValue = moveValue;
                bestMove = pit;
            }
        }
        return bestMove - (flag - 1) * 7 + flag * 10 + 1;
    }
}
