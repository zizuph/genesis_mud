/* File:          /d/Khalakhor/ship/macdunn/pier2.c
 * Creator:       Teth
 * Date:          September 7, 1997
 * Modifications:
 * Purpose:       This is the pier for the Khalakhor to Ansalon
 *                ship.
 * Related Files: /d/Khalakhor/ship/macdunn/
 *                /d/Khalakhor/ship/macdunn/ansalon/
 *                /d/Khalakhor/open/SHIPLINES
 *                /d/Khalakhor/ship/macdunn/std/pier_base.c
 * Comments:
 * Ship rerouted to tabor sogh and uses another pier now
 * Tapakah, 05/2009
 * Pier now involved in Pan-Donut Circle Line, Tapakah, 05/2009
 */

#pragma save_binary
#pragma strict_types

#include "local.h"
#include <stdproperties.h>
#include <macros.h>
#include "/d/Genesis/gsl_ships/ships.h"

inherit "/d/Khalakhor/ship/macdunn/std/pier_base";

#define SIGN     "/d/Sparkle/area/sparkle/gsl_ships/circle-line/objs/sign"
static object  sign;

public int *
query_local_coords()
{
    return ({8, 11});
}

public void
create_pier()
{
    add_cmd_item(({"into the harbour","in the harbour","in cala fasgadh",
        "into cala fasgadh","into the ocean","into ocean","into the water",
        "into water","harbour","cala fasgadh","water","off the pier",
        "off pier"}),({"jump","dive"}),"@@go_tide1");

    add_prop(ROOM_I_NO_CLEANUP,1);

    add_exit(MACDUNN_DIR + "pier3", "east",0,0);

  sign = clone_object(SIGN);
  sign->move(TO);
  reset_room();
  add_pier_entry(MASTER_OB(TO), "Port Macdunn", "Pan-Donut Circle");
  initialize_pier();
}

object
query_sign ()
{
  return sign;
}

/*
public void
add_stuff()
{
    seteuid(getuid(this_object()));

    if (!sign)
    {
        sign = clone_object(MACDUNN_DIR + "ansalon/sign");
        sign->move(this_object());
    }
    }*/
