/* bonesmth: Workshop of the Tyr weapon/bonesmith. */

inherit "/std/room";
#include "defs.h"
#include "/d/Cirath/common/mobber.h"

void
reset_room()
{
/*
    bring_room_mob("tentavvar", TYR_NPCS+"bonecrft.c", 1);
*/
}

void create_room()
{
    set_short("bone smithy");
    set_long("The air is filled with so many particles that breathing is "+
             "nigh impossible. A hundred forgotten fragments of weapons "+
             "litter the floor, competing with the forge, anvil, and racks "+
             "of tools. This can be only one place: The workshop of Tyr's "+
             "resident bonesmith Tentavvar. Cleaner air lies north on the "+
             "the street and west in the weapon merchant's.\n");

    add_item(({"floor", "fragments", "fragments", "floor", "forge", "anvil",
               "rack", "racks", "tool", "tools"}),
             "Other then the thick coat of debris, not really of note.\n");

    INSIDE

    add_exit(TZ_CARAVAN+"rd_cw_04.c", "north", 0, 1);
    add_exit(TZ_CARAVAN+"weapmrch.c", "west", 0, 1);

    reset_room();
}
