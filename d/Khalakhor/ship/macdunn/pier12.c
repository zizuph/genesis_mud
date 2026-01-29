/* File:          /d/Khalakhor/ship/macdunn/pier12.c
 * Creator:       Teth
 * Date:          September 7, 1997
 * Modifications:
 * Purpose:       This is the pier for the Khalakhor to Shire
 *                ship.
 * Related Files: /d/Khalakhor/ship/macdunn/
 *                /d/Khalakhor/ship/macdunn/shire/
 *                /d/Khalakhor/open/SHIPLINES
 *                /d/Khalakhor/ship/macdunn/std/pier_base.c
 *                /d/Khalakhor/ship/macdunn/peat.c
 * Comments:
 * Ported to the new ship system by Tapakah, 04/2009
 */

#pragma save_binary
#pragma strict_types

#include <macros.h>
#include "local.h"
#include <stdproperties.h>
#include "/d/Genesis/gsl_ships/ships.h"

inherit "/d/Khalakhor/ship/macdunn/std/pier_base";

void add_stuff();

object ship;
object sign;
object bale;

public int *
query_local_coords()
{
    return ({10, 15});
}

public void
create_pier()
{
    add_cmd_item(({"into the harbour","in the harbour","in cala fasgadh",
        "into cala fasgadh","into the ocean","into ocean","into the water",
        "into water","harbour","cala fasgadh","water","off the pier",
        "off pier"}),({"jump","dive"}),"@@go_tide2");

    add_prop(ROOM_I_NO_CLEANUP,1);
    add_prop(OBJ_S_WIZINFO,"To restart the ship, ONLY if it is stuck, type " +
      "'Call here restart_ship <reason>'.\nThis is the starting " +
      "room for the Shire <Grey Havens> ship.\n");    

    add_exit(MACDUNN_DIR + "pier11", "west",0,0);

    bale = clone_object("/d/Khalakhor/ship/macdunn/peat.c");
    bale->move(this_object(), 1);

  add_pier_entry(MASTER_OB(TO), "Port Macdunn", "Line to Cadu");
  initialize_pier();
    //add_stuff();
}

public void
add_stuff()
{
    seteuid(getuid(this_object()));
    if (!ship)
    {
        ship = clone_object(MACDUNN_DIR + "shire/ship");
        ship->start_ship();
    }
    if (!sign)
    {
        sign = clone_object(MACDUNN_DIR + "shire/sign");
        sign->move(this_object());
    }
}

public void
restart_ship(string reason)
{
    if (!reason)
    {
        write("You need a reason to restart a ship!\n");
        return 0;
    }
    (ship->query_captain())->remove_object();
    ship->remove_object();
    add_stuff();
    write_file("/d/Khalakhor/log/shiprestart", extract(ctime(time()), 4, 15)
      + " Macdunn-Grey Havens " 
      + capitalize(this_player()->query_real_name())
      + " " + reason + "\n");
    write("Ship restarted.\n");
}
