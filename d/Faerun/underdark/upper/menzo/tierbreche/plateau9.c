/*
 *  faerun/underdark/upper/menzo/tierbreche/plateau9.c
 *
 *  
 *  Created by Midnight, 13-2-2004
 */

#include "defs.h"
inherit P_MENZO_TIERBRECHE + "std/base_room";

/*
 * Function name: create_tierbreche_room
 * Description  : Construct a room for the Tier Breche part of Menzoberranzan
 */
void create_tierbreche_room()
{
	object door;
	
	set_short("In front of a high building");
	set_long("You are standing in front of a building which is  " +
                 "shaped like a pyramid. " +
                 "Smooth rocks forms a large square entrance " +
                 "and they are glowing " +
                 "with a soft dark blue shimmer. Stalactites hangs down " +
                 "from high above you like sharp deadly pikes, almost " +
                 "meeting the spires of the tower in mid-air. " +
                 "The ground beneath you is smoothly cut directly into the " +
                 "caverns rock, and it almost have the polished shiny finish " +
                 "of decorative marble. The magical glow from the  " +
                 "building is mirrored onto the stone floor.\n");
                 
        // Create and configure door
	door = clone_object(P_MENZO_SORCERE + "obj/ground_gate");
	door->configure_ground_door("east", "entrance", 
		P_MENZO_MELEE + "first1");
	door->move(this_object());
		 
	add_item(({"entrance"}),
        "You can see the entrance to Melee-Magthere, which is the " +
        "academy for Warriors here in Menzoberranzan. The doorway " +
        "is about two stories high and made partially of a black " +
        "metal and partially of blackened wood. The emblem of the " +
        "Melee-Magthere is burnt into the doorway.\n");
        
                
        add_item(({"plateau"}),
        "This is the Tier Breche. You can spot three buildings " +
        "on top of the plateau. The plateau is the highest point " +
        "above the city in this two-mile wide cavern.\n");
        
        
        add_item(({"building"}),
        "You marvel at the sight of this spectacular pyramid-shaped " +
        "building. It is a spectacular building with walls of smooth stone.\n");
        
               
      
        add_item(({"rocks"}),
        "They are made of smooth stone which has been magically altered " +
        "to glow in a soft dark blue shimmering light. They mark the " +
        "entrance of Melee-Magthere.\n");
        
        add_item(({"ceiling","cavern ceiling"}),
        "The upper surface of this grand cavern is filled with " +
        "stalactites which looms over the area like sharp pikes.\n");
                
        add_item(({"stalactites"}),
        "The mineral-laden water has dripped down along the rock " +
        "from the ceiling of the cavern and during countless of centuries " +
        "it has formed gigantic stalactites which looms over the city.\n");
        
        
        add_exit("plateau8", "southwest");
        add_exit(P_MENZO_MELEE + "first1", "east");
        add_exit("plateau10", "west");

}