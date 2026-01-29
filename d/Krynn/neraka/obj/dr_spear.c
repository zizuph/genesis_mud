inherit "/std/weapon";
#include <wa_types.h>
#include <stdproperties.h>
#include <formulas.h>
#include <macros.h>

void
create_weapon()
{
    set_name("spear");
    set_adj("nasty");
    set_short("nasty spear");
    set_default_weapon(16, 15, W_POLEARM, W_IMPALE, W_ANYH);
    set_long("A steel spear with one pointed end.\n");
    add_prop(OBJ_I_VOLUME, 450);
}

