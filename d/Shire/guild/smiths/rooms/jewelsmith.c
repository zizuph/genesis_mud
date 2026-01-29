/*
 * Palmer 13 Aug 2006
 *
 * The NPC here gives out a quest for an enchanted gem
 * that will be used by a Smith to create magic weapons/armours.
 * The gem is found on Tolfalas island.
 *
 */

#pragma save_binary;

inherit "/d/Shire/room";

#include "smiths.h"
#include "/d/Shire/common/defs.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include <cmdparse.h>

#define JEWELSMITH         (SMITHSDIR_NPC+"jewelsmith")

void reset_room(); 

object jewelsmith;

void
create_room() {
    set_short("Jewelsmith's workshop in Smiths Guild");
    set_long("This is the master jewelsmith's room. " +
        "This tidy room has a workbench with several iron boxes " +
        "bolted firmly in place.\n");
    add_item(({"boxes", "iron boxes"}), "The iron boxes are locked securely.\n");
    add_item("workbench", "The workbench has a clean surface.\n");
    add_exit(SMITHSDIR_ROOMS+"master_r","north",0);

    add_prop(ROOM_I_INSIDE,1);
    add_prop(ROOM_I_NO_ATTACK, 1);
    add_prop(OBJ_M_NO_ATTACK,1);
    add_prop(ROOM_I_NO_MAGIC_ATTACK, 1); 


    reset_room();
}

init() {
    ::init();
}


void
reset_room()
{
    if (!objectp(jewelsmith))
    {
        seteuid(getuid(TO));

        jewelsmith = clone_object(JEWELSMITH);
        jewelsmith->move_living("X", TO);
    }
    else if (ENV(jewelsmith) != TO)
    {
        jewelsmith->move_living("X", TO);
    }
}

