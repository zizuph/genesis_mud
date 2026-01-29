/*
 *  faerun/underdark/upper/menzo/tierbreche/plateau1.c
 *
 *  
 *  Created by Midnight, 12-2-2004
 */

#include "defs.h"
inherit P_MENZO_TIERBRECHE + "std/base_room";

/*
 * Function name: create_tierbreche_room
 * Description  : Construct a room for the Tier Breache part of Menzoberranzan
 */
void create_tierbreche_room()
{
	set_short("On top of the stair");
	set_long("The wide impressive descends steeply towards " +
                 "towards the city beneath you. You stand upon the " +
                 "plateau which houses the drow Academies of Menzoberranzan. " +
		 "From here you have a spectacular view over the city of " +
		 "Menzoberranzan, since this is the highest place above " +
		 "ground in this cavern of great size. From where you stand, you " +
		 "can also see the three buildings of the Academy. " +
		 "The Sorcere, the Melee-Magthere and the Arach-Tinilith.\n");
		 
	add_item(({"stair", "stairs"}),
        "This is a grand stair made of natural stone and it looks " +
        "as if it's been carved directly into the mountain. " +
        "It's clims steeply down towards the city .\n");

        add_item(({"plateau"}),
        "This is the Tier Breche. You can spot three buildings " +
        "on top of the plateau. The plateau is the highest point " +
        "above the city in this two-mile wide cavern.\n");
        
        add_item(({"buildings", "building"}),
        "On top of the plateau you can spot three very different " +
        "buildings. One gracefully curving many-spired tower, one " +
        "giant building shaped like a pyramid and finally an " +
        "intriguing building shaped like a giant spider.\n");
        
        add_item(({"sorcere", "the sorcere", "first building"}),
        "The tower which houses the wizard academy of Menzoberannzan " +
        "is gracefully curved with many spires.\n");
        
        add_item(({"melee-magthere", "the melee-magthere", "second building"}),
        "The building of the Melee-Magthere is shaped like an impressive " +
        "pyramid. It houses the warrior academy of Menzoberranzan.\n");
        
        add_item(({"arach-tinilith", "the arach-tinilith", "third building"}),
        "The priestesses of Lloth studies in a huge building shaped " +
        "like a giant spider.\n");
        
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
        
        
        
        add_exit("stair", "stair");
        add_exit("plateau2", "north");
               

}