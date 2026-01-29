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
    set_place(TENT);
    set_long_desc("This is the inside of a typical village tent. Some kind " +
		  "of bed is along one side, and there is also a table and " +
		  "a few chests.");
    add_tent_exit("southeast",ROOM + "intersect2");
    add_item(({"side","table","chests","chest"}),"@@nothing_special@@");
    set_auto_reset(SHUTABLE,random(3),random(3));
}

string
nothing_special()
{
    return ("You see nothing special.\n");
}
