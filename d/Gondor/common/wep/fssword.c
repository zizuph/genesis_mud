/* shortsword on the ground  */
inherit "/std/weapon";

#include <formulas.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>

public void
create_weapon() 
{
    set_name(({"shortsword","sword", }));
    set_pname("shortswords");
    set_pname("swords");
    set_short("shortsword");
    set_pshort("shortswords");
    set_adj("short");
    set_long(break_string("This shortsword looks as if it has seen hard use, "+
             "and it was of crude quality to begin with - probably "+
             "orc made.", 75) + "\n");
    set_default_weapon(12, 8, W_SWORD, W_SLASH|W_IMPALE, W_ANYH, 0);
    add_prop(OBJ_I_WEIGHT, 2300);
    add_prop(OBJ_I_VOLUME,  700);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(12,8)+random(10)-5);

    set_dull(2);
}
