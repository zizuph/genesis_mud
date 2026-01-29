/*
 *
 * Base Tents for Karg Camp
 *
 * Ckrik June 1998.
 * Took out typo -- Amelia 7/27/98
 * 
 */
/* 2017-11-06 Malus: Adding ROOM_I_INSIDE */ 
#pragma strict_types
#pragma no_clone
#include <stdproperties.h>
inherit "/d/Earthsea/std/room";

public void create_tent() { }

public nomask void
create_earthsea_room()
{    
    set_short("A tent in the camp");
    set_long("A tent in the camp. You see the emblem of " +
        "the Kargad Empire on the sides of the tent. The " +
        "Karg warriors must be using this place as base camp " +
        "for their raids. You see many sleeping arrangements and " +
        "various armours and weapons lying on " +
        "the ground.\n");
    add_item((({"emblem", "emblems"})),
        "The emblems of the Kargad Empire.\n");
    add_item((({"arrangements", "ground"})),
        "The arrangements are currently unoccupied.\n");
    add_item((({"weapon", "weapons", "armour", "armours"})),
        "They kept in pretty good shape.\n");
    add_prop(ROOM_I_INSIDE, 1);
    create_tent();
}
