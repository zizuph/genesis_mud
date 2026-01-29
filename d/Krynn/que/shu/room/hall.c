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
    set_place(HALL);
    set_long_desc("There is plenty of room for gatherings of the entire tribe, usually " +
		  "there are always a few people around discussing the current state " +
		  "of affairs. To the north there is a direct connection to another house, " +
		  "while the main entrance is to the southeast. The floor is covered with " +
		  "a carpet, otherwise, the room is completely bare.");

    add_exit(ROOM + "chief","north");
    add_exit(ROOM + "intersect1","southeast");
    add_item(({"side","table","chests","chest"}),"@@nothing_special@@");
    set_auto_reset(SHUTABLE,random(5)+2,random(3));
}

string
nothing_special()
{
    return ("You see nothing special.\n");
}
