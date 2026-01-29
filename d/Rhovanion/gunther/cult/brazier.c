/*
 * The small brazier carried by all Cult of Melkor members.
 *
 * By Gunther 940718
 */


inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Rhovanion/defs.h"
#include "guild.h"

string query_auto_load() { return MASTER; }

init()
{
	::init();
	add_action("light_me", "light");
	add_action("extinguish_me", "extinguish");
	add_action("droppable", "droppable");
}	

create_object()
{
	set_short("small coal brazier");
	set_long("This is a portable coal brazier, made by the Cult of"
		+" Melkor to be used by its members. It consists of a box"
		+" made from a dark metal alloy with small ventilation holes"
		+" set in at the bottom. It is filled with " + "@@lighted_brazier");
	set_name("brazier");
	set_adj("small");
	add_adj("coal");
	
	add_name("_cult_brazier");
	
	add_prop(OBJ_M_NO_DROP, 1);
	add_prop(OBJ_M_NO_SELL, 1);
	add_prop(OBJ_M_NO_STEAL, 1);

	add_prop(OBJ_S_WIZINFO, "This is an object used by members of the"
		+" Cult of Melkor. It is unsellable and features three commands"
		+" droppable, light and extinguish. When lighted the brazier"
		+" has the OBJ_I_HAS_FIRE prop set. Its used by members to "
		+"perform the rite of sacrifice.\n");
}

string
lighted_brazier()
{
	if(query_prop(OBJ_I_HAS_FIRE))
		return "burning red-hot coals.\n";
	else
		return "blackened pieces of coal.\n";
}

droppable(string str)
{
	int nDrop;
	
	nDrop = query_prop(OBJ_M_NO_DROP);
	
	if(nDrop) write("You can now drop the brazier.\n");
	else write("You will now hang on to the brazier.\n");
	nDrop = 1 - nDrop;
	
	if(nDrop) add_prop(OBJ_M_NO_DROP, 1);
	else remove_prop(OBJ_M_NO_DROP);
	return 1;
}


light_me(string str)
{  
	int nRoomType;
	NF("Light what ?\n");
	if(str != "brazier") return 0;
	
	NF("The brazier is already burning!\n");
	if(query_prop(OBJ_I_HAS_FIRE)) return 0;
	
	NF("You cannot light the brazier here!");
	nRoomType = ENV(TP)->query_prop(ROOM_I_TYPE);
	if(nRoomType == ROOM_IN_WATER || nRoomType == ROOM_UNDER_WATER)
		return 0;
		
	write("You set the coals glowing in the brazier.\n");
	say(QCTNAME(TP) + " lights " + HIS(TP) + " small "
		+"coal brazier, sending tendrils of smoke up into the air.\n");

	add_prop(OBJ_I_HAS_FIRE, 1);
	return 1;
}

extinguish_me(string str)
{
	NF("Extinguish what ?\n");
	if(str != "brazier") return 0;
	
	NF("The brazier isn't burning!\n");
	if(!query_prop(OBJ_I_HAS_FIRE)) return 0;
	
	write("You extinguish the brazier.\n");
	say(QCTNAME(TP) + " extinguishes " + HIS(TP) + " small "
		+ "coal brazier.\n");
	
	remove_prop(OBJ_I_HAS_FIRE);
        return 1;
}

public void
water_extinguish()	
{
	if(query_prop(OBJ_I_HAS_FIRE))
	{
		write("The brazier goes out.\n");
		say("The small brazier carried by " + QTNAME(TP) + "stops "
			+" burning.\n");
		remove_prop(OBJ_I_HAS_FIRE);
	}
}






