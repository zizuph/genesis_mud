#pragma save_binary
#pragma strict_types

inherit "/std/weapon";

#include <formulas.h>
#include <stdproperties.h>
#include <wa_types.h>

public void
create_weapon()
{
    set_name("dagger");
    add_name("knife");
    set_pname(({"daggers", "weapon", "knives", }));
    set_short("sharp dagger");
    set_adj("sharp");
    add_adj("metal");  /* added by Gorboth, July 2007 */
    set_long("It is a sharp dagger with a long thin blade.\n");
    
    set_default_weapon(12, 12, W_KNIFE, W_IMPALE);

    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(12, 12) + random(41));
}
