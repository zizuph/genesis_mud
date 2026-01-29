/*
 * A curator for the Knighthood museum in the Spur
 * Modified by Kentari from elistan.c - 12/96
 */
 
#include "/d/Krynn/solamn/hctower/spur/local.h"

inherit M_FILE

#include <money.h>
#include <ss_types.h>
#include <macros.h>
#include <filter_funs.h>

void
create_krynn_monster()
{
    set_name("ellard");
    add_name("curator");
    set_race_name("human");
    set_introduce(1);
    set_title("the Curator of the Sacred Solamnic Museum");
    set_gender(0);
    set_adj("grey-haired");
    add_adj("knowledgable");
    set_long("This is a man who seems old at first glance. His "+
        "eyes are lighted by a glow from within. He radiates "+
        "joy and good health, and would appear to know a great "+
        "many things.\n");
    set_extra_long("He is wearing the medal of Paladine around his neck.\n");

    add_prop(CONT_I_HEIGHT, 190);
    add_prop(CONT_I_WEIGHT, 70100);
    MONEY_MAKE_SC(random(10) + 5)->move(TO);
    add_prop(NPC_I_NO_LOOKS,  1);
    add_prop(NPC_I_NO_RUN_AWAY, 1);
    default_config_npc(random(20) + 70);
    set_skill(SS_AWARENESS, 80);
    set_skill(SS_UNARM_COMBAT, 80);
    set_skill(SS_SPELLCRAFT, 80);
    set_skill(SS_HERBALISM, 80);
    set_skill(SS_ELEMENT_LIFE, 80);
    set_skill(SS_FORM_DIVINATION, 80);
    set_all_hitloc_unarmed(80);
    set_alignment(1000);
    set_knight_prestige(-10);

    set_act_time(180);

    add_act("@@stop_all_fights@@");
    add_act("say Please take a look around at this humble museum for " +
	    "there is much to see");
    add_act("@@stop_all_fights@@");
    
    add_ask(({"museum"}),
	    "say This museum is a wealth of knowledge and history about " +
	    "the Knights of Solamnia, for to explore one's future, one " +
	    "must learn the lessons of the past.\n" +
	    "Please, feel free to examine any and everything you see, " +
	    "and enjoy!", 1); 
    add_ask(({"spells","clerical spells","magic","clerics"}),
	    "emote sighs briefly and looks down in thought, then says: " +
	    "clerical abilities granted by Paladine and his sons was " +
	    "withdrawn with the Cataclysm. We faithfully await the " +
	    "day in which our Gods shall return to us, and with their " +
	    "coming, once again grant us a portion of their divine " +
	    "powers.", 1); 
    add_ask(({"plains", "solamnia"}),
	    "say Why, I thought everyone knew that the Plains of Solamnia " +
	    "are southeast of this Spur!", 1);   
    add_ask(({"draconians", "army", "blue army"}),
	    "say I have no knowledge about this.",1);
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
	    command("emote looks about with such concern for this " +
		    "place that all fighting subsides out of shame.\n");
	}
    return "";
}

