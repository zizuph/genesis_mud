
/*
 * Written by Quis for the Goblin Start Area 920516
 */

#pragma save_binary

inherit "/std/room";

#include "/sys/stdproperties.h"
#include "../goblins.h"

void
create_room()
{
    object ob;
    ::create_room();

    change_prop(ROOM_I_INSIDE,1);
    change_prop(ROOM_I_LIGHT,1);
    add_prop(OBJ_S_WIZINFO, "@@wizinfo");

    set_short("Living quarters of the goblin caverns.");
    set_long(BSNN(
        "This chamber is obviously being used as the cavern armoury. " +
        "You see piles of spears and shields lining the walls." 
      ));

    add_exit(GOBLIN_CAVERN_DIR + "tunnel3", "northeast", 0, 0);

    add_item(({"spears","shields","armour", "weapons","equipment"}),
        "These are very bad.\n");
}

string 
wizinfo() 
{
    return (BSN("This location gives out a free shield and spear to any " + 
        "goblin that wants one.  The spear and shield are quite horrid " + 
        "and the goblin may well lose it to wear.  The idea here is to " + 
        "replace the \"Oh look, a sword lying on the ground!\" with " +
        "something a bit more logical.  Only one set of equipment per " +
        "reset is allowed, per reboot per player."
        ));
}