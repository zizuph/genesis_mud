
inherit "/std/weapon";
#include <wa_types.h>
#include <formulas.h>
#include "/d/Krynn/haven/local.h"

public void
create_weapon()
{
    set_name("battleaxe");
    add_name(({"weapon", "axe"}));
    set_pname("battleaxe");
    add_pname(({"axes", "weapons"}));
    set_adj(({"bladed", "double", "double-bladed"}));
    add_adj(({"metal","steel","battle"}));
    set_short("two-handed battleaxe");
    set_pshort("two-handed battleaxes");
    set_long("This is a large battleaxe, with two large blades. "+
      "Neidar, or hill dwarves, prefer such double bladed axes, "+
      "so you guess that it's dwarven. It's well balanced, and "+
      "an extraordinary weapon.\n");

    set_default_weapon(35, 30, W_AXE, W_SLASH, W_BOTH);

    add_prop(OBJ_I_VOLUME, 3000);
    add_prop(OBJ_I_WEIGHT, 4000);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(35,30));
}
