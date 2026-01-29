/*
 * Test Pier for Genesis ShipLines
 *
 * Created by Petros, April 2009
 */

#pragma save_binary
#pragma strict_types

#include <stdproperties.h>      
#include <macros.h>                                             
#include "../ships.h"

inherit STDPIER;

public void
create_pier()
{
	set_short("Test Pier One");
	set_long("This pier is available for testing.\n");

    add_pier_entry(MASTER_OB(this_object()), "Port One", "Port to Port Two");
}
