// Navarre October 12th 2008, increased the stats on the weapon as it is a magical weapon and yet never used by anyone as its way crappier than anything else out there.

inherit "/std/weapon";
inherit "/lib/keep";

#include <wa_types.h>
#include <stdproperties.h>
#include <formulas.h>
#include <macros.h>

create_weapon()
{
    set_name("scimitar");
    add_name("sword");
    set_adj("runed");
    add_adj("metal");  /* it is, isn't it? -Gorboth */
    set_short("runed scimitar");
    set_long("This scimitar is of a strange and exotic make. " +
      "Consisting of a huge curved blade and a small one-handed " +
      "hiltless handle, it looks almost unwieldable. Yet it " +
      "balances reasonably well in your hand. Along the " +
      "length of the blade runes have been inscribed.\n");

    add_item("runes","Elven runes run up and down the blade of "+
      "the scimitar, glowing slightly.\n");
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(MAGIC_AM_MAGIC,({ 10, "enchantment"}));
    add_prop(MAGIC_AM_ID_INFO,({"This weapon has been " +
	"enchanted so that one can balance this two-handed blade " +
	"in one hand.\n",5}));
    set_default_weapon(42,42,W_SWORD,W_SLASH,W_ANYH);
    add_prop(OBJ_M_NO_BUY, 1);
    add_prop(OBJ_I_VOLUME, 3600);
    add_prop(OBJ_I_WEIGHT, 3500);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(35,35));
}

