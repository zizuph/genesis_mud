/* Started by Gorret,
 * continued by Erine,
 * finished by Aridor
 * 07/95 
 */

#include "../local.h"
inherit INBASE_ROOM;
#include RND_MEET

void
create_que_shu_room()
{
    set_place(HOUSE);
    set_long_desc("This is the best built house in the village. A special exit leads " +
		  "south directly into another house, while the main entrance is to the " +
		  "east.");

    add_exit(ROOM + "vill1","east");
    add_exit(ROOM + "hall","south");
    add_item(({"side","table","chests","chest"}),"@@nothing_special@@");
    set_auto_reset(SHUTABLECHIEFTAIN);
}

string
nothing_special()
{
    return ("You see nothing special.\n");
}
