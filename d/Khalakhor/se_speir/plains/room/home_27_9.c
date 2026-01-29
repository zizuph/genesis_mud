/*
 * the shepherd's home
 *
 * Zima  - May 18, 1998
 */
#pragma strict_types
#include <stdproperties.h>
#include "plains.h"
 
inherit "/d/Khalakhor/std/room";
#include "/d/Khalakhor/sys/defs.h"
#include <macros.h>
 
string  *npc_file=(({"shep_wife","shep_kid","shep_kid"}));
object  *npc=allocate(sizeof(npc_file));
 
 
public void check_npc()
{
   int i;
   for (i=0; i<sizeof(npc_file); i++)
      if (!objectp(npc[i]))
         {
         npc[i] = clone_object(NPC2+npc_file[i]);
         npc[i]->arm_me();
         npc[i]->move(TO);
         tell_room(TO,QCTNAME(npc[i])+" enters from the yard.\n");
         }
}
 
public void reset_room()
{
   check_npc();
}
 
 
public void
create_khalakhor_room()
{
    set_short("a small home");
    set_long("   You are in a small stone home situated on the grassy plains "+
        "near the river Sorra. Simply enough constructed, the " +
        "walls are lined with little in the way of " +
        "treasures or decorations. A small fireplace " +
        "stands cold against one wall, nearby that " +
        "a small table. A pegboard for cloaks and " +
        "plaides is mounted near the door, and a " +
        "bed sits near the back of the one room " +
        "dwelling.\n");
 
    add_prop(ROOM_I_INSIDE,1);
 
    add_item(({"floor", "ground"}),
        "The floor of the home is made simply from hard-packed " +
        "dirt.\n");
    add_item(({"walls", "wall"}),
        "The walls of the home are made from thin slates of " +
        "of some dark grey stone, carefully stacked to form " +
        "a wall that is relatively weather-proof and strong " +
        "despite the absence of any joining material.\n");
    add_item(({"roof", "ceiling"}),
        "The ceiling of the home is a simple thatch and wooden " +
        "rafter construction.\n");
    add_item(({"thatch", "seaweed", "seagrass"}),
        "The thatch looks to be tightly-bundled mats of " +
        "some sort of seagrass or seaweed.\n");
    add_item(({"rafters"}),
        "The thatch of the roof is supported by a handful of " +
        "very thin wooden rafters.\n");
    add_item(({"fireplace", "firepit"}),
        "Built into the wall, the small fireplace provides " +
        "both a means of cooking and warming the small " +
        "home on cold nights.\n");
    add_item(({"bed"}),
        "The bed is little more than a few wool blankets " +
        "spread across a thick pallet of straw.\n");
    add_item(({"blankets","wool blankets"}),
        "Thick and heavy, those blankets would provide " +
        "warm covers even on the coldest night.\n");
    add_item(({"pallet", "straw", "pallet of straw"}),
        "The straw looks fresh, and is probably " +
        "changed regularly.\n");
    add_item(({"table"}),
        "The little table isn't meant for very many " +
        "people to use at once, but still appears to " +
        "be used frequently.\n");
    add_item(({"pegboard"}),
        "The pegboard is a single board fixed to the " +
        "wall beside the door, with a few wooden pegs " +
        "projecting from it for people to hang clothing " +
        "on.\n");
 
    add_exit(PLAINS+"plains_26_9","west");
    reset_room();
}

public int *
query_global_coords()
{
    return ({3,0});
}
