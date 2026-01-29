/* This is Avena, a deadly, female, halfling warrior who must be defeated
   as part of one of the gladiators skill enhancing quests.
   code (c) 1998 Damian Horton
   redone March 2001, for Raumdor.
*/

#pragma strict_types
#pragma save_binary

#include "/d/Cirath/defs.h"
#include <ss_types.h>
#include <macros.h>
#include <wa_types.h>
#include <options.h>
#include "/d/Cirath/athas/gladiator/guruquest/guruquest.h";

inherit CIRATH_DIR + "lib/log_npc_kills";
inherit "/lib/unique"; //her weapon may be 'unique'
inherit "/d/Genesis/lib/intro.c"; //so she may introduce himself

void
create_monster ()
{
    object knife;//one of her weapons, might be magical

    //  ::create_monster();

    set_name("avena");
    set_living_name("avena");
    set_race_name("halfling");
    set_title("Streetbrawler Extraordinaire");
    set_adj("cunning");
    add_adj("rambunctious");
    set_gender(1);
    set_long("Rumoured to be an escaped gladiator from another "+
	     "city, she has become a fixture in the streets of "+
	     "Tyr. Delighting in nothing more than a good fight, "+
	     "she has never been known to back down from anything "+
	     "which could be construed as a challenge. More than "+
	     "one fool has regretted their underestimation of "+
	     "her skills.\n");

    set_stats(({90, 155, 85, 75, 65, 125}));
    set_skill(SS_WEP_KNIFE, 82);
    set_skill(SS_DEFENCE, 84);
    set_skill(SS_PARRY, 76);
    set_skill(SS_2H_COMBAT, 80);
    set_skill(SS_UNARM_COMBAT, 62);
    set_skill(SS_BLIND_COMBAT, 48);
    set_alignment(0);
    add_prop(LIVE_I_QUICKNESS, 120); //20% faster than normal
    set_exp_factor(155); //quickness, special, two-handed combat

    //only three fire daggers  may be in the game at once,
    //and she boots with one only 35% of the time
    knife = clone_unique(QUEST_DIR + "wep/fire_dagger", 6, QUEST_DIR + "wep/elegant_knife", 1, 35);
    knife->move(TO);
    command("wield all");

    equip(({QUEST_DIR + "wep/elegant_knife",
	    QUEST_DIR + "arm/bone_bracers",
	    QUEST_DIR + "arm/inix_greaves"}));

    set_act_time(3);
    add_act("emote glances at her surroundings with disdain.");
    add_act("emote tosses her daggers into the air, catching them with "+
	    "nonchalant grace."); 
    add_act("say Anyone wanna fight?");
    add_act("say Surely someone thinks they can beat up a puny halfling "+
	    "like myself.");
    add_act("emote gets an unstable glint in her eyes.");

    set_cact_time(2);
    add_cact("emote throws her head back and cackles.");
    add_cact("emote derides her foe as being incompetant.");
    add_cact("say Run home to your ma while you still can.");
    add_cact("emote smiles amusedly.");
     
    LOAD_GURU_SHADOW(AVENA);

     // must do this to have write permissions:
    setuid();
    seteuid(getuid());

    log_my_kills(LOG_DIR +" Avena_kills");
}

/* Avena's brutal dagger thrusts! 
   Provided Avena still a knife or dagger, she has an
   additional attack with it every 5 rds. Her chance to hit with this
   attack is (360-opponents dex)/360. Damage is 25+random(200)
   Returns 0 if it cannot be performed.

*/
int
thrust(object enemy)
{ 
    object* knives;//one of her knives
    mixed* hitresult; //result of hit_me
    string how; //description of the damage
    
    knives = query_weapon(-1); //all the weapons she wields
    
    if (!sizeof(knives))
    {
	return 0; //cannot special without a weapon
    }
    if (random(360)> enemy->query_stat(SS_DEX))
    {
	// She HITS!
	hitresult = enemy->hit_me(300, W_IMPALE, TO, -1);
	
	how = "stinging";
	if (hitresult[0] > 5) how = "grazing ";
	if (hitresult[0] > 10) how = "slicing ";
	if (hitresult[0] > 20) how = "piercing ";
	if (hitresult[0] > 40) how = "stabbing ";
	if (hitresult[0] > 80) how = "disemboweling ";

	enemy->catch_msg("Catching you off guard, "+QTNAME(TO)+
			 " strikes out rapidly, "+how+" you with her "+
			 "knife!\n");
	tell_watcher(QCTNAME(TO)+" strikes out rapidly at "+
		     QTNAME(enemy)+", " + how + " " + 
		     HIM_HER(enemy)+" with her knife!\n", TO, enemy);
	
	if(enemy->query_hp() <= 0)
	{  //attack was lethal!
	    enemy->do_die(TO);
	}
	
	else
	{  //She missed :(
	    enemy->catch_msg(QCTNAME(TO)+" rapidly thrusts at you with "+
		   "her knife, but you evade her attack.\n");
	   tell_watcher(QCTNAME(TO)+" rapidly thrusts at "+
		    QTNAME(enemy)+" with her knife, but "+
		    HE_SHE(enemy)+" evades her attack.\n", TO, enemy);
	}
    }

    return 1; //no other attack this round
}

int
special_attack(object enemy)
{       
    
    if(! random(6))
    {
	return thrust(enemy);
    }
    return 0; //continue with the round
}     

/* Done chiefly to prevent players from doing in, special, leave
   tactics against her: She always thrusts immediately upon being engaged.
*/
public void
attacked_by(object ob)
{
  ::attacked_by(ob);
    // alarmed so that the messages will be printed after the room
    // description, etc.
    set_alarm(0.0, 0.0, &thrust(ob));
}

/*
 * Function name: greetings 
 * Description:   This function makes the npc do a greeting to people it
 *                already know and to fellow npc's. It is possible to
 *                redefine, not however that it should never contain an
 *                'introduce myself' command. Personalized for Derryn.
 * Arguments:     object who - the living that introduced to me
 *
 */
public void
greet(object who)
{
    command("say Yes, yes, I know your name. You gonna try to take me "+
	"or what?!");
    command("command stare challeng " + OB_NAME(who));
}
/*
 * Function name:       introduce
 * Description:         This function makes the npc do an introduction to a
 *                      player that has not been introed to it earlier.
 *                      Changed for variety.
 * Arguments            object who - the livint that introduced tome
 *
 */
public void
introduce(object who)
{
    command("introduce myself to " + OB_NAME(who));
} 
