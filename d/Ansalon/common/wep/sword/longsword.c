#pragma strict_types
inherit "/std/weapon";
inherit "/lib/keep";
#include <wa_types.h>
#include <stdproperties.h>

void
create_weapon()
{
    set_name(({"sword","longsword"}));
    set_adj("shiny");
    add_adj("steel");
    set_short("shiny steel longsword");
    set_long("A pretty ordinary steel longsword. This blade " +
      "is quite common amongst the soldiers of the " +
      "lands of Ansalon. \n");
    set_default_weapon(26,26,W_SWORD, W_SLASH | W_IMPALE, W_ANYH);
    update_prop_settings();
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT)/11);
}
