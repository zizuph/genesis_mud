/* This is the first of two rooms which compose the faerie riddle quest.
   This room is outside the magical circle of wood. There is an encrypted
   message on the outer wall, following the variable instructions thereon
   will allow entrance to the inner circle where a more devious challenge
   awaits the worthy player.

   Code (c) 2000 to Damian Horton - BKA Casimir.
*/
 
#pragma strict_types
#pragma save_binary 

#include "/d/Emerald/sys/paths.h"
#include "/d/Emerald/sys/weather.h"
#include <ss_types.h>
#include <macros.h>
#include "/d/Emerald/quest_handler/quest_handler.h"


//inherits from encrypt.c, which contains the encryption routines
inherit "/w/casimir/encrypt.c";

//global variables

int Arch; //whether or not the archway allowing access to the interior
          //of the circle is open

string Access_Verb; //string which denotes what action is needed to open
                    //the gateway 
string Last_Player; //name of the last player to attempt to open the gateway
string Char_String; //the encrypted message whose deciphering will allow
                    //for the opening of the archway 
int String_Number; //number of times the required action must be repeated
                   //to open the archway
int Player_Number; //the number of times Last_Player has performed that
                   //action
object Circle_Room; //the room accessed through the archway by solving
                    //the first part of the encryption

//prototypes
string char_function();
string long_fun();
string arch_fun();
string wall_fun();
void set_char_string();
int hop_func(string arg);
int howl_func(string arg);
int bark_func(string arg);
int enter_func(string arg);
int climb_func(string arg);
void open_archway();

void
create_valley_room()
{
  // ::create_valley_room();

    /* Make sure the room is loaded, so we can find it */ 
    LOAD_ERR("d/Emerald/blackwall/valley1/encrypt");
    Circle_Room = find_object("d/Emerald/blackwall/valley1/encrypt");

    set_short("a mystical glade");
    set_em_long("@@long_fun@@");		
    add_item(({"wall", "living wall", "wood", "living wood",
		   "wooden wall", "wood wall", "roots", "entity",
		   "tree-like entity", "tree",
		   "branches", "bark", "leaf-encrusted branches"}),
	     wall_fun);
		   
    add_item(({"concentration", "scratches", "gouges",
		 "scratches and gouges", "concentration of scratches",
		 "concentration of gouges", "series", "letters",
		 "concentration of scratches and gouges",
		 "series of letters", "characters", "runes",
		 "pattern"}), char_function);
    
    add_item(({"archway", "portal", "clearing", "shimmering archway"}),
	     arch_fun);

    set_char_string(); //set up the encrypted message

    add_exit(BLACKWALL_VALLEY1_DIR + "valley1_50", "north", 0, 4);
}

void
init()
{
    ::init();
    add_action(hop_func, "hop");
    add_action(howl_func, "howl");
    add_action(bark_func, "bark");
    add_action(enter_func, "enter");
    add_action(climb_func, "climb");
}

/* VBFC long description of the room. Players who have completed the first
   part of the quest, but not the second,  will perceive a shimmering archway
   allowing them to pass through the wall. 
*/
string
long_fun()
{
    string descrip;
    descrip =  "Within a dense forest. A strange wall, made of "+  
	"living wood rises out of the ground in front of you. "+
	"The wall is about five  metres in height and completely "+
	"surrounds a circular area approximatly 30 metres "+
	"in diamater. Neither treetop nor structure stands "+
	"out from behind the wall, though many of the "+
	"surrounding trees do surpass it in height. ";

    if (QH_QUERY_QUEST_COMPLETED(this_player(), "Faerie_riddle2") ||
	! (QH_QUERY_QUEST_COMPLETED(this_player(), "Faerie_riddle1")) ||
	Circle_Room->player_present())
    {
	descrip += "There is no visible method of obtaining passage through "+
		"the wall.\n";
    } 

    else
    {
	descrip += "A shimmering archway allows passage into the enclosed "+
	    "clearing.\n";
    }

    return descrip;
}

/* VBFC description of the wall. Certain players (see above) will see a
   shimmering portal which just doesn't exist for others. The portal
   is never visible if another player is in the room on the other side.
*/
string
wall_fun()
{
    string descrip;
    descrip = "The wall seems to be some sort of living, tree-like "+
	"entity. Roots visibly extend from the base of the wall "+
	"into the ground, and a few small, leaf-encrusted branches "+
	"protrude from the wall at random intervals. The wall has "+
	"no bark, but its wood is unblemished, save for one place "+
	"where there is a concentration of scratches and gouges. ";

    if (QH_QUERY_QUEST_COMPLETED(this_player(), "Faerie_riddle2") ||
    	! (QH_QUERY_QUEST_COMPLETED(this_player(), "Faerie_riddle1")) ||
	Circle_Room->player_present())
    {    
	descrip +=  "The wall appears to be far too smooth to be climbed, "+
	    "even by an expert.\n";
    }

    else
    { 
	descrip += "A shimmering archway, just big enough for you "+
	    "to enter allows passage into the clearing the wall "+
	    "encloses.\n";
    }

    return descrip;
}

/* VBFC description of the shimmering archway. Those who have completed
   the first part, but not the second part of the faerie riddle quest
   may see, and thus examine, the archway. Others may not.
*/

string
arch_fun()
{
    if (QH_QUERY_QUEST_COMPLETED(this_player(), "Faerie_riddle2") ||
	! (QH_QUERY_QUEST_COMPLETED(this_player(), "Faerie_riddle1"))||
	Circle_Room->player_present())
    {
	//the player cannot see the archway, therefor...
	return "You find no archway.\n";
    } 

    return "A strange, shimmering archway, just large enough to "+
	"you through it, appears to grant access to the clearing "+
	"enclosed by the wall. The shimmering makes it impossible "+
	"to make out details of what lies beyond, though the "+
	"ground is green, and there are no obvious trees, or "+
	"structures. It should be possible to enter the archway.\n";
}

/* Returns true if this_player()  has sufficient language skill/int
   to make out the characters, false otherise. Used when a character
   examines or reads the characters.
*/
int
decipher_chars()
{
    int difficulty;
    difficulty = 25 + random(10); //SS_LANGUAGE + SS_INT/10 must
                                  //exceed this value for success     

    if (this_player()->query_skill(SS_LANGUAGE) + (this_player()->
	query_stat(SS_INT) / 10) > difficulty)
    {
	return 1;
    }

    return 0;
}

/* Called by reset_room, this function determines what string is 
   encrypted on the wall, and thereby determines what is required 
   to open the archway. It sets up all the appropriate global
   variables, and encodes that string in one of four different
   encryption schemes.
 */
void
set_char_string()
{
    string num_string; //textual form of String_Number
    int anumber; //random int generated every time this function is called
    string* code_array; //array used in developing code
    mapping code; //the code via which the string will be encrypted

    anumber = random(3);
   
    switch(anumber)
    {
    case 0:
	Char_String = "To enter the forbidden hall, prove thy "+
	    "worth to us all: ";
	break;

    case 1:
	Char_String = "If beyond these walls ye wish to pass, first";
	break;
	
    default:
	Char_String = "If it is entrance that you seek, then it pays "+
	    "to first be meek: ";
    }

    anumber = random(4) + 1;
    String_Number = anumber; 

    switch (anumber)
    {
    case 1:	     
	num_string = "once";
	break;
    case 2:
	num_string = "twice";
	break;
    case 3:
	num_string = "thrice";
	break;
    case 4:
	num_string = "four times";
	break;
    default:
	num_string = "five times";
    }
    
    anumber = random(3);

    switch (anumber)
    {

    case 0:
	Char_String += " bark " + num_string + " like a dog.";
	Access_Verb = "bark";
	break;
	
    case 1:
	Char_String += " hop " + num_string + " like a rabbit.";
	Access_Verb = "hop";
	break;

    default:
	Char_String += " howl " + num_string + " like a wolf.";
	Access_Verb = "howl";
    }

    // Encrypting Char_String with one of 4 randomly determined,
    // but easily broken codes.

    anumber = random(4);

    switch (anumber)
    {

    case 0:
	code_array = ({"e", "c", "d", "f", "i", "g", "h", "j",
		       "o", "k", "l", "m", "n", "p", "u", "q", "r",
		       "s", "t", "v", "a", "w", "x", "y", "z", 
		       "b"});
	break;

    case 1:
	code_array = ({"u", "z", "b", "c", "a", "d", "f", "g", "e",
		       "h", "j", "k", "l", "m", "i", "n", "p", "q",
		       "r", "s", "o", "t", "v", "w", "x", "y"});

	break;

    case 2:
	code_array = ({"c", "d", "e", "f", "g", "h", "i", "j", "k",
		       "l", "m", "n", "o", "p", "q", "r", "s", "t",
		       "u", "v", "w", "x", "y", "z", "a", "b"});
	break;
	
    default:
	code_array = ({"y", "z", "a", "b", "c", "d", "e", "f", "g",
		       "h", "i", "j", "k", "l", "m", "n", "o", "p",
		       "q", "r", "s", "t", "u", "v", "w", "x"});
    }

    //Alphabet is a global variable in encrypt.c
    code = mkmapping(Alphabet, code_array);
    Char_String = encrypt(Char_String, code);
}

/* VBFC for examining the scratches. If the player has sufficient 
   language ability, he will be able to read the scratches, not that
   that may do him a whole lot of good. */

string
char_function()
{
    string return_value;

    return_value = "A set of deep gouges mars the otherwise unblemished "+
	"surface of the wall. ";

    if (! decipher_chars())
    {

	// the player hasn't the language skill to determine that they
	// form a distinct pattern

	return_value += " The gouges have an unnatural quality about the "+
	    "way they are laid out. They appear to have been inscribed in "+
	    "some sort of deliberate pattern, the signifigance of which "+
	    "is lost on you.\n";
    }

    else
    {
	return_value += " Upon closer examination, it is apparant that the "+
	    "scratches form a series of letters as follows: \n\n" +
	    Char_String + "\n";
    }

    return return_value;
}    

/* Each of the following three functions are add_actions which might
   allow the player to open the archway. The appropriate action
   must be repeated an appropriate number of times to cause the
   archway to appear.

   Note: Any use of the correct verb will work, a player need only
   "howl", not "howl like a wolf" (that will also work) to open the 
   archway.
   
   Note also: If the verb used is not correct, no notify_fail() message
   will be printed, and the player will merely get a "What?" response.

   The correct verb is determined by the message inscribed upon the wall,
   and is set at random.
*/

int
hop_func(string arg)
{
    if (! (Access_Verb == "hop"))
    {
	return 0;
    }

    // the verb is correct, therefor:

    write("You hop like a rabbit!\n");
    say("Abruptly, " + QCTNAME(this_player()) + " hops up and down "+
	"like a bunny rabbit!\n");

    if (! (Last_Player == this_player()->query_name()))
    {
	Last_Player = this_player()->query_name();
	Player_Number = 0;
    }
    
    Player_Number++;

// Check to see i
    if (Player_Number == String_Number)
    {
	open_archway();
    }

    return 1;
}
   
int
howl_func(string arg)
{
    if (!(Access_Verb == "howl"))
    {
	return 0;
    }

    // the verb is correct, therefor:

    write("You howl like a wolf.\n");
    say("Abruptly, " + QCTNAME(this_player()) + " throws " +
	this_player()->query_possessive() + " to the sky and "+
	"howls like a wolf.\n");

    if (! (Last_Player == this_player()->query_name()))
    {
	Last_Player = this_player()->query_name();
	Player_Number = 0;
    }
    
    Player_Number++;

// Check to see i
    if (Player_Number == String_Number)
    {
	open_archway();
    }

    return 1;
}

int
bark_func(string arg)
{
    if (! (Access_Verb == "bark"))
    {
	return 0;
    }

    // the verb is correct, therefor:

    write("You bark like a dog.\n");
    say("Abruptly, " + QCTNAME(this_player()) + " barks sharply, in "+
	this_player()->query_possessive() + " best imitation of a "+
	"dog.\n");

    if (! (Last_Player == this_player()->query_name()))
    {
	Last_Player = this_player()->query_name();
	Player_Number = 0;
    }
    
    Player_Number++;

// Check to see i
    if (Player_Number == String_Number)
    {
	open_archway();
    }

    return 1;
}

/* Add_action function which allows a player to enter the 
   archway, IFF he can see it.
*/
int
enter_func(string arg)
{
    if (QH_QUERY_QUEST_COMPLETED(this_player(), "Faerie_riddle2") ||
	! (QH_QUERY_QUEST_COMPLETED(this_player(), "Faerie_riddle1")) ||
	Circle_Room->player_present())
    {
	//no archway exists for that player, therefor he gets a
	//"What?" message.
	return 0;
    } 

    if (! parse_command(arg, ({}), "[the] 'archway' / 'clearing'"))
    {
	//command failed;
	notify_fail("Enter what, the archway?\n");
	return 0;
    }

    //Command successful:
    
    write("Tentatively, you step through the archway, and into the "+
	  "enclosed clearing beyond.\n");
    say(QCTNAME(this_player()) + " walks straight through the "+
	"wall!!!\n");

    Circle_Room->set_riddle(); //set up the specific riddle for that player
    this_player()->move_living("M", Circle_Room, 1, 0);
    return 1;
}

/* Add_action to handle a player who attempts to climb the wall.
   The result is inevitably failure.
*/
int
climb_func(string arg)
{
    if (! parse_command(arg, ({}), "[up] [the] [wood] [wooden] 'wall'"))
    {
	//command failed:
	notify_fail("Climb what, the wall?");
	return 0;
    }

//Command succeeded - not that this is advantageous to the player.
    write("You attempt to climb up the smooth wooden wall, but find "+
	  "that it is impossible. You slip and land hard on your rump!\n");
    say(QCTNAME(this_player()) + " attempts to climb the smooth wooden "+
		"wall but succeeds only in falling, landing "+
		"unceremoniously on " + this_player()->query_possessive() +
		" behind.\n");
    return 1;
}
  
/* This function is called when a player completes the actions necessary
   to open the archway into the magical enclosed by the wall. Opening
   the archway completes the quest "Faerie_riddle1", resulting in a
   small experience award for the player. Until such a time as the
   player completes Faerie_riddle2, he/she will be able to see, and
   use the archway, at will.
*/

void
open_archway()
{
    if (QH_QUERY_QUEST_COMPLETED(this_player(), "Faerie_riddle2"))
    {
	// player has already done the quest, he cannot enter again
	write("Nothing happens...\n");
	return;
    }

    if (Circle_Room->player_present())
    {
	//there is someone in the other room, so the archway cannot open
	
	write("A strange sensation comes over you. You feel that somehow "+
	      "something important has changed about this location, but "+
	      "that you will have to return at a different time to learn "+
	      "exactly what has happened.\n");
	return;
    }

    if (QH_QUERY_QUEST_COMPLETED(this_player(), "Faerie_riddle1"))
    {
	//player has already opened the portal once, he can already see it
	write("Nothing happens, though the archway "+
	      "remains open.\n");
	return;
    }

    write("Abruptly, a section of the wood wall begins "+
	  "shimmer in front of you. Gradually the "+
	  "shimmering coalesces into a shimmering archway "+
	  "which would seem to allow access to the grassy "+
	  "clearing within.\n");
    
    if (QH_QUEST_COMPLETED(this_player(), "Faerie_riddle1"))
    {
	/*the player has just completed the first part of the 
	  Faerie riddle quest - the award is taken care of by the
	  QH_QUEST_COMPLETED macro. */

	if (this_player()->query_average_stat() > 50)
	{
	    write("You feel more experienced.\n");
	}
	else
	{
	    write("You feel a little more experienced.\n");
	}
    }

    else
    {
	write("If there is no reason why you should "+
	      "not be awarded experience for your "+
	      "actions, please file a bug report.\n");
    }  
}


    







