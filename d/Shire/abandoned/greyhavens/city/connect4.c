/*
   Connect Four Game for the
   Drunken Boar Brewpub in Mithlond

   by Palmer - April 05, 2004
   
   "sit on chair" (both players)
   "play <column number>"
   
   Your piece drops to the bottom. Connect 4
   vertically, horizontally or diagonally to win.
   
   "stand up" to leave after game is over or "resign" 
   during game.
   
   There is a scoreboard you may examine.
   
*/

inherit "/d/Shire/std/room";
#include "/d/Shire/sys/defs.h"
#include <stdproperties.h>
#include <macros.h>

#define COLOR0 0
#define COLOR1 1
#define WIDTH 7
#define HEIGHT 6
#define EMPTY 0
#define X 0
#define O 1
#define VOID -1
#define NONE 0
#define BOTH 2
#define SCOREBOARD "/d/Shire/greyhavens/scoreboard"


/* Prototypes: */

public void score_game(string wnt, string lsr);
private void add_score(string plyr, int stats);
public int read_stuff(string str);
public int check_win(int row, int column);
public string play_move(string str);
public int color_to_start();
public object check_player(string playname);
public void init_game(int comp);
public int stand_up(string str);
public string stand_up_desc();
public void start_game(string str);
public string start_game_desc();
public static mixed *connect4;
public string connect4_long();
public int drop_coin(int column);
public void draw_board();
public string resign();
public int abandon(string str);
public string read_scoreboard();

public static int moves_made;
public static int color_to_play;
public static string *player;
public static string seat_name;

string poster_text = "Two players try to connect four pieces in a row either " +
    "horizontally, vertically, or diagonally. Sit on a chair to play. " +
    "Play <column number> to drop a piece in a slot. It will fall to " +
    "the bottom. Stand up to leave after playing or you may resign in " +
    "the middle of a game.";
    

/*
 * Function name:   create_shire_room
 * Description:     Basic Shire room setup
 *                  
 * Argument:        
 * Returns:         
 */
void
create_shire_room()
{
    set_short("The Drunken Boar Connect Four Room");

    set_long("The Connect Four Room in The Drunken Boar Brewpub.\n" +
    "@@connect4_long@@\n\n" +
    "On the wall is a poster with the rules written on it " +
    "and a scoreboard. There are two oak chairs for people " +
    "to sit on when they play.\n");

    add_item(({"chair", "chairs"}), "The chairs are made of oak.\n");
    add_item(({"rules", "poster"}), poster_text + "\n");
    add_item(({"scores", "board", "scoreboard"}), "@@read_scoreboard@@");
    add_item(({"wall", "walls"}), "It's made of rough hewn oak.\n");
    seat_name = "chair";
    add_prop(ROOM_I_NO_ATTACK, 1);
    add_prop(OBJ_M_NO_ATTACK,1);
    add_prop(ROOM_I_NO_MAGIC_ATTACK, 1); 

    add_prop(ROOM_I_INSIDE,1);
    add_prop(ROOM_I_NO_ALLOW_STEED, 1);
    add_prop(ROOM_I_NO_CLEANUP,1);
    player = allocate(2);
    moves_made = 0;
    init_game(BOTH);
    setuid();
    seteuid(getuid());
 
    // add_exit("/d/Shire/bree/rooms/town/stable/club/foyer", "west");
}

    
/*
 * Function name:   check_win(int row, int column)
 * Description:     Checks for four pieces in a row either vertically,
 *                  horizontally or diagonally.
 * Argument:        row and column numbers
 * Returns:         0 = no win, 1 = win
 */
int
check_win(int row, int column)
{
  int coin, x, y, inline;

  coin = color_to_play + 1;
  inline = 1;

  /* Check diagonal right to left */
  for (x = column+1, y = row+1; (x <= column+3) && (x < WIDTH) && (y < HEIGHT); 
       x++, y++)
  {
    if (connect4[x][y] == coin)
        inline++;
    else
        break;
  }
  if (inline == 4) return 1;
  for (x = column-1, y = row-1;(x >= column-3) && (x >= 0) && (y >= 0);
       x--, y--)
  {
    if (connect4[x][y] == coin)
        inline++;
    else
        break;
  }
  if (inline >= 4)
      return 1;
  inline = 1;

  /* Check diagonal left to right */
  for (x = column-1, y = row+1;(x >= column-3) && (x >= 0) && (y < HEIGHT); 
       x--, y++) {
    if (connect4[x][y] == coin)
        inline++;
    else
        break;
  }
  if (inline == 4) return 1;
  for (x = column+1, y = row-1;(x <= column+3) && (x < WIDTH) && (y >= 0);
       x++, y--)
  {
    if (connect4[x][y] == coin)
        inline++;
    else
        break;
  }
  if (inline >= 4)
      return 1;
  inline = 1;

  /* Check horizontal rows */
  for (x = column+1; (x <= column+3) && (x < WIDTH); x++) {
    if (connect4[x][row] == coin)
        inline++;
    else
        break;
  }
  if (inline == 4) return 1;
  
  for (x = column-1; (x >= column-3) && (x >= 0); x--)
  {
    if (connect4[x][row] == coin)
        inline++;
    else 
        break;
  }
  if (inline >= 4)
      return 1;
  inline = 1;

  /* Check vertical row */
  if (row >= 3) {
     for (x = row-1; x >= row-3 ; x--)
     {
       if (connect4[column][x] == coin)
           inline++;
       else 
           break;
     }
     if (inline >= 4)
         return 1;
  }
  return 0;
}



/*
 * Function name:   .
 * Description:     
 *                  
 * Argument:        
 * Returns:         
 */
int
abandon(string str)
{
  string desc;

  desc = "The game is abandoned.\n";
  if (desc) {
    write(desc);
    return 1;
  }
  return 0;
}


public void
score_game(string winner, string loser)
{
    add_score(winner, 1);
    add_score(loser, 0);    
}

private void
add_score(string plyr, int stats)
{
    mapping Scoreboard;
    int wins, losses;
    
    Scoreboard = restore_map(SCOREBOARD);
    if (!mappingp(Scoreboard))
        Scoreboard = ([ ]);

    if (!Scoreboard[plyr])
    {
    
        if (stats)
            Scoreboard+=([plyr:({1,0})]);
        else
	    Scoreboard+=([plyr:({0,1})]);
    }
    else
    {
       wins = Scoreboard[plyr][0];
       losses = Scoreboard[plyr][1];
	
       if (stats)
           Scoreboard[plyr][0] = wins + 1;
       else
           Scoreboard[plyr][1] = losses + 1;
    }
    save_map(Scoreboard, SCOREBOARD);
    

}


/*
 * Function name:   .
 * Description:     
 *                  
 * Argument:        
 * Returns:         
 */
int
read_stuff(string str)
{
    if (!strlen(str))
    {
        notify_fail("Read what? Your mind?\n");
        return 0;

    }
    if ((str != "poster") && (str != "scoreboard"))
    {
        notify_fail("Read what? There is a poster and scoreboard you may read.\n");
        return 0;
    }
    if (str == "poster")
    	write(poster_text + "\n");
	
    if (str == "scoreboard")
        write(read_scoreboard());
		
    return 1;
}


public string
read_scoreboard()
{    
    mapping Scoreboard;
    int i, n;
    string *keys, lines;
    mixed vals;
    
    Scoreboard = restore_map(SCOREBOARD);
    if (!mappingp(Scoreboard))
        Scoreboard = ([ ]);
 
    keys = m_indices(Scoreboard);
    vals = m_values(Scoreboard);

    n = sizeof(keys);
    lines =   "Player        Wins  Losses\n";
    lines += ("==========================\n\n");
    for (i = 0; i < n; i++)
    {
        //lines +=(CAP(keys[i]) + "\t\t\t" + vals[i][0] + "\t" + vals[i][1] + "\n");
	lines +=sprintf("%-=13s %4d    %4d", CAP(keys[i]), vals[i][0], vals[i][1]);
	lines += "\n";
    }
    return lines;
}



/*
 * Function name:   .
 * Description:     
 *                  
 * Argument:        
 * Returns:         
 */
void
init()
{
    ::init();
    add_action("stand_up", "stand");
    add_action("start_game", "sit");    
    add_action("play_move", "play");    
    add_action("resign", "resign");        
    // add_action("abandon", "abandon");
    add_action("read_stuff", "read");
}


/*
 * Function name:   .
 * Description:     
 *                  
 * Argument:        
 * Returns:         
 */
void
init_game(int comp)
{
  int x, y;
  if (!pointerp(connect4)) {
    connect4 = allocate(WIDTH);
    for (x =0; x < WIDTH; x++) connect4[x] = allocate(HEIGHT);
  }
  for (x = 0; x < WIDTH; x++)
    for (y = 0; y < HEIGHT; y++)
      connect4[x][y] = 0;
  moves_made = 0;
  switch (comp) {
    case NONE: 
        color_to_play = !color_to_play;
	break;
    case X:
        player[X] = 0;
	color_to_play = VOID;
	break;
    case O:
        player[O] = 0;
	color_to_play = VOID;
	break;
    case BOTH:
        player[X] = player[O] = 0;
	color_to_play = VOID;
	break;
  }
}


/*
 * Function name:   .
 * Description:     
 *                  
 * Argument:        
 * Returns:         
 */
int
stand_up(string str)
{
  string desc;

  if (!str || (str && str != "up")) {
    notify_fail("Stand up you mean?\n");
    return 0;
  }
  desc = stand_up_desc();
  if (desc) {
    write(desc);
    return 1;
  }
  return 0;
}


/*
 * Function name:   .
 * Description:     
 *                  
 * Argument:        
 * Returns:         
 */
string
stand_up_desc()
{
  string name;
  int color;

  name = this_player()->query_real_name();
  if (name == player[COLOR0] || name == player[COLOR1]) {
    if (moves_made) {
      return "You cannot stand up in the middle of a game. " +
             "Do you wish to resign?\n";
    }
    if (name == player[COLOR0])
        color = COLOR0;
    else
        color = COLOR1;
    
    init_game(color);
    say(QCTNAME(TP) + " gets up off " +
        TP->query_possessive() + " " + seat_name + ".\n");

    return "You stand up.\n";
  }
  else 
  {
    notify_fail("You do not occupy one of the " + seat_name + "s.\n");
    return 0;
  }
}


/*
 * Function name:   .
 * Description:     
 *                  
 * Argument:        
 * Returns:         
 */
string
resign()
{
  string name;
  int winner;
  object opposition;

  name = TP->query_real_name();
  if (!name)
      return 0;
  if (color_to_play == VOID)
  {
    notify_fail("There is no game in progress!\n");
    return 0;
  }
  if (name == player[COLOR0] || name == player[COLOR1])
  {
    if (!moves_made)
    {
       write("You stand up. No moves in this game have been made.\n");
       // return stand_up_desc();
       return "";
    }
    if (name == player[COLOR0])
        winner = COLOR1;
    else 
        winner = COLOR0;
    write("You resign from the game.\n");
    opposition = check_player(player[winner]);
    
    say(QCTNAME(opposition) + " wins the game " + 
       "because " + QTNAME(TP) + " resigned.\n", ({opposition, TP}));
    tell_object(opposition, "You win the game " +
       "because your opponent resigned.\n");
    score_game(opposition->query_real_name(), TP->query_real_name());
    init_game(NONE);
  } else {
    notify_fail("You are not currently playing!\n");
    return 0;
  }
  return "";
}


/*
 * Function name:   .
 * Description:     
 *                  
 * Argument:        
 * Returns:         
 */
string
start_game_desc()
{
  object player1, player2;
  string name;
  int color;
  object tmp;
  
  name = this_player()->query_real_name();
  if (name == player[COLOR0] || name == player[COLOR1])
     return "You are already sitting on a " + seat_name + ".\n";

  if (player[COLOR0] && player[COLOR1]) {
    player1 = check_player(player[COLOR0]);
    player2 = check_player(player[COLOR1]);
    if (!player1 && !player2) {
      /*
      tell_room(this_object(), "The game between " +
                capitalize(player[COLOR0]) + " and " +
                capitalize(player[COLOR1]) +
                " has been abandoned because they are both absent.\n");
        */
      tell_room(this_object(), "The game has been abandoned " +
          "because both players are absent.\n");
	
      init_game(BOTH);
    } else {
      return "A game is already in progress, you can't occupy a chair.\n";
    }
  }

  write("You sit down on one of the " + seat_name + "s.\n");

  if (!player[COLOR0])
  {
      player[COLOR0] = this_player()->query_real_name();
      write("You will play O's.\n");
  }
  else
  {
      player[COLOR1] = this_player()->query_real_name();
      write("You will play X's.\n");
  }
  say(QCTNAME(TP) + " sits down on one of the " + seat_name + "s.\n");

  if (player[COLOR0] && player[COLOR1]) {
    player1 = check_player(player[COLOR0]);
    player2 = check_player(player[COLOR1]);

    if (!player1 || !player2)
    {
      if (!player1)
          color = COLOR0;
      else
          color = COLOR1;
	  
      tell_room(this_object(), capitalize(player[color]) + "'s " +
                seat_name + " is no longer reserved.\n");
      init_game(color);
      
    } 
    
    else {

      color_to_play = color_to_start();

      tell_room(this_object(), QCTNAME(player1) + " and " +
          QTNAME(player2) + " have started a game.\n", ({player1, player2 }));      
      
      if (color_to_play == COLOR1) {
        tmp = player1;
        player1 = player2;
        player2 = tmp;
      }
      tell_object(player1, "You have the first move.\n");
      tell_object(player2, "Your opponent has the first move.\n");
     }
  }
  return "";
}


/*
 * Function name:   .
 * Description:     
 *                  
 * Argument:        
 * Returns:         
 */
int
start_game(string str)
{
  string desc;

  if (!str || (str != "on " + seat_name && str != "in " + seat_name &&
                                           str != seat_name &&
               str != "on seat" && str != "in seat" && str != "seat")){
    write("Sit on what?\n");
    return 1;
  }

  desc = start_game_desc();
  if (desc != 0) {
    write(desc);
    return 1;
  }
  return 0;
}


/*
 * Function name:   .
 * Description:     
 *                  
 * Argument:        
 * Returns:         
 */
object
check_player(string playname)
{
  object opposition;

  opposition = find_player(playname);
  if (!opposition || (environment(opposition) != this_object()))
     return 0;
 
  return opposition;

}


/*
 * Function name:   .
 * Description:     
 *                  
 * Argument:        
 * Returns:         
 */
int
drop_coin(int column)
{
  int x;

  if (connect4[column][HEIGHT-1])
    return 0;

  while (connect4[column][x++]);
     connect4[column][x-1] = color_to_play+1;
  return x;
}



/*
 * Function name:   .
 * Description:     
 *                  
 * Argument:        
 * Returns:         
 */
int
color_to_start()
{
    return random(2);
}


/*
 * Function name:   .
 * Description:     
 *                  
 * Argument:        
 * Returns:         
 */
string
board_desc()
{
  string desc;

  desc = "The board has been designed for\n" +
         "playing connect 4. The board looks like this:\n\n";

  return desc + connect4_long() + "\n";
}


/*
 * Function name:   .
 * Description:     
 *                  
 * Argument:        
 * Returns:         
 */
string
connect4_long()
{
  int x,y;
  string board;
  board = "";
  for (x = 1; x <= WIDTH; x++) board += "   " + x;
  board += "\n";
  for (y = HEIGHT-1; y >= 0 ; y--) {
    board += " ";
    for (x = 0; x < WIDTH; x++) board += "----";
    board += "-\n |";
    for (x = 0; x < WIDTH; x++) {
       board += " " + ((connect4[x][y]) ? ((connect4[x][y] == 1) ? "O" : "X") : " ") + " |";
    }
    board += "\n";
  }
  board += " ";
  for (x = 0; x < WIDTH; x++)
      board += "----";
  board += "-\n";
  for (x = 1; x <= WIDTH; x++)
      board += "   " + x;
  board += "\n";
  
  return board;
}


/*
 * Function name:   .
 * Description:     
 *                  
 * Argument:        
 * Returns:         
 */
void
draw_board()
{
    tell_room(this_object(), "\n" + connect4_long() + "\n"); ;
}


/*
 * Function name:   .
 * Description:     
 *                  
 * Argument:        
 * Returns:         
 */
string
play_move(string str)
{
  int column, row;
  string name;
  object opposition;

  if (!str) {
    notify_fail("Play what?\n");
    return 0;
  }
  name = this_player()->query_real_name();
  if (!name) return 0;
  if (color_to_play == VOID) {
    notify_fail("There is no game in progress!\n");
    return 0;
  }
  if (name == player[color_to_play]) {
    /* Check if opposition is still in room */
    opposition = check_player(player[!color_to_play]);
    
    if ((sscanf(str,"%d", column) == 1) && (column >= 1) && (column <= WIDTH)) {
       if ((row = drop_coin(column-1))) {
         write("You drop a " + ((color_to_play) ? "X" : "O") +
               " in column " + column + ".\n");
         say(QTNAME(TP) + " drops a " + ((color_to_play) ? "X" : "O") +
                                " into column " + column + ".\n");
         moves_made++;
         tell_room(this_object(), "\n" + connect4_long() + "\n");
         tell_room(this_object(), "You hear a " +
            ((random(2)) ? "plonk" : "klink") + " noise.\n");
  
         if ((moves_made >= 7) && check_win(row-1, column-1)) {
           write("You win the game! Your opponent stands up.\n");
           say(QCTNAME(TP) + " wins the game!\n", ({opposition, this_player()}));
           if (opposition)
	   {
	       tell_object(opposition, "You lost the game and stand up.\n");
	     
	     say(QCTNAME(opposition) + " lost the game and stands up.\n", ({opposition, TP}));
	   }
	   score_game(TP->query_real_name(), opposition->query_real_name());
           init_game(!color_to_play);
	   
           return "";
         }

         if (moves_made == (WIDTH*HEIGHT)) {
	 /*
           write("You draw the game with " +
                 capitalize(player[!color_to_play]) + ".\n");
           if (opposition)
             tell_object(opposition, "You draw the game with " +
                                      capitalize(player[color_to_play]) + ".\n");
           say("The game between " +
               capitalize(player[color_to_play]) + " and " +
               capitalize(player[!color_to_play]) + " has been drawn.\n", opposition || this_player());
	 */
	   tell_room(TO, "The game is a draw!\n");
           init_game(NONE);
           return "";
         }
         color_to_play = !color_to_play;
         return "";
       } else {
         notify_fail("That is not a valid move!\n");
         return 0;
       }
    } else {
      notify_fail("Column must be between 1 and " + WIDTH + ".\nplay <column>\n");
      return 0;
    }
  } else 
        if (name != player[!color_to_play]) {
            notify_fail("You are not currently playing!\n");
         return 0;
  } else
    {
        notify_fail("It is not your turn!\n");
        return 0;
    }
}
