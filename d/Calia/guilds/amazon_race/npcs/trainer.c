/*
 *    trainer.c  
 *
 * trainer.
 *
 * Baldacin@Genesis, Dec 2003   
 *
 */
#include "../defs.h"
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
inherit NPC+"std_amazon";
 
void
create_amazon()
{
	string *equipment = ({ARM+"brown_pants",ARM+"camo_cloak",ARM+"leather_armour",ARM+"leather_boots", WEP+"spear"});

    set_name("azealia");
    add_name("trainer_");
    set_adj("tall");
    add_adj("fierce");
    set_long("Tall and fierce is the first things that come into "+
		"mind when looking at this Amazon warrior. Her duty amongst the "+
		"amazons is training the inhabitants of the settlement. They start "+
		"their training very early, even children get some basic defensive "+
		"education here.\n");
    set_title("the Legendary Amazon of the Silent Forest and Expert Trainer");
    set_gender(G_FEMALE);
    set_stats(({156, 156, 156, 156, 156, 156}));
    
    add_ask(({"leave", "leave guild"}),"say Yes, it is possible to leave "+
      "the Amazons in this room, just issue 'depart from guild'.", 1);
    add_ask(({"join", "join guild"}), "say Yes, It is possible to 'affiliate' "+
      "yourself with the Amazons in this room.\n", 1);
	add_ask(({"skills", "train","improve","learn"}), "say It is possible for "+
		"the Amazons to 'learn' and 'improve' some skills here.", 1);
    add_ask(({"token", "obtain token"}), "say You can get a new token if you "+
      "lost it. Just 'obtain' one here.", 1);
      
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

    command("say to "+TP->query_name()+" I have no idea what you are talking about.");
    command("shrug");
    return "";
}


public void
add_introduced(string name)
{
    command("introduce me to " + name);
}