/*
 *  faerun/underdark/upper/menzo/tierbreche/plateau14.c
 *
 *  
 *  Created by Midnight, 13-12-2004
 */

#include "defs.h"
inherit P_MENZO_TIERBRECHE + "std/base_room";

/*
 * Function name: create_tierbreche_room
 * Description  : Construct a room for the Tier Breche part of Menzoberranzan
 */
void create_tierbreche_room()
{
	set_short("On a path glowing in a soft blue shimmer");
	set_long("You are walking on a path marked by smooth rocks,  " +
                 "which markes the way between Melee-Magthere and Sorcere " +
                 "on Tier Breche. The rocks along side of the path glows " +
                 "with a soft dark blue shimmer. Stalactites hang down " +
                 "from high above like sharp deadly pikes. " +
                 "The plateau you are walking on stands in spectacular " +
                 "contrast to the rough-looking ceiling. " +
                 "The ground is smoothly cut directly into the " +
                 "caverns rock, and it almost have the polished shiny finish " +
                 "of decorative marble. The magical glow from the surrounding " +
                 "buildings are mirrored into the stone floor beneath you.\n");
		 
	
        
                
        add_item(({"plateau", "tier breche"}),
        "This is the Tier Breche. You can spot three buildings " +
        "on top of the plateau. The plateau is the highest point " +
        "above the city in this two-mile wide cavern.\n");
        
        
        add_item(({"buildings", "building"}),
        "On top of the plateau you can spot three very different " +
        "buildings. One gracefully curving many-spired tower, one " +
        "giant building shaped like a pyramid and finally an " +
        "intriguing building shaped like a giant spider.\n");
        
        add_item(({"first building", "sorcere"}),
        "The tower which houses the wizard academy of Menzoberannzan " +
        "is gracefully curved with many spires.\n");
        
        add_item(({"second building"}),
        "The building of the Melee-Magthere is shaped like an impressive " +
        "pyramid. It houses the warrior academy of Menzoberranzan.\n");
        
        add_item(({"third building"}),
        "The priestesses of Lloth studies in a huge building shaped " +
        "like a giant spider.\n");
        
        add_item(({"rocks"}),
        "They are made of smooth stone which has been magically altered " +
        "to glow in a soft dark blue shimmering light. They mark the " +
        "path between the entrance of Tier Breche and Sorcere.\n");
        
                
        add_item(({"stalactites"}),
        "The mineral-laden water has dripped down along the rock " +
        "from the ceiling of the cavern and during countless of centuries " +
        "it has formed gigantic stalactites which looms over the city.\n");
        
        add_item(({"stalagmites"}),
        "Rock formations of various sizes has been formed like pointed " +
        "pikes from the grouns and up towards the cavern ceiling high" +
        "above. The mineral-heavy water drops continuously downwards " +
        "from the ceiling to make the protusions grow slowly over " +
        "centuries.\n");
        
        add_exit("plateau13", "east");
        add_exit("plateau6", "west");
               

}