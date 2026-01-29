/* Weapon coded by Arren, April 94 */ 

inherit "/std/weapon";
inherit "/lib/keep.c";

#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <formulas.h>
#include "/d/Gondor/defs.h"

void
create_weapon()
{
    set_name("battle-axe");
    set_pname("battle-axes");
    add_pname("axes");
    add_pname("battleaxes");
    add_name(({ "axe", "battleaxe" }));
    set_adj(({ "black", "battle" }));
    set_short("black battle-axe"); 
    set_long(BSN("An axe with a metal reinforced wooden shaft, and a "+
        "black blade."));

    set_default_weapon(21, 28, W_AXE, W_SLASH, W_ANYH, 0);
    
    add_prop(OBJ_I_VOLUME, 900);  
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(21,28)+random(150)-75);
}
