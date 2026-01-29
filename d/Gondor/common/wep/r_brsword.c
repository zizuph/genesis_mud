inherit "/std/weapon";

#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>
#include <formulas.h>

#include "/d/Gondor/defs.h"

public void
create_weapon()
{
    set_name("broadsword");
    add_name("sword");
    set_pname("broadswords");
    add_pname("swords");
    set_adj( ({"steel", "elven", "fine" }) );
    set_short("steel broadsword");
    set_pshort("steel broadswords");
    set_long("This solid steel broadsword was crafted by elves, and looks like\n"+
        "a very fine weapon.\n");
    set_default_weapon(24,30,W_SWORD,W_SLASH | W_IMPALE,W_NONE,0);
    add_prop(OBJ_I_WEIGHT, 5000);
    add_prop(OBJ_I_VOLUME, 600);
    add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(24,30) + random(150) - 75);
    add_prop(GONDOR_M_RANGERS_NO_SELL,1);
}

