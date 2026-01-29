// file name: /d/Avenir/common/dead/mon/revenant_m
// creator(s): Lilith Sept 2021
// purpose:    To populate the catacombs with a mythic undead
// note:       Limit 7 cloned in the 150 rooms.
// update(s):   

inherit "/d/Avenir/inherit/monster";
inherit "/d/Genesis/specials/npc/stat_based_specials";
#include "/d/Avenir/smis/sys/statserv.h"

#include "../dead.h"
#include <cmdparse.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <money.h>

#define DEATH_LOG "/d/Avenir/log/deaths/revenant"

// Global Variables
string *randadj, *randrace, short_desc;

/* This is called by the placer file, not the npc */
void
equip_me()
{
    seteuid(getuid());
   
    /* Coin for each eye, based on npc size */
    MONEY_MAKE_PC(2)->move(this_object());
	equip("/d/Avenir/common/obj/syb_coin");

    /* burial paraphernalia */
    add_armour(OBJ +"death_shroud");
    add_armour(OBJ +"shroud_sash");
    add_armour(OBJ +"ring");	
       
	/* Lets make these things wear items that identify what they were in life. 
 	 * None of these items is exceptional in any way.
	 */ 
    switch(random(5))
    {
        case 0:  // holm noble
	        add_weapon("/d/Avenir/common/holm/obj/dagger");
	        equip(OBJ +"rushlight");
            add_armour("/d/Avenir/common/bazaar/Obj/worn/codpiece");
			// add_weapon("/d/Avenir/common/holm/obj/falchion_nm");
	    break;

        case 1:  // troloby punisher
            add_armour("/d/Avenir/common/bazaar/Obj/worn/pboots");
            add_armour("/d/Avenir/common/bazaar/Obj/worn/harness");
            add_armour("/d/Avenir/common/bazaar/Obj/worn/loincloth");    
			equip("/d/Avenir/common/bazaar/Obj/food/crusty_bread");
	    break;

        case 2:  // dwarven guard
            add_armour("/d/Avenir/common/bazaar/Obj/worn/bracers");
            add_armour("/d/Avenir/common/bazaar/Obj/worn/helm");
            add_armour("/d/Avenir/common/bazaar/Obj/worn/boots");
          //  add_weapon("/d/Avenir/common/bazaar/Obj/wield/gsword");	
		break;

        case 3:   // inquisitor
            add_armour("/d/Avenir/common/holm/obj/armour");
            add_armour("/d/Avenir/common/holm/obj/boots");
		  	add_weapon("/d/Avenir/common/bazaar/Obj/wield/cane");
            equip(OBJ +"rushlight");
       	break;

        case 4:  // dej minha
            add_armour("/d/Avenir/common/city/obj/worn/buskins");
            add_armour("/d/Avenir/common/city/obj/worn/filibeg");
	        add_armour(OBJ +"bracelet");					
         // add_weapon("/d/Avenir/common/city/obj/wep/d2ndsword");
        break;
    }
	// The add_weapon and add_armour functions do the wear and wield calls
	// but just to make sure I'm getting the desired results....
    command("$wear all");	 
    command("$unwield all"); //No weapons wielded, it's a mindless revenant.
                             //giving it unarmed abilities instead.
  							 
}

void
create_monster()
{
    int wep;
    randadj = ({"bloody","grayish","disgusting","stinking",
              "rotting","slimy","mottled","decayed",
			  "once handsome","moldy-faced","rancid",
			  "insect-infested","bloated"});
    randrace = ({"revenant", "cadaver", "carcass"});

    set_name(({"revenant", "_Dead_Isle_Rev", "undead", "_crypt_crawler"}));
    set_race_name(randrace[random(sizeof(randrace))]);
    set_adj(randadj[random(sizeof(randadj))]);
	add_adj("collossal");
	    short_desc = implode(query_adjs(), " ") +" "+ query_race();
    set_short(short_desc);
    set_long("This "+ short_desc +" was animated from one of the "
        +"innumerable bodies that line the catacombs.\n"	
		+"It seems to be about "+query_exp_title()+" in size, "
		+"but it is hard to be sure of anything where the undead "
		+"are involved.\n"
		+"It appears to be very disturbed by your presence here.\n"
		+"There is a coin covering each eye.\n"
		+"");
    set_alarm(1.0,0.0,"set_m_in","staggers in");
    set_alarm(1.0,0.0,"set_m_out","lurches out");
	set_gender(G_NEUTER);
    set_alignment(0);   	
	
	// Myth sized revenant-there are 7 at 190-224
	default_config_npc(190 + (random(35)));
	
	// fights unarmed so lets give skills based on mob size.
	set_skill(SS_AWARENESS,    100); // foil imbue thieves
    set_skill(SS_DEFENCE,      100); // reduce melee damage 	
    set_skill(SS_ACROBAT,      100); // reduce melee damage
	set_skill(SS_UNARM_COMBAT, 100);
    set_skill_extra(SS_UNARM_COMBAT, 50);	
    set_skill(SS_BLIND_COMBAT, 100); 
	set_skill(SS_SPELLCRAFT,   100); // reduce caster damage
	set_skill(SS_FORM_ABJURATION,100); // reduce caster damage
 	
    wep = 50 +(random(11));  // 50-60 
    set_all_attack_unarmed(wep, wep);
	set_all_hitloc_unarmed(60 +(random(21))); // AC 60-80 Before armors
	// 60 AC = 56.47% damage reduction
	// 70 AC = 62.11% damage reduction
    // 80 AC = 67.02% damage reduction

	// Trying to set magic res for magic users to something similar 
	// to what the native AC is for melee fighters.	
	// 19 MR = ~30% damage immunity
	// 25 MR = ~40% damage immunity
	// 40 MR = ~60% damage immunity	
	add_prop(MAGIC_I_RES_MAGIC, 60 +(random(5))); //60-64
	
	// set height and weight to align with size and descs
	add_prop(CONT_I_HEIGHT, TO->query_average_stat());
	add_prop(CONT_I_WEIGHT, TO->query_average_stat() * 300);
    add_prop(LIVE_I_SEE_DARK, 1); 
    add_prop(LIVE_I_UNDEAD, 1);
    add_prop(LIVE_I_NEVERKNOWN,1);
	add_prop(LIVE_I_NO_CORPSE, 1);
	add_prop(LIVE_M_NO_ACCEPT_GIVE, 1);
    
    // I'm always aggressive.
    set_aggressive(1); 	

    add_prop(NPC_I_NO_FEAR, 1);
    add_prop(NPC_I_NO_LOOKS, 1);
	add_prop(NPC_I_NO_RUN_AWAY, 1);
  
    set_cact_time(10);
    add_cact("emote roars with rage.");
    add_cact("scream");
    add_cact("emote rips off an arm and beats you with it.");
    add_cact("emote aims a bony finger toward your eyes.");
    add_cact("emote spits a tooth at you.");
    add_cact("emote splatters you with stinking body fluids.");
    add_cact("emote lurches sideways and bounces you into the wall.");

    set_act_time(20);
    add_act("emote looks around in apparent confusion.");
    add_act("emote shuffles this way and that.");
    add_act("emote eyes you zealously.");
	add_act("emote growls: I cannot rest until you are gone from here.");
    add_act("emote grunts and gurgles in an attempt to speak.");
    add_act("emote whispers something about Mascarvin...");
	add_act("emote cries out: May Mascarvin grant me rebirth soon.");
    add_act("emote croaks: Even in death I choose to serve the Gods.");
    add_act("emote complains: Why do you disturb my rest?");
	
}

public string cr_attack_desc(int id)
{
    if (id == W_LEFT)
    {
        return "rotting left fist";
    }
    if (id == W_RIGHT)
    {
        return "maggot-infested right fist";
    }
    return ::cr_attack_desc(id);
}


public int
special_attack(object victim)
{
	
    mixed * hitresult;
	int avg_stat, hurt;
    string how, hdesc;
	object poison;
	
    if (ENV(victim) != ENV(TO) || victim->query_ghost())
    {
        TO->stop_fight(victim);
        return 1;
    }
	
    // 33% chance of a normal or special attack.
    if (random(3))
        return 0;

    // Choose power of hit based on mob stat size.
    hitresult = do_stat_based_attack(TO, victim, W_BLUDGEON);
	
	// The attack was evaded
	if (intp(hitresult))
		return 1;
	
    if (hitresult[0] <= 0)
    {
        // Handle misses.
        query_combat_object()->tell_watcher(QCTNAME(TO) + " tries to bite " + QTNAME(victim) +
	        " but misses completely.\n", victim);
        victim->catch_msg(QCTNAME(TO) + " tries to bite you with its "
		    +"foul, rotting teeth but misses completely!\n");
        return 1;
    }
    // hitresult as percentage of health
    how = "unharmed";
    if (hitresult[0] > 0)
	how = "more disgusted than anything else.";
    if (hitresult[0] > 5)
	how = "a painful ache where you were bitten.";
    if (hitresult[0] > 10)
	how = "where every tooth sank into your skin.";
    if (hitresult[0] > 25)
	how = "a bite has been ripped out of your flesh!";
    if (hitresult[0] > 50)
	how = "like you're on fire where you were bitten!";
    if (hitresult[0] > 75)
	    how = "as though you might die from the poison in its bite!";
	
    //The poison is mostly a nuisance. 
	if (random(7) == 0)
	{
	    poison = clone_object(OBJ +"bite_poison");
        poison->reconfig_me(20);
        poison->move(victim, 1);
        poison->start_poison();
	}
	
    hdesc = hitresult[1];
    query_combat_object()->tell_watcher(QCTNAME(TO) + " lunges for " + QTNAME(victim) 
	    + " and sinks its teeth into "+victim->query_possessive() +" "+ hdesc 
		+"\n", victim); 
    victim->catch_msg(QCTNAME(TO) + " lunges toward you, teeth snapping, and "
	    +"bites you on the "+ hdesc +"!\n");
    victim->catch_msg("You feel " + how + "\n");
	
    return 1;
}
		

/* Logging death info. */
void
do_die(object killer)
{
    object *foos = query_enemy(-1);
    string *killers;
	
    if (query_hp() > 0)
        return;
	
    if (!killer)
        killer = previous_object();
	
    foos -= ({ killer });
    killers = (foos)->query_name();
	
    /* Logging death for various reasons */
    SCROLLING_LOG(DEATH_LOG, "Rev ("+ TO->query_average_stat() +") by "+
	killer->query_name() +"("+ killer->query_average_stat() +") "+
	(sizeof(killers) ? "with "+ COMPOSITE_WORDS(killers) : "solo"));

    ::do_die(killer);
    STATSERV_LOG_EVENT("Crypt", "revenants killed");
}
