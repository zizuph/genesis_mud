/* created by Aridor 11/30/93 */

inherit "/std/weapon";
inherit "/lib/keep";

#include "../local.h"
#include <ss_types.h>
#include <formulas.h>
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>

string color = "blue";

/*prototype*/
void set_color(string new_color);

void
create_weapon()
{
    set_name("battleaxe");
    set_pname("battleaxes");
       set_short("blue heavy battleaxe");
    add_name("axe");
    add_pname("axes");
    add_pname("weapons");
    set_adj("heavy");
    set_adj("blue");
    add_adj("metal");  /* it is, isn't it? -Gorboth */
    set_long("@@my_long");
    set_default_weapon(32, 52, W_AXE, W_SLASH | W_BLUDGEON, W_BOTH);
    set_wf(TO);
    add_prop(OBJ_M_NO_BUY, 1);
    add_prop(OBJ_I_COLORABLE, 1);
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(OBJ_S_WIZINFO,"The extremely heavy weapon is usable only " +
	     "through its magic, reducing it's weight to about 1/2. When " +
	     "hitting, the axe still has the force of all its weight, " +
	     "giving a formidable penetration value.\n");
    add_prop(MAGIC_AM_ID_INFO,
	     ({"The blade of this axe feels magical.\n",10,
		 "Even though the battleaxe feels heavy, you realize that " +
		 "the weapon would actually be more than twice as heavy " +
		 "if no magic was involved here.\n", 40,
		 "This makes the weapon fairly easy to wield considering " +
		 "its weight, and of course the weapon hits opponents like " +
		 "it had its original weight.\n", 45}));
    add_prop(MAGIC_AM_MAGIC,({80,"enchantment"}));
    add_prop(OBJ_I_VOLUME, 6800);
    add_prop(OBJ_I_WEIGHT, 4800);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(32,52) + 1000); /* it is magical! */
}

string
query_recover()
{
    return MASTER + ":" + query_wep_recover() + "&&" + color;
}

void
init_recover(string arg)
{
    string *a = explode(arg,"&&");
    set_color(a[1]);
    init_wep_recover(a[0]);
}

string
my_long()
{
  return "This is a very heavy weapon with a very sharp and heavy blade. " +
    "The blade of this axe sparkles in a mysterious " + color + " color.\n";
}

void
set_color(string new_color)
{
    remove_adj(color);
    color = new_color;
    set_adj(color);
    set_short(color + " heavy battleaxe");
}

public string
query_color()
{
    return color;
}

mixed
wield(object what)
{
    if (TP->query_base_stat(SS_STR) > 60)
      return 0;
    return "You are unable to wield the " + color + " heavy battleaxe.\n";
}

mixed
unwield(object what)
{
    return 0;
}
