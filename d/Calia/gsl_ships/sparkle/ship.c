/*
 * Ship between Sparkle and Gelan in Calia
 *
 * New Genesis ShipLine ship ported from the old ship system.
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
                  CALIA_GSL_DIR + "captain",
                  CALIA_GSL_DIR + "ticket", 
               ({ GELAN_PORT, 
                  SPARKLE_PORT }) );
                          
    if (!IS_CLONE)
    {
        return;
    }
    
    setuid();
    seteuid(getuid());
    
    set_cabin(CALIA_GSL_DIR + "cabin");
    set_deck(CALIA_GSL_DIR + "deck");

	set_name("ship");
	add_name("boat");
	add_adj("swift");
	add_adj("blue");
	set_long("The sloop is painted a bright blue. Its elegant design "+
		"tells you that it must be very swift. The triangular "+
		"white sail contains a figure of a blue dolphin.\n");    
}
