/*
 *    amazon.c  
 *
 * A sneaking amazon
 *
 * Baldacin@Genesis, Dec 2003   
 *
 */
#include "../ldefs.h"
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
inherit AMAZONSTD;


void
create_amazon()
{
    string *equipment = ({AMAARMDIR+"brown_pants",AMAARMDIR+"camo_cloak",
                          AMAARMDIR+"leather_armour",AMAARMDIR+"leather_boots",
                          AMAWEPDIR+"spear"});
    add_name("_sneaky_one");
    set_adj( ({"courageous", "strong", "agile", "sturdy", "steadfast"})[random(5)] );
    add_adj( ({"black-haired", "camouflaged", "sneaky", "short-haired"})[random(4)] );
    set_long("This female seems to be a fierce warrior. Stealthy and strong.\n");
    set_stats(({70 + random(25),     
                70 + random(25),     
                70 + random(25),     
                70 + random(25),     
                70 + random(25),     
                70 + random(25)})); 
         
    set_default_answer(VBFC_ME("def_answer"));
    equip_this(equipment);
}

int
can_npc_see(object player)
{
	if (CAN_SEE(TO, player) && CAN_SEE_IN_ROOM(TO))
		return 1;
	return 0;
}

string
def_answer()
{
    if (!can_npc_see(TP))
	{
	    command("say What?! Who's there!");  
		return "";
	}

    command("say to "+TP->query_name()+" I don't have time to talk.");
    command("shrug");
    return "";
}