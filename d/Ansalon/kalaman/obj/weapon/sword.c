inherit "/std/weapon";
inherit "/lib/keep";
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include "../../local.h"

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
    add_prop(OBJ_I_VOLUME, 3600);
    add_prop(OBJ_I_WEIGHT, 3700);
    add_prop(KALAMAN_NOBUY,1);
}
