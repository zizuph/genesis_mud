#include "/d/Krynn/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <stdproperties.h>
#include "/d/Krynn/common/clock/clock.h"

inherit POOLBOTTOM_IN;

#define ORB  "/d/Krynn/guilds/wohs/objs/test_orb"

object orb;

void
reset_poolbottom_room()
{
    if(!objectp(orb))
    {
        orb = clone_object(ORB);
        orb->move(TO, 1);
    }
}

create_poolbottom_room()
{
    set_short("hallway within the school of High Magic");
    set_long("You stand in a hallway within the eastern wing of the school of " +
        "High Magic. A door to your north opens up to the residential quarters of " +
        "the students, while to your south is the school's storage chamber. A passageway " +
        "to your west leads to the great hall.\n");

    add_item(({"door"}),
       "To your north a door opens in to the residential area of the school.\n");

    add_item(({"passageway","west","western passageway","west passageway"}),
       "A passageway leads west to the great hall.\n");

    add_item(({"hall","great hall"}),"To your west down a passageway is the massive great hall of " +
       "Poolbottom, the school of High Magic. \n");

    add_item(({"walls","sandstone walls","grey sandstone walls","high sandstone walls",
               "blocks","sandstone blocks","grey sandstone blocks"}),
       "The school has been build from grey sandstone blocks mined from quarries " +
       "far to the south near Pax Tharkas. The workmanship of the walls is seamless, " +
       "most likely done by a master dwarven mason.\n");

    clone_object(EPATH + "/obj/sohm_board")->move(TO);

    add_exit(ROOM + "ng_hall","west",0);
    add_exit(ROOM + "start","north",0);
    add_exit(ROOM + "storage","south",0);

    reset_poolbottom_room();
}