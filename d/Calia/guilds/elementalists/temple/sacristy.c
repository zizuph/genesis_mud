
/*
 * sacristy.c
 *
 * Sacristy for the Elemental 
 * 
 *
 * Copyright (C): Jaacar (Mike Phipps), Jul 24, 2003
 *
 */
 
#pragma strict_types

#include "defs.h"

inherit TEMPLE_ROOM_BASE;

object cabinet;

void 
reset_room() 
{
    if (!(cabinet)) 
    {
        cabinet=clone_object(ELEMENTALIST_OBJS+"cabinet");
        cabinet->move(TO);
    }

}

public void
create_temple_room()
{
    set_short("Sacristy");
    set_long("You are in a small chamber known as the sacristy. This "+
        "chamber holds all of the ceremonial and holy items for use "+
        "in ceremonies. A small cabinet sits against the southern "+
        "wall.\n\n");

    add_item(({"wall","walls"}),"The walls of this room are painted "+
        "bright gold in colour. Against the south wall there is a "+
        "cabinet. In the northern wall is a small golden door.\n");
    add_item("floor", "The floor and ceiling are both constructed with "+
      "a grey stone and then smoothed and polished afterwards. The floor "+
      "is quite comfortable to walk on.\n");
    add_item("ceiling", "The floor and ceiling are both constructed with "+
      "a grey stone and then smoothed and polished afterwards.\n");

    add_exit(ELEMENTALIST_TEMPLE + "middle10", "east", "@@cannot_enter_middle_circle", 1, "@@cannot_see_middle_circle");
    add_exit(ELEMENTALIST_TEMPLE+"outer13a","south",0,1);
    reset_room();
}

/*
 * Function: enter_inv
 * Description: block unwanted people from entering.
 */
void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    // Don't allow Temple banned people from entering.
    if (GUILD_MANAGER->query_is_punish_resource_banned(ob))
    {
    	ob->move(from);
        ob->catch_msg("You've been banned from entering the "+
            "Temple Sacristy!\n");
        return;
    }
}
