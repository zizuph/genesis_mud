#pragma strict_types

/*
* Middle of west pier of Gont Port
*
* Coded by Porta 971018.
* Ported to the new ship system by Tapakah
*/

inherit "/d/Earthsea/std/room.c";
#include "defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/d/Genesis/gsl_ships/ships.h"
inherit LIBPIER;

object ship, sign;

#define SIGN     "/d/Sparkle/area/sparkle/gsl_ships/circle-line/objs/sign"
static object  sign;

void
reset_room()
{
  /*
    object to = this_object();

    if (!objectp(ship))
    {
	ship = clone_object(ANSALON_LINE + "ship");
	ship->move(to);
	ship->start_ship(0);
    }
  */
}

int
restart_ship()
{
  /*
    if (objectp(ship))
    {
	ship->start_ship(0);
	return 1;
    }
    return 0;
  */
}

void
create_earthsea_room()
{
    set_short("West Pier");
    set_long(break_string("You are standing on the West Pier"+
	" stretching out into the bay of Gont Port and"+
	" everywhere around you can see different kinds of"+
	" ships anchored. This is a very busy harbour with"+
	" a forest of masts swaying back and forth in the"+
	" breeze coming in from the sea. At this pier"+
	" there are mostly traders, but also a few"+
	" passenger ships with far distant destinations."+
	" You hear the sound of hawsers creaking against"+
	" woodwork when the ships rock in the small waves."+
	" A salty smell of sea and fish is in the air.\n", 70));

    add_item("pier", "The pier is built from sturdy timber"+
      " logs, stretching far out in the bay. There are"+
      " many ships anchored along the side, coming from"+
      " different places of the Archipelago.\n");
    add_item("ships","A great number of ships are anchored"+
      " in Gont Port with masts swaying back and forth in"+
      " the small waves coming in. You see galleys, sloops,"+
      " caravels and many other types.\n");
    add_item("masts","The masts are swaying back and forth"+
      " in the breeze.\n");
    add_item("harbour","This is the Port of Gont, a busy"+
      " trading harbour with many ships visiting every"+
      " year.\n");
    add_item("waves","The waves are very small here, finding"+
      " their way through the narrow canal between the Armed"+
      " Cliffs.\n");
    add_item("cliffs","Almost straight south are the Armed"+
      " Cliffs, and between them the canal leading into the"+
      " secluded bay.\n");

    add_exit(CALIA_LINE + "west_pier1.c", "west");
  sign = clone_object(SIGN);
  sign->move(TO);
  reset_room();
  add_pier_entry(MASTER_OB(TO), "Gont", "Pan-Donut Circle");
  initialize_pier();

}
object
query_sign ()
{
  return sign;
}
