inherit "/std/room";
inherit "/d/Faerun/thornhold/sandbox/tictactoe";

int whosmove;
int aipiece;

void
create_room()
{
  set_short("Tic Tac Toe Room");
  set_long("A small room with a table and two chairs.\n");

  add_cmd_item("table", ({"read", "examine", "exa", "look"}), "@@look_board@@");
  add_cmd_item("sign", "read", "To make a move use the command mm row col piece.\n" +
                               "For example to place an X in the upper right: mm A2X\n" +
                               "To start over use: cb\n");
  add_item("sign", "Looks like it has rules on it.\n");

  call_out("clear_board", 1);
}

/*
 * Function name: make_move
 * Description  : Add a piece to the board
 * Arguments    : string what_move - the square to play
 * Returns      : int 1/0 - success/failure.
 */
public nomask varargs int
make_move(string what_move)
{
    int space, win;

    win = check_winner();
    if(win > 0)
    {
        if(win == 3)
          notify_fail("The the game is a tie.\n");
        else
          notify_fail(sprintf("%s has already won!\n", decode_piece(win)));
        notify_fail("Perhaps you would like to start a new game.\n");
	return 0;
    }
    
    if (whosmove == 0)
        notify_fail("Not your move yet.\n");

    if (!stringp(what_move))
    {
	notify_fail("You need to choose a move.\n");
	return 0;
    }

    space = parse_move(what_move);
    //write(sprintf("You: %d Him %d %s\n", space, aipiece, what_move));
    if(space == aipiece)
      write("Hey you cheated!\n");
    else if(space == 0)
    {
       notify_fail(what_move + " is not a valid move.\n");
      return 0;
    }
    else
      write("You move " +  what_move + ".\n");

    win = check_winner();
    if(win>0)
    {
      if(win==3)
        write(sprintf("Looks like a cats game!\n"));
      else
        write(sprintf("%s wins!\n", decode_piece(win) ));
    }
    else
    {
      call_out("ai_mover", 2);
    }
      
    return 1;
}

void
ai_mover()
{
  int win;
  win=simple_move(aipiece);
  write(sprintf("An invisible opponent makes a move.\n"));
  
  win = check_winner();
  if(win>0)
  {
    if(win==3)
      write(sprintf("Looks like a cats game!\n"));
    else
      write(sprintf("%s wins!\n", decode_piece(win) ));
  }
  whosmove = 1;
}

string
look_board()
{
  return "A table with a tic tac toe game on it.\n" +
         show_board();
}

/*
 * Function name: clear_board
 * Description  : reset the board
 * Arguments    :
 * Returns      : int 1/0 - success/failure.
 */
public nomask varargs int
clear_board()
{
    whosmove = random(2);
    reset_board();
    
    if(whosmove == 0)
    {
     aipiece = 1;
     ai_mover();
     write(sprintf("I'll play an X.\n"));
   }
   else
   {
     aipiece = 2;
     write(sprintf("Play an X.\n"));
   }
    
    return 1;
}

/*
 * Init, routine that adds commands.
 */
void
init()
{
    ::init(); /* Always good to do. */

    add_action(make_move, "mm", 0);
    add_action(clear_board, "cb", 0);
}
