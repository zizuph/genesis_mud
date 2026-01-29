
/*
	coded by Amelia for use on the Calian beach

        It's found if one searches the rocks there on the 
        room beach1. Last revised by Maniac 15/8/96
*/

inherit "/std/weapon";

#include <wa_types.h>
#include <stdproperties.h>

nomask
create_weapon() 
{
    set_name("knife");
    set_pname("knives");
    set_adj("fishing");
    add_adj("sharp");
    set_short("sharp fishing knife");
    set_long("This is a knife used by fishermen. It is "+
		"very sharp. The hilt of the knife is covered "+
		"in small sea shells of many colours.\n");
    set_default_weapon(10, 10, W_KNIFE, W_SLASH, W_ANYH);
    add_prop(OBJ_I_VOLUME,450);
    add_prop(OBJ_I_WEIGHT,1400);
    add_prop(OBJ_I_VALUE, 100);
}

