/* created by Aridor, 09/10/94 */

#include "../local.h"

inherit CITIZEN;

#include <money.h>
#include <ss_types.h>
#include <macros.h>
#include <filter_funs.h>

void
equip_me()
{
    seteuid(getuid(TO));
    clone_object(OBJ + "wrobe")->move(TO);
    clone_object(OBJ + "sandals")->move(TO);
    command("wear all");
}

void
create_citizen()
{
    set_name("crysania");
    add_name("cleric");
    set_race_name("human");
    set_introduce(", Revered Sister, Cleric of Paladine");
    set_gender(1);
    set_adj("black-haired");
    add_adj("humble");
    set_long("@@my_long@@She is helping poor people and also can perform " +
	     "healing prayers.\n");
    set_extra_long("She is wearing the medal of Paladine around her neck.\n");
    default_config_npc(random(10) + 60);
    set_skill(SS_AWARENESS, 40);
    set_skill(SS_SPELLCRAFT, 80);
    set_skill(SS_HERBALISM, 50);
    set_skill(SS_ELEMENT_LIFE, 40 + random(40));
    set_skill(SS_FORM_DIVINATION, 40 + random(40));
    set_all_hitloc_unarmed(10);
    set_alignment(1100);
    set_knight_prestige(-8);
    add_prop("_live_m_attack_thief", "poor_thief");
    set_act_time(0);
    add_act(({"say Stay away from the Shoikan grove.",
		"say That place is cursed." }));
    add_act("@@heal_someone_in_need@@");
    add_act("@@heal_someone_in_need@@");
    add_act("@@heal_someone_in_need@@");
    add_act("@@stop_all_fights@@");
    add_act("@@stop_all_fights@@");
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
	    "say Yes, my order serves the god of good, Paladine. He gives " +
	    "protection and rewards all of a good soul with his wisdom. The " +
	    "order bases on the knowledge on the Disks of Mishakal.",1);
    set_random_move(10);
    set_restrain_path(TDIR);
}

void
attacked_by(object who)
{
    ::::attacked_by(who);
    set_alarm(3.0,0.0,"stop_all_fights");
}

int
hook_victim_no_steal_bonus()
{
    write("You feel a divine presence prohibiting your attempt.\n");
    return 2000;
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
	  command("emote lays her hands upon your head " +
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

void
poor_thief(object thief, object obj, object victim)
{
    command("say I pity you.");
    command("sigh");
    command("say Do you really need to do this, " + thief->query_nonmet()+"?");
}
