/*
 *  faerun/underdark/upper/menzo/tierbreche/plateau6.c
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
	set_long("You are standing in front of a gracefully curved  " +
                 "building with many spires which is raised towards the " +
                 "cavern ceiling. Smooth rocks forms a half circle in front " +
                 "of the entrance to the building and they are glowing " +
                 "with a soft dark blue shimmer. Stalactites hangs down " +
                 "from high above you like sharp deadly pikes, almost " +
                 "meeting the spires of the tower in mid-air. " +
                 "The ground beneath you is smoothly cut directly into the " +
                 "caverns rock, and it almost have the polished shiny finish " +
                 "of decorative marble. The magical glow from the  " +
                 "building is mirrored onto the stone floor.\n");
                 
        // Create and configure door
	door = clone_object(P_MENZO_SORCERE + "obj/ground_gate");
	door->configure_ground_door("west", "entrance", 
		P_MENZO_SORCERE + "first1");
	door->move(this_object());
		 
	add_item(({"entrance"}),
        "You can see the entrance to Sorcere, which is the " +
        "academy for Wizards here in Menzoberranzan. The doorway " +
        "is about two stories high and made partially of a black " +
        "metal and partially of blackened wood. The emblem of the " +
        "Sorcere is burnt into the doorway.\n");
        
                
        add_item(({"plateau"}),
        "This is the Tier Breche. You can spot three buildings " +
        "on top of the plateau. The plateau is the highest point " +
        "above the city in this two-mile wide cavern.\n");
        
        
        add_item(({"building"}),
        "You marvel at the sight of this spectacular tower-shaped " +
        "building. It has several gracefully curved spires, which " +
        "extends towards the cavern ceiling in various sizes and shapes. " +
        "It glows around the edges in shifting blue and purple " +
        "twilight-seeming shimmer. Here and there you see small " +
        "openings in the smooth walls, which hints at a rare " +
        "flickering candle light.\n");
        
        add_item(({"first building", "sorcere"}),
        "The tower which houses the wizard academy of Menzoberannzan " +
        "is gracefully curved with many spires.\n");
        
      
        add_item(({"rocks"}),
        "They are made of smooth stone which has been magically altered " +
        "to glow in a soft dark blue shimmering light. They mark the " +
        "a half circle at the entrance of Sorcere.\n");
        
        add_item(({"ceiling","cavern ceiling"}),
        "The upper surface of this grand cavern is filled with " +
        "stalactites which looms over the area like sharp pikes.\n");
                
        add_item(({"stalactites"}),
        "The mineral-laden water has dripped down along the rock " +
        "from the ceiling of the cavern and during countless of centuries " +
        "it has formed gigantic stalactites which looms over the city.\n");
        
        
        add_exit("plateau5", "southeast");
        add_exit(P_MENZO_SORCERE + "first1", "west");
        add_exit("plateau14", "east");

}