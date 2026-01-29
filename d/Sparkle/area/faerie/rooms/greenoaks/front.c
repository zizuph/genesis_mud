/*
 * Forest path leading to Wild Elves Guild
 * By Finwe, July 2001
 */
 
#pragma strict_types
#include "defs.h" 

inherit TOWN_BASE;

//string road_type = "path";
#define ROOMS_DIR   ("/d/Shire/cypress/guilds/wrunner/rooms/")

void
create_town_room()
{
/*
    set_area("outside");
    set_areaname("an exquisite building");
    set_land("Cypress");
    set_areatype(0);
    set_areadesc(road_type);
*/

    set_short("Outside an exquisite building");
    set_long(short() + ". " + s_desc_sky_outside_sky() + "You stand before a large, exquiste building. It " +
        "is made of white blocks and lies hidden in the forest. " +
        "Lovely gardens surround the building and ancient trees " +
        "grow everywhere.\n");

    add_item(({"building", "white building"}),
        "The white building stands in the distance, south of " +
        "here. It lies hidden in the trees and looks impressive.\n");
    add_item("path",
        "The path is wide and set with white stone blocks. It " +
        "leads north into the forest.\n");
    add_item("exquisite building",
        "The exquisite building is one story high and fashioned " +
        "of white stone. It is  surrounded by gardens and ancient " +
        "trees. A column of white stone is set to the left side " +
        "of the entrance.\n");
    add_item("entrance",
        "The entrance is wide with an slightly arched top " +
        "leading into the building.");
    add_item(({"top", "arched top"}),
        "The top is fashioned from one piece of white stone and " +
        "set on to the top of the entrance.\n");
    add_item(({"marker", "column", "column of white stone"}),
        "The column is about waist high and circular. In golden " +
        "letters and engraved on the front it reads, " +
        "'Guild of the Wild Elves'\n");

    add_item(({"stone blocks", "white stone blocks"}),
        "The white stone blocks are hewn of white marble. They " +
        "are very large and perfectly square. Some are used to " +
        "make the avenue while other stone blocks are used to " +
        "make the building.\n");
    add_item(({"gardens",}),
        "They surround the building in a tapestry of color. The " +
        "gardens are works of art showing the skills of the " +
        "elves. Some fountains are placed in the gardens, " +
        "providing a melodious, bubbling sound.\n"); 
    add_item(({"ivy", "ivies"}),
        "The ivy is ancient and grows over the building. " +
        "Despite its age, it looks very young and healthy.\n");
    add_item(({"ivy leaf", "ivy leaves"}),
        "The leaves of the ivy vary in shape. They are heart, " +
        "curly, fan, bird's foot, typical shaped leaves. Some " +
        "of the plants have green and white leaves which " +
        "contrast with the rest of the plants and building.\n");
    add_item(({"fountains", "fountain"}),
        "The fountains are lovely and full of a life all their " +
        "own. Each are a work of art and are diverse in their " +
        "shape and styles. Some are multi-level bowls with water " +
        "that pours over their edges into large bowls. Other " + 
        "fountains are basins with water spraying up. Still " + 
        "other fountains imitate brooks with water bubbling over " +
        "stones. They all contribute to the relaxing musical " +
        "sounds that surround the building.\n");

    add_exit(GO_DIR + "road23", "north");
    add_exit(ROOMS_DIR + "join", "south");
}
