#pragma save_binary
#pragma strict_types

inherit "/std/weapon";

#include <formulas.h>
#include <stdproperties.h>
#include <wa_types.h>

public void
create_weapon()
{
    set_name("bat");
    set_short("billy bat");
    set_pshort("billy bats");
    set_adj("well used");
    add_adj( ({"hard", "wooden", "billy", }));
    set_long("It is a hard wooden billy bat.\n");

    set_default_weapon(16, 8, W_CLUB, W_BLUDGEON, 0);

    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(16, 8) + random(41));
}

