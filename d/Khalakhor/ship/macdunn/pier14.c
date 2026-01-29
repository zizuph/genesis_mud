/* File:          /d/Khalakhor/ship/macdunn/pier14.c
 * Creator:       Damaris
 * Date:          03/2001
 * Modifications:
 * Purpose:       This is the pier for the Khalakhor to SaMorgan
 *                ship.
 * Related Files: /d/Khalakhor/ship/macdunn/
 *                /d/Khalakhor/ship/macdunn/samorgan/
 *                /d/Khalakhor/ship/macdunn/std/pier_base.c
 *                /d/Khalakhor/open/SHIPLINES
 * Comments:
 */

#pragma save_binary
#pragma strict_types

inherit "/d/Khalakhor/ship/macdunn/std/pier_base";
#include "local.h"
#include <stdproperties.h>
#include "/d/Khalakhor/sys/paths.h"
void add_stuff();

object ship;
object sign;
object bird;

public int *
query_local_coords()
{
    return ({8, 17});
}

public void
create_pier()
{
	add_cmd_item(({"into the harbour","in the harbour","in cala fasgadh","into cala fasgadh","into the ocean","into ocean","into the water", "into water","harbour","cala fasgadh","water","off the pier", "off pier"}),({"jump","dive"}),"@@go_tide1");

        add_prop(ROOM_I_NO_CLEANUP,1);
        add_prop(OBJ_S_WIZINFO,"To restart the ship, ONLY if it is "+
        "stuck, type: 'Call here restart_ship <reason>'.\nThis is the "+
        "starting room for the SaMorgan ship.\n");
        add_exit(MACDUNN_DIR + "pier15", "east",0,0);
        
        bird = clone_object(COM_WILDLIFE + "gull");
        bird->set_restrain_path(MACDUNN_DIR);
        bird->move(this_object(), 1);
        add_stuff();
}

public void
add_stuff()
{
	seteuid(getuid(this_object()));
  /*
	if (!ship)
	{
		ship = clone_object(SHIPS + "macdunn/samorgan/ship");
		ship->start_ship();
	}
  */
	if (!sign)
	{
		sign = clone_object(SHIPS + "macdunn/samorgan/sign");
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
        + " Madunn - SaMorgan " + capitalize(this_player()->query_real_name())
        + " " + reason + "\n");
        write("Ship restarted.\n");
}
