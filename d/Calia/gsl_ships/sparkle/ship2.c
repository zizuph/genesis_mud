/*
 * Ship between Sparkle and Gelan in Calia
 *
 * New Genesis ShipLine ship ported from the old ship system.
 * Experimental double ship per line
 *
 * Created by Petros, April 2009
 */

#pragma save_binary
#pragma strict_types

#include <macros.h>
#include "ship.h"

inherit STDSHIP;

public void
create_ship()
{
    ::create_ship();

    set_ship_line(MASTER_OB(this_object()), 
                  CALIA_GSL_DIR + "captain2",
                  CALIA_GSL_DIR + "ticket", 
               ({ SPARKLE_PORT, 
                  GELAN_PORT }) );
                          
    if (!IS_CLONE)
    {
        return;
    }
    
    setuid();
    seteuid(getuid());
    
    set_cabin(CALIA_GSL_DIR + "cabin2");
    set_deck(CALIA_GSL_DIR + "deck2");

	set_name("ship");
	add_name("boat");
	add_adj("swift");
	add_adj("green");
	set_long("The sloop is painted a bright green. Its elegant design "+
		"tells you that it must be very swift. The triangular "+
		"white sail contains a figure of a green dolphin.\n");    
}
