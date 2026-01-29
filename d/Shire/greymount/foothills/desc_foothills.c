/*
	*Base file for the path to the Grey Mountains
	*Altrus, June 2005
*/
 
#include "/d/Shire/sys/defs.h"
#include "/d/Shire/greymount/defs.h"
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>

inherit "/std/room";
inherit "/d/Shire/std/room/room_tell";
inherit "/cmd/std/command_driver";

/*
 * Function name : set_add_river_far
 * Arguments     : str: none
 * Description   : adds standard descr for the Anduin as seen
 *                 far away
 */
void add_foothills()
{
	add_item(({"foothills", "hills"}), "The tumbled hills at the foot of the Misty Mountains rise just to the west here. They are rugged hills, full of gullies and covered in wild grasses.\n");
	add_item("gullies", "Some of them are deep, others mere shallow cuts in the hills, but they cover the foothills, making for a treacherous landscape even at this low level.\n");
	add_item(({"wild grass", "wild grasses"}), "The grass is long and dry, and sways and bends whenever the wind blows across hills.\n");
}

/*
 * Function name : set_add_river_far
 * Arguments     : str: none
 * Description   : adds standard descr for the Anduin as seen
 *                 far away
 */
void add_anduin_far()
{
	add_item(({"river", "anduin", "the great river", "great river"}), "The river, Anduin, appears as a thin ribbon in the distance.\n");
}

/*
 * Function name : set_add_river_near
 * Arguments     : str: none
 * Description   : adds standard descr for the Anduin as seen
 *                 nearby
 */

void add_anduin_near()
{
	add_item(({"river", "anduin", "the great river", "great river"}), "The Anduin River flows north and south. The sound of it can be heard nearby.\n");
}


/*
 * Function name : set_add_river_near
 * Arguments     : str: none
 * Description   : adds standard descr for the Anduin as seen
 *                 upclose and personal
 */

void add_anduin_close()
{
	add_item(({"river", "anduin", "the great river", "great river", "water"}), "This is the mighty Anduin. It is the greatest river in Middle-earth as it flows south from its many tributaries in the northern mountains. The water looks surprising calm here as it flows past reeds, grasses, and other water plants.\n");
	add_item( "water plants", "Tall grasses, water flowers, reeds, rushes, and other tall plants grow at the edge of the Anduin. They probably offer some refuge for small animals.\n");
	add_item(({"water flowers"}), "They grow at the edge of the river. They are yellow, blue, purple and other colors.\n");
	add_item(({"reeds", "rushes"}), "They grow at the river's edge and are healthy looking with arrow shaped ends. Some are bent over, floating in the river.\n");
	add_item(({"wildlife", "animals"}), "Wildlife is evident in the vale by animal tracks that dot the " +
        "land. However, the animals remain hidden from your view, probably watching you.\n");
	add_item(({"tracks", "animal tracks"}), "They are prints left behind by animals that have travelled this way. Some are fresh while others are faint and older.\n");
}

/*
 * Function name : set_add_misty_far
 * Arguments     : str: none
 * Description   : adds standard descr for the misty mountains
 *                 as seen far away
 */

void add_misty_far()
{
	add_item(({"mountains", "misty mountains"}), "The Misty Mountains rise to the west. Their jagged peaks are covered with clouds and look imposing, even from this distance.\n");
	add_item("peaks", "The peaks are rugged, of varying heights, but they all rise high above you, shrouded in mist and cloud.\n");
	add_item(({"mist", "cloud", "clouds"}), "The clouds and mist, from which the mountain range gets its name, cover the tops of the peaks in a fine shroud.\n");
}


/*
 * Function name : set_add_misty_near
 * Arguments     : str: none
 * Description   : adds standard descr for the misty mountains
 *                 as seen near
 */

void add_misty_near()
{
	add_item(({"mountains", "misty mountains"}), "The Misty Mountains tower above you to your west. They are a great chain of mountains that run north and south through Middle-earth. Their peaks are shrouded with clouds and are imposing. Rumours speak of goblins and orcs inhabiting the Misty mountains.\n");
	add_item("peaks", "The peaks are rugged, of varying heights, but they all rise high above you, shrouded in mist and cloud.\n");
	add_item(({"mist", "cloud", "clouds"}), "The clouds and mist, from which the mountain range gets its name, cover the tops of the peaks in a fine shroud.\n");
}


/*
 * Function name : set_add_misty_close
 * Arguments     : str: none
 * Description   : adds standard descr for the misty mountains
 *                 as seen near
 */

void add_misty_close()
{
	add_item(({"mountains", "misty mountains"}), "The Misty Mountains dominate your view as you stand at their feet. Large boulders and rocks have tumbled down from the mountain and lay strewn about.\n");
	add_item(({"boulders", "rocks"}), "They must have fallen during an avalanche. Best be careful while travelling through here.\n");
}

/*
 * Function name : set_add_mirk_close
 * Arguments     : str: none
 * Description   : adds descr of mirkwood forest close up
 */
void add_mirk_close()
{
	add_item(({"forest", "mirkwood", "mirkwood forest", "greenwood", "greenwood forest", "greenwood the great", "wood", "the great wood", "taur e-ndaedelos"}), "Large trees dominate the forest to the east, known as Mirkwood. It is the largest forest in Middle-earth stretching from the north to the south. Mirkwood is dark and foreboding, and only the bravest enter it.\n");
	add_item(({"large trees", "trees"}), "The trees are dark and ancient looking. Their trunks are dark green to black colored and are twisted. They grow close together, preventing travel into the forest.\n");
	add_item(({"branches", "tree branches"}), "The branches are very thick and twisted. They are dark green to black colored and are covered with countless black leaves.\n");
	add_item(({"leaves", "dark leaves", "dark leaf", "leaf"}), "The dark leaves hang silently from the branches. They are large and teardrop shaped.\n");
}

/*
 * Function name : set_add_mirk_near
 * Arguments     : str: none
 * Description   : adds descr of mirkwood forest nearby
 */
void add_mirk_near()
{
    add_item(({"forest", "mirkwood", "mirkwood forest", "greenwood", "greenwood forest", "greenwood the great", "wood", "the great wood", "taur e-ndaedelos"}), "The forest spreads north and south. It is large, as it spreads before you. Large trees are visible which are crowned with dark leaves.\n");
    add_item(({"large trees", "trees"}), "The trees of the forest are dark and ancient looking. They grow close together, creating a black wall in the distance.\n");
    add_item(({"branches", "tree branches"}), "The branches of the trees of the forest are very thick and twisted. Dark leaves hang from the branches.\n");
    add_item(({"leaves", "dark leaves", "dark leaf", "leaf"}), "The dark leaves are large and teardrop shaped.\n");
}

/*
 * Function name : set_add_mirk_far
 * Arguments     : str: none
 * Description   : adds descr of mirkwood forest far away
 */
void add_mirk_far()
{
    add_item(({"forest", "mirkwood", "mirkwood forest", "greenwood", "greenwood forest", "greenwood the great", "wood", "the great wood", "taur e-ndaedelos"}), "It is a large carpet of dark trees and spread out to the east. The forest stretches north and sout, blocking your view beyond it.\n");
    add_item(({"large trees", "trees"}), "The trees are of the forest are difficult to look at, but they look ancient and twisted, and all look black colored.\n");
    add_item(({"branches", "tree branches"}), "The branches of the forest are difficult to see, but the largest ones look dark and twisted.\n");
    add_item(({"leaves", "dark leaves", "dark leaf", "leaf"}), "The leaves are difficult to see, but they all look black and evil looking.\n");
}

void add_rush()
{
	add_item(({"small river", "rushdown", "rhimdath"}), "This is the river Rhimdath, also known as the Rushdown. It is small, compared to the larger Anduin, into which the Rushdown feeds.\n");
}

void add_lang_near()
{
	add_item(({"river", "langflood"}), "The river Langflood can be seen in the distance. The sound of it can be heard nearby as it rushes south to join the larger Anduin.\n");
}

void add_lang_close()
{
	add_item(({"river", "langflood"}), "This is river Langflood. The loud flow fills your ears as it rushes south to join the larger Anduin. The water looks surprising calm here as it flows past reeds, grasses, and other water plants.\n");
	add_item( "water plants", "Tall grasses, water flowers, reeds, rushes, and other tall plants grow at the edge of the Langflood. They probably offer some refuge for small animals.\n");
	add_item(({"water flowers"}), "They grow at the edge of the river. They are yellow, blue, purple and other colors.\n");
	add_item(({"reeds", "rushes"}), "They grow at the river's edge and are healthy looking with arrow shaped ends. Some are bent over, floating in the river.\n");
	add_item(({"wildlife", "animals"}), "Wildlife is evident in the vale by animal tracks that dot the " +
        "land. However, the animals remain hidden from your view, probably watching you.\n");
	add_item(({"tracks", "animal tracks"}), "They are prints left behind by animals that have travelled this way. Some are fresh while others are faint and older.\n");
}