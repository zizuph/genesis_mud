/* 
* /d/Gondor/lorien/dimrill/rooms/road8.c
* On the road just south of Durins Stone and north of the Silverlode
* Between the Great gates of Moria to the northwest and the forest 
* of Lothlorien in the east.
*
*Mona 2020
*/
#pragma strict_types

#include "../../lorien_defs.h"
#include <stdproperties.h>
#include <macros.h>

inherit LORIEN_STD_DIR + "dimrill_base";

void 
create_dimrill_room()
{
    set_items_all_dimrill();
    set_items_near_dimrill();
    set_items_mereafar();
    set_tells_dimrill(); 

    set_short("Along a road between mountain and valley");
    set_long("As the road climbs to the north, " + VBFC("light_type") + " "+
    "reflects off of the surface of a pond or mere in the distance. The " +
    "road continues through the valley and towards the entrance to Moria, " +
    "which glares down from atop a mountain to the northwest. To the " +
    "southeast a new stream tumbles along side the road as it winds its " +
    "way south and eastward from here\n"); 
    add_item( ({"start of stream", "start of the stream", "stream start",
        "stream head", "head of stream", "head of the stream", "water",
        "head", "new stream"}),
        "The water appears to be pouring out of the some rocks to the " +
        "southwest, forming a swiftly flowing stream.\n");
    add_item( ("rocks"), "It is too hard to see much about them from this " +
        "distance.\n");
    add_item( ("stream"), "The stream flows to the south and east, making " +
        "a soft scraping purr of rushing water.\n");
    add_item( ({"entrance", "entrance moria", "entrance to moria",
        "moria entrance"}),
        "You can see the great gates from here.\n");

    add_exit(DIMRILL_DIR_RM + "road7", "north", 0, 3, 0);
    add_exit(DIMRILL_DIR_RM + "see_silverlode", "south", 0, 1, 0);

    

//add body of water	 
// add mereafar
// add orc patrols through here
//add tour
}