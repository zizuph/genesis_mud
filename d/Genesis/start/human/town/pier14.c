// /d/Genesis/start/human/town/pier14.c
// Ported to the new ship system by Tapakah, 10/2008

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
    set_short("Berth 14 - Golden Island");
    set_long("\n"+
             "You are at the east end of the south pier.\n" +
             "The sea is lapping gently beneath you in rippling patterns.\n"+
             "It seems to you that the sea here has some special golden hue.\n"
             );

    add_item(({"water" }),"The waves look foreboding. "+
      "You need a boat to go out there.\n"+
      "");

    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
    add_prop(ROOM_S_MAP_FILE, "sparkle_city_genesis.txt");

    add_exit(TOWN_DIR + "pier15", "east");
    add_exit(TOWN_DIR + "pier13", "west"); 

    add_pier_entry(MASTER_OB(this_object()), "Sparkle", "Pier to Golden Island");
}
