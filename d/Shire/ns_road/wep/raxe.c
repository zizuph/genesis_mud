/*
 * Weapon used by Ruffian
 * -- Finwe, February 2020
 */
inherit "/std/weapon";
#include "/d/Shire/sys/defs.h"
#include <macros.h>
#include <stdproperties.h>
#include <formulas.h>
#include <wa_types.h>


void
create_weapon()
{
    set_name(({"axe"}));
    set_pname(({"axes"}));
    set_short("heavy axe");
    set_pshort("heavy axes");
    set_adj(({"sturdy", "long"}));
    add_adj("metal"); 
    set_long("This is a heavy axe . It is sturdy with a single blade " +
        "on each side of the top of the handle. The handle is wrapped " +
        "in leather to give the wielder a better grip. The blades are " +
        "chipped from usage but still look sharp.\n");

    set_hit(29);
    set_pen(25);
    set_wt(W_AXE);
    set_dt(W_SLASH | W_BLUDGEON);
    set_hands(W_ANYH);

    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(29,25));
}
