#pragma save_binary
#pragma strict_types

#include <stdproperties.h>
#include <macros.h>

#include "../defs.h"
#include "/d/Genesis/gsl_ships/ships.h"

inherit STDPIER;

void
create_pier()
{
  ::create_pier();
    set_short("Berth 1 - Earthsea Gont Port");
    set_long("\n"+
      "This is the prominent north pier.\n"+
      "Ships from far away shores have found a calm place to ride out\n" +
      "many a storm lying here by this very pier. You see a warehouse\n" +
      "to the north and a jetty far to the east.\n"+
	  "There is a sign here that reads: Berth 1 - Gont.\n" +
      "To the immediate east construction works have been started.\n");

    add_item(({"warehouse" }),
		"It looks strong and sturdy.\n");
    add_item(({"pier" }),
		"If there is a prominent part of the harbour and pier,\n"+
		"this is it. The north pier is by far the cleanest and\n"+
		"best maintained part of the harbour.\n");
    add_item(({"jetty" }),
		"Go have a look. It is a quite sceenic place.\n");

    add_exit(TOWN_DIR + "ware4","north");
    add_exit(TOWN_DIR + "pier2","west");
    add_exit("/d/Sparkle/area/sparkle/room/town/newbie-pier_1","east");
             

    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
    add_prop(ROOM_S_MAP_FILE, "sparkle_city_genesis.txt");

  add_pier_entry(MASTER_OB(this_object()), "Sparkle", "Pier to Gont, Earthsea");
  initialize_pier();
}

