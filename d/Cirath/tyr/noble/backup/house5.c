/* house4.c: Rich house 4: Serpine, 04-22-95 */

inherit "/std/room";
#include "defs.h"
#include "/d/Cirath/common/mobber.h"

void
reset_room()
{
    bring_room_mob("noble", TYR_NPC+"rich_hmn.c", 1, 1);
    bring_room_mob("slave", TYR_NPC+"slav_hmn.c", 2);
}

void
create_room()
{
    set_short("lavish townhouse");
    set_long("No expense has been spared on this townhouse. The finest "+
             "silks drape the furniture, and soft cushions are scattered "+
             "throughout the room. Water-hungry plants grace every "+
             "corner, and artwork covers every wall. This one building "+
             "represents enough resources to rebuild half the warrens.\n");

    add_item(({"silks", "finest silks", "silk"}), "Silk this smooth only "+
             "comes from the dreaded flying silk-worms of Athas, or "+
             "rather, from the cocoons holding their victims.\n");

    add_item("furniture", "Made from the fine wood found only in the "+
             "Emerald Triangle.\n");

    add_item(({"plants", "plant"}), "Pretty, yet wasteful.\n");

    add_item(({"cushion", "soft cushion", "cushions", "soft cushions"}),
             "So soft they must have come from the feathers of a newly "+
             "hatched Roc. They only have a three meter wingspan at that "+
             "early age.\n");

    INSIDE

    add_exit(TYR_NOBLE+"rd_hr_04.c", "southwest", 0, 1);
    reset_room();
}
