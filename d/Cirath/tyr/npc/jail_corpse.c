/*
* Created by: Luther
* Date: August 2001
*
* File: /d/Cirath/tyr/npc/jail_corpse.c
* Comments: Corpse in cell2_12.c
*/

inherit "/std/object";
#include "defs.h"

void
create_object()
{
    if (!IS_CLONE) return;
    set_name("corpse");
    add_name("_corpse_");
    add_adj("skinless");
    add_adj("elf");
    add_prop(OBJ_I_NO_GET, "The skeleton is chained to the wall and doesn't want to leave!\n");
    add_prop(OBJ_M_NO_STEAL, "The corpse is chained to the wall!\n");
    set_long("This skinless, creepy looking corpse looks alive! Judging from the "+
             "position it is in, it must have died in extreme pain. Its skeletal "+
             "hands still grasp the chains around its wrist. Its feet look like they "+
             "are kicking at something, you can't help but think this place is "+
             "harsh.\n");
}
