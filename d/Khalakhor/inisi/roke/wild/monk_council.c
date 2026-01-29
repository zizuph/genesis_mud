/*
 * monk_council.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/room.c";

#include "defs.h"
#include <macros.h>

void
create_room()
{
/*    set_short("kaheda courtroom");*/
    set_short("impressive room");

/*
    set_long("This is the Kaheda court. Here the council decides about important\n" +
             "matters concerning the guild. The Kaheda council has the power to ban\n" +
             "any member of the guild. The council is also responsible for giving\n" +
             "honorary titles to famous members.\n" +
             "There is a half-circular table at the far end of the room and there are\n" +
             "five huge chairs behind it. There is also a simple table with a small\n" +
             "chair in the middle of the room.\n" +
             "Behind the largest chair you can see a small door leading south\n" +
             "Above the door is an expensive-looking goldframed plaque.\n");
*/
    set_long("This is a large, impressive room whose purpose is " +
             "long-forgotten. A small doorway leads south.\n");

/*
    add_prop(ROOM_M_NO_ATTACK,
             "You can not do that while on Sacred ground.\n");
    add_item("table",
             "Hmm. There are actually two tables here but none of them" +
             "looks interesting.\n");
    add_item("door", "There is a small sign on the door.\n");
    add_item("sign", "The sign says: Councilmembers ONLY !\n");
    add_cmd_item("sign", "read", "The sign says: Councilmembers ONLY !\n");
    add_item("chair", "There is no fun in looking at a chair.\n");
    add_item("chairs", "There are six of them. Five large and one small.\n");
    add_item("plaque", "@@boardfun");
*/
    INSIDE;

    add_exit("monk_h1", "north");
    add_exit("monk_secret", "south");
}

#if 0
string
boardfun()
{
    string str;
    int i;
    mixed s;

    str = "The Honorable Councilmembers are:\n";
    /*
    seteuid(getuid(TO));

    s = (SECRET)->query_council_list(1);

    for (i = 0; i < sizeof(s); i++)
        str += capitalize(s[i]) + "\n";
    */
    return str;
}
#endif
