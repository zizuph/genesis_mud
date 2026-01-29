/* 
* North pier.
*
* Coded by Porta 971121.
* Line changed to newbie line Kalad/Gont, Tapakah, 05/2009
*/

#pragma strict_types
#pragma no_clone

#include <stdproperties.h>
#include <macros.h>
#include "/d/Genesis/gsl_ships/ships.h"

inherit STDPIER;

public void
create_room()
{
    add_prop(ROOM_S_MAP_FILE, "earthsea_map.txt");
    set_short("Halfway out on the North Pier");
    set_long("This is the north pier of"+
        " Gont Port, resting on sturdy timber logs bolted"+
        " far down in the bottom of the sea. The busy"+
        " harbour is all around you, with many ships"+
        " anchored at the three major piers and smaller"+
        " crafts by the shore. Hundreds of masts sway"+
        " back and forth in the rhythm of the small waves"+
        " coming in through the narrow canal between the"+
        " high cliffs guarding the entrance to the bay."+
        " A fresh breeze comes from the south, bringing"+
        " the salty smell of the sea.\n");
    add_item("pier","The pier is very long, stretching"+
        " far out into the bay. It is resting on sturdy"+
        " timber logs bolted far down into the bottom of the"+
        " sea, connected with wooden boards.\n");
    add_item("logs","Looking down the side of the pier"+
        " you can see the sturdy timber logs it is resting"+
        " on.\n");
    add_item("ships","Many ships are anchored in this"+
        " harbour. At this particular pier you can see"+
        " mostly traders, coming from the southern part of"+
        " the Archipelago carrying silk and spices but also"+
        " a few passenger ships allowing journeys far abroad"+
        " to different countries.\n");
    add_item("harbour","The great Port of Gont is all around"+
        " you, busy with many traders loading and unloading"+
        " their goods here. You believe that there are at least"+
        " a hundred ships anchored in the harbour for the moment.\n");
    add_item("water","The grey sea water is below you, and looks"+
        " very cold.\n");
    add_item("cliffs","To the southeast are the famed Armed"+
        " Cliffs, guarding the entrance to the secluded harbour"+
        " basin. You can see a tower built on the top of each"+
        " cliff.\n");
    add_item("masts","A forest of high masts sway back and"+
        " forth in the rhytm of the small waves.\n");
    add_exit("city_street/city_road17", "north");
    add_exit("north_pier2", "south");
    add_pier_entry(MASTER_OB(this_object()), "Gont", "Newbie Line C");
    initialize_pier();
}

