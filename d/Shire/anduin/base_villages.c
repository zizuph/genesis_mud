/*
 * Base file for the villages of Anduin
 * Finwe, August 2005
 */
 
#include "/d/Shire/sys/defs.h"
#include "local.h"
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>

inherit AREA_ROOM;
inherit HERB_SEARCH;
inherit "/d/Shire/std/room/room_tell";
inherit "/lib/commands.c";
inherit "/d/Shire/anduin/base_common";

void create_vil_room() {}
 
public void
create_area_room()
{
/*
    set_areadesc("road");
    set_area("in");
    set_areaname("the village");
    set_land("Wilderland");
    set_areatype(1);
*/
    areadesc = "broad road";
    area = "in";
    areaname = "the village";
    land = "Wilderland";
    areatype = 0;

   
    extraline = "More descr here.";

    add_item("sky",
        "It is @@day_desc@@. @@daylight_desc@@ fills the " +
        "sky.\n");


    set_room_tell_time(random(ROOM_TELL_TIME) + 30);
    add_room_tell("A few birds fly overhead.");
    add_room_tell("Some clouds float lazily across the sky.");
    add_room_tell("The grasses sway in the breeze.");
    add_room_tell("Some clouds drift by, blocking the " +
        "@@sun_moon@@.");
    
    add_prop(ROOM_I_INSIDE, 0); // This is an outdoor room

    create_vil_room();
    add_std_herbs("plain");

}

/*
 * Function name : set_add_road
 * Description   : adds descr of road in village
 */
void set_add_road()
{
    add_item(({"road", "path", "trail"}),
        "The road is well trodden and bare of grass. On either side " +
        "of it grow bushes, grasses, and flowers.\n");
    add_item(({"bushes"}),
        "They are thick and grow alongside the road. The bushes are " +
        "healthy looking and grow in groups among the grass.\n");
    add_item(({"grasses"}),
        "The grass has been cut but still moves about in the wind. It " +
        "is a healthy green color with various wildflowers growing in " +
        "it. Some bushes grow in the grass as well as tall clover.\n");
    add_item(({"flowers", "wildflowers"}),
        "Many different types of flowers grow here. Some are tall, while " +
        "others are short or even hidden among the grasses, visible " +
        "only when the grasses move. They are different colors, shapes, " +
        "and sizes.\n");
    add_item(({"meadow", "grassland", "field", "meadows"}),
        "This is a wide area of land covered with wild grasses. The grasses " +
        "wave in the breeze and are up to your ankles. Growing in the grass " +
        "are flowers and clover.\n");
    add_item(({"grasses", "wild grasses", "tall grasses", "tall grass", 
            "grasses", "grass"}),
        "It is an emerald green, healthy looking, and covers the meadow. " +
        "Clover and wild flowers grow between the grasses.\n");


}

/*
 * Function name : 
 * Description   : adds descr of 
 */
void set_add_clover()
{
    add_item(({"clover"}),
        "This is a tall plant with three to five leaves on each stalk. " +
        "The leaves are unusually large and a deep emerald green. Large " +
        "purple flowers grow among the clover.\n");
    add_item(({"clover flower", "clover flowers", "purple flowers", 
            "purple flower"}),
        "The large purple flowers are a ball of dense, purple spikes. " +
        "They are the size of a fist and smell sweet.\n");
}

/*
 * Function name : set_set_square
 * Description   : adds descr of 
 */
void set_set_square(string str)
{
    add_item(({"square"}),
        "This is the center of the village. The villagers come here " +
        "daily to discuss local events and meet with each other. " + str +
        "\n");

}

/*
 * Function name : set_wood_planks
 * Description   : adds descr of wood planks used in buildings
 */
void set_wood_planks(string str)
{
    add_item(({"planks", "plank", "wood planks", "wood plank", "board", 
            "boards"}),
        "The planks are long, wide, and thick. They have been cut from old " +
        "trees and planed smooth. The planks look weathered but still " +
        "in good condition. " + str + "\n");

}
