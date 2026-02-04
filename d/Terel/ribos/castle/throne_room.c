/* This comment tells emacs to use c++-mode  -*- C++ -*- */

/*
 * throne_room.c
 *
 * Vader
 * Recoded by Sorgum 950602
 */

#include "/d/Terel/include/Terel.h"
#include "local.h"
inherit STDROOM;


public int do_throne_sit(string str);
public int do_bench_sit(string str);
int do_go_curtain(string str); 


/*
 * Function name: query_object_list
 * Description:   return list of objects to clone at each reset.
 */
public string*
query_object_list()
{
    return ({CASTLE_DIR + "monster/okayguard",
	     CASTLE_DIR + "monster/weakguard"});		 
}

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    ::create_room();
    set_short("Castle throne room");

    set_long("You are in a marvelous hall.  The walls are made of " +
	     "marble, and there are several columns that support " +
	     "the ceiling, which you now notice is covered in " +
	     "art work.  There are benches all around where people sit " +
	     "to hear the king.  At the back of this room is a " +
	     "raised platform where people who wish to address " + 
	     "the king kneel.  In the middle of the room, on the " +
	     "floor, is a large silver colored star that is " +
	     "outlined in gold.  There is a curtain at the back " +
	     "of the room, directly behind the kings throne.\n");

    set_dircmd("curtain");

    add_item(({"curtain", "curtains"}),
	     "It is a bright red color, and covers the entire rear wall.\n");

    add_item(({"platform"}),
	     "Just a simple raised platform, like a stage.\n");

    add_item(({"benches"}),
	     "These benches, compared to the rest of the " +
	     "room, are simple.  But\nput them anywhere else, " +
	     "and they would be the most elegant benches in the " +
	     "land.  You can sit in one.\n");

    add_item(({"ceiling", "art", "art work", "artwork"}),
	     "The ceiling is filled with murals depicting a slightly " +
	     "sensationalized way\nof life in this land.\n");

    add_item(({"wall", "walls", "marble walls"}),
	     "The walls are made of a dark colored marble, " +
	     "almost black, but more\nclose to a dark grey.\n");

    add_item(({"throne", "kings throne"}),
	     "This throne is a marvelous place for the king to sit.  " +
	     "It is wide, soft, and perfectly fitted to the kings " +
	     "physique.\n");

    add_item(({"star", "silver star"}),
	     "It is well known that the Star is the Universal " +
	     "symbol of Wisdom.\n" + 
	     "It has no beginning, and no end.  Its points form " +
	     "a perfect circle.\n");

    INSIDE;

    add_exit(CASTLE_DIR + "court", "south", 0);

    reset_room();

}

/*
 * Function name: init
 * Description:   Add the 'command items' of this object. 
 */
public void
init()
{
   ::init();
   add_action(do_bench_sit,  "sit");
   add_action(do_bench_sit,  "sit on bench");
   add_action(do_bench_sit,  "sit in bench");
   add_action(do_throne_sit, "sit on throne");
   add_action(do_throne_sit, "sit in throne");
   add_action(do_go_curtain, "enter");
   add_action(do_go_curtain, "move");    
}

/*
 * Function name: do_bench_sit
 * Description:   Handle the enter action
 * Returns:       1/0
 */
public int
do_bench_sit(string str)
{
     write("You slide onto the bench, suddenly remembering that no matter " +
	   "how elegant the bench, they are all still uncomfortable.  " +
	   "You wait around for a while, wondering if the king will make " +
	   "an address today.\n" + 
	   "You stand up, not willing to wait on the king any more.\n");
     return 1;
}

/*
 * Function name: do_throne_sit
 * Description:   Handle the enter action
 * Returns:       1/0
 */
public int
do_throne_sit(string str)
{
   write("As you try to sit on the throne, a large gnome appears.\n" +
	 "The large gnome says: You should know better than to sit on the " +
	 "throne\nof the king!!!  GET OUT!!!!\n" +
	 "The large gnome gives you a swift kick, sending you flying " +
	 "across\nthe room.\n" +
	 "The gnome vanishes, as suddenly as he appeared.\n");
   return 1;
}

/*
 * Function name: do_go_curtain
 * Description:   Handle the enter action
 * Returns:       1/0
 */
public int
do_go_curtain(string str)
{
    if(!str || (str != "curtain")) {
	NF("Enter what?\n");
	return 0;
    }
    
    write("You enter the curtain.  There is a hallway behind it.\n");
    TP->move_living("through the curtain", CASTLE_DIR + "m_hall1_1");
    return 1;
}
 
