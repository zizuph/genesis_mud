#pragma strict_types

inherit "/d/Earthsea/std/room.c";

#include "defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"


#define PIER2 "/d/Earthsea/ships/sparkle_line/east_pier2.c"
#define CITYROOM21 GONT_CITY + "city_road21"

object ship;
object sign;


int
restart_ship()
{
  // ship->start_ship(0);
}

void
reset_room()
{
  /*
    object to = this_object();
    if (!objectp(ship))
    {
	ship = clone_object(AVENIR_LINE + "ship");
	ship->move(to);
	ship->start_ship(0);
    }
  */
}


void
create_earthsea_room()
{
    add_prop(ROOM_S_MAP_FILE, "earthsea_map.txt");
    set_short("Halfway out on the East Pier");
    set_long(break_string("This is the east pier of"+
	" Gont Port, resting on sturdy timber logs bolted"+
	" far down in the bottom of the sea. The busy"+
	" harbour is all around you, with many ships"+
	" anchored at the three major piers and smaller"+
	" crafts by the shore. Hundreds of masts sway"+
	" back and forth in the rhythm of the small waves"+
	" coming in through the narrow canal between the"+
	" high cliffs guarding the entrance to the bay."+
	" A fresh breeze comes from the south, bringing"+
	" the salty smell of the sea.\n", 70));

    add_item("canal", "The canal leads through the high cliffs into the bay.\n");
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
    add_item("cliffs","To the southwest are the famed Armed"+
      " Cliffs, guarding the entrance to the secluded harbour"+
      " basin. You can see a tower built on the top of each"+
      " cliff.\n");
    add_item("masts","A forest of high masts sway back and"+
      " forth in the rhytm of the small waves.\n");
    sign = clone_object(AVENIR_LINE + "sign1");
    sign->move(TO);

    add_exit(CITYROOM21, "east");
    add_exit(PIER2, "west");
    reset_room();
}
