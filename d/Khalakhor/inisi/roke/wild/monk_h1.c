/*
 * monk_h1.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/room.c";

#include "defs.h"

void
create_room()
{
    set_short("a large hall");

/*
    set_long("You are in a large hall on the second floor. The walls are " +
             "covered by great paintings with scenes from different wars " +
             "in the history of Nyreese. To your south you can see a " +
             "courtroom, to the west there is a small dining room. The " +
             "exit to the north are guarded by two sturdy monks.\n");
*/
    set_long("You are at the top of the stairs, in a large hall on the " +
             "second floor.\n" +
             "A cultural treasure! The walls are covered with great, dusty " +
             "paintings with scenes from different wars in the history of " +
             "Nyreese. To the south you can see another dusty room, and to " +
             "the west is a small room.\n");

/*
    add_prop(ROOM_M_NO_ATTACK,
             "You can not do that while on Sacred ground.\n");
    add_item(({"monk", "monks"}), "The monks are big and hairy.\n");
*/
/*
    add_item(({"painting","paintings"}),"You can see five paintings here.\n"+
             "You realize that it must be the five councilmembers.\n");
*/
    add_item(({"painting", "paintings"}),
             "You can see five paintings here. " +
             "Each seems to be showing an individual performing some " +
             "mighty deed. Obviously those five were important people " +
             "for those who once lived here.\n");

    INSIDE;
    add_exit("monk_entr", "down");
    add_exit("monk_h2", "north");
    add_exit("monk_council", "south");
    add_exit("monk_dinner", "west");
    add_exit("monk_discuss", "east");
}
