/*
 * Test Ship for the Genesis ShipLine
 *
 * Example ship to show how easy it is to create a shipline.
 * The two most important things in this file are the set_deck
 * and the set_ship_line calls. 
 *
 * Created by Petros, April 2009
 */

#pragma save_binary
#pragma strict_types

#include <macros.h>
#include "../ships.h"

inherit STDSHIP;

public void
create_ship()
{
    ::create_ship();

    set_ship_line(MASTER_OB(this_object()), 
                  SHIP_DIR + "example/captain",
                  SHIP_DIR + "example/ticket", 
                  ({ SHIP_DIR + "example/pier_1", 
                     SHIP_DIR + "example/pier_2"}) );
                          
    if (!IS_CLONE)
    {
        return;
    }
    
    setuid();
    seteuid(getuid());
    
    set_deck(SHIP_DIR + "example/deck");

	set_name("ship");
	add_name("boat");
    add_adj("test");
	set_long("This is a test ship for the Genesis ShipLine.\n");    
}
