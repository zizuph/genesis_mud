/* A typical "thug" for /Emerald/thief_lair
   Code (c) 1999 Damian Horton. BKA Casimir. */

#pragma strict_types
#pragma save_binary 

#include <const.h>
#include "/d/Emerald/sys/paths.h"

inherit THIEF_LAIR_DIR + "npc/base_thug.c";

void
create_bandit() 
{  
    string *adjective = ({"sturdy", "worn", "untrustworthy", "brutal"}); 
    string *weapon = ({"broadsword", "mace", "axe", "club", "knife"});
    int helm = random(6), body_armour = random(6); 

    add_name("bandit");
    set_adj(adjective[random(sizeof(adjective))]); 

    if (random(4))
    {
         set_gender(G_MALE);
    }
    else
    {
        set_gender(G_FEMALE); 
    }

    set_long("This individual gives the impression that "+ 
	     query_pronoun() + " has lived in the "+
	     "wilderness for some time now. "+
	     capitalize(query_pronoun()) + " looks to be the sort "+
	     "to be in to all kinds of mischief and probably has "+
	     "the skills to match.\n");

    add_equipment(({THIEF_LAIR_DIR + "wep/bandit_" + 
		      weapon[random(sizeof(weapon))],
		      THIEF_LAIR_DIR + "arm/quilt_leggings"}));
    
  
    if ((helm > 2))
    {
	add_equipment(({THIEF_LAIR_DIR + "arm/studded_helm.c"}));
    }
    if (helm == 2)
    {
	add_equipment(({THIEF_LAIR_DIR + "arm/iron_helm.c"}));
    }

    if (body_armour > 2)
    {
	add_equipment(({THIEF_LAIR_DIR + "arm/iron_ringmail.c"}));
    }
    if (body_armour == 1 || body_armour == 2)
    {
	add_equipment(({THIEF_LAIR_DIR + "arm/elf_chainmail.c"}));
    }

    config_bandit(55 + random(20));

    set_speak(({"You better have a good reason to be here. Perhaps to give "+
		    "me some loot?"}));

    set_act_time(6);
    add_act("emote appraises your equipment greedily.");
    add_act("emote looks ready to mug you!");
    add_act("say You would save yourself a lot of trouble if you gave "+
	    "up your equipment now...");
    add_act("emote curses the elves.");

    set_cact_time(6);
    add_cact("say Give up your loot now and I'll consider sparing your life!");
    add_cact("say You stinking son of an elvish nobleman!");
    add_cact("emote laughs, an unstable glint apparent in " + 
	     query_possessive() + " eyes.");
    add_cact("say This will be like stealing candy from baby.");
} 




