// /d/Genesis/start/human/town/pier11.c
// Ported to new ship system, Tapakah, 05/2009

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
  set_short("Berth 11 - Kalad");
  set_long("You are near the east end of the south pier.\n" +
           "Looking east you see another berth before the pier ends" +
           " in nothing but water.\n" +
           "There is a sign here that reads: Berth 11 - Kalad.\n");
  
    add_item(({"sign" }),
             "The sign has text which reads: " +
             "The Sealover to Kabal in Kalad.\n");
    add_cmd_item(({"sign"}), "read", 
                 "The sign has text which reads: " +
                 "The Sealover to Kabal in Kalad.\n");

    add_item(({"water" }),"The waves look foreboding. "+
      "You need a boat to go out there.\n"+
      "");

    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
    add_prop(ROOM_S_MAP_FILE, "sparkle_city_genesis.txt");

    add_exit(TOWN_DIR + "pier10", "west");
    add_exit(TOWN_DIR + "pier12", "east");
    add_pier_entry(MASTER_OB(this_object()), "Sparkle", "Passage to Kabal");
    initialize_pier();
}
