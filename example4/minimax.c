#include "minimax.h"
#include <stdio.h>
typedef struct {
  minimax_score_t score;
  tictactoe_location_t location;
} scored_move_t;
scored_move_t chosenMove;
#define CENTER_INDEX 1
#define STARTING_DEPTH 0

/**
 * @brief Recursive function to find best move
 *
 * @param board current board position
 * @param is_Xs_turn which side is up to move
 * @param depth current depth of board
 * @return minimax_score_t
 */
static minimax_score_t minMax(tictactoe_board_t *board, bool is_Xs_turn,
                              uint8_t depth) {
  scored_move_t moveScoreTable[TICTACTOE_BOARD_ROWS * TICTACTOE_BOARD_COLUMNS];
  uint8_t scoreTableIndex = 0;
  minimax_score_t boardScore = minimax_computeBoardScore(board, !is_Xs_turn);
  // if the game is over return score
  if (minimax_isGameOver(boardScore)) {
    return boardScore;
  }
  /**Loop through each row*/
  for (uint8_t row = 0; row < TICTACTOE_BOARD_ROWS; row++) {
    /**Loop through each column*/
    for (uint8_t column = 0; column < TICTACTOE_BOARD_COLUMNS; column++) {
      /**if the quare is empty evaluate a move at that point**/
      if (board->squares[row][column] == MINIMAX_EMPTY_SQUARE) {
        board->squares[row][column] =
            is_Xs_turn ? MINIMAX_X_SQUARE : MINIMAX_O_SQUARE;
        moveScoreTable[scoreTableIndex].location.column = column;
        moveScoreTable[scoreTableIndex].location.row = row;
        moveScoreTable[scoreTableIndex].score =
            minMax(board, !is_Xs_turn, depth + 1);
        board->squares[row][column] = MINIMAX_EMPTY_SQUARE;
        scoreTableIndex++;
      }
    }
  }
  scored_move_t bestScore = moveScoreTable[0];
  // pick the best move based on whose turn it is
  if (is_Xs_turn) {
    for (uint8_t i = 1; i < scoreTableIndex; i++) {
      if (moveScoreTable[i].score > bestScore.score) {
        bestScore = moveScoreTable[i];
      }
    }
  } else {
    for (uint8_t i = 1; i < scoreTableIndex; i++) {
      if (moveScoreTable[i].score < bestScore.score) {
        bestScore = moveScoreTable[i];
      }
    }
  }
  // if we are at the top pick the best move
  if (depth == STARTING_DEPTH) {
    chosenMove = bestScore;
  }
  return bestScore.score;
}

/**
 * @brief Finds the best move for a given board
 *
 * @param board current state of the board
 * @param is_Xs_turn Which player the computer is
 * @return tictactoe_location_t the location of the move
 */
tictactoe_location_t minimax_computeNextMove(tictactoe_board_t *board,
                                             bool is_Xs_turn) {
  minMax(board, is_Xs_turn, STARTING_DEPTH);
  return chosenMove.location;
}

/**
 * @brief Returns current board score
 *
 * @param board The current positition of board
 * @param is_Xs_turn if true the last move was an 'X'
 * @return minimax_score_t The score, (X win, O win, Draw or not endgame)
 */
minimax_score_t minimax_computeBoardScore(tictactoe_board_t *board,
                                          bool is_Xs_turn) {
  bool foundWin = true;
  bool foundEmpty = false;
  tictactoe_square_state_t searchFor;
  // choose the piece to search for
  if (is_Xs_turn) {
    searchFor = MINIMAX_X_SQUARE;
  } else {
    searchFor = MINIMAX_O_SQUARE;
  }
  /*search across each row*/
  for (uint8_t row = 0; row < TICTACTOE_BOARD_ROWS; row++) {
    foundWin = true;
    for (uint8_t column = 0; column < TICTACTOE_BOARD_COLUMNS; column++) {
      if (board->squares[row][column] != searchFor) {
        foundWin = false;
        break;
      }
    }
    if (foundWin) {
      if (is_Xs_turn)
        return MINIMAX_X_WINNING_SCORE;
      else
        return MINIMAX_O_WINNING_SCORE;
    }
  }
  /*check across each column*/
  for (uint8_t column = 0; column < TICTACTOE_BOARD_COLUMNS; column++) {
    foundWin = true;
    for (uint8_t row = 0; row < TICTACTOE_BOARD_ROWS; row++) {
      if (board->squares[row][column] != searchFor) {
        foundWin = false;
        break;
      }
    }
    if (foundWin) {
      if (is_Xs_turn)
        return MINIMAX_X_WINNING_SCORE;
      else
        return MINIMAX_O_WINNING_SCORE;
    }
  }
  // check diagonals
  if (board->squares[CENTER_INDEX][CENTER_INDEX] == searchFor) {
    if ((board->squares[0][0] == searchFor &&
         board->squares[TICTACTOE_BOARD_ROWS - 1]
                       [TICTACTOE_BOARD_COLUMNS - 1] == searchFor) ||
        (board->squares[TICTACTOE_BOARD_ROWS - 1][0] == searchFor &&
         board->squares[0][TICTACTOE_BOARD_COLUMNS - 1] == searchFor)) {
      if (is_Xs_turn)
        return MINIMAX_X_WINNING_SCORE;
      else
        return MINIMAX_O_WINNING_SCORE;
    }
  }
  // see if it is a draw or unfinished
  for (uint8_t column = 0; column < TICTACTOE_BOARD_COLUMNS; column++) {
    for (uint8_t row = 0; row < TICTACTOE_BOARD_ROWS; row++) {
      if (board->squares[row][column] == MINIMAX_EMPTY_SQUARE) {
        return MINIMAX_NOT_ENDGAME;
      }
    }
  }
  return MINIMAX_DRAW_SCORE;
}

// Init the board to all empty squares.
void minimax_initBoard(tictactoe_board_t *board) {
  for (uint8_t row = 0; row < TICTACTOE_BOARD_ROWS; row++) {
    for (uint8_t column = 0; column < TICTACTOE_BOARD_COLUMNS; column++) {
      board->squares[row][column] = MINIMAX_EMPTY_SQUARE;
    }
  }
}

/**
 * @brief Determines if the game is over by looking at the score
 *
 * @param score the board score
 * @return true if the game has ended false otherwise
 */
bool minimax_isGameOver(minimax_score_t score) {
  return (score == MINIMAX_DRAW_SCORE) || (score == MINIMAX_O_WINNING_SCORE) ||
         (score == MINIMAX_X_WINNING_SCORE);
}