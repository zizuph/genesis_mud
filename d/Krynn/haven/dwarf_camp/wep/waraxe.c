
inherit "/std/weapon";
#include <wa_types.h>
#include <formulas.h>
#include "/d/Krynn/haven/local.h"

public void
create_weapon()
{
    set_name("waraxe");
    add_name(({"weapon", "axe"}));
    set_pname("waraxes");
    add_pname(({"axes", "weapons"}));
    set_adj(({"bladed", "double", "double-bladed"}));
    add_adj("metal");  /* added by Gorboth, July 2007 */

    set_short("double-bladed waraxe");
    set_pshort("double-bladed waraxes");
    set_long("This short axe has two large blades, one on each "+
      "side. It's probably dwarven, judging from the size, and "+
      "the Neidar, or hill dwarves, prefer such double bladed "+
      "axes.\n");

    set_default_weapon(30, 25, W_AXE, W_SLASH, W_ANYH);

    add_prop(OBJ_I_VOLUME, 3000);
    add_prop(OBJ_I_WEIGHT, 4000);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(30,25));
}
