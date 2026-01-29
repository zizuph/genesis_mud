
inherit "/std/weapon"

#include "/sys/wa_types.h" 
#include "/sys/stdproperties.h"
#include "/d/Rhovanion/defs.h"
#include SWS + "sw.h"

void
create_weapon()
{
	set_name("knife");
	set_adj("runed");
	set_short("runed knife");
	set_long("@@exa_knife");

	set_wf(TO);

	set_hit(25);
	set_pen(25);

    set_wt(W_KNIFE); 
    set_dt(W_SLASH | W_IMPALE); 

    set_hands(W_ANYH); 

	add_prop(OBJ_I_IS_MAGIC_WEAPON,1);
	add_prop(MAGIC_AM_MAGIC, ({10,"enchantment"}));
	add_prop(OBJ_S_WIZINFO,"This knife is for"
		+" Spellweavers guildmembers only; it is extra"
		+" strong, having a hit and pen value of each 25."
		+" It also cannot be sold or bought."
		+" 2 are cloned by the armory.c room in the Spellweaver"
		+" guild.  These are the only 2 starting in the game."
		+" This weapon will be the one called with the"
		+" epee spell."
		+"\n");
   add_prop(MAGIC_AM_ID_INFO,"This"
	+" knife contains a special magical strength"
	+" that will hit enemies with more force than a usual"
	+" knife.  It is a special weapon of the Spellweavers."
	+"\n");
	
	add_prop(OBJ_M_NO_BUY,1);
	add_prop(OBJ_M_NO_SELL,1);

}

exa_knife()
{
	if(TP->query_guild_member(GUILD_NAME))
		TP->catch_msg("The runes on this small knife say that it belongs"
			+" to the Spellweaver guild. It seems like a rather good knife.\n");
	else
		TP->catch_msg("Both the handle and the blade of this knife are"
			+" covered by myriads of small runes. The knife feels heavy"
			+" in your hands and not very comfortable.\n");
	return 1;
}

int
wield()
{
	if(TP->query_guild_member(GUILD_NAME))
		return 0;
	TP->catch_msg("As you grip the knife the runes burn your skin."+
				" You let go of the knife.\n");
	return -1;
}
