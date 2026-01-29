
inherit "/std/armour";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Rhovanion/defs.h"
#include SWS + "sw.h"

void
create_armour()
{
	set_name("jerkin");
	add_name("leather"); add_name("leather armour"); add_name("armour");
	set_adj("runed"); add_adj("leather");
	set_long("@@exa_lthr");
    
    set_default_armour();
	set_ac(24);
	set_at(2);

	add_prop(OBJ_I_IS_MAGIC_ARMOUR,1);
	add_prop(OBJ_M_NO_BUY,1);
	add_prop(OBJ_M_NO_SELL,1);
	add_prop(MAGIC_AM_MAGIC,({10,"enchantment"}));
	add_prop(OBJ_S_WIZINFO,"This leather armour"
			+" can only be worn by Spellweavers, and is"
			+" tougher (ac 24) than a normal leather armour might be."
			+" It is cloned once in the armory room of the"
			+" spellweaver guild.  It also cannot be bought"
			+" or sold."
			+" Additionally, this is the armour called"
			+" by the Spellweavers' 'aegis' spell"
			+".\n");
	add_prop(MAGIC_AM_ID_INFO, "This leather armour"
		+" is extra tough due to magical strength. It seems to originate"
		+" from the Spellweavers.\n");
	
	set_af(TO);
	
}

exa_lthr()
{
	if(! TP->query_guild_member(GUILD_NAME))
		TP->catch_msg("This is a tough brown leather jerkin, covered"
			+" in runes painted in with black. It looks rather drab"
			+" actually.");
	else TP->catch_msg("The runes on this leather jerkin tells you that"
			+" it is the property of the Spellweavers. The armour feels"
			+" both light and good.\n");
	return 1;
}

int
wear()
{
	if(TP->query_guild_member(GUILD_NAME))
        return 0;
	TP->catch_msg("As you start to put the jerkin on, it turns as rigid as"
		+" stone. Try as you might, you cannot put it on.\n");
	return -1;
}

string
query_recover()
{
    return MASTER + ":" + query_arm_recover();
}

void
init_recover(string arg)
{
    init_arm_recover(arg);
}
