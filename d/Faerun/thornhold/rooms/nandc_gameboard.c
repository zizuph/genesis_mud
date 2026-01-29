/*
 *  Allow the addition of a naughts and crosses game.
 */
#pragma strict_types

inherit "/d/Faerun/thornhold/rooms/tictactoe";

#include "defs.h"

static object player_x;
static object player_o;
// X is player 1 O is player 2
static int whosmove;

int
check_turn(object player)
{
   if( (player == player_x) && (whosmove == 1) )
        return 1;

   if( (player == player_o) && (whosmove == 2) )
        return 1;
   
   return 0;
}

/*
 * Function name: make_move
 * Description  : Add a piece to the board
 * Arguments    : string what_move - the square to play
 * Returns      : int 1/0 - success/failure.
 */
public nomask varargs int
do_move(string what_move)
{
    int success, win, drunk, row, col, piece;

    if( TP->query_prop("_is_playing_nc_") != 1 )
    {
        NF("You are not playing!\n");
        return 0;
    }   

    if( !check_turn(TP) )
    {
        NF("It's not your move.\n");
        return 0;
    }

    if (!stringp(what_move))
    {
        NF("You need to choose a move.\n");
        return 0;
    }
   
    //Check how drunk they are % wise
    drunk = (100 * TP->query_intoxicated() ) / TP->intoxicated_max();
    
    if( random(drunk) > 25 )
    {
        success = random_move(whosmove);
        TP->catch_msg("Oops. Maybe you'll have better luck sober.\n" );
    }
    else
    {
        row = parse_row(what_move);
        col = parse_col(what_move);
        piece = parse_piece(what_move);
        
        if( piece != whosmove )
        {
            NF("You tried to play the wrong piece. No cheating!\n");
            return 0;
        }
        
        if(test_move(row,col,piece))
        {
            make_move(row,col,piece);
            TP->catch_msg("You move " +  what_move + ".\n" + show_board() );
        }
        else
        {
            NF(what_move + " is not a valid move.\n");
            return 0;
        }
    }
    
    if(whosmove == 1)
        whosmove = 2;
    else
        whosmove = 1;

    win = check_winner();
    if( win > 0 )
    {
      if(win==3)
      {
        player_x->catch_msg("Looks like a cats game!\n");
        player_o->catch_msg("Looks like a cats game!\n");
      }
      else if(win==1)
      {
        player_x->catch_msg("You won!\n");
        player_o->catch_msg("You lost.\n");
      }
      else
      {
        player_x->catch_msg("You lost.\n");
        player_o->catch_msg("You won!\n");
      }
      player_x->command("$stand");
      player_o->command("$stand");
    }
      
    return 1;
}

// Add a player to a free spot
public int
add_player(object new_player)
{
    if( player_x == 0 )
    {
        player_x = new_player;
        player_x->add_prop("_is_playing_nc_",1);
        player_x->add_prop(LIVE_S_EXTRA_SHORT, " seated at the game table");
        return 1;
    }

    if( player_o == 0 )
    {
        player_o = new_player;
        player_o->add_prop("_is_playing_nc_",1);
        player_o->add_prop(LIVE_S_EXTRA_SHORT, " seated at the game table");
        return 1;
    }
        
    return 0;
}

// If the player is in the game remove them. In either case kill the property and extra just in case.
public void
remove_player(object player)
{
    if( player_x == player )
        player_x = 0;

    if( player_o == player )
        player_o = 0;
        
    player->remove_prop("_is_playing_nc_");
    player->remove_prop(LIVE_S_EXTRA_SHORT);
}

// How many players? 0, 1 or 2
public int
query_players()
{
    int num;
    num = 0;
    if(player_x != 0)
        num++;
    if(player_o != 0)
        num++;

    return num;
}

// Shuffle players
public int
shuffle_players()
{
    object temp;
    if( (random(2) == 0) && (query_players() == 2) )
    {
        temp = player_x;
        player_x = player_o;
        player_o = temp;
    }
}

public void
start_game()
{
  // X's go first who is who is shuffled
  whosmove = 1;
  shuffle_players();
  reset_board();
  // Make sure board state doesn't get reset unless a game starts
  
  // Starting a game should inform each player it's game on
  player_x->catch_msg("The game has begun and you are playing crosses. " +
                  "It's your move. Examine the gameboard for instructions.\n");

  player_o->catch_msg("The game has begun and you are playing naughts. " +
                  "You are waiting for your opponent to move. " +
                  "Examine the gameboard for instructions.\n");
}

/*
 * Called when a player types 'sit at game'
 * This should 
  */
int
do_sit(string str)
{
  string *argarr;

  if( TP->query_prop("_is_playing_nc_") == 1 ) 
  {
      NF("You're already playing!\n");
      return 0;
  }
 
  if (!str)
  {
    NF("Sit where?\n");
    return 0;
  }
  
  argarr=explode(str," ");
  if( sizeof(argarr) < 2)
  {
    NF("Sit where?\n");
    return 0;
  }
  if( (argarr[0]!="at") && (argarr[1]!="game") )
  {
      NF("Sit Where?\n");
      return 0;
  }
  
  if( query_players() >= 2 )
  {
      NF("Only two people can play at a time.\n");
      return 0;
  }
  
  TP->catch_msg("You sit down in a chair at the gametable.\n");
  tell_room(TO,QCTNAME(TP) + " sits down in a chair at the gametable.\n",TP);
  add_player(TP);

  // Stitting second player starts game. Winning forces a stand up. Thus games get set right.
  if( query_players() == 2 )
    start_game();

  return 1;
}

/*
 * Called when people stand up
 */
int
do_stand(string str)
{
  if( TP->query_prop("_is_playing_nc_") != 1 )
  {
      NF("You're not sitting down!\n");
      return 0;
  }
  
  tell_room(TO, QCTNAME(TP) + " pushes " + TP->query_possessive() + " chair " +
                "away from the gametable and stands up.\n", TP);
  TP->catch_msg("You push your chair away from the gametable and stand up.\n");
  remove_player(TP);
  return 1;
}

/*
 * Keep people from wandering off standing up.
 */
int do_nothing ()
{
  if (TP->query_prop("_is_playing_nc_")) 
  {
    write ("You must stand up from the table before you can do that.\n");
    return (1);
  }
  return (0);
}

/*
 * Function name: init_nandc_game
 * Description:   Use this function to set up and play actions.
 *                Add this function in the init() function.
 */
void
init_nandc_game()
{
    setuid(); 
    seteuid(getuid());
   
    add_action("do_sit", "sit");
    add_action("do_stand", "stand");
    add_action("do_move", "move");

    add_action ("do_nothing", "north");
    add_action ("do_nothing", "south");
    add_action ("do_nothing", "east");
    add_action ("do_nothing", "west");
    add_action ("do_nothing", "southeast");
    add_action ("do_nothing", "southwest");
    add_action ("do_nothing", "northeast");
    add_action ("do_nothing", "northwest");
    add_action ("do_nothing", "up");
    add_action ("do_nothing", "down");
    add_action ("do_nothing", "in");
    add_action ("do_nothing", "out");
    add_action ("do_nothing", "quit");    
  
    reset_board();
}

/*
 * Function name: configure_game_table
 * Description:   Use this function to set up what the game table name is and looks like.
 *                Add this function in the create function.
 */
void
configure_game_table()
{
    TO->add_item(({"game", "board", "gameboard"}), "@@look_board@@");
    TO->add_item(({"table", "gametable"}),
              "On this table sits a simple gameboard carved from wood with " + 
              "sets of intersecting lines that forms a grid.\n");
}

/*
 * Function name: look_board
 * Description:   This function shows the player the game state and who is playing.
 */
string
look_board()
{
    string lmsg = "";

    lmsg += "A board with a naughts and crosses game on it:\n";
    lmsg += show_board();
    
    if(query_players() == 0)
    {
        lmsg += "No one seems to be playing at the moment. ";
        lmsg += "If you would like to play you could sit at the table.\n";
    }

    if(query_players() == 1)
    {
        if( TP->query_prop("_is_playing_nc_") )
        {
            lmsg += "You are waiting for an opponent.\n";
        }
        else
        {
            if(player_x != 0)
                lmsg += player_x->query_The_name(TP);
            else
                lmsg += player_o->query_The_name(TP);
            lmsg += " seems to be waiting for an opponent. ";
            lmsg += "If you would like to play you could sit at the table.\n";
        }
    }

    if( (query_players() == 2) && !TP->query_prop("_is_playing_nc_") )
    {
        lmsg += player_o->query_The_name(TP);
        lmsg += " seems to be playing naughts against ";
        lmsg += player_x->query_the_possessive_name(TP) + " crosses.\n";
    }

    if (TP->query_prop("_is_playing_nc_"))
    {    
        if(TP == player_x)
        {
            lmsg += "You are playing crosses. ";
            if(query_players() == 2)
            {
                lmsg += "against ";
                lmsg += player_o->query_the_possessive_name(TP) + " naughts. ";
            }
        }
        else
        {
            lmsg += "You are playing naughts, ";
            if(query_players() == 2)
            {
                lmsg += "against ";
                lmsg += player_x->query_the_possessive_name(TP) + " crosses. ";
            }
        }
        lmsg += "To make a move use the command: move row col piece.\n";
        lmsg += "For example to place an piece in the upper right: ";
        if(TP == player_x)
            lmsg += "move A3X\n";
        else
            lmsg += "move A3O\n";
        lmsg += "If you need to stop playing stand up from the " +
                 "player's seat.\n";
    }
    return lmsg;
}
