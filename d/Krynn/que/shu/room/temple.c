/* Started by Gorret,
 * continued by Erine,
 * finished by Aridor
 * 03/95 
 */

#include "../local.h"
inherit INBASE_ROOM;
#include RND_MEET


void
create_que_shu_room()
{
    set_place(TEMPLE);
    set_long_desc("You are inside a temple. Apparently this temple is " +
		  "dedicated to the ancestors of the village folk. " +
		  "There is an altar at the east wall of the room, otherwise, " +
		  "the temple is empty.");

    add_exit(ROOM + "intersect1","southwest");
    add_exit(ROOM + "vill1","northwest");
    add_item(({"altar"}),"@@nothing_special@@");
    set_auto_reset(SHUTABLE);
}

string
nothing_special()
{
    return ("You see nothing special.\n");
}
