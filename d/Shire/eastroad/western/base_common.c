/*
 * This file file contains common items for the Great East Road, West
 * Finwe, March 2005
 */

#include "local.h"
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>

inherit "/std/room";
inherit "/d/Shire/std/room/room_tell";


/*************************************************************************
 * routines inherited by other routines go here
 *************************************************************************/

/*
 * Function name : set_add_plants
 * Description   : adds descr of plants found in fields.
 */
void set_add_plants()
{
    add_item(({"plants"}),
        "They grow in abundance here. They are healthy looking and " +
        "well-nourished from a recent flooding of the river. Small " +
        "trees, bushes, and grasses grow around here.\n");
    add_item(({"trees", "small trees"}),
        "They are short and grow in small, scattered groups. They " +
        "have been pruned to retain their small size.\n");
    add_item(({"bushes"}),
        "They are bushy and all sizes. They grow alongside the lane " +
        "and in scattered groups. The bushes look healthy and well " +
        "nourished from the floods.\n");
    add_item(({"grasses", "grass"}),
        "The grass is short and green, and grows wild across the fields. " +
        "To keep it under control, it looks like the grass was recently " +
        "pruned or cut.\n");
}
/*
 * Function name : set_add_tells
 * Description   : adds descr of
 */
void set_add_tells()
{
    set_room_tell_time(60+random(30));
    add_room_tell("A fish splashes in the river.");
    add_room_tell("Frogs croak alongside the river.");
    add_room_tell("A traveller passes by and greets you.");
    add_room_tell("Farm sounds echo in the distance.");
}



/*************************************************************************
 * end of routines inherited by other routines
 *************************************************************************/

/*
 * Function name : set_add_villages
 * Description   : adds descr of hobbit villages in the distance
 */
void set_add_villages()
{
    add_item(({"village", "villages", "hobbit village", "hobbit villages",
            "towns", "town", "hobbit towns", "hobbit town"}),
        "They stand in the distance, and too small to make out any " +
        "details.\n");

}

/*
 * Function name : set_add_farms
 * Description   : adds descr of farms in the distance
 */
void set_add_farms()
{
    add_item(({"farms", "farm"}),
        "They are stand in the distance, like green squares scattered " +
        "across the area. There are very few of them because they're " +
        "away from any nearby towns.\n");
}

/*
 * Function name : set_add_brandywine
 * Description   : adds descr of the brandywine river
 */
void set_add_brandywine()
{
    add_item(({"river", "baranduin river", "brandywine river",
            "baranduin", "brandywine"}),
        "It is a large river flowing north and south. It marks the " +
        "eastern border of the Shire. The river floods its " +
        "banks occasionally, leaving the surrounding land marshy. The " +
        "river is a dark, brown color, and flows lazily past you.\n");
    add_item(({"banks", "riverbanks"}),
        "They are large and rounded, and plunge suddenly into the river. " +
        "The banks have been cleared of plants and are dark brown.\n");
    set_add_tells();
}

/*
 * Function name : set_add_stonebows_away
 * Description   : adds descr for Stonebows bridge and the Inn for an
 *                 adjacent room
 */
void set_add_stonebows_bridge_away()
{
    add_item(({"bridge", "baranduin bridge", "brandywine bridge",
            "bridge of stonebows", "bridge of stonebows", "stonebows bridge"}),
        "The bridge crosses the Brandywine river. It is ancient looking, " +
        "built of stones and good masonry that has lasted for many " +
        "ages of the world.\n");
    add_item(({"stone", "stones", "well-crafted stones",
            "well-crafted stone"}),
        "The well-crafted stones are much smaller than the boulders, "+
        "about the size of a large keg of ale.\n");
}

/*
 * Function name : set_add_plains
 * Description   : adds descr of fields along the
 *                 riverbanks of the Brandywine river
 */
void set_add_plains()
{
    add_item(({"field", "level field", "wide field", "wide level field",
            "fields"}),
        "The fields are green and thick. Rich, green grass grows on it. " +
        "They are spongy from frequent floodings of the river. " +
        "Plants grow in abundance on the in the fields.\n");
    set_add_plants();
}


/*
 * Function name : set_add_road
 * Description   : adds descr of road
 */
void set_add_road()
{
    add_item(({"road", "lane", "country lane"}),
        "The country lane is well travelled by hobbits and others travellers. " +
        "It is wide and follows the river as it passes through the fields. " +
        "Plants grow on other side of it.\n");
}

/*
 * Function name : set_add_causeway
 * Description   : adds descr of causeway and road on top of it
 */
void set_add_causeway()
{
    add_item(({"causeway"}),
        "It is a raised road and crosses the fields along the Brandywine " +
        "river. It was built centuries ago and blocks the floods from " +
        "the river from running over the farmlands to the west. \n");
    add_item(({"stone blocks", "stone block", "heavy stone block",
            "heavy block", "heavy stone blocks"}),
        "The stone blocks are dark grey and square shaped. They are " +
        "stacked on top of each other.\n");

}

/*
 * Function name : set_add_causeway
 * Description   : adds descr of
 */
void set_add_causeway_top()
{
    add_item(({"causeway"}),
        "It is a raised road and crosses the fields along the Brandywine " +
        "river. The causeway is as wide as the country lane and looks " +
        "strong. The top of the causeway is faced with heavy stone blocks.\n");
    add_item(({"stone blocks", "stone block", "heavy stone block",
            "heavy block", "heavy stone blocks", "blocks", "stones"}),
        "The stone blocks are dark grey and square shaped. They are " +
        "laid flat and make up the top of the causeway. They are durable " +
        "and look flat from countless years of use.\n");
    add_item(({"fields"}),
        "On either side of the causeway, there are fields. Those on " +
        "the east side look wetter than normal. They look recently " +
        "flooded. The fields on the west look healthy and vibrant, " +
        "and full of life.\n");
    add_item(({"road", "lane"}),
        "The road runs across the top of the causeway. It is wide and " +
        "faced with heavy stone blocks. They are durable and look well " +
        "worn from countless travellers who have used it.\n");
    add_item(({"worn stones"}),
        "They are part of the road, and are now worn smooth from constant " +
        "traffic on the causeway.\n");
    add_item(({"farms", "farmlands", "farm", "farmland"}),
        "They are spread out to the west. They look orderly and well " +
        "cared for. Around each farm you see buildings in the distance.\n");
    add_item(({"buildings"}),
        "They are small and stand in the distance, and are surrounded " +
        "by farms. From up here, it's hard to make out much more " +
        "about them.\n");
    add_item(({"distance"}),
        "There are farms and buildings spread out as far as you can see " +
        "to the west.\n");
}

void down_off_cause()
{
    write("You walk down off the causeway onto a country lane.\n\n");
}


void up_to_cause()
{
    write("You walk up to the top of the causeway.\n\n");
}

