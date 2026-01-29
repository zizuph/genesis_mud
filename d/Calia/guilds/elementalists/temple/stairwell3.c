/*
 * Central Stairwell on the Elemental Cleric floor
 * 
 * Created by Petros, March 2014
 * 
 * Mofications:
 *   - Allowed access by Elders who are now able to use task
 *     functions - Mirandus, Nov 24, 2020
 */

#pragma strict_types

#include "defs.h"

inherit TEMPLE_ROOM_BASE;
inherit "/lib/guild_support";

// Defines

// Prototypes

// Global Variables

public void
create_temple_room()
{
  set_short("Third Floor Central Stairwell");
  set_long("Compared to the complex elegance of the main floor of the Elemental "
     + "Temple, you are quite surprised to find that this floor is "
     + "actually quite simple. The walls do not seem to be made of the "
     + "same grey rock material and there are no signs of the crystalline "
     + "veins that you have seen elsewhere in the Temple. You see rooms "
     + "that serve the Elemental Clerics to the north, west, "
     + "east, south and southwest.\n\n");

  try_item( ({ "walls", "wall" }),
     "The walls are made of wood panels, lacquered over "
     +"with a glossy paint. Painted upon them are beautiful "
     +"murals that depict the Elementals interacting with "
     +"their creation.\n");
     
  try_item( ({ "paint", "glossy paint", "mural", "murals", 
              "beautiful murals", "elementals", "creation", 
              "painting" }),
    "There are murals on every available surface of this stairwell. "
    + "The Elementals are shown in various states of action.\n");

  try_item( ({ "north", "practice room" }),
     "To the north, you spot what appears to be a practice room. Other "
     + "Elemental Clerics are learning to control the elements.\n");
  
  try_item( ({ "south", "chambers", "council chambers" }),
     "To the south, you see a chamber with some couches and important "
     + "looking papers. It appears to be some sort of council chamber.\n");

  try_item( ({ "east", "board room" }),
     "To the east, you see a large bulletin board. Some gnomes busy "
     + "themselves with posting and adjusting the notes on the board.\n");

  try_item( ({ "west", "storage chamber", "equipment room" }),
     "To the west, you see a number of equipment lying around. You "
     + "suspect that this is the storage chamber "
     +"for the Elemental Clerics.\n");
    
  try_item( ({ "southwest", "study" }),
     "To the southwest, you see a small study for the "
     +"Elemental Clerics.\n");
        
  try_item( ({ "staircase", "stairwell", "steps" }),
    "The black stairwell appears to have been grown rather than been "
    + "carved out of the inside of the pillar. Block wooden "
    +"steps lead down to the second floor of the Temple.\n");
    
    add_exit(ELEMENTALIST_TEMPLE + "stairwell2", "down"); 
    add_exit(ELEMENTALIST_TEMPLE + "ec_rack", "west", 
        "@@cannot_enter_cleric_floor", 1, "@@cannot_see_cleric_floor");    
    add_exit(ELEMENTALIST_TEMPLE + "ec_boardroom", "east", 
        "@@cannot_enter_cleric_floor", 1, "@@cannot_see_cleric_floor");
    add_exit(ELEMENTALIST_TEMPLE + "cleric_councilroom", "south", 
         "@@cannot_enter_south", 1, "@@cannot_see_south");
    add_exit(ELEMENTALIST_TEMPLE + "ec_practice", "north", 
         "@@cannot_enter_cleric_floor", 1, "@@cannot_see_cleric_floor");
    add_exit(ELEMENTALIST_TEMPLE + "study", "southwest", 
         "@@cannot_enter_cleric_floor", 1, "@@cannot_see_cleric_floor");
}

public int
cannot_see_south()
{	    
    if (this_player()->query_wiz_level() > 0)
    {
        return 0;
    }
    
    if (GUILD_MANAGER->query_is_ec_council(TP, 1))
    	return 0;
  
    if (GUILD_MANAGER->query_is_elder_cleric(TP, 1))
      return 0;
  
    else
      	return 1;
}

public int
cannot_enter_south()
{
	if (this_player()->query_wiz_level() > 0)
    {
        return 0;
    }
    
    if (GUILD_MANAGER->query_is_ec_council(TP, 1))
    	return 0;
   
   if (GUILD_MANAGER->query_is_elder_cleric(TP, 1))
      return 0;
    
    // Non-council members cannot use these exits.
    write("As you attempt to enter, you feel a calming restraining "
          + "force preventing your movement. You get the sense that "
          + "you must be an Elder Cleric of the Elementals to enter.\n");
    return 1;
}

public void
init()
{
    ::init();
    init_guild_support();
}
