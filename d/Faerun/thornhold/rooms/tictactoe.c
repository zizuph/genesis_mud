/* Tic Tac Toe
 * Gnim 2016
 * Base game support code.
 *
 * Board is arranged in array:
 * 
 * 0|1|2
 * -+-+-
 * 3|4|5
 * -+-+-
 * 6|7|8
 *
 * 0 in array is no piece
 * 1 in array is X
 * 2 in array is 0
 *
 */

int *board_state;
int *winners = ({0,1,2, 3,4,5, 6,7,8, 0,3,6, 1,4,7, 2,5,8, 0,4,8, 6,4,2});

// Reset Game
void
reset_board()
{
  board_state = ({0,0,0, 0,0,0, 0,0,0});
}

// Check for winner, returns winner
//   0 is no winner
//   1 is X winner
//   2 is O winner
//   3 is tie/cats game 
int
check_winner()
{
  int k,win,plr;

  //Check all 8 possible wins
  win = 0;
  for(k=0; k < 8; k++)
  {
    plr = board_state[winners[k*3+0]];
    if(plr == board_state[winners[k*3+1]] && plr == board_state[winners[k*3+2]])
      win = board_state[winners[k*3+2]];
    if(win > 0)
      return win;
  }
  
  //Check that there are moves left
  for(k=0; k < 9; k++)
    if(board_state[k] == 0)
      return win;

  return 3;
}

// Translate numerical id to piece string
string
decode_piece(int code)
{
    string piece;

    switch(code)
    {
    case 0:
      piece = sprintf(" ");
      break;
    case 1:
      piece = sprintf("X");
      break;
    case 2:
      piece = sprintf("O");
      break;
    case 3:
      piece = sprintf("N");
      break;
    default:
      piece = sprintf("?");
      break;
    }

    return piece;
}

// Make an ai move
int
simple_move(int piece)
{
  int k;

  if(!(piece == 1 || piece == 2))
    return 0;

  //Check that there are moves left
  for(k=0; k < 9; k++)
  {
    
    if(board_state[k] == 0)
    {
      board_state[k] = piece;
      return 1;
    }
  }   
  return 0;
}

// Get piece string for a given board location
string
show_piece(int row, int col)
{
    return decode_piece(board_state[row*3+col]);
}

// Make a game board display string
string
show_board()
{
  string display_board = "";
  
  display_board  = sprintf("      1 2 3\n");
  display_board += sprintf("    A %s|%s|%s\n", show_piece(0,0), show_piece(0,1), show_piece(0,2));
  display_board += sprintf("      -+-+-\n");
  display_board += sprintf("    B %s|%s|%s\n", show_piece(1,0), show_piece(1,1), show_piece(1,2));
  display_board += sprintf("      -+-+-\n");
  display_board += sprintf("    C %s|%s|%s\n", show_piece(2,0), show_piece(2,1), show_piece(2,2));

  return(display_board);
}

// Add a piece to the board based on mymove string
// row col piece
// Ex: upper right x : A3X
// Return 1 for valid move 0 for invalid
int
parse_move(string mymove)
{
  int row,col,piece;

  if (!stringp(mymove))
    return 0;
 
  if (strlen(mymove) != 3)
    return 0;

  switch(mymove[0])
  {
    case 'A':
    case 'a':
      row = 0;
      break;
    case 'B':
    case 'b':
      row = 1;
      break;
    case 'C':
    case 'c':
      row = 2;
      break;
    default:
      row = -1;
      break;
  }

  switch(mymove[1])
  {
    case '1':
      col = 0;
      break;
    case '2':
      col = 1;
      break;
    case '3':
      col = 2;
      break;
    default:
      col = -1;
      break;
  }

  switch(mymove[2])
  {
    case 'X':
    case 'x':
      piece = 1;
      break;
    case 'O':
    case 'o':
      piece = 2;
      break;
    default:
      piece = 0;
      break;
  }

  if(row==-1 || col==-1 || piece==0)
    return 0;
 
  if(board_state[row*3+col] == 0)
  {
    board_state[row*3+col] = piece;
    return piece;
  }
  else
    return 0;
}

int
parse_row(string mymove)
{
  int row;

  if (!stringp(mymove))
    return 0;
 
  if (strlen(mymove) != 3)
    return 0;

  switch(mymove[0])
  {
    case 'A':
    case 'a':
      row = 1;
      break;
    case 'B':
    case 'b':
      row = 2;
      break;
    case 'C':
    case 'c':
      row = 3;
      break;
    default:
      row = 0;
      break;
  }
  
  return row;
}

int
parse_col(string mymove)
{
  int col;

  if (!stringp(mymove))
    return 0;
 
  if (strlen(mymove) != 3)
    return 0;

  switch(mymove[1])
  {
    case '1':
      col = 1;
      break;
    case '2':
      col = 2;
      break;
    case '3':
      col = 3;
      break;
    default:
      col = 0;
      break;
  }
  
  return col;
}

int
parse_piece(string mymove)
{
  int piece;

  if (!stringp(mymove))
    return 0;
 
  if (strlen(mymove) != 3)
    return 0;

  switch(mymove[2])
  {
    case 'X':
    case 'x':
      piece = 1;
      break;
    case 'O':
    case 'o':
      piece = 2;
      break;
    default:
      piece = 0;
      break;
  }
  
  return piece;
}

int
test_move(int row, int col, int piece)
{
  if( (row > 0) && (row <= 3) && (col > 0) && (col <= 3) && (piece > 0) && (piece < 3) )
  {
      if(board_state[(row-1)*3+(col-1)] == 0)
        return 1;
      else
        return 0;
  }
}

int
make_move(int row, int col, int piece)
{
  if( (row > 0) && (row <= 3) && (col > 0) && (col <= 3) && (piece > 0) && (piece < 3) )
  {
    board_state[(row-1)*3+(col-1)] = piece;
    return 1;
  }
  return 0;
}

// Add a piece to the board randomly
// Return 1 for valid move 0 for invalid
int
random_move(int piece)
{
  int row,col,piece;
  
  row = random(3);
  col = random(3);
  make_move(row, col, piece);
}