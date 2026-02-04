/*
 * Calathin Townhouse 1 Key
 *
 * Lilith March 2022
 *
 */

#pragma strict_types
#pragma save_binary 

#include <files.h>      
#include <macros.h>      
#include <std.h>           
#include <stdproperties.h>
#include "../calathin1/h1.h"    

inherit HOUSE_KEY;

public void
create_key()
{
    ::create_key();

    set_name("key");
    add_name( ({HOUSE_NAME}) );
    set_adj("iron");
    add_adj(({"townhouse", "house"}));
    set_long("This appears to be a key to your house " +
        "in western Calathin.\n");
    set_key(HOUSE_NAME);

    // This needs to match the name in the house data manager.
    set_house_name(HOUSE_NAME);
}

