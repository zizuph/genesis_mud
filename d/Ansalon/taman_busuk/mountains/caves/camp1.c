#include "../local.h"
#include "/d/Ansalon/common/defs.h"

#include <stdproperties.h>

inherit CAVE_BASE;

object reb1,reb2,reb3,reb4;

void
reset_cave_room()
{
    if (!objectp(reb1))
        reb1 = clone_npc(MNPC + "rebel");
    if (!objectp(reb2))
        reb2 = clone_npc(MNPC + "rebel");
    if (!objectp(reb3))
        reb3 = clone_npc(MNPC + "rebel");
    if (!objectp(reb4))
        reb4 = clone_npc(MNPC + "rebel");
}

void
create_cave_room()
{
    set_short("a camp in a large cave");
    set_long("You are in a large cavern under the Taman Busuk " +
    "mountains. There is some sort of a camp set here, evident " +
    "by the various equipment stacked against the walls, and " +
    "bedrolls spread on the ground. The cave is lit and warmed " +
    "by scattered campfires. " +
    "The camp is spread out south of here, while a narrow " +
    "passage leads northeast.\n");

    add_cave_items();
    add_camp_items();

    add_item(({"floor", "uneven floor"}),
    "The cave floor has been cleared of loose rocks and rubble.\n");

    add_item(({"passage","narrow passage"}),
    "The narrow passage leads northeast into darkness.\n");

    add_prop(ROOM_I_LIGHT, 1);

    add_exit(CAVE_DIR + "camp2", "southwest");
    add_exit(CAVE_DIR + "camp3", "south");
    add_exit(CAVE_DIR + "camp4", "southeast");
    add_exit(CAVE_DIR + "cave8", "northeast");
}

