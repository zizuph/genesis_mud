inherit "/std/weapon";
inherit "/lib/keep";
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>

create_weapon()
{
    set_name(({"sword","rapier","weapon"}));
    set_adj("thin");
    set_short("thin rapier");
    set_long("This thin steel rapier is typical of the sort of weapon " +
      "nobles all over Ansalon carry. Light and quick to strike, in the hands of " +
      "a master it can fill a foe full of holes in no time.\n");
    set_default_weapon(30, 18, W_SWORD, W_IMPALE, W_ANYH);
    add_prop(OBJ_I_VOLUME, 3600);
    add_prop(OBJ_I_WEIGHT, 2500);
}
