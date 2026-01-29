/*created by Macker 07/27/94
  Updated by Arman  03/25/04

 */

inherit "/std/weapon";

#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include "/d/Krynn/icewall/local.h"

inherit MELT_BASE

create_weapon()
{
	set_name("frostreaver");
	add_name("axe");
	set_short("frostreaver");
	set_long("This heavy battleaxe is made of ice! It is unusually " +
          "dense ice, and incredibly sharp... you imagine you could " +
          "easily cleave through the thickest armour and inflict the " +
          "most devastating damage with this weapon, assuming you " +
          "keep it away from the warmth of the sun!\n");
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(MAGIC_AM_MAGIC, ({ 80, "enchantment"}));
    add_prop(MAGIC_AM_ID_INFO, ({"This battleaxe is made of ice gathered " +
          "from a secret location on Icewall Glacier by the Revered Priests " +
          "of the Ice Folk. The blade of this weapon is formed through a " +
          "mystical and painstaking process known only to these priests, " +
          "however the end result is a weapon as deadly as any! However, " +
          "temperatures above freezing will eventually rend this weapon " +
          "useless.\n",35}));
	/* The frostreaver is Raggart Knug's best weapon. */
	/* If you think it is too strong, 
		just remember the Tintanic ;) */

	set_default_weapon(45, 60, W_AXE, W_SLASH, W_BOTH);
	add_prop(OBJ_I_VOLUME, 12200);
        add_prop(OBJ_I_WEIGHT, 9000);
	make_me_meltable();
}
