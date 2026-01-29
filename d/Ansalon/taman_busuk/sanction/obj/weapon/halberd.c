inherit "/std/weapon";
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>

create_weapon()
{
    set_name("halberd");
    set_adj("rusty");
    add_adj("old");
    set_short("rusty old halberd");
    set_long("This long steel weapon might once have been impressive, but it " +
             "has been left without care for too long. A worm eaten pole with an " +
             "axe-like blade made of rusty steel attached to the end of it.\n");
    set_default_weapon(22,38, W_POLEARM, W_SLASH|W_IMPALE, W_BOTH);
    add_prop(OBJ_I_VOLUME, 2000);
    add_prop(OBJ_I_WEIGHT, 10000);
}
