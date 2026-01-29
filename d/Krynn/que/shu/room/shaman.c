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
    set_place(SHAMANHUT);
    set_long_desc("");

    add_tent_exit("west",ROOM + "vill1");
    add_item(({"side","table","chests","chest"}),"@@nothing_special@@");
    set_auto_reset(SHUTABLESHAMAN);
}

string
nothing_special()
{
    return ("You see nothing special.\n");
}
