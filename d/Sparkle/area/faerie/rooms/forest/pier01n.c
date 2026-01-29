/*
 * The pier for the Vingaard Keep shipline for Faerie
 * By Finwe, April 2005
 * Utilized for Pan-Donut Circle line, Tapakah, 05/2009
 */
 
#include "defs.h"
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
 
inherit BEACH_BASE;
inherit "/d/Genesis/gsl_ships/lib/pier";

#define SIGN     "/d/Sparkle/area/sparkle/gsl_ships/circle-line/objs/sign"
static object  sign;

void
create_beach_room()
{
    setuid();
    seteuid(getuid());
    add_prop(ROOM_S_MAP_FILE, "faerie_map_east.txt");

    set_short("A long wooden pier");
    set_long(short() + ". " + s_desc_sky_outside_sky() + "It extends north " +
        "out into the lake. The pier is worn from " +
        "many travellers who come this way. A sign is set at one end " +
        "of the pier.\n" );

    add_prop(ROOM_I_NO_CLEANUP, 1);


    reset_room();
   
    set_add_beach();
    set_add_forest();
    set_pier_top();
    
    add_exit(FOREST_DIR + "landing",  "south");
  sign = clone_object(SIGN);
  sign->move(TO);
  add_pier_entry(MASTER_OB(TO), "Faerie", "Pan-Donut Circle");
  initialize_pier();
}

void
reset_room()
{
  // start_ship(0);
}


object
query_sign ()
{
  return sign;
}
/*
string read_sign()
{
    return "On the sign, painted in the common tongue, you read:\n\n" +
    "    Ship to Vingaard Keep\n" + 
    "    Fare is 30 copper coins\n" + 
    "    Youngsters travel for free\n\n";
    }*/
