

/* room2.c
   Mort 911004 */

inherit "/std/room";
#include <macros.h>
#define PATH "/d/Terel/mountains/"
#define TP this_player

/*
 * Function name: create_room()
 * Description  : Create the room.
 * In this function, we declare everything that should be fixed
 * when the room is started, and not changed in resets.
 */

create_room() {

    set_short("Great Chasm");
    set_long("Here in the midst of the icy mountains is a great\n" +
             "chasm that spreads out to the east, making travel\n" +
	     "impossible except to the west.\n");
add_my_desc("A huge snowdrift blocks passage southward.\n");
add_item("A massive icy chasm, it is deep and perilous.\n");
add_item(({"drift", "snowdrift"}),
   "A mass of ice and snow built up by the wind. It looks as though\n"
  + "it is partly a rock formation over which everything has been\n"
   + "built around. There is a small hole in the drift.\n");
add_item("hole", "It is a hole melted in the snowdrift, it is all\n"
  + "iced over. It seems to be some kind of hollow.\n");
       add_cmd_item("hole","enter","@@fall_func@@");     
 
add_exit("/d/Terel/mountains/ice2", "west",0);
}
string
fall_func()
{
        say(QCTNAME(TP())+" crawls into the hole.\n"
        + "You hear a muffled yell, then silence..\n");
        write(break_string("You crawl into the hole, only to realize rather "
        + "belatedly that what you thought was a hollow is in fact a near-"
        + "vertical tunnel! You shoot down for what seems like ages, and "
        + "attain considerable speed before being deposited (painfully) on "
        + "an icy surface..\n",70));
        TP()->move_living("into the hole",PATH+"chasm1");
	return "";
}

/*
 * Function name:
 * Description  :
 */

