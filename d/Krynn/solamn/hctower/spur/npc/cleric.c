// modelled after Ari's Chrysania. 
// Trying to keep the 'clerics of Paladine' consistent.

#include "../local.h"

inherit M_FILE

#include <money.h>
#include <ss_types.h>
#include <macros.h>
#include <filter_funs.h>

void
create_krynn_monster()
{
    set_name("elistan");
    add_name("cleric");
    set_race_name("human");
    set_introduce(1);
    set_title("the Revered Son of Paladine");
    set_gender(0);
    set_adj("grey-haired");
    add_adj("vigorous");
    set_long("This is a man who seems old at first glance. His "+
        "eyes are lighted by a glow from within. He radiates "+
        "joy and good health, and would appear to know a great "+
        "many things.\n");
    set_extra_long("He is wearing the medal of Paladine around his neck.\n");

    default_config_npc(random(30) + 60);
    set_skill(SS_AWARENESS, 80);
    set_skill(SS_SPELLCRAFT, 80);
    set_skill(SS_HERBALISM, 80);
    set_skill(SS_ELEMENT_LIFE, 80);
    set_skill(SS_FORM_DIVINATION, 80);
    set_all_hitloc_unarmed(80);
    set_alignment(1000);
    set_knight_prestige(-10);

    set_act_time(30);

    add_act("@@heal_someone_in_need@@");
    add_act("@@heal_someone_in_need@@");
    add_act("@@stop_all_fights@@");
    add_act("@@stop_all_fights@@");
    
    add_ask(({"grove", "shoikan"}),
	    "say The evil has taken hold there, it's like a thorn in the " +
	    "side of Palanthas.", 1); 
    add_ask(({"plains", "solamnia"}),
	    "say Why, I thought everyone knew that the Plains of Solamnia " +
	    "are southeast of Palanthas!", 1);   
    add_ask(({"draconians", "army", "blue army"}),
	    "say I have no knowledge about this.",1);
    add_ask(({"paladine","cleric","sister","order","god","good","disks",
		"disks of mishakal","mishakal"}),
	    "say Yes, my order serves the God of Good, Paladine. He gives " +
	    "protection and rewards all of a good soul with his wisdom.",1);
   add_ask(({"spells", "magic", "training", "train"}),
            "say With complete dedication to Paladine, all is possible, "+
            "even that which seems impossible.", 1);
   add_ask(({"help"}),
            "I don't need any help at this time, thank you.",1);
}

void
add_introduced(string name)
{
    command("introduce myself to " + name);
}



void
attacked_by(object who)
{
    ::::attacked_by(who);
    set_alarm(3.0,0.0,"stop_all_fights");
}

string
heal_someone_in_need()
{
    object *who = FILTER_LIVE(all_inventory(E(TO)));
    object *possible = ({ });
    int i,skill;
    for (i=0;i<sizeof(who);i++)
      if (who[i]->query_alignment() > 0 && interactive(who[i]) &&
	  (who[i]->query_max_hp() - who[i]->query_hp()) > 10)
	possible = ({ who[i] }) + possible;
      else
	possible = possible + ({ who[i] });
    skill = random(query_skill(SS_FORM_DIVINATION) +
      query_skill(SS_ELEMENT_LIFE) + query_base_stat(SS_WIS)) - random(100);
          command("emote mumbles a prayer.");
    if (sizeof(possible) && skill > 0)
      {
	  possible[0]->heal_hp(skill);
	  command("emote lays his hands upon your head " +
		    "and you feel the grace and power of Paladine flowing " +
		    "through you, healing you.");
      }
    return "";
}

string
stop_all_fights()
{
    object *who = FILTER_LIVE(all_inventory(E(TO)));
    mixed *fighting;
    int skill = query_skill(SS_FORM_DIVINATION) +
      query_skill(SS_ELEMENT_LIFE) + query_base_stat(SS_WIS);
    fighting = who->query_attack();
    command("emote mumbles a prayer.");
    if (fighting && sizeof(fighting))
      fighting = fighting - ({ 0 });
    if (fighting && sizeof(fighting))
      if (random(100) < random(skill))
	{
	    who->stop_fight(who);
	    command("emote summons the presence of the gods to this " +
		    "place and all fighting subsides immediatly.");
	}
    return "";
}

