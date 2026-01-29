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
  set_short("Berth 7 - Emerald");
  set_long("\n"+
           "This is the south pier.\n"+
           "The seabirds swoop and swerve just beyond reach of the" +
           " edge of the pier. Slowly they circle over the water, their" +
           " wings gliding on the breeze keeping a sharp lookout" +
           " for tasty tidbits to eat. The pier continues east.\n" +
           "South from here a new building is erected.\n");
  
  add_item(({"sea", "water" }),
	  "Pieces of fish and other leftovers from the fishermen's\n"+
	  "boats are floating in the water. It makes it less inviting\n"+
      "to swim around in, unless you're a seagull.\n");
  add_item(({"birds","bird","seagull","seagulls" }),
	  "The seagulls are quite busy trying to get the best pieces of fish\n"+
      "and their shrieks are quite deafening.\n");
  add_item(({"building","house","structure"}),
      "You see a large stone building with a big banner over it.\n");
  add_item(({"banner"}),"The banner reads: Genesis ShipLines Company\n");
  
  add_exit(TOWN_DIR + "pier6", "west");
  add_exit(TOWN_DIR + "pier8", "east");
  add_exit("/d/Sparkle/area/city/shiplines/office/entrance", "south",);// gs_not_open_yet);
  add_prop(ROOM_I_INSIDE, 0);
  add_prop(ROOM_I_TYPE, ROOM_NORMAL);
    add_prop(ROOM_S_MAP_FILE, "sparkle_city_genesis.txt");

  add_pier_entry(MASTER_OB(this_object()), "Sparkle", "Pier to Emerald");
  initialize_pier();
}
