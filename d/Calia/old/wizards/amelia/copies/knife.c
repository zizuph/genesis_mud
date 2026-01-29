/*
 * Knife coded by Lord Rastlin
 */

inherit "/std/weapon";

#include <wa_types.h>
#include <stdproperties.h>

nomask
create_weapon() 
{
    set_name("knife");
    set_adj("shining");
    set_short("shining knife");
    set_long("It is a shining knife, but it is\n"
	     + "quite heavy for a knife.\n");
    set_default_weapon(10, 10, W_KNIFE, W_IMPALE, W_ANYH);
    set_alarm(2.0,0.0,"add_prop",OBJ_I_WEIGHT,1400);
    add_prop(OBJ_I_VOLUME,450);
}
