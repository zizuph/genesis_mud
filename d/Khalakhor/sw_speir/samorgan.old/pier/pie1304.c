/**********************************************************************
 * - pie01304.c                                                     - *
 * -                                                                - *
 * - Created by Damaris@Genesis 07/Y2K                              - *
 * - ReCoded by Damaris@Genesis 03/2005                             - *
 **********************************************************************/
#pragma strict_types

#include <macros.h>
#include "../defs.h"
#include "/d/Genesis/gsl_ships/ships.h"

inherit PIER_ROOM;

void add_stuff();

object ship;
object sign;

public int *
query_local_coords()
{
    return ({1, 5});
}

public void
create_pier()
{
	add_exit("pie1305", "east");
  add_pier_entry(MASTER_OB(TO), "Sa Morgan", "Route to Cadu");
  initialize_pier();
	
	/* ensure other pier loaded, ship on way */
	//("/d/Khalakhor/ship/macdunn/pier14")->get_this_object();
	//add_stuff();
}

public void
add_stuff()
{
	seteuid(getuid(this_object()));
	if (!sign)
	{
		sign = clone_object("/d/Khalakhor/sw_speir/samorgan/obj/macsign");
		sign->move(this_object());
	}
}
