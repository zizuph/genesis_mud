/*
 *  faerun/underdark/upper/menzo/tierbreche/plateau2.c
 *
 *  
 *  Created by Midnight, 12-2-2004
 */

#include "defs.h"
inherit P_MENZO_TIERBRECHE + "std/base_room";

/*
 * Function name: create_tierbreche_room
 * Description  : Construct a room for the Sorcere part of Menzoberranzan
 */
void create_tierbreche_room()
{
	set_short("At the entrance of Tier Breche");
	set_long("You stand before the entrance of Tier Breche. Two " +
                 "carved columns, marked by exceptionally great size, " +
                 "frames the entrance to the academy. Two perfectly " +
                 "cut spider statues made of shiny black obsidian leers " +
                 "down at you from the top of the high columns as if " +
                 "they are vigilantly guarding the entrance. From here " +
                 "you have a perfect view over the city.\n");
		 
	add_item(({"entrance"}),
        "The entrance to Tier Breche is marked by two fifteen feet " +
        "heigh stone columns.\n");
        
        add_item(({"columns"}),
        "The entrance to Tier Breche is marked by two fifteen feet " +
        "heigh stone columns. Two statues of guarding spiders has " +
        "been carved upon the stalagmite columns.\n");

        add_item(({"spider", "spiders"}),
        "The eeire statues of giant spiders are carved on top " +
        "of the stalagmite columns which marks the entrance. " +
        "They look very much alive as if they are observing your " +
        "every move.\n");
        
        add_item(({"view"}),
        "The colours of Menzoberranzan can be seen at their best " +
        "from this plateau. The magical fires which are lit by wizards " +
        "to brighten up houses and roads glows everywhere, in nuances " +
        "ranging from bright blue to deep purple. You can see rows and rows " +
        "of castles thrumming in a glow of magic. " +
        "This city is perfection of form, where not a stone has been " +
        "left to it's natural shape. The stalagmites and stalactites " +
        "raises up from the ground and hangs down from the ceiling, giving " +
        "the impression of jaws of sharp fangs. Occasionally they meet in " +
        "midair and form. gigantig columns.\n");
        
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
        
        add_exit("plateau1", "south");
        add_exit("plateau3", "north");
               

}