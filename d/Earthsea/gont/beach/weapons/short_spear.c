#pragma strict_types

inherit "/std/weapon";
 
#include <wa_types.h>
#include <stdproperties.h>
 
public void
create_weapon()
{
    set_name("spear");
    set_adj("short");
    set_adj("flint");
    set_short("short flint spear");
    set_pshort("short flint spears");
    set_long("A short spear with a knapped flint spearhead.\n");
    set_default_weapon(15, 20, W_POLEARM, W_IMPALE|W_SLASH, W_ANYH);
    add_prop(OBJ_I_WEIGHT, 2500);
    add_prop(OBJ_I_VALUE, 150);
}
