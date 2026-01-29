/*
 * Broken bottle by Teth Feb.15,96
 * modified from knife coded by Rastlin
 */

inherit "/std/weapon";

#include <wa_types.h>
#include <stdproperties.h>

nomask
create_weapon() 
{
    set_name("bottle");
    add_name("knife");
    set_adj("broken");
    set_short("broken bottle");
    set_pshort("broken bottles");
    set_long("Apparently someone had one too many bottles of wine " +
	     "and broke this piece of glassware. It is a dirty green " +
             "colour with sharp jagged edges. It might be usable as " +
             "a knife.\n");
    set_default_weapon(7, 12, W_KNIFE, W_IMPALE, W_ANYH);
    set_alarm(2.0,0.0,"add_prop",OBJ_I_WEIGHT,800);
    add_prop(OBJ_I_VOLUME,775);
}
