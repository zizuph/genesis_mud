/*
 * inner_entry.c
 * This is a temorary file, it will change later.
 * Written by Trenix@Genesis, 8-17-93
 *
 */

inherit "/std/room";
#include <stdproperties.h>

void
create_room()
{
    set_short("Small room in the obsidian caves");
    set_long(break_string("This is a small area in the obsidian "+
             "caves. The darkness in the stone seems to go on "+
             "forever. Strangly enough you have no difficulty "+
             "viewing your environment since you see no light "+
             "sources.\n",50));
    add_prop(ROOM_I_LIGHT,5);
/*    add_prop(OBJ_I_LIGHT,5);  /* Wasn't sure which was right. */ ROOM */
    add_prop(ROOM_I_IS,1);
    add_prop(ROOM_I_INSIDE,1);
}

init()
{
    ::init();
}

/* EOF */
