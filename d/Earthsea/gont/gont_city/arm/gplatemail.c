/*  Imported from Roke for Alexander
 *  Typos corrected
 *  Amelia 3/24/98
 *  originally coded by Vladimir
 *  9/2003 Ckrik, made armour magical to reflect it's 45 AC
 *  2-14-2004 Ckrik, fixed weight and volume
 */

#pragma strict_types

inherit "/std/armour";
inherit "/lib/keep";

#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>

public void
create_armour()
{
    set_name("platemail");
    set_short("green steel platemail");
    set_long("It is made from green steel. Across the "+
        "breastplate is a large symbol of two crossed "+
        "axes over a map of the world.\n");
    set_keep(1);
    set_adj("green");
    add_adj("steel");
    set_default_armour(45, A_TORSO);
    add_prop(OBJ_M_NO_BUY, 1);
    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
    add_prop(OBJ_S_WIZINFO, 
	     "An enchanted platemail worn by Alexander, " +
	     "the marshal of Gont.\n");
    add_prop(MAGIC_AM_ID_INFO,
        ({ "This armour is magically reinforced.\n",
        10 }));
    add_prop(MAGIC_AM_MAGIC, ({ 10, "enchantment" }));
    add_prop(OBJ_I_WEIGHT, 8000);
    add_prop(OBJ_I_VOLUME, 1600);
    add_prop(OBJ_I_VALUE, 1600);
}

public string 
query_recover()
{
    return MASTER + ":" + query_arm_recover();
}

public void
init_recover(string arg)
{
    init_arm_recover(arg);
}
