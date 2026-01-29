/* File         : /d/Khalakhor/se_speir/plains/room/tforbase.c
 * Creator      : Zima@Genesis
 * Date         : ?         
 * Purpose      : Base forest file for the forest north of MacDunn.
 * Related Files: 
 * Comments     : 
 * Modifications: Heavily modified by Darragh 01-01-23
 *              : Updated with baits, Treacher Sept 2021
 */

#pragma strict_types

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>

#include "plains.h"
#include "/d/Khalakhor/sys/paths.h"
#include "/d/Khalakhor/sys/terrains.h"

inherit "/d/Khalakhor/std/room";
inherit BAITSEARCH;
 
#define MAX_BAITS      3
#define BAIT_OBJECT    OBJ + "catalpa-worm"

void
create_add_items()
{
   add_item(({"forest","woods","woodlands"}),
            "It is a light forest of tall trees, mostly pine.\n");
   add_item(({"treetop","treetops","tops"}),
            "The treetops of the pine forest rustle gently in the "
          + "wind, high above you.\n");
   add_item(({"trees","tree"}),
            "They are tall and straight, mostly pine, their "
          + "branches stretching out in all directions high "
          + "above.\n");
   add_item(({"pine","pines","pine trees"}),
            "The pines are tall and straight with dark brown "
          + "bark and long green needles. A few pine cones "
          + "hang from a few of the branches high above.\n");
   add_item(({"cone","cones","pine cones","pine cone"}),
            "A few brown cones hang in the pines, high above "
          + "your head.\n");
   add_item(({"needles","pine needles"}),
            "The pine needles are long and green, at least "
          + "those still living on the trees. Those carpeting "
          + "the floor have turned brown.\n");
   add_item(({"floor","forest floor","ground","carpet","layer"}),
            "The floor of the forest is carpeted with a layer "
          + "of fallen needles and branches.\n");
   add_cmd_item(({"tree","pine"}),"climb",
            "The trees are too difficult to climb.\n");
}
void
create_room_tells()
{
   add_tell(({"A mild breeze sweeps through the woods, rustling "
            + "the treetops.\n",
              "You hear a faint scratching sound somewhere in "
            + "the distance.\n",}));
}
public void
create_tforest()
{
   set_short("In a light forest");
   set_long("   You are in a light forest, populated mostly "
          + "with tall straight pines which tower above "
          + "you. The floor of the forest is covered with "
          + "dead needles and branches, which crunch softly "
          + "beneath your feet. The still air is permeated "
          + "with the scents of the trees.");

    set_terrain(TERRAIN_MIXEDWOOD);

	  // Set up baits in the base room, and search results
	  set_up_baits(BAIT_OBJECT, ({"tree", "trees"}), MAX_BAITS);
	  set_up_bait_strings(({
		    "You riffle through the leaves but find nothing.",
		    "You riffle through the leaves but don't find anything " +
			    "special. There doesn't seem to be any more worms here.",
		    "You riffle through some leaves and find a %s!",
		    "riffles through some leaves in a tree and picks down a %s!",
	  }));

    create_add_items();

    set_tell_time(600);
    create_room_tells();

    reset_room();
}

void
create_tforest_room()
{
    create_tforest();
}

void
reset_room()
{
    reset_baits();
}