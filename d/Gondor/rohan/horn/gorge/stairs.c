inherit "/d/Gondor/rohan/horn/helmsdeep.c";

#include "/d/Gondor/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/d/Gondor/rohan/horn/hd_defs.h"

object sentinel;

/* Prototypes */
void reset_room();

void create_helmsdeep_room()
{
    object door;

    set_short_desc("Stairs to the rear-gate of the Hornburg");
    set_extra_long("Broad stairs, well-used, rise to a gate in the outer "+
    "wall of the keep.  Below the stairs, a path leads further up the gorge "+
    "to the south. ");
    KEEP;
    PATH;
    GORGE;
    CLIFFS;
    MOUNTAINS;
    add_item("wall",BS("The wall was made long ago by the sea-kings "+
    "of Gondor.\n"));
    add_item(({"stairs", "steps"}) ,BSN(
    "The steps are broad enough for a horse to be led down from the gate."));

    add_exit(ROH_DIR + "horn/gorge/ifield","south",0);

    door = clone_object(ROH_DIR + "horn/doors/rear_gate_in");
    door->move(TO);

    reset_room();
}

void reset_room()
{
    sentinel = clone_npc(sentinel, (ROH_DIR + "horn/npc/g_sentinel"));
}
