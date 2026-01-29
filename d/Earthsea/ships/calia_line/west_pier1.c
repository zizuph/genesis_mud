#pragma strict_types

/* 
* The west pier of Gont Port.
*
* Coded by Porta 971017.
*/


inherit "/d/Earthsea/std/room.c";

#include "defs.h"
#include <stdproperties.h>


object ship;
object sign;


void
reset_room()
{
  /*
    object to = this_object();

    if (!objectp(ship))
    {
	ship = clone_object(CALIA_LINE + "ship");
	ship->move(to);
	ship->start_ship(0);
    }
  */
}

int
restart_ship()
{
  //ship->start_ship(0);
}

void
create_earthsea_room()
{
    add_prop(ROOM_S_MAP_FILE, "earthsea_map.txt");
    set_short("Halfway out on the West Pier");
    set_long(break_string("This is the west pier of"+
	" Gont Port, resting on sturdy timber logs bolted"+
	" far down in the bottom of the sea. The busy"+
	" harbour is all around you, with ships"+
	" anchored by the three major piers and smaller"+
	" crafts by the shore. Hundreds of masts sway"+
	" back and forth in the rhythm of the small waves"+
	" coming in through the narrow canal between the"+
	" steep cliffs guarding the entrance to the bay."+ 
	" Located around the harbour is a large city,"+
	" with many stone buildings and high towers."+
	" A fresh breeze comes from the south, bringing"+
	" the salty smell of the sea.\n", 70));

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
      " forth in the rhythm of the small waves.\n");

    add_exit(GONT_CITY + "city_road14.c", "west");
    add_exit(ANSALON_LINE + "west_pier2", "east");
    reset_room();

    sign = clone_object(CALIA_LINE + "sign1");
    sign->move(this_object());

}
