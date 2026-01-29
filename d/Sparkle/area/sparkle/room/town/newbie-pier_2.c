/*
 * Newbie pier (there will be four of them) of Sparkle
 * Tapakah, 05/2009
 */

#include <macros.h>

#pragma save_binary
#pragma strict_types

#include <stdproperties.h>   /* for ROOM_S_MAP_FILE, etc */
#include "defs.h"
#include "/d/Genesis/gsl_ships/ships.h"

inherit STDPIER;

#define TOWN_DIR "/d/Genesis/start/human/town"

void
create_pier ()
{
  set_short("Berth B - Newbie line to Port Macdunn and Grey Havens");
  set_long("\n"+
           "This is the north pier.\n"+
           "This recently constructed pier is the extension of the old "+
           "north pier. The service that runs here is a circle line "+
           "helping new players around the donut.\n"+
           "To the far west you see the old pier and the town of Sparkle. "+
           "Across the water to the south you see a very long pier "+
           "from which numerous ships are departing to all destinations "+
           "around the realms. Far to the east you see a jetty.\n");
  add_item(({"pier" }),
           "If there is a prominent part of the harbour and pier,\n"+
           "this is it. The north pier is by far the cleanest and\n"+
           "best maintained part of the harbour.\n");
  add_item(({"jetty" }),
           "Go have a look. It is a quite scenic place.\n");

  add_exit("newbie-pier_1", "west");
  add_exit("newbie-pier_3", "east");

  add_prop(ROOM_I_TYPE, ROOM_NORMAL);
  //add_prop(ROOM_S_MAP_FILE, "sparkle_city_current.txt");

  add_pier_entry(MASTER_OB(this_object()), "Sparkle", "Newbie Line B");
  initialize_pier();
  
}
