inherit "/d/Rhovanion/common/erebor/caves.c";
inherit "/lib/pub";

#include <stdproperties.h>
#include <macros.h>
#include <money.h>
#include "/d/Rhovanion/defs.h"
#define CAVE_DIR ERE_DIR + "ere1/"

create_cave()
{
    
  set_rock_type("cold grey granite");
  set_cave_name("the Lonely Mountain");
  set_region("northern");
  set_cave("Erebor");
  set_cave_type(6);
  set_long("Just as you enter the tavern every person turns towards you and "
     + "the room is filled with silence. As the other guests see that you "
     + "are just another traveller who seeks company and some nice food, "
     + "they turn theire back on you and starts talking loudly with eachother "
     + "again. As you look around the tavern you see that it is about half"
     + "filled with visitors sitting at the wooden tables, drinking ale and "
     + "eating. Standing against the east wall you see a long oak bar, behind "
     + "the bar a fat human is looking interested at you. ");
 
    add_item("bar", "Its a greasy bar, really disgusting.\n");
    add_item("menu", "It has some readable words on it.\n");
    add_item("chairs",
	"They are made out dark wood, obviously from outside Lonely Mountain.\n"); 
    add_item("tables", "They are speckled with spots of puke and beer.\n");
    add_cmd_item("menu", "read", "@@read");

    add_drink( ({ "beer", "beers", "small", "small beer" }),
	"beer", "small", 100, 4, 12, 0, 0,
	"It's a small but refreshing beer.\n", 0);
    
    add_drink( ({ "beer", "beers", "large", "large beer" }),
	"beer", "large", 200, 50, 36, 0, 0,
	"It's a large strong dwarven beer.\n", 0);
    
    add_drink( ({ "wine", "wines", "sweet", "sweet wine" }),
	"wine", "sweet", 200, 20, 72, 0, 0,
	"It has a deep red colour and smells wonderful.\n", 0);
    
    add_food( ({ "potato", "potato soup", "soup", "soups" }),
	"soup", "potato", 65, 80, "plate of potato soup", 
	"plates of potato soup",
	"It doesn't smell very good at all.\n", 0);
    
    add_food( ({ "mushrooms", "yucky", "plate of yucky mushrooms", 
        "plate", "plates" }),
	"mushrooms", "yucky", 110, 110, "plate of yucky mushrooms",
	"plates of yucky mushrooms",
	"They look extremely disgusting.\n", 0);

  
  add_exit(CAVE_DIR + "lm1c28","west",0,1);
}

/*
 * Function name: init
 * Description:   Initalize the pub actions
 */
void
init()
{
    ::init(); /* Since it's a room this must be done. */

    init_pub();
}

/*
 * Function name: read
 * Description:   Read the menu
 * Arguments:     str - hopefully the menu
 */
int
read(string str)
{
    write(" " 
        + "\n" 
	+ "   Small beer                 12 cc\n" 
	+ "   A Large Dwarven beer       36 cc\n"
	+ "   Some really sweet wine     72 cc\n" 
	+ "   Potato soup                80 cc\n" 
	+ "   Plate of yucky mushrooms   210 cc\n\n" 
	+ "Try 'buy beer with gold' if you wanna specify what to\n" 
	+ "pay with, or 'test buy beer' to see what would happen\n" 
	+ "if you typed 'buy beer'. 'buy 10 beer' would get you\n" 
	+ "ten beers from the bar, but it takes a little while to\n" 
	+ "give them all to you.\n");
    return 1;
}
