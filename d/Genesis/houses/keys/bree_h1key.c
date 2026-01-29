/*
 * BREEDOOR + h1door_in.c
 *
 * Varian - Feb 2020
 *
 */

#pragma strict_types
#pragma save_binary 


#include <files.h>      
#include <macros.h>      
#include <std.h>           
#include <stdproperties.h>
#include "../defs.h"    

inherit HOUSE_KEY;

public void
create_key()
{
    ::create_key();

    set_name("key");
    add_name( ({"bree_h1_key", "bree key"}) );
    set_adj("iron");
    set_long("This appears to be a key to your townhouse " +
        "in the village of Bree.\n");
    set_key("bree_h1_key");

    // This needs to match the name in the house data manager.
    set_house_name("bree1");
}

