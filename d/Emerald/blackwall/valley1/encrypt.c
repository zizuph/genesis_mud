/* This room contains the second portion of the Faerie Riddle
   Quest. 

   Code (c) 2000 to Damian Horton - BKA Casimir.
*/
 
#pragma strict_types
#pragma save_binary 

#include "/d/Emerald/sys/paths.h"
#include "/d/Emerald/sys/weather.h"
#include <macros.h>
#include <math.h>
#include <filter_funs.h>
#include <stdproperties.h>

#define SEED 5653454312 //seed for NAME_TO_RANDOM
#define NUM_RIDDLES 1 //number of riddles supported by this room

inherit BLACKWALL_VALLEY1_DIR + "base_valley.c";

//global variables
string* Alphabet = ({"a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k",
		     "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v",
		     "w", "x", "y", "z"});

mapping Code; //the code via which the riddle is encrypted
int Riddle; //which riddle is currently in effect?

//The various riddles:

string Riddle0 = "It breathes, it eats, it reproduces,\n"+
          "And still it is not alive,\n" +
          "Bring it here and it will grow,\n"+
          "And you can watch it thrive.\n"; //fire

string Riddle1 = "In marble halls as white as milk,\n"+
          "Lined with skin as soft as silk,\n"+ 
          "Within a fountain crystal-clear,\n"+
          "A golden apple doth appear,\n"+
          "No doors are there to this stronghold,\n"+
          "Yet thieves break in and steal the gold.\n";//egg

string Riddle2 = "It does not have eyes,\n"+
          "But once it did see,\n"+
          "Once it had thoughts,\n"+
          "But now it lies empty.\n";//skull

string Riddle3 = "Bring me that which is without begining and without "+
                 "end,\nAnd is often home to a girl's best friend.\n";
         //ring or necklace

string Riddle4 = "Six faces I have,\n"+
          "And twenty-one eyes,\n"+
          "I will roll in this place,\n"+
          "Or you will lose face.\n"; //six-sided die

string Riddle5 = "Its life can be measured in hours,\n"+
          "It serves by being consumed.\n"+
          "Thin it is quick, fat it is slow.\n"+
          "Expose it to wind and its doomed.\n"; //candle

string Riddle6 = "It lives its first life in the Heavens,\n"+
          "You'd only catch it if you flew,\n"+
          "In another its hard as rock,\n"+
          "And so that life will not do.\n"+
          "Its third life you will take,\n"+
          "And bring its coffin too.\n";//anything containing water
          
// not yet implemented

string Riddle7 = "Dark with white markings,\n"+
          "And smooth like a rock,\n"+
          "Where learning occurs,\n"+
          "I help convey thought.\n"; //chalk board

//prototypes
int encrypt_test(string arg);
string vine_message();
mapping randomize_alphabet();

void
create_valley_room()
{
    set_short("A mystical glade.");
    set_em_long("A mystical glade, enclosed by a wall of living wood. "+
		"No trees or large plants grow within the wooden walls "+
		"Grass carpets most of the ground within the walls, "+
		"however, save for a mound of peculiar vines which lies "+
		"at the center of the clearing. At the very centre of "+
		"this mound lies a seemingly purposeful circle "+
		"of white stones. An archway provides egress from this "+
		"place.\n");

    add_item(({"grass", "short grass", "green grass", "short green grass"}),
	     "A short green grass carpets the enclosed glade, save for "+
	     "the central mound. The grass appears to have been trimmed, "+
	     "being of a constant height, and sufficiently short to "+
	     "be easily trod upon.\n");

    add_item(({"mound", "center"}),
	     "The center of the glade rises above the surrounding grass. "+
	     "Upon it grows a vast quantity of a leafy vine. Rising out "+
	     "of the center of the vines is a circle of white stones. "+
	     "There is something very strange about "+
	     "the way the vines flow around the circle, and over the "+
	     "ground.\n");

    add_item(({"walls", "living walls", "wood", "living wood",
		   "wooden walls", "wood walls", "roots", "entity",
		   "tree-like entity", "continuous entity", "tree",
		   "continous tree like entity"}),
	     "Twenty foot high wooden walls surround the glade. They are "+
	     "not ordinary walls, constructed of wooden boards. Rather, "+
	     "they seem to be a single, continuous, tree-like entity. "+
	     "The tops of roots are clearly visible at the base of the "+
	     "wall, and the occasional small leafy branch extrudes itself "+
	     "from it. The wood of the wall is a light chestnut color, "+
	     "but is not covered by any sort of bark. The wall is "+
	     "unblemished, displaying no evidence of rot, nor any other "+
	     "kind of damage. The archway via which you entered is the "+
	     "only apparent hole in the wall.\n");
		   
    add_item(({"archway", "gateway", "hole", "hole in the wall"}),
	     "An arch-shaped gateway represents the only break in the "+
	     "continous living wall which encircles this glade. Peering "+
	     "through the archway affords a distorted view "+
	     "of the thick woods which surround this place. The archway "+
	     "is barely large enough to allow the passage of a big man. "+
	     "You could enter the archway to leave this place.\n");
     
    add_item(({"view", "distorted view", "distortion", "shimmering",
		   "shimmering view"}),
	     "The view through the archway is oddly distorted, with the "+
	     "surrounding forest appearing to shimmer when viewed from "+
	     "here.\n");

    add_item(({"vines", "leafy vines", "peculiar vines"}),
	     vine_message);

    add_item(({"woods", "thick woods"}),
	     "The glade is located in the heart of a thick forest. The "+
	     "forest beyond the wooden wall is barely visible through "+
	     "the shimmering archway.\n");
    
    Code = randomize_alphabet(); //set up the code
    Riddle = random(7); //default riddle value, SHOULD end be changed when
                        //a player enters the room

    add_prop(ROOM_M_NO_TELEPORT, 1);
    add_prop(ROOM_M_NO_TELEPORT_TO, 1);

    /* added these on the off chance that someday spells will be able
       to check rooms for properties. */

    add_prop(MAGIC_AM_MAGIC, ({80, "faerie aura"}));
    add_prop(MAGIC_AM_ID_INFO, ({"A strong enchantment fills this grove.",
				  10, "The magic of the fay is clearly "+
				  "at work here.", 40, "Indeed, a strong "+
				  "personal connection has been made to "+
				  "this place by a powerful faerie.\n",
				  80}));

    clone_object(BLACKWALL_DIR + "obj/circle_of_stones")
      ->move(this_object());
}

/* Add_action function which allows a player to enter the 
   archway, IFF he can see it.
*/
int
enter_func(string arg)
{
    if (! parse_command(arg, ({}), "[the] 'archway' "))
    {
	//command failed;
	notify_fail("Enter what, the archway?\n");
	return 0;
    }

    //Command successful:
    
    write("You step through the shimmering archway.\n"); 
    this_player()->move_living("M", BLACKWALL_VALLEY1_DIR + "encrypt_outer",
			       1, 0);
    say(QCTNAME(this_player()) + " walks straight through the wooden "+
	"wall in front of you!\n");

    return 1;
}

void
init()
{
    ::init;
    add_action(encrypt_test, "encrypt");
    add_action(enter_func, "enter");
}


/* This function is called from encrypt_outer. Players may not gain
   access to this room when another player is already in it. This
   function returns true if there is a player present within
   the room so as to not allow others to enter. */

int
player_present()
{ 
    if (sizeof(FILTER_PLAYERS(all_inventory()))) 
    { 
	return 1;
	
    }

    return 0;
}

/* This function creates a mapping which will allow for the encryption
   of a string in the following manner:

   Each instance of one letter will be replaced by another, unique, letter.
   
   The index of the mapping is the alphabet, with each index being mapped
   to another letter, uniquely, but at random.
*/
   
mapping
randomize_alphabet()
{
    string* temp;
    mixed* random_array;
    mapping return_value;
    int i, ran;

    random_array = ({});
    temp = Alphabet;

    for (i = 0; i < sizeof(Alphabet); i++)
    {
	ran = random(sizeof(temp));
	random_array += ({temp[ran]});
	temp -= ({temp[ran]});	
    }
    
    Code = mkmapping(Alphabet, random_array);
    return mkmapping(Alphabet, random_array);
}
    
/* This function encryptes a string accoding to the code supplied in 
   a mapping.

   args: string s - the string to be encrypted
         mapping codemap - The index of this map should be the set of 
	                   characters to be encrypted, with the value
			   at the index representing what they are to be
			   encrypted to.

   returns: The string, now encrypted.

   NB: This function treats capital letters as lower case letters, and
   will capitalize the coded letter, if possible - it will probably
   throw an error if you map a capital letter to a non-alphabetic
   character. 
   
   Also, because of the inherent properties of mappings, mapping a
   character to zero will not work as expected - the character will remain
   unchanged.
*/  



string
encrypt(string s, mapping codemap)
{
    int i;
    int is_capital; //true if the original character was uppercase
    string* array_s;
    mixed* encrypted_array;
    encrypted_array = ({});

    // break s down into an array of single characters
    array_s = explode(s, "");

    /* loop through that array, checking each in turn, and adding an
       appropriate to anyother array, which will then be imploded into
       a string and returned */

    for (i = 0; i < sizeof(array_s); i++)
    { 
	is_capital = 0;

	/* First, if the character is a capital, we reduce it to lower
	   case, and set the is_capital flag. */

	if (array_s[i] == capitalize(array_s[i]))
	{
	    array_s[i] = lower_case(array_s[i]);
	    is_capital = 1;
	}
	 
       /* Now we check to see if the character exists as an index in the
	   the codemap. */

	if (!codemap[array_s[i]])
	
	{ 
	    /* it does not, we do not change it */
	    encrypted_array += ({array_s[i]});
	}
	
	else
	{
	    /* it does, so we change it according to the value of that
	       index recapitalizing  the character, if necessary */
	    
	    if (is_capital)
	    {		
		
	   	encrypted_array += ({capitalize(codemap[array_s[i]])});
	    }
	   
	    else
	    {
		encrypted_array += ({codemap[array_s[i]]});
	    }
	}
    }

    return implode(encrypted_array, "");
}

/* This sets up the riddle appropriate to the player (based upon name
   to random) which is encrypted in this room. This function is called
   as soon as a player enters the room. Note that unless this code is
   changed, a player will always have the same riddle to solve.

   This function is varargs for debugging purposes only. If the argument
   is specified the riddle will be set to that value.
*/
varargs void
set_riddle(int i)
{
    if (i)
    {
	Riddle = i;
	return;
    }
    
    Riddle = NAME_TO_RANDOM(this_interactive()->query_real_name(), 354234,
			    6); 
}

/* Used by the circle of stones which is in this room to determine what riddle
   is currently active, and hence, the solution.
*/
int
get_riddle()
{
    return Riddle;
}
    
string
vine_message()
{
    string return_value; //the string containing the encrypted riddle,
                         //which will be returned

     return_value = "You examine the vines closely. Perhaps it is a trick "+
	 "of your mind, but you could swear that the vines shape and form "+
	 "themselves into a sequence of letters as follows: \n\n";

    switch (Riddle)
    {

//the return value will Riddle, encrypted
    case 0:     
	return_value += encrypt(Riddle0, Code);
	break;
    case 1:
	return_value += encrypt(Riddle1, Code);
	break;
    case 2:
	return_value += encrypt(Riddle2, Code);
	break;
    case 3:
	return_value += encrypt(Riddle3, Code);
	break;
    case 4:
	return_value += encrypt(Riddle4, Code);
	break;
    case 5: return_value += encrypt(Riddle5, Code);
	
    default:
	return_value += encrypt(Riddle6, Code);
	break;
    }

    return return_value;
}
/* Test for the encryption algorithm, takes the argument, encryptes
   it at random, and then writes it to the screen. */

int
encrypt_test(string arg)
{
    mapping random_map;
    string return_value;

    random_map = randomize_alphabet();
    
    if (arg == "test")
    { 
	return_value = encrypt("two words\nanother two words", random_map);
    }
    
    else
    { 
	return_value = encrypt(arg, random_map);
    }
    
    write(return_value);
    return 1;
}







