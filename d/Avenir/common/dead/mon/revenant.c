// file name: /d/Avenir/common/dead/mon/revenant
// creator(s): Lilith June 2021
// purpose:    To populate the catacombs with fresh undead
// note:       Equivalent to 3 different sizes of npcs. 
//             When cloned the file will try to do an equal
//             distribution across the 3 sizes ranging from
//             stat av 100 to 160 +random(25).
// bug(s):
// update(s):   Lilith July 2021 Found the /std/act/add_things.c
//                    and updated this file to use it for equipping.
//              Zizuph Aug 2021  added cr_attack_desc so Lilith could
//                    could give unique description to "fists" on 
//                    /std/monster instead of using /std/creature
//              Lilith, Sep 2021: updated the base SS_BLIND_COMBAT amt and
//                setup logging in do_die(), change to npc stat ranges.
//              Lilith Feb 2022: Reduced native armour to 30. Got feedback
//                from Cherek and Zizuph that they are too tough for 
//                the amount of exp generated at kill. Also removed 
//                magic res since the combat system calcs it based on AC now.
//              Lilith May, 2022: removed native armour. Npcs don't give 
//                out enough exp to be worth the work and I don't want to 
//                try to figure out what the 'right' exp_factor should be.

inherit "/d/Avenir/inherit/monster";
inherit "/d/Genesis/specials/npc/stat_based_specials";
#include "/d/Avenir/smis/sys/statserv.h"

#include "../dead.h"
#include <cmdparse.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <money.h>

// Define the 3 different revenant sizes
#define MOB_0     0
#define MOB_1     1
#define MOB_2     2

#define DEATH_LOG "/d/Avenir/log/deaths/revenant"

// Global Variables
public int      Strength = 0;
string *randadj, *randrace, short_desc;

/* 
 * Function:    set_mob_strength
 * Description: Called inside setup_random_mob, it indicates
 *              which elf type this is.
 */
public void
set_mob_strength(int strength)
{
    Strength = strength;
}

/*
 * Function:    get_mob_strength
 * Description: Returns the value set during the random generation.
 */
public int
get_mob_strength()
{
    return Strength;
}

/*
 * Function:    setup_random_mob
 * Description: Randomly select a type of mob to generate.
 *              They base is 100:130:160 +random(25)
 *              Adjective desc helps mortals figure out at a
 *				glance what size their opponents are.
 */
public void
setup_random_mob()
{
    int base_stat, mob_type;  
    string short_desc;
    
    /* The random generation type will take all the existing types
     * and try to do an equal distribution.
	 */
    object * instances = object_clones(find_object(MASTER));
    if (!sizeof(instances))
    {
        mob_type = random(3);
    }
    else
    {
        int * counts = ({ 0, 0, 0 });
        foreach (object instance : instances)
        {
            int strength = instance->get_mob_strength();
            ++counts[strength];
        }
        int mincount = applyv(min, counts);
        mob_type = max(0, member_array(mincount, counts));
    }
    // Set the strength so that it can be looked up later.
    set_mob_strength(mob_type);
    switch (mob_type)
    {
		case MOB_0: add_adj(({"average"}));
			break;  // 100 base			
		case MOB_1: add_adj(({"strong"}));
			break;  // 130 base
		case MOB_2: add_adj(({"tough"}));
			break;  // 160 base
    }
    
    // Set up the actual stats    
    base_stat = 100 + (mob_type * 30) + random(25);
    default_config_npc(base_stat);   		
}


/* This is called by the placer file, not the npc */
void
equip_me()
{
    int size;
    seteuid(getuid());
   
    /* Coin for each eye, based on npc size */
    size = TO->get_mob_strength(); 
    switch (size)
	{
        case 0: MONEY_MAKE_SC(2)->move(this_object());
            break;
	    case 1: MONEY_MAKE_SC(2)->move(this_object()); 
	        break;
		case 2:	MONEY_MAKE_GC(2)->move(this_object());
		    break;
	}
  
	/* Occasional sybarun coin or ring */
	if (random(5) <2)
	    equip("/d/Avenir/common/obj/syb_coin");
    else
		add_armour(OBJ +"ring");
	

	/* Lets make these things wear items that identify what they were in life. 
 	 * None of these items is exceptional in any way.
	 */ 
    /* burial paraphernalia */
    add_armour(OBJ +"death_shroud");
    add_armour(OBJ +"shroud_sash");
       
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
            add_armour("/d/Avenir/common/bazaar/Obj/worn/jpants");
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

string
my_long()
{
	return "This "+ short_desc +" was animated from one of the "
        +"innumerable bodies that fill the niches of the catacombs.\n"	
		+"It seems to be about "+query_exp_title()+" in size, "
		+"but it is hard to be sure of anything where the undead "
		+"are involved.\n"
		+"It appears to be very disturbed by your presence here.\n"
		+"There is a coin covering each eye.\n"
		+"";
}
void
create_monster()
{
	setuid();
    seteuid(getuid());	
    setup_random_mob();
    int wep;
    randadj = ({"bloody","grayish","disgusting","stinking",
              "rotting","slimy","mottled","decayed",
			  "once handsome","moldy-faced","rancid",
			  "insect-infested","bloated"});
    randrace = ({"revenant", "cadaver", "carcass"});

    set_name(({"revenant", "_Dead_Isle_Rev", "undead", "_crypt_crawler"}));
    set_race_name(randrace[random(sizeof(randrace))]);
    set_adj(randadj[random(sizeof(randadj))]);
	    short_desc = implode(query_adjs(), " ") +" "+ query_race();
    set_short(short_desc);
    set_long(my_long);
    set_alarm(1.0,0.0,"set_m_in","staggers in");
    set_alarm(1.0,0.0,"set_m_out","lurches out");
	set_gender(G_NEUTER);
    set_alignment(0);   	
	
	// fights unarmed so lets give skills based on mob size.
    set_skill(SS_AWARENESS,    70 + (15*Strength)); // 70:85:100
    set_skill(SS_DEFENCE,      70 + (15*Strength)); // reduce melee damage 	
    set_skill(SS_ACROBAT,      70 + (15*Strength)); // reduce melee damage
    set_skill(SS_UNARM_COMBAT, 70 + (15*Strength));	 
    set_skill(SS_BLIND_COMBAT, 70 + (15*Strength)); 
    set_skill(SS_SPELLCRAFT,   70 + (15*Strength)); // reduce caster damage
    set_skill(SS_FORM_ABJURATION,70 + (15*Strength)); // reduce caster damage
 	
    // native armour and unarmed attacks are based on mob size.
    wep = 10 + (10*Strength);  
    set_all_attack_unarmed(wep, wep);
 
    // set height and weight to align with size and descs
    add_prop(CONT_I_HEIGHT, TO->query_average_stat());
    add_prop(CONT_I_WEIGHT, TO->query_average_stat() * 300);
    add_prop(LIVE_I_SEE_DARK, 1); 
    add_prop(LIVE_I_UNDEAD, 1);
    add_prop(LIVE_I_NEVERKNOWN,1);
    add_prop(LIVE_I_NO_CORPSE, 1);
    add_prop(LIVE_M_NO_ACCEPT_GIVE, 1);
    
    // I'm mobile and aggressive 
    set_restrain_path(CRYPT);
    set_monster_home(CRYPT +random(100));
    set_random_move(20,0);   

    if (random(3) == 0)    // attacks 33% of the time.
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
    
//    set_alarm(0.1, 0.0, add_attacks);
	
}
/*  Too tough with this. Its like haste but better ;)
void add_attacks()
{
    query_combat_object()->cb_set_attackuse(150);
}
*/
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
	
    //The poison is mostly a nuisance, but lets make it rare anyway. 
	if (89 < random(100))
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
	STATSERV_LOG_EVENT("crypt", "revenants killed");
    /* Logging death for various reasons */
    SCROLLING_LOG(DEATH_LOG, "Rev ("+ TO->query_average_stat() +") by "+
	killer->query_name() +"("+ killer->query_average_stat() +") "+
	(sizeof(killers) ? "with "+ COMPOSITE_WORDS(killers) : "solo"));

    ::do_die(killer);

}
