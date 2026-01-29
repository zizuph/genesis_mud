inherit "/std/weapon";
inherit "/lib/keep";
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>

create_weapon()
{
    set_name(({"sword","rapier","weapon"}));
    add_name("_dont_react_to");
    set_adj("deadly");
    set_short("deadly rapier");
    set_long("This exotic weapon is of fine make. Made from the best steel money can buy, " +
      "and crafted by the finest of weaponsmiths of Kalaman, this weapon is well balanced, " +
      "and light. ideal for the quick strike.\n");
    set_default_weapon(35,26,W_SWORD, W_IMPALE, W_ANYH);
    add_prop(OBJ_I_VOLUME, 3600);
    add_prop(OBJ_I_WEIGHT, 2500);
}
