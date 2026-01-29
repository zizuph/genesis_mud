/*
   Connect Four Game for the
   Drunken Boar Brewpub in Mithlond

   Temporarily in The Prancing Pony
   
   by Palmer - April 05, 2004
   
   ** NOTE FOR AoP **: 
   ~shire/log/connect4_bets is a log file of all bets,
   challenges (messengers sent), and winnings. 
   
   "sit on chair" (both players)
   "play <column number>"
   
   Your piece drops to the bottom. Connect 4
   vertically, horizontally or diagonally to win.
   
   "stand up" to leave after game is over or "resign" 
   during game.
   
   There is a scoreboard you may examine.

   ChangeLog:
   Please add your name, date and any changes here unless
   you are fixing a typo.
   
   Palmer April 25, 2004 -
     Added description to players sitting in chairs. Made
     poster easier to read.

   Palmer April 29, 2004 -
     Added option for player who starts game to "decline start"
     and let other player begin game.

     You can 'exa board' to see who has the next move.     
           
   Palmer May 3, 2004 -
     You can 'challenge <player> <wager>' to send them
     a hobbit messenger with a scroll challenging them to a game.

   Palmer May 8, 2004 -
     You may 'bet <nbr gold coins>' before the first move is made.
     
*/

inherit "/d/Shire/std/room";
inherit "/lib/trade";

#include <money.h>
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
// #define SCOREBOARD "/d/Shire/greyhavens/scoreboard"
#define SCOREBOARD "/d/Shire/bree/rooms/town/scoreboard"
#define SCROLL "/d/Shire/bree/rooms/town/c4_scroll"
#define MAX_MESSENGERS 5
#define WAGER_PLACED "_connect4_wager"
#define WAGER_LOG "connect4_bets"
#define C4_CHALLENGES "_connect4_challenges"

// Prototypes: 
private void pay_winner(object plyr);
private void add_score(string plyr, int stats);
private void return_wager(object plyr);
public void send_messenger(string p_name, object sender, object scroll);
public int do_challenge(string str);
public int do_bet(string str);
public string exa_chair(string str);
public int decline_start(string str);
public int cheater_security();
public string smack_caster(string str);
public string smack_thief(string str);
public void score_game(string wnt, string lsr);
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
public string exa_board();
public int drop_coin(int column);
public void draw_board();
public string resign();
public string read_scoreboard();
public int do_bet(string str);


// Globals 
public static int Moves_made;
public static int Color_to_play;
public static int Gambling_rounds_played;
public static string *Player;
public static string Seat_name;
public object Player1, Player2;


string poster_text = 
    "Objective: \n" +
    "  Two players try to connect four pieces in a row either \n" +
    "  horizontally, vertically, or diagonally.  \n" +
    "\n" +
    "How to play: \n" +
    "1) Sit on a chair. \n" +
    "2) 'play <column number>' to drop a piece in a slot. It will fall to \n" +
    "   the bottom. Stand up to leave after playing or you may resign in \n" +
    "   the middle of a game. \n" +
    "   (Minstrels should use 'cplay' instead of 'play'). \n" +
    "\n" +
    "You may also 'bet <nbr gold coins>' before the first move is made.\n" +
    "Please read the fine print, especially if you are betting.\n";

string fine_print =
    "You may 'challenge <player> [wager]' to send someone a message\n" +
    "offering a game.\n\n" +

    "The scoreboard will show your name after a game is over. Keep \n" +
    "this in mind if you wish to remain anonymous.\n\n" +
    
    "If the board looks strange, use a fixed-width font such as Courier.\n\n" +
    
    "If you have the first move but would like to allow your opponent\n" +
    "to start, you may 'decline start'.\n\n"+
    
    "You may examine the board to see who's turn it is.\n\n" +
    
    "Gambling (Optional):\n\n" +
    
    "** Play at your own risk! **\n\n" +
    
    "Barliman will hold your bets until the game is over.\n" +
    "You may 'withdraw bet', but not after the game has begun.\n" +
    "You may only use gold coins to bet with. No copper, no stinky " +
    "Sybarun 'coins'.\n" +
    "If you resign, your opponent wins and takes the gold.\n";


/*
 * Function name:   create_shire_room
 * Description:     Basic Shire room setup
 *                  
 * Argument:        none
 * Returns:         none
 */
void
create_shire_room()
{
    set_short("The Connect Four Room in The Prancing Pony");

    set_long("The Connect Four Room in The Prancing Pony.\n" +
    "@@connect4_long@@\n" +
    "On the wall is a poster with the rules written on it " +
    "and a scoreboard. There are two oak chairs for people " +
    "to sit on when they play.\n");

    add_item(({"board", "game"}), "@@exa_board@@\n");
    add_item(({"chair", "chairs", "second chair"}), "@@exa_chair@@\n");
    add_item(({"rules", "poster", "instructions"}), poster_text + "\n");
    add_item(({"scores", "highscores", "scoreboard"}), "@@read_scoreboard@@");
    add_item(({"the fine print", "fine print"}), fine_print);
    add_item(({"wall", "walls"}), "They are made of rough hewn oak.\n");
    Seat_name = "chair";
    add_prop(ROOM_I_NO_ATTACK, 1);
    add_prop(OBJ_M_NO_ATTACK,1);
    add_prop(ROOM_I_NO_MAGIC_ATTACK, 1); 
    add_prop(ROOM_I_INSIDE,1);
    add_prop(ROOM_I_NO_ALLOW_STEED, 1);
    add_prop(ROOM_I_NO_CLEANUP,1);
    Player = allocate(2);
    Moves_made = 0;
    init_game(BOTH);
    setuid();
    seteuid(getuid());
    config_default_trade();
    /* Only accept gold for bets. We don't want people handing Barliman
        coins of lower value then cancelling bets to get zero exchange rate */
    set_money_accept(({0,0,1,0}));
    add_exit("/d/Shire/common/bree/inn", "south", cheater_security);
}


/*
 * Function name:   init
 * Description:     inits stuff
 *                  
 * Argument:        none
 * Returns:         none
 */
void
init()
{
    ::init();
    add_action("do_challenge", "challenge");
    add_action("decline_start", "decline");    
    add_action("stand_up", "stand");
    add_action("stand_up", "rise");
    add_action("smack_thief", "steal");
    add_action("smack_thief", "borrow");
    add_action("smack_caster", "cast");
    add_action("start_game", "sit");    
    add_action("play_move", "play");
    add_action("play_move", "cplay");        
    add_action("resign", "resign");        
    add_action("read_stuff", "read");
    add_action("do_bet", "bet");
    add_action("do_withdraw", "withdraw");    
}
    
    
   
/*
 * Function name:   do_bet
 * Description:     Bet player coins for 3 rounds of connect4
 *                  
 * Argument:        string str
 * Returns:         0/1
 */
int
do_bet(string str)    
{
    int wager, owager, *result;
    string *args, for_c, get_c;
   
    if (TP != Player1 && TP != Player2)
    {
        notify_fail("You can't bet because you aren't playing.\n");	
        return 0;
    }

    if (Player1->query_wiz_level() || Player2->query_wiz_level())
    {
        notify_fail("Immortals may not bet money.\n");	
        return 0;
    }
        
    if (Moves_made)
    {
        notify_fail("A game is in progress. Wait until the start of a new game.\n");	
        return 0;
    }

    if (TP->query_prop(WAGER_PLACED))
    {
        notify_fail("You've already placed a bet. You'll have to withdraw it before you may place another.\n");	
        return 0;
    }
        
    if (!strlen(str))
    {
        notify_fail("Syntax: bet <amount in gold coins>\n" +
                    "Example: bet 50\n");	
        return 0;
    }

    args = explode(str, " ");
    if (sizeof(args) !=1)
    {
        notify_fail("Syntax: bet <amount in gold coins>\n" +
                    "Example: bet 50\n");
        return 0;
    }

    wager = atoi(str);
    if (wager < 10)
    {
        notify_fail("You must bet at least ten gold coins.\n");	
        return 0;
    }


    if (Player1->query_prop(WAGER_PLACED))
    {
        owager = Player1->query_prop(WAGER_PLACED);
        if (wager != owager)
	{
	    notify_fail(sprintf("You must bet the same amount. Your " +
                    "opponent bet %i gold coins.\n", owager));
            return 0;
        }
    }

    if (Player2->query_prop(WAGER_PLACED))
    {
        owager = Player2->query_prop(WAGER_PLACED);
        if (wager != owager)
	{
	    notify_fail(sprintf("You must bet the same amount. Your " +
	    "opponent bet %i gold coins.\n", owager));
            return 0;
        }
    }
    
        
    result = pay(wager * 144, TP,0,0,0,0);
    // write(sprintf("%i\n", sizeof(result)));
    // dump_array(result);
    if (sizeof(result)==1)
    {
	notify_fail("You don't have " + str + " gold coins to bet. Only gold coins " +
	"may be used.\n");
	return 0;
    }

    Gambling_rounds_played = 0;
    TP->add_prop(WAGER_PLACED, wager);    
    write("You bet " + str + " gold coins.\n");
    say(QCTNAME(TP) + " bets " + str + " gold coins.\n");
    write("Barliman comes in and collects " + str + " coins from you.\n");
    tell_room(TO, "Barliman comes in and collects " + str + " gold coins from " +
    QTNAME(TP) + ".\n", TP);
    tell_room(TO, "Barliman leaves south.\n");
    log_file(WAGER_LOG, ctime(time()) + " " + CAP(TP->query_real_name()) +
    sprintf(" bet %i gold coins.\n", wager));
    return 1;    
}


/*
 * Function name:   do_withdraw
 * Description:     Withdraw bet before game is started
 *                  
 * Argument:        string "bet"
 * Returns:         0/1
 */
int
do_withdraw(string str)
{
    int wager;
    
    if (!str)
    {
	notify_fail("Withdraw what? Bet?\n");
	return 0;
    }
    
    if (str != "bet" && str != "wager")
    {
	notify_fail("Withdraw what? Bet?\n");
	return 0;
    }

    if (Moves_made || Gambling_rounds_played)
    {
	notify_fail("The game has already started. You may not withdraw your bet.\n");
	return 0;
    }
    
    wager = TP->query_prop(WAGER_PLACED);
    
    if (!wager)
    {
	notify_fail("You have no bet placed.\n");
	return 0;
    }
    return_wager(TP);
    return 1;
    
}


/*
 * Function name:   return_wager
 * Description:     Return coins to better
 *                  
 * Argument:        object plyr
 * Returns:         0/1
 */
private void
return_wager(object plyr)
{
    object coins;
    int wager = plyr->query_prop(WAGER_PLACED);
    
    tell_room(TO, "Barliman comes in and hands " + QTNAME(plyr) +
      " some coins.\n", plyr);
    write(sprintf("Barliman hurries in and returns the %i gold coins you bet.\n", wager));
    tell_room(TO, "Barliman rushes out.\n");    
    plyr->remove_prop(WAGER_PLACED);
    coins = MONEY_MAKE_GC(wager);
    coins->move(plyr);
    log_file(WAGER_LOG, ctime(time()) + " " + CAP(plyr->query_real_name()) +
    sprintf(" had %i gold coins returned after withdrawing a bet.\n", wager));
}


/*
 * Function name:   pay_winner
 * Description:     Give coins to winner
 *                  
 * Argument:        object plyr
 * Returns:         0/1
 */
int
pay_winner(object winner)
{
    object coins;
    int wager;
    
    wager = (winner->query_prop(WAGER_PLACED) * 2);
    
    tell_room(TO, sprintf("Barliman comes in and hands " + QTNAME(winner) +
      " %i gold coins.\n", wager), winner);
    write(sprintf("Barliman hurries in and gives you %i gold coins.\n", wager));
    tell_room(TO, "Barliman rushes out.\n");    
    Player1->remove_prop(WAGER_PLACED);
    Player2->remove_prop(WAGER_PLACED);
    coins = MONEY_MAKE_GC(wager);
    coins->move(winner);
    log_file(WAGER_LOG, ctime(time()) + " " + CAP(winner->query_real_name()) + sprintf(" won %i gold coins.\n", wager));
}


/*
 * Function name:   do_challenge
 * Description:     Challenge player to game of connect4 by sending message
 *                  
 * Argument:        string str
 * Returns:         0/1
 */
int
do_challenge(string str)
{    
    string body, victim, challenger, wager, *arg;
    object scroll;
    int nbr_challenges;

    if (!strlen(str))
    {
        notify_fail("Syntax: challenge <player> <wager>\n\n" +
		    "Examples:\n" +
		    "challenge Palmer\n" +
		    "challenge Lars 50 gold\n" +
		    "challenge Abeni all the tea in Bree\n\n");
        return 0;
    }
    
    arg = explode(str, " ");
         
    challenger = TP->query_name();
    victim = CAP(arg[0]);
    wager = str[strlen(arg[0])..];
         
    // Wizards may challenge wizards but mortal may not,
    // to prevent checking if wizards are logged in
    if (SECURITY->query_wiz_rank(LOW(victim)) && !TP->query_wiz_level())
    {
        tell_room(TO, "A curly-haired hobbit runs in and yells, " +
	"'I am afraid of wizards. Send mail!'\n");
        tell_room(TO, "The curly-haired hobbit dashes off.\n");
	return 1;
    }    
        
    nbr_challenges = TP->query_prop(C4_CHALLENGES);
    if (nbr_challenges >= MAX_MESSENGERS)
    {
        notify_fail("You've sent enough challenges for today.\n");
	return 0;
    }
	
    body = "\nGreetings, " + victim + "!\n\n" +
      challenger + " has challenged you to a game " +
      "of Connect Four at the Prancing Pony\n" +
      "in Bree.\n\n";
    if (sizeof(arg) > 1)       
       body += CAP(HE_SHE(TP)) + " wagers:" + wager + ".\n";
       
    tell_room(TO, "A curly-haired hobbit runs off with a scroll.\n");  
    FIXEUID;   
    
    log_file(WAGER_LOG, ctime(time()) + " " + CAP(TP->query_real_name()) +
    " challenged " + victim + ", wagering" + wager + "\n");
    
    TP->add_prop(C4_CHALLENGES, nbr_challenges + 1);
    scroll = clone_object(SCROLL);
    scroll->set_text(body);
    send_messenger(victim, TP, scroll);
    return 1;
}


/*
 * Function name:   send_messenger
 * Description:     Move scroll to challengee
 *                  
 * Argument:        text player_name, object scroll
 * Returns:         0 - Can't find payer / 1 - Message sent
 */
public void
send_messenger(string victim, object sender, object scroll)
{
    object o = find_player(LOW(victim));

    if (objectp(o) && !o->query_invis())
    {
        scroll->move(o);
	tell_object(o, "A curly-haired hobbit runs up to you, hands you a scroll and dashes off.\n");
	
        tell_room(environment(o), "A curly-haired hobbit runs up to " + 
        QTNAME(o)+", hands " + HIM_HER(o) + " a scroll and dashes off.\n", o);
 
    }
    else    
    
    {
        tell_object(sender, "The curly-haired hobbit was unable to find " + victim + ".\n");
	scroll->remove_object();
    }

}


/*
 * Function name:   exa_chair
 * Description:     Shows chair and who is occupying it
 *                  
 * Argument:        none
 * Returns:         int 0/1
 */

string
exa_chair(string str)
{
  /*
   if (Color_to_play == VOID)
   {
          return "They are well-worn but comfortable looking oak chairs.";
   }
   return "Someone is sitting in the chair.";

    if (check_player(Player[COLOR0]))
        // return QCTNAME(Player1) + " is sitting in the oak chair.";
	return "Foo is sitting in the oak chair.";
    else
    */
   return "These are well-worn but comfortable looking oak chairs.";
}



/*
 * Function name:   decline_start
 * Description:     Player with first move may decline and let
 *                  other player begin
 *                  
 * Argument:        string str
 * Returns:         0/1
 */
int
decline_start(string str)
{
    object tmp;
    
    if (TP->query_real_name() != Player[COLOR0] && TP->query_real_name() != Player[COLOR1] )
    {
        notify_fail("You're not playing.\n");
        return 0;
    }
    if (str=="start")
    {
        if (Moves_made)
	{
             write("The game has already begun.\n");
	     return 1;
	}
        if (Player1 == TP)
	{
             write("You decline to start the game.\n");
             tmp = Player1;
             Player1 = Player2;
             Player2 = tmp;
             tell_object(Player1, "You have the first move.\n");
             tell_object(Player2, "Your opponent has the first move.\n");	     
             Color_to_play = !Color_to_play;	     
	     return 1;
	}
	else
	{
             notify_fail("Its not your turn.\n");
             return 0;
	}
	
    }
    else 
    {
         notify_fail("Decline what? Start?\n");
         return 0;
    }
}



/*
 * Function name:   cheater_security
 * Description:     Make sure players don't try to leave to avoid a loss
 *
 * Argument:        None
 * Returns:         1 - pass/ 0 - bloack
 */
int
cheater_security()
{
    string s = TP->query_real_name();
    
    if ( s == Player[COLOR0] || s == Player[COLOR1] )
    {
	write("You're sitting in a chair and can't quite seem to move south.\n");
        return 1;
    }
    
    return 0;
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

  coin = Color_to_play + 1;
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
       x--, y++) 
  {
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
 * Function name: leave_inv
 * Description:   Called when objects leave this container or when an
 *                object is about to change its weight/volume/light status.
 * Arguments:     ob: The object that just left this inventory.
 *                to: Where it went.
 */ 
void leave_inv(object ob, object to)
{

    ::leave_inv(ob, to);
    if(!objectp(to) || !objectp(ob))
        return;
      
    /* We remove "sitting in a chair..." in case person is transed, 
        or teleports out of the chair somehow */
	
    if(TP->query_prop("_sitting_connect4"))
    {
      TP->remove_prop(LIVE_S_EXTRA_SHORT);
      TP->remove_prop("_sitting_connect4");
    }

}

/*
 * Function name:   score_game
 * Description:     Updates scoreboard for winner and loser
 *                  
 * Argument:        string winner name, string loser name
 * Returns:         none
 */
public void
score_game(string winner, string loser)
{
    add_score(winner, 1);
    add_score(loser, 0);    
}

/*
 * Function name:   add_score
 * Description:     Updates scoreboard after game is over
 *                  
 * Argument:        string player's name / int win or loss
 * Returns:         none
 */
private void
add_score(string plyr, int stats)
{
    mapping Scoreboard;
    int wins, losses, wager;
    
    Scoreboard = restore_map(SCOREBOARD);
    if (!mappingp(Scoreboard))
        Scoreboard = ([ ]);
	
    wager = find_player(LOW(plyr))->query_prop(WAGER_PLACED);

    if (!Scoreboard[plyr])
    {
    
        if (stats)
            Scoreboard+=([plyr:({1,0,wager})]);
        else
	    Scoreboard+=([plyr:({0,1,wager})]);
    }
    else
    {
       wins = Scoreboard[plyr][0];
       losses = Scoreboard[plyr][1];
       
       if (stats)
       {
           Scoreboard[plyr][0] = wins + 1;
	   Scoreboard[plyr][2] += wager;
       }
       else
           Scoreboard[plyr][1] = losses + 1;
    }
    save_map(Scoreboard, SCOREBOARD);
    

}


/*
 * Function name:   read_stufff
 * Description:     Parse the read command
 *                  
 * Argument:        string - what you're trying to read
 * Returns:         int 0/1
 */
int
read_stuff(string str)
{
    if (!strlen(str))
    {
        notify_fail("Read what? Your mind?\n");
        return 0;

    }
    if ((str != "poster") && (str != "scoreboard") && (str != "instructions") && (str != "rules") && str !="the fine print" && str !="fine print")
    {
        notify_fail("Read what? There is a poster and scoreboard you may read.\n");
        return 0;
    }
    if (str == "poster" || str =="instructions" || str =="rules")
    	write(poster_text + "\n");
	
    if (str == "scoreboard")
        write(read_scoreboard());

    if (str == "fine print" || str == "the fine print")
        write(fine_print);
	
			
    return 1;
}

/*
 * Function name:   read_scoreboard
 * Description:     Builds a scoreboard of wins/losses
 *                  
 * Argument:        none
 * Returns:         string of scoreboard
 */
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
    lines =   "Player        Wins  Losses     Gold\n";
    lines += ("===================================\n\n");
    for (i = 0; i < n; i++)
    {
	lines +=sprintf("%-=13s %4d    %4d     %4d\n", CAP(keys[i]), vals[i][0], vals[i][1], vals[i][2]);
    }
    return lines;
}


/*
 * Function name:   init_game
 * Description:     Initializes board, chooses color to start
 *                  
 * Argument:        int comp
 * Returns:         None
 */
void
init_game(int comp)
{
  int x, y;
  
  // Player1=NONE, Player2=NONE;
  
  if (!pointerp(connect4)) {
    connect4 = allocate(WIDTH);
    for (x =0; x < WIDTH; x++) connect4[x] = allocate(HEIGHT);
  }
  for (x = 0; x < WIDTH; x++)
    for (y = 0; y < HEIGHT; y++)
      connect4[x][y] = 0;
  Moves_made = 0;
  switch (comp) {
    case NONE: 
        Color_to_play = !Color_to_play;
	break;
    case X:
        Player[X] = 0;
	Color_to_play = VOID;
	break;
    case O:
        Player[O] = 0;
	Color_to_play = VOID;
	break;
    case BOTH:
        Player[X] = Player[O] = 0;
	Color_to_play = VOID;
	break;
  }
}


/*
 * Function name:   stand_up
 * Description:     Attempt to leave game by standing
 *                  
 * Argument:        string up
 * Returns:         int 0/1
 */
int
stand_up(string str)
{
  string desc;

  if (stringp(str))
  {
      if (str != "up")
      {
          notify_fail("Stand up you mean?\n");
          return 0;
      }
  }

  TP->remove_prop(LIVE_S_EXTRA_SHORT);
  TP->remove_prop("_sitting_connect4");
  if (TP == Player1)
      Player1 = 0;
  if (TP == Player2)
      Player2 = 0;
            
  desc = stand_up_desc();
  if (desc)
  {
    write(desc);
    return 1;
  }
  return 0;
}


/*
 * Function name:   stand_up_desc
 * Description:     Shows message when you try to stand up
 *                  
 * Argument:        None
 * Returns:         String
 */
string
stand_up_desc()
{
  string name;
  int color;

  name = TP->query_real_name();
  if (name == Player[COLOR0] || name == Player[COLOR1]) {
    if (Moves_made) {
      return "You cannot stand up in the middle of a game. " +
             "Do you wish to resign?\n";
    }
    if (name == Player[COLOR0])
        color = COLOR0;
    else
        color = COLOR1;
    
    init_game(color);
    say(QCTNAME(TP) + " gets up off " +
        TP->query_possessive() + " " + Seat_name + ".\n");

    return "You stand up.\n";
  }
  else 
  {
    notify_fail("You do not occupy one of the " + Seat_name + "s.\n");
    return 0;
  }
}


/*
 * Function name:   resign
 * Description:     End a game
 *                  
 * Argument:        None
 * Returns:         String showing how game ends
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
  if (Color_to_play == VOID)
  {
    notify_fail("There is no game in progress! Sit in a chair to join a game.\n");
    return 0;
  }
  if (name == Player[COLOR0] || name == Player[COLOR1])
  {

    if (Moves_made == 0)
    {
       write("You stand up and abandon the game.\n");
       say(QCTNAME(TP) + " stands up and resigns the game.\n");
       TP->remove_prop(LIVE_S_EXTRA_SHORT);
       TP->remove_prop("_sitting_connect4");
       if (Player1->query_prop(WAGER_PLACED))
           return_wager(Player1);
       if (Player2->query_prop(WAGER_PLACED))	   
           return_wager(Player2);
       if (name == Player[COLOR0])
          init_game(COLOR0);
       else 
          init_game(COLOR1);

       // return stand_up_desc();
       return "";
    }
    if (name == Player[COLOR0])
        winner = COLOR1;
    else 
        winner = COLOR0;
    write("You resign from the game.\n");
    opposition = check_player(Player[winner]);
    say(QCTNAME(opposition) + " wins the game " + 
       "because " + QTNAME(TP) + " resigned.\n", ({opposition, TP}));
    tell_object(opposition, "You win the game " +
       "because your opponent resigned.\n");
    score_game(opposition->query_real_name(), TP->query_real_name());
    write("You stand up and abandon the game.\n");
    say(QCTNAME(TP) + " stands up and resigns the game.\n");
    TP->remove_prop(LIVE_S_EXTRA_SHORT);
    TP->remove_prop("_sitting_connect4");
    if (TP->query_prop(WAGER_PLACED))
        pay_winner(opposition);    
    
    if (name == Player[COLOR0])
        init_game(COLOR0);
    else 
        init_game(COLOR1);
  } else {
    notify_fail("You are not currently playing!\n");
    return 0;
  }
  return "";
}


/*
 * Function name:   start_game_desc
 * Description:     Shows people joining or starting game
 *                  
 * Argument:        none
 * Returns:         string showing action
 */
string
start_game_desc()
{
  
  string name;
  int color;
  object tmp;
  
  name = TP->query_real_name();
  if (name == Player[COLOR0] || name == Player[COLOR1])
     return "You are already sitting on a " + Seat_name + ".\n";

  if (Player[COLOR0] && Player[COLOR1]) {
    Player1 = check_player(Player[COLOR0]);
    Player2 = check_player(Player[COLOR1]);
    if (!Player1 && !Player2) {

      tell_room(this_object(), "The game has been abandoned " +
          "because both players are absent.\n");
	
      init_game(BOTH);
    } else {
      return "A game is already in progress, you can't occupy a chair.\n";
    }
  }

  write("You sit down on one of the " + Seat_name + "s.\n");
  TP->add_prop("_sitting_connect4",1);
  TP->add_prop(LIVE_S_EXTRA_SHORT," is sitting in a chair");    
  if (!Player[COLOR0])
  {
      Player[COLOR0] = TP->query_real_name();
      write("You will play O's.\n");
      TP->add_prop(LIVE_S_EXTRA_SHORT," is sitting in a chair playing O's");
  }
  else
  {
      Player[COLOR1] = TP->query_real_name();
      write("You will play X's.\n");
      TP->add_prop(LIVE_S_EXTRA_SHORT," is sitting in a chair playing X's");
  }
  say(QCTNAME(TP) + " sits down on one of the " + Seat_name + "s.\n");

  if (Player[COLOR0] && Player[COLOR1]) {
    Player1 = check_player(Player[COLOR0]);
    Player2 = check_player(Player[COLOR1]);

    if (!Player1 || !Player2)
    {
      if (!Player1)
          color = COLOR0;
      else
          color = COLOR1;
    /* 
      tell_room(this_object(), capitalize(Player[color]) + "'s " +
                Seat_name + " is no longer reserved.\n"); */
	
      init_game(color);
      
    } 
    
    else {

      Color_to_play = color_to_start();

      tell_room(this_object(), QCTNAME(Player1) + " and " +
          QTNAME(Player2) + " have started a game.\n", ({Player1, Player2 }));      
      
      if (Color_to_play == COLOR1)
      {
        tmp = Player1;
        Player1 = Player2;
        Player2 = tmp;
      }
      tell_object(Player1, "You have the first move.\n");
      tell_object(Player2, "Your opponent has the first move.\n");
     }
  }
  return "";
}


/*
 * Function name:   start_game
 * Description:     Lets player sit on chair to start game
 *                  
 * Argument:        string - chair
 * Returns:         int 0/1
 */
int
start_game(string str)
{
  string desc;

  if (str)
  {
      if ((str != "on " + Seat_name && str != "in " + Seat_name &&
          str != Seat_name && str != "on seat" && str != "in seat" 
	  && str != "seat"))
      {
          write("Sit on what?\n");
          return 1;
      }
  }
  
  desc = start_game_desc();
  
  if (desc != 0) {
    write(desc);
    return 1;
  }
  return 0;
}


/*
 * Function name:   check_player
 * Description:     Determines if player is still in room
 *                  
 * Argument:        string - player's name
 * Returns:         mixed player's object or int 0 if player is missing
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
 * Function name:   drop_coin
 * Description:     Adds coin to board array
 *                  
 * Argument:        int column
 * Returns:         int 0 or row
 */
int
drop_coin(int column)
{
  int x;

  if (connect4[column][HEIGHT-1])
    return 0;

  while (connect4[column][x++]);
     connect4[column][x-1] = Color_to_play+1;
  return x;
}



/*
 * Function name:   color_to_start
 * Description:     Picks a random player to start game
 *                  
 * Argument:        none
 * Returns:         int 1/2
 */
int
color_to_start()
{
    return random(2);
}


/*
 * Function name:   exa_board
 * Description:     Shows description of board and whos turn is next
 *                  
 * Argument:        none
 * Returns:         string - Description / who is playing
 */
string
exa_board()
{
  string top, bottom, pname;

  top = "The board has been designed for " +
         "playing connect 4.\n\n";
  if (Moves_made)
  {
      pname = check_player(Player[Color_to_play])->query_the_name(TP);
      if (pname == TP->query_name())
          pname = "your";
      else
          pname += "'s";
      bottom = "It is " + pname + " turn to play.\n";
  }      
  else
     bottom = "";

  return top + connect4_long() + bottom;
}


/*
 * Function name:   connect4_long
 * Description:     Draws board
 *                  
 * Argument:        none
 * Returns:         string - The current board
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
 * Function name:   draw_board
 * Description:     Shows board to everyone in the room
 *                  
 * Argument:        none
 * Returns:         none
 */
void
draw_board()
{
    tell_room(this_object(), "\n" + connect4_long() + "\n"); ;
}

/*
 * Function name:   smack_thief(string str)
 * Description:     Scold thieves and kender for trying to ruin a game.
 *                  
 * Argument:        string - whatever spell they try
 * Returns:         int 0
 */
string
smack_thief(string str)
{
    say(QCTNAME(TP) + " stumbles clumsily.\n");
    say(QCTNAME(TP) + " blushes.\n");
    notify_fail("You notice everyone watching you.\n");
    return 0;
}


/*
 * Function name:   smack_caster(string str)
 * Description:     Scold magic users for trying to ruin a game.
 *                  
 * Argument:        string - whatever spell they try
 * Returns:         int 0
 */
string
smack_caster(string str)
{
    say(QCTNAME(TP) + " winces in pain after " + HE_SHE(TP) + " tries to cast a spell.\n");
    notify_fail("Your brain hurts.\n");
    return 0;
}

/*
 * Function name:   play_move
 * Description:     Attempts to drop piece on board game
 *                  
 * Argument:        string - column number
 * Returns:         int 0/1
 */
string
play_move(string str)
{
  int column, row, wager;
  string name, *args;
  object opposition, tmp;

  
  if (!str) {
    notify_fail("Play what? Choose a column number.\n");
    return 0;
  }
  
  args = explode(str, " ");
  if (sizeof(args) != 1 || !atoi(args[0])) {
    notify_fail("Play what? Choose a column number.\n");
    return 0;
  }
    
  name = TP->query_real_name();
  if (!name) return 0;
  if (Color_to_play == VOID) {
    notify_fail("There is no game in progress! Two players must be seated.\n");
    return 0;
  }
  
  if (Player1->query_prop(WAGER_PLACED))
  {
      if (!Player2->query_prop(WAGER_PLACED))
      {
         wager = Player1->query_prop(WAGER_PLACED);      
         notify_fail(sprintf("A bet of %i gold coins has been placed. " +
	 "Both players must bet or the bet must be withdrawn before " +
	 "the game can begin.\n", wager));
         return 0;
      }
   }   
      
  if (Player2->query_prop(WAGER_PLACED))
  {
      if (!Player1->query_prop(WAGER_PLACED))
      {
         wager = Player2->query_prop(WAGER_PLACED);
         notify_fail(sprintf("A bet of %i gold coins has been placed. " +
	 "Both players must bet or the bet must be withdrawn before " +
	 "the game can begin.\n", wager));
	 return 0;
      }
   }   

         
  if (name == Player[Color_to_play]) {
    /* Check if opposition is still in room */
    opposition = check_player(Player[!Color_to_play]);
    
    if ((sscanf(str,"%d", column) == 1) && (column >= 1) && (column <= WIDTH)) {
       if ((row = drop_coin(column-1))) {
         write("You drop an " + ((Color_to_play) ? "X" : "O") +
               " in column " + column + ".\n");
         say(QTNAME(TP) + " drops an " + ((Color_to_play) ? "X" : "O") +
                                " into column " + column + ".\n");
         Moves_made++;
         tell_room(this_object(), "\n" + connect4_long() + "\n");
         tell_room(this_object(), "You hear a " +
            ONE_OF_LIST(({"plonk", "plink", "klink", "kerplunk", "klonk"})) + " noise.\n");
  
         if ((Moves_made >= 7) && check_win(row-1, column-1))
	 {
           write("You win the game!\n");
           say(QCTNAME(TP) + " wins the game!\n", ({opposition, TP}));
	   score_game(TP->query_real_name(), opposition->query_real_name());	   
           if (TP->query_prop(WAGER_PLACED))   
	       pay_winner(TP);
           if (opposition)
	   {
	       tell_object(opposition, "You lost the game.\n");
	       say(QCTNAME(opposition) + " lost the game.\n", ({opposition, TP}));
	   }

	   init_game(NONE);
	Color_to_play = color_to_start();

	Player[COLOR0] = Player1->query_real_name();
	Player[COLOR1] = Player2->query_real_name();
	tell_room(this_object(), QCTNAME(Player1) + " and " +
		QTNAME(Player2) + " have started a game.\n", ({Player1, Player2 }));      
	
	tell_object(check_player(Player[Color_to_play]), "You have the first move.\n");
	tell_object(check_player(Player[!Color_to_play]), "Your opponent has the first move.\n");

           return "";
         }

         if (Moves_made == (WIDTH*HEIGHT))
	 {
	   tell_room(TO, "The game is a draw!\n");
           if (Player1->query_prop(WAGER_PLACED))
	      return_wager(Player1);
           if (Player2->query_prop(WAGER_PLACED))
	      return_wager(Player2);
	      	   
           init_game(NONE);
           return "";
         }
         Color_to_play = !Color_to_play;
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
        if (name != Player[!Color_to_play]) {
            notify_fail("You are not currently playing!\n");
         return 0;
  } else
    {
        notify_fail("Its not your turn!\n");
        return 0;
    }
}
