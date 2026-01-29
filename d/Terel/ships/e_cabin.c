/* This comment tells emacs to use c++-mode -*- C++ -*- */

#include "/d/Terel/include/Terel.h"
inherit "/d/Genesis/ship/cabin";

/*
 * Function name: create_cabin
 * Description  : Create the ship cabin
 */
public void
create_cabin()
{
    set_short("The captain's cabin");
    set_long("This cabin has a rather spartan look.  This ship is new, " +
	     "and its " +
	     "captain hasn't had much time to decorate his cabin.  " +
	     "There is a fine antique desk in one corner, on top of " +
	     "which is the Captain's Log.  The windows look out onto the " +
	     "ocean, making the faint of heart seasick at times.  " +
	     "There is also small amounts of naval paraphenalia that you " +
	     "would expect to see in a Captains cabin.\n");
    
    add_item(({"log", "captains log"}), 
	     "This is a fine, leather-bound book that the captain uses to " +
	     "keep a history of this ships life.\n");
    
    add_item("desk", "This fine teak desk must be worth a fortune; too " +
	     "bad it's bolted to the floor!\n");
    
    add_item(({"maps", "map", "chart", "charts"}), "Most of the maps and " +
	     "charts seem to depict the sea lanes around Calathin.");
    
    add_item(({"sextant", "compass"}), "It would hardly be the Captain's " +
	     "cabin without a sextant and compass, would it?");
    
    add_item("window",
	     "Through the small circular port you see the ceaseless march " +
	     "of green waves.\n");
    
    add_exit(SHIP_DIR + "e_deck", "fore", 0);
}

/*
 * Function name: init
 * Description:   Add the 'command items' of this object. 
 */
public void
init()
{
    ::init();
    add_action("read", "read");
}

/*
 * Function name: read
 * Description:   Handle the read action
 * Returns:       1/0
 */ 
public int
read(string str)
{
    if (str != "book") {
	NF("Read what?\n");
	return 0;
    }
    else {
	write("Captains Log, Calathin Expeditioner:\n" +
       "\n" +
       "Left Calathin drydock after completion of this vessel.\n" +
       "Trial run was taken from Calathin to Sparkle, a known and safe " +
       "route.\n" +
       "We then started routine runs from Calathin to the elven\n" +
       "village.  Personally, I don't care much for elves, but as\n" +
       "long as they pay for their tickets, I can hold back the urge\n" +
       "to rip their little ears off.\n" +
       "\nFive trips later:  One little elf in particular was making\n" +
       "nuisance of himself.  He kept asking how long it would be before\n" +
       "we would get there.  He asked OVER and OVER again, and I " +
       "finally blew\n" +
       "my top.  I threw him overboard.  Im not sorry for what I have\n" +
       "done, rather I am proud.  If any elf bothers me, I would\n" +
       "always be proud to rip it apart.\n");
       return 1;
    }
}
