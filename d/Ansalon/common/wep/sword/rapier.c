#pragma strict_types
inherit "/std/weapon";
inherit "/lib/keep";
#include <wa_types.h>
#include <stdproperties.h>

void
create_weapon()
{
    set_name(({"sword","rapier"}));
    set_adj("deadly");
    set_short("deadly rapier");
    set_long("This exotic weapon is of fine make. Made from the best steel money can buy, " +
      "and crafted by the finest of weaponsmiths of Kalaman, this weapon is well balanced, " +
      "and light. Ideal for the quick strike.\n");
    set_default_weapon(35,26,W_SWORD, W_IMPALE, W_ANYH);
    update_prop_settings();
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT)/11);
}
