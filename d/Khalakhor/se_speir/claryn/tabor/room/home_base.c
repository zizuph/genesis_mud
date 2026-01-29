/*
 * home_base.c
 *
 * Baseroom for the homes in Tabor Sogh.
 *
 * Khail - January 17 / 98.
 * Zima  - March 15, 1998   - added cloning of villagers
 */
#pragma strict_types
#include <stdproperties.h>
#include "room.h"
#define  MAX_NPC 3
 
inherit "/d/Khalakhor/std/room";
#include "/d/Khalakhor/sys/defs.h"
#include <macros.h>
 
object  trunk;
object* npc = allocate(MAX_NPC);
int     numnpc=-1;
 
public int *
query_global_coords()
{
    return VILLAGE_COORDS;
}
 
public void
check_npc()
{
   int i;
   if (numnpc==-1) numnpc=random(MAX_NPC);
   for (i=0; i<numnpc; i++)
      if (!objectp(npc[i]))
         {
         npc[i] = clone_object(VILLAGER);
         npc[i]->arm_me();
         npc[i]->move(TO);
         tell_room(TO,QCTNAME(npc[i])+" wanders up.\n");
         }
}
 
public void
check_trunk()
{
    if (trunk && present(trunk, this_object()))
        return;
 
    seteuid(getuid());
    trunk = clone_object(OBJ + "trunk");
    trunk->move(this_object());
}

public void
reset_room()
{
   check_trunk();
   check_npc();
}

 
public void
create_home()
{
    set_short("a small home");
    set_long("   You are in one of the small homes in " +
        "Tabor Sogh. Simply enough constructed, the " +
        "walls are lined with little in the way of " +
        "treasures or decorations. A small fireplace " +
        "stands cold against one wall, nearby that " +
        "a small table. A pegboard for cloaks and " +
        "plaides is mounted near the door, and a " +
        "bed sits near the back of the one room " +
        "dwelling.\n");
 
    INSIDE;
 
    add_item(({"floor", "ground"}),
        "The floor of the home is made simply from hard-packed " +
        "dirt.\n");
    add_item(({"walls", "wall"}),
        "The walls of the home are made from thin slates of " +
        "some dark grey stone, carefully stacked to form " +
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
 
    reset_room();
}
