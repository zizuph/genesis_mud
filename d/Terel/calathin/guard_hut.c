/*
 * Guard hut for the gate keeper of Calathin.
 * Coded by Shinto 111599
 */

#include "/d/Terel/include/Terel.h"
inherit STDROOM;

#include <stdproperties.h>
#include <macros.h>

query_object_list()
{
    return (({CALATHIN_DIR + "npc/gate_keeper"}));

}

public void
create_room()
{
    set_short("Guard house outside the north gate of Calathin");
    set_long("A small wooden structure used by the Sergeant of the "+
            "Calathin Guard. Two windows face out to the road, one to "+
             "each side of the doorway. A desk sits on the opposite side "+
            "of the room, facing the door.\n");
    add_item(({"window", "windows"}), "The windows view the road outside.\n");
    add_item("desk", "The Sergeant's desk has some papers on it. It's a "+
               "strong wooden desk.\n");

    add_exit(CALATHIN_DIR + "north_gate", "out", 0);
    reset_room();

}
