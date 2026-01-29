/**********************************************************************
 * - smithy.c                                                       - *
 * - This is a forge for the Blacksmiths of Shire, lay guild.       - *
 * - Created by Damaris@Genesis 02/2005                             - *
 **********************************************************************/
#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>
#include "room.h"
#include "/d/Khalakhor/sys/defs.h"

inherit "/d/Khalakhor/std/room";


object smith;

public int *
query_local_coords()
{
    return ({11,6});
}

public int *
query_global_coords()
{
    return VILLAGE_COORDS;
}
/*
 * Function name: reset_room
 * Description  : Resets the room, mainly to make sure the smith
 *                is where he's supposed to be.
 * Arguments    : n/a
 * Returns      : n/a
 */
public void
reset_room()
{
    ::reset_room();
    if (!smith)
    {
	smith = clone_object(NPC + "milligan");
	smith->arm_me();
	smith->move(TO);
	tell_room(TO, QCTNAME(smith) + " wanders in from " +
	  "the other room.\n");
	return;
    }
    else if (!present(smith))
    {
	if (smith->query_attack())
	    return;
	else
	{
	    tell_room(environment(smith), QCTNAME(smith) +
	      "suddenly looks around with a start, and rushes " +
	      "off somewhere.\n");
	    smith->move_living("M", TO);
	    tell_room(TO, QCTNAME(smith) + " rushes in from " +
	      "the other room.\n");
	}
    }
}

public void
create_khalakhor_room()
{
    set_short("A merchant forge");
    set_long("   This is a merchant forge that has been set "+
      "aside for Milligan CallaHaan to use as he was a great "+
      "smith here in Port MacDunn. You can purchase needed "+
      "items for forging simply by paying him for items. "+
      "There are iron bars, wooden poles and leathers that "+
      "are for sale in bins.\n");

    add_item(({"forge"}),
      "The forge is next door.\n");
    add_item(({"area", "here", "room", "merchant forge"}), query_long);
    add_item(({"iron", "piles of iron"}),
      "There's three distinct different piles of iron in the bins, " +
      "one appears to be pure, raw ingots of iron, the other " +
      "contains shreds of scrap iron left over from projects, or " +
      "from items that broke and couldn't be repaired. There "+
      "are also iron bars that are for sale.\n");
    add_item(({"bin", "bins"}),
      "The bins are filled with iron bars, wooden poles and leathers.\n");
    add_item(({"poles", "pole","wooden poles", "wood poles", "wood pole", "wodden pole"}),
      "There are wooden poles in the bins for sale.\n");
    add_item(({"leather", "leathers"}),
      "There are plenty of leathers piled in bins for sale.\n");
    add_item(({"bars", "bar", "iron bars", "iron bar"}),
      "There are plenty of iron bars in the bins for sale.\n");
    
    add_item(({"ingots", "pile of ingots"}),
      "Regular-shaped blocks of pure iron, the ingots get used " +
      "in the blades of finer-quality weapons.\n");
    add_item(({"scrap iron", "pile of scrap iron"}),
      "The scrap iron pile is somewhat larger than the one with " +
      "the iron ingots, and full of pretty much what you'd " +
      "expect in a scrap heap, nothing useful.\n");
    add_item(({"floor", "ground"}),
      "The floor of forge is hard-packed dirt, and pock-marked " +
      "where bits of hot iron landed.\n");
    add_item(({"walls", "wall"}),
      "The walls of the smithy are made from various sized " +
      "pieces of hard grey stone, carefully placed together " +
      "and packed with clay.\n");
    add_item(({"roof", "ceiling"}),
      "The ceiling of the forge is also made of stone, somehow " +
      "cunningly placed and mortared in place, so no wood was " +
      "used in the construction of the building, reportedly a " +
      "building technique known only to the masters of the " +
      "different smithy crafthalls.\n");

    INSIDE;

    add_exit("blacksmith_forge", "south");
    set_alarm(0.5, 0.0, reset_room);

 
}

