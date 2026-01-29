#pragma save_binary
#pragma strict_types

inherit "/std/weapon";

#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>

void
create_weapon()
{
    set_name("knife");
    set_pname("knives");
    set_adj("newbie");
    set_short("newbie knife");
    set_pshort("newbie knives");

    set_adj("tiny");

    set_hit(5);
    set_pen(4);
    set_wt(W_KNIFE);
    set_dt(W_IMPALE | W_SLASH);
    set_hands(W_NONE);
    add_prop(OBJ_I_WEIGHT, 200);
    add_prop(OBJ_I_VOLUME, 75);
  
    set_long("This is a newbie knife. It has no real value to anyone\n"+
	     "but a real newbie. It's not a great weapon but its\n"+
	     "better than nothing at all...\n");

    add_prop(OBJ_I_VALUE, 1);
    add_prop(OBJ_I_WEIGHT, 201); 
}
