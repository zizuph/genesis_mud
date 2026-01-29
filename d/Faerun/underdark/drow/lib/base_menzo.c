/*
 *  faerun/underdark/upper/menzo/std/menzo_room.c
 *
 *  Standard room for Menzoberranzan and surroundings
 *
 *  Created by Wully, 12-2-2004
 *  Light added, 26-9-2005, Midnight
 */

#include "/d/Faerun/defs.h"
#include "defs.h"
#include <stdproperties.h>

inherit FAERUN_ROOM_BASE;

/*
 * Function name: create_menzo_room
 * Description  : Construct a room for Menzoberranzan
 */
void create_menzo_room()
{
}

/*
 * Function name : add_fungi
 * Description   : adds descr of fungi farmed in menzo
 */
void add_fungi()
{
    add_item(({"fungi"}),
        "There are all types of fungi growing here. There are mosses, " +
        "lichens,  mushrooms, and molds. They are grown for both food " +
        "and other uses in the city.\n");
    add_item(({"mushrooms"}),
        "They are giant-size. They are carefully tended and very tall. " +
        "They grow in groups and are well tended.\n");
    add_item(({"lichen", "lichens", "molds", "mold"}),
        "They grow in gardens beneath the mushrooms. They are different " +
        "shapes, sizes, and different colors.\n");
    add_item(({"moss", "mosses"}),
        "They grow in separate beds away from the mushrooms, lichens, " +
        "and molds. The mosses are mostly colorless having been grown in " +
        "the dark and have different shapes and sizes.\n");
}


/*
 * Function name: create_underdark_room
 * Description  : Construct a room for the underdark
 */
nomask void create_faerun_room()
{
	// Set defaults
	set_faerun_area("menzoberranzan");
    add_prop(ROOM_I_LIGHT, 0);
    set_faerun_level(FL_UNDERDARK);
    INDOORS;


	// Call the constructor
	create_menzo_room();
}

/*
 * Function name : add_donigarten_descr
 * Description   : adds descr of donigarten
 */
void add_donigarten_descr()
{
    add_item(({"donigarten"}),
        "It is dominated by a large lake and an island in the middle. " +
        "Beds of moss, fungi, and giant mushrooms grow abundantly there. " +
        "They are guarded by drow patrols.\n");
    add_item(({"pond", "lake"}),
        "The pond is large enough to surrounnd a small island. A few boats " +
        "bob on its dark surface.\n");
    add_item(({"island", "isle", "isle of rothe"}),
        "The island is moss covered and not very large. A herd of animals " +
        "wander around, grazing on the moss.\n");
    add_item(({"animals", "animal", "rothe"}),
        "They are large and resemble oxe. The rothe have two large horns " +
        "that curl downward and out. Their fur appears brown and shaggy. " +
        "The animals wander around on the island.\n");
    add_item(({"boats"}),
        "They are small vessels, bobbing on the surface of the pond.\n");
    add_fungi();
}



/*
 * base room descriptions
 */

string menzo_descr1(string str)
{
    return short() + ". Houses and buildings crowd the road, which wander " +
    "past statues. They are limned with faerie fire and glow eerily. Drow " +
    "push past you, cursing you in their dark tongue. " + str + "\n";
}

string menzo_descr2(string str)
{
    return short() + ". The wide road wanders around carved stalactites " +
    "and stalagmites. They block the view of most of the city. The hot air " +
    "is stifling and oppressive here. " + str + "\n";
}

string menzo_descr3(string str)
{
    return short() + ". Buildings crowd the wide road, with more noble " +
    "houses set away in the distance. Shadows lurk between the buildings, " +
    "hiding a brooding evil. " + str + "\n";
}

string menzo_descr4(string str)
{
    return short() + ". The air is comfortably warm, yet oppressive. " +
    "It blows past you but smells stale. Houses and buildings crowd the " +
    "road, which wander past statues. " + str + "\n";
}

string menzo_descr5(string str)
{
    return short() + ". Buildings crowd the wide road, with more noble " +
    "houses set away in the distance. They are flanked by large statues. " +
    "Drow shove you aside, cursing you in their dark tongue. " + str + "\n";
}

string menzo_descr6(string str)
{
    return short() + ". The road meaders here. It wanders past carved " +
    "stalactites and stalagmites. The stifling air is warm but stale " +
    "from being underground. " + str + "\n";
}
