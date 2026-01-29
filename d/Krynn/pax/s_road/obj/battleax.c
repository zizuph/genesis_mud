inherit "/std/weapon";
#include <wa_types.h>
#include <stdproperties.h>
#include <formulas.h>
#include <language.h>
#include <macros.h>
#include "/d/Krynn/pax/local.h"

create_weapon()
{
   set_name(({"dwarven war axe", "axe"}));
   set_short("war axe");
   set_long("Wielded by some hill-dwarf clansmen, this is a very old " +
            "fashioned but effective weapon. It has a single, razor sharp " +
            "blade that is very well balanced, and a short shaft wrapped " +
            "in leather that feels comfortalble to the touch.\n");
   set_default_weapon(30, 25, W_AXE, W_SLASH, W_ANYH);
   add_prop(OBJ_I_VOLUME, 1800);
   add_prop(OBJ_I_WEIGHT, 6000);
   add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(30,25));
}
