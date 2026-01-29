/*
 * Filename:		village.c
 * Description: 	Area around Newports, Abanasinia
 *
 * Coded by:		Aridor, 03/95
 *
 * Revision history:
 * Oct 25 1999 by Boron: Added warfare support
 * Oct 14 2014 by Mortis: Updated sign.
 */

#include "local.h"

inherit BASE_FILE;

#define RAT       LIV + "rat"
#define LEATHER   OBJ + "leather"
#define PLANK     OBJ + "plank"

int rats2 = 0;
int rats4 = 0;

/* Prototypes */
public int read_sign();

void
reset_plains_room()
{
    rats2 = 0;
    rats4 = 0;
}

void
create_newport_room()
{
    set_short("The village of Newports");
    set_long("You are in the middle of the village Newports. There is nothing " +
	     "special around here, you count five cottages around you. The houses " +
	     "have apparently been built on the shore of a huge body of water. " +
	     "A soft salty breeze blows into your face and a few seagulls fly " +
	     "overhead. The dirty village road you stand on leads west to a " +
	     "crossroads. Piers extend out into the water to the " +
	     "east, southeast, and south. A sign has been placed here.\n");

    add_item("sign","It has readable words on it.\n");
    add_cmd_item(({"sign","words"}),"read","@@read_sign@@");

    add_item(({"village road","road"}),
	     "The road you stand on is dusty and bumpy. It leads west out of " +
	     "the village and east to the pier.\n");
    add_search(({"village road","road"}),3,"/std/coins",-3);
    add_item(({"pier","piers"}),"It would be better if you visited.\n");
    add_item(({"sea","water","newsea","ocean"}),"It's east of you.\n");
    add_item("village","There are five houses about, 3 of them on the north side " +
	     "of the road and two on the south. Also to the village belongs the " +
	     "village road, which you are standing on right now, and the pier " +
	     "out onto Newsea to the east.\n");
    add_item(({"house","houses","cottage","cottages"}),
	     "Which house do you want to look at? There are five houses around.\n");
    add_search(({"house","houses","cottage","cottages"}),-4,
	       "Search which house? There are five houses around.\n");
    add_cmd_item(({"house","houses","cottage","cottages"}),"enter",
		 "There are five houses around, which one do you want to enter?\n");
    add_item(({"house 1","first house"}),
	     "This house is northwest from you and it looks a little shabby.\n");
    add_cmd_item(({"house 1","first house"}),"enter",
		 "You find nothing of interest there.\n");
    add_item(({"house 2","second house"}),
	     "This house north of you looks like it's the oldest of all, and " +
	     "apparently no one lives there anymore.\n");
    add_search(({"house 2","second house"}),4,"find_rats",1);
    add_cmd_item(({"house 2","second house"}),"enter",
		 "There is no door left anymore and you hear some ominous " +
		 "sounds coming from the house.\n");
    add_item(({"house 3","third house"}),
	     "The house northeast from you is closest to the water. You can see " +
	     "a sign above the door saying 'Delivery Office'.\n");
    add_cmd_item(({"house 3","third house"}),"enter",
		 "@@enter_office@@");
    add_item(({"house 4","fourth house"}),
	     "The fourth house in the village is southwest of you. It's more " +
	     "like a shed or a barn where things are stored.\n");
    add_search(({"house 4","fourth house"}),5,"find_rats",1);
    add_cmd_item(({"house 4","fourth house"}),"enter",
		 "There is no door left anymore and you hear some ominous " +
		 "sounds coming from the house.\n");
    add_item(({"house 5","fifth house"}),
	     "The house south of you is the newest of the village, it doesn't " +
	     "look quite as shabby as the rest of them, but other than that you " +
	     "cannot see anything special.\n");
    add_cmd_item(({"house 5","fifth house"}),"enter",
		 "You find nothing of interest there.\n");
    add_item("breeze","A soft breeze coming in from the sea.\n");
    add_item("seagulls","They are having fun flying about in the breeze.\n");

    add_exit(TDIR + "road1","west",0,3);
    add_exit(PIER,"east");
    add_exit(PIER3,"south");
    add_exit(PIER2,"southeast");
    add_exit(TDIR + "office","northeast");
}


string
find_rats(object who, string what)
{
    int i;
    int house = (what == "house 2" || what == "second house");
    /* house is:  1 if 'house2', 0 if 'house4' */
    /*who->catch_msg("House: " + house);*/
    if ((house && rats2 > 1) || (!house && rats4 > 1))
      return "Your search reveals nothing special.\n";
    if (house)
      rats2++;
    else
      rats4++;
    if ((house && rats2 == 1) || (!house && rats4 == 1))
      {
	  if (random(6))
	    {
		clone_object(LEATHER)->move(TO,1);
		return "You find an old tattered leather armour.\n";
	    }
	  clone_object(PLANK)->move(TO,1);
	  return "You find a wooden club.\n";
      }
    for(i=-1;i<random(4);i++)
      clone_object(RAT)->move(TO,1);
    return "You look intently through the house and scare up a pack of rats!\n";
}

string
enter_office()
{
    TP->command("northeast");
    return "";
}

public int
read_sign()
{
	say(capitalize(TP->query_the_name()) + " studies the sign by the road.\n");
	write("The sign reads...\n");
	cat(TDIR + "village_sign.txt", 1, 55);

	return 1;
}

