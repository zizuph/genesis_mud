
/*
	* The Spellweaver cowl 
 * Coded 1April1994 by Farlong & Quetzl

 * Breakstrings removed 940603 by Gunther

 */
inherit "/std/armour";

#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include "sw.h"

create_armour()
{
set_name("cowl");
set_adj("magical");
set_short("Spellweaver cowl");
add_name("_spellweaver_cowl");
set_long("This is a heavy cowl of a very dark material."
	+"  Sewn on it are numerous intricately-shaped runes.  It is the"
	+" mantle of a Spellweaver, marking its bearer as a servant"
	+" of the darkness, and a being of great magical power.\n");

set_at(A_ROBE);
set_ac(6);
set_af(TO);
set_likely_break(0);
set_likely_cond(0);

add_prop(OBJ_I_IS_MAGIC_ARMOUR,1);
add_prop(OBJ_M_NO_BUY,1);
add_prop(OBJ_M_NO_SELL,1);
add_prop(OBJ_M_NO_DROP,1);
add_prop(OBJ_S_WIZINFO, "This is the spell object"
	+" for the Spellweavers guild.  It is unbreakable, undroppable,"
	+" unsellable, unbuyable, etc."
	+"\n");

}

int
set_condition(int condition)
{
	return 0;
}

int query_armour_hits()
{
	return 0;
}

string
arm_condition_desc()
{
	return "";
}

wear()
{
	write("You wear your Spellweaver cowl around"
	+" your body, wrapping it tightly around you, and the darkness"
	+" welcomes you with its embrace.\n");
say(QCTNAME(TP)+" wraps a dark Spellweaver cowl around "+TPOS+" body.\n");
return 1;
}

remove()
{
write("You remove the Spellweaver's cowl from around your"
	+" body, and feel somehow naked now.\n");
say(QCTNAME(TP)+" removes the cowl of the Spellweavers from around "+TPOS+" body.\n");
return 1;
}

query_auto_load()
{
	return MASTER;
}
