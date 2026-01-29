// spectral guardian  /d/Avenir/common/dead/mon/spectral_guardian
// creator(s):        Lilith July 2021
// last update:
// purpose:           Spectral Guardian of the Tombs of the High Lords.
//                    This is an incorporeal spectral minion who has
//                    chosen to guard the tomb of a High Lord.
//                    It is non-aggressive unless someone tries to
//                    enter the area it protects.
//                    Since it has no true corporeal body, it can only be damaged
//                    by magical weapons, however, it has a native immunity 
//                    to most spellcast magic.
//
//                    If you wear a death mask you can get past it w/o
//                    being attacked
// note:
// bug(s):
// to-do:   ZIZ:  I need a magical roar attack that does psychic damage and increases panic.
//                 also randomized cloning of 2 of the spectral items

inherit "/lib/unique";
inherit "/std/monster";
inherit "/std/combat/unarmed";
inherit "/d/Genesis/specials/npc/stat_based_specials";
inherit "/d/Genesis/specials/resist";
inherit "/d/Avenir/inherit/defeat";
#include "/d/Avenir/include/relation.h"
#include "/d/Avenir/include/defs.h"
#include "/d/Avenir/smis/sys/statserv.h"

#include <composite.h>
#include <filter_funs.h>
#include <formulas.h>
#include <language.h>
#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include <wa_types.h>

#include "../dead.h"

#define KILL_FILE	"/d/Avenir/log/deaths/spectral_guardian"
#define DEBUG 1

int alarm_id, been_attacked, last_start_fight = time(), last_hit, who, me, o_stat;
object wep1, wep2, armr1, armr2;

/* Function prototypes */
string my_long();
void drop_unwanted(object what, object who);

/* Create the npc */
void
create_monster()
{
    /* If I'm not a clone, don't bother with the rest */
    if (!IS_CLONE)
        return;

    set_race_name("guardian");
    add_name(({"_Avenir_Spectral_Guardian", "spectral guardian", 
	    "specter", "spectre"}));
    add_adj(({"bright", "brightly-glowing", "glowing", "spectral" }));
    set_gender(G_NEUTER);
    set_long(my_long);
    set_short("spectral guardian ");
	
    default_config_npc(random(20) + 130);
    set_attack_unarmed(0,50,50,W_SLASH | W_IMPALE,50,"scythe-like right claw");
    set_attack_unarmed(1,50,50,W_SLASH | W_IMPALE,50,"scythe-like left claw");
    set_all_hitloc_unarmed(50); // Native armor in all hitlocs is 50
    set_alignment(1000); // To the outside world, this dutiful guardian is "good"
    set_stat_extra(SS_INT, 50);
	set_stat_extra(SS_WIS, 50);
	
    set_skill(SS_2H_COMBAT, 100);
    set_skill(SS_WEP_SWORD, 100);
    set_skill(SS_WEP_KNIFE, 100);
    set_skill(SS_BLIND_COMBAT, 100);
	set_skill(SS_AWARENESS, 100);
    set_skill(SS_PARRY, 150);
    set_skill(SS_ACROBAT, 150);
    set_skill(SS_DEFENCE, 150);
    set_skill(SS_UNARM_COMBAT, 150);

	add_prop(LIVE_I_QUICKNESS, 125);
    add_prop(LIVE_I_UNDEAD, 1); 
    add_prop(LIVE_I_SEE_DARK, 1);
	add_prop(LIVE_I_NO_CORPSE, 1); 
	add_prop(NPC_I_NO_RUN_AWAY,1);
    add_prop(NPC_I_NO_FEAR, 1);
	add_prop(NPC_I_NO_LOOKS, 1);
    add_prop(CONT_I_HEIGHT, 240);
    add_prop(CONT_I_WEIGHT, 5000);  /* Insubstantial */
    add_prop("_live_m_attack_thief", "thief_fun");
    add_leftover(OBJ + "spectral_orb", "spectral orb",1, "", 1,0);
    remove_prop(NPC_M_NO_ACCEPT_GIVE);
	
    set_act_time(20);
     add_act("emote floats motionlessly in the air.");
     add_act("emote leaves a greenish after-blur in the air as it moves.");
	 add_act("emote seems to glow even brighter as it draws strength from "
	     +"an unknown source.");
	 add_act("emote seems to move without moving as the green energy it "
	     +"is made of pulses around it.");
	 add_act("emote is so charged with energy that you can feel wave after "
	     +"wave of it pulsing against you.");
	 add_act("emote slowly turns its head and looks directly at you.");
	 add_act("emote appears to be a fixed point in space around which "
	     +"everything else moves.");
    set_cact_time(4);
      add_cact("emote skewers you with a stray shard of spectral energy "
	     +"that burns with ice-cold intensity for just a moment.");
      add_cact("emote whips a tendril of glowing greenish energy in your "
	     +"direction.");
	  add_cact("emote follows your every move with the glowing orbs of "
	     +"its eyes.");
	  add_cact("emote lunges at you, trailing streaks of green energy.");
    set_m_in("swirls in");
	set_mm_in("rapidly takes form in the gathering mist.");
    set_restrain_path("/d/Avenir/common/dead/catacombs/");
    set_monster_home("/d/Avenir/common/dead/catacombs/crypt_s7");
    set_exp_factor(125); /* because it is so hard to kill  */
 
}

void
equip_me()
{
    seteuid(getuid());
}

string
my_long()
{
    string  str;

    str = "A luminous green mist has coalesced into the form of an "
        +"ancient warrior.\n"
	    +"It is an insubstantial, vaporous being of spectral energy that "
		+"glows a strange and somewhat unnerving greenish colour. "
		+"Parts of it seem to dissipate into nothingness, only to swirl "
		+"back into view again in a pulsing, chaotic ebb and flow.\n"
		+"Only its equipment seems contain its form or have any solidity.\n"
		+"It radiates watchfulness and ferocity.\n";
	return str;

}


/*
 * Function name:   reconfig_me()
 * Description:     This function scales npc based on size of enemy
 * Arguments:       ob - attacker
 * Notes:           called through attacked_by and init_living
 */
void
reconfig_me(object ob)
{
    int s, t;

    /* Lets try to stop resets in combat. */
    if (this_object()->query_hp() < this_object()->query_max_hp())
        return;

    /* Scale to opponent */
    s = ob->query_average_stat();
    o_stat = s;

    switch (s)
    {
        case 15..100:   t = (s / 6); break; /* 16% larger */
        case 101..150:  t = (s / 5); break; /* 20% larger */
        case 151..199:  t = (s / 4); break; /* 25% larger */
        case 200..250:  t = (s / 3); break; /* 33% larger */
        case 251..400: 	t = (s / 2); break; /* 50% larger */	
        default:        t = (s / 2); 
    }   

    default_config_npc(t + s);
    refresh_living();      

}


void
thief_fun(object thief, object victim, object ob)
{
    been_attacked = 1;
	set_alarm(1.0, 0.0, &command("emote makes a slow staccato "
	    +"sound that might be laughter--or a curse."));
    set_alarm(1.8, 0.0, &command("kill " + OB_NAME(thief)));
}

public void
enter_inv(object obj, object from)
{
    ::enter_inv(obj, from);
	
    if (obj->id("poison"))    //poisons have no effect
		obj->remove_object();
	if (obj->id("paralyze")); // paralyze has no effect
	    obj->remove_object();
    if (living(from))
        set_alarm(2.0, 0.0, &drop_unwanted(obj, from));
    return;
}

void 
drop_unwanted(object what, object who)
{
 	command("emote seems to watch as the "+ what->short() +" slowly drifts "+
	    "through it and falls to the ground.\n");
	what->move(ENV(TO),1);
    return;
}

/*
 * check_meet look for infidels, 
 */
void
check_meet(object tp)
{
    if (!present(tp, environment(TO)))
        return;

    if (IS_INFIDEL(tp))
    {
		reconfig_me(tp);
        command("kill "+ OB_NAME(tp));
        return;
    }
	if (tp->query_prop("_live_m_attack_thief"))
	{
		reconfig_me(tp);
        command("kill "+ OB_NAME(tp));
        return;
	}		
    if (tp->query_prop(DMASK_PROP))
    {
        command("bow to "+ OB_NAME(tp));
        return;
    }       
}


/* Add some magical resistance to even the playing field */
varargs mixed 
query_magic_protection(string prop, object what)
{
    if (what == this_object())
    {
	    switch(prop)
        {   /* Mostly incorporeal and resistant to magic spells */
			case MAGIC_I_RES_FIRE:	// Fire is its vulnerability
			    return ({ 20, 1 });
			case MAGIC_I_RES_COLD:
            case MAGIC_I_RES_DEATH:
            case MAGIC_I_RES_ELECTRICITY:
            case MAGIC_I_RES_LIFE:
                return ({ 50, 1 });
            default:
              break;
        }
    }
    return ::query_magic_protection(prop, what);
}


/*
 * Function name:   attacked_by
 * Description:     This routine is called when we are attacked.
 * Arguments:       ob: The attacker
 */
void
attacked_by(object ob)
{
    ::attacked_by(ob);
    TO->set_intoxicated(intoxicated_max());
    if (!been_attacked)
    {
        been_attacked = 1;
        reconfig_me(ob);
    }
}



/*
 * Function name:   do_push
 * Description:     Called from special_attack, used to reduce # of attackers.
 * Arguments:       victim / attacker
 */
private void
do_push(object victim)
{
    mixed enemies = FILTER_PRESENT_LIVE(query_enemy(-1)); 
    string *exit_cmds;
    string exit;
    int    ind;
  
    if (!environment() || !sizeof(enemies))
        return;

    object selected = one_of_list(enemies);    

    tell_watcher("The "+ short() +" appears to toss a ball of spectral " 
	    +"energy into "+ QNAME(selected) +", who stumbles away"
		+"!\n", TO, selected);
    selected->catch_msg("A roiling ball of spectral green energy splatters "
        +"all over you. It is shockingly cold and... Oh dear gods it "
        +"BURNS!\n");
    int damage = F_PENMOD(60, 100) * F_STR_FACTOR(query_average_stat())
        / 100;
    damage -= damage * combine_resistances(selected, 
        ({MAGIC_I_RES_DEATH, MAGIC_I_RES_MAGIC})) / 100;
        
    selected->hit_me(damage, MAGIC_DT, this_object(), -1);

    object shadow = clone_object(OBJ + "fear_sh");
    shadow->configure_shadow(selected, this_object());
    selected->run_away(); 
}


public void
do_roar(object victim)
{
    mixed enemies = FILTER_PRESENT_LIVE(query_enemy(-1)); 

    if (!environment() || !sizeof(enemies))
        return;

    tell_room(environment(), QCTNAME(this_object()) + " draws back and emits a "
      + "disturbing, cacophonous roar.\n");

    int heal = 0;

    foreach (object enemy : enemies)
    {
        if (environment(enemy) != environment())
        {
            continue;
        }
        
        int damage = F_PENMOD(60, 100) * F_STR_FACTOR(query_average_stat())
            / 100;
        damage -= damage * combine_resistances(enemy, 
            ({MAGIC_I_RES_DEATH, MAGIC_I_RES_MAGIC})) / 100;
        mixed * result = enemy->hit_me(damage, MAGIC_DT, this_object(), -1);
        if (sizeof(result) >= 4)
        {
            heal += result[3] / 2; // Half the damage sent will be healed.
            // A portion of the damage causes panic.
            enemy->add_panic(result[3] / 5);  
        }
        string msg = "";
        switch (result[0])
        {
            case -3..0:
                msg = "You feel unaffected by the eerie sound.\n";
                break;
            case 1..5:
                msg = "The sound rings in your ears.\n";
                break;
            case 6..10:
                msg = "The sound strongly reverberates in your head.\n";
                break;
            case 11..20:
                msg = "Your head pounds heavily from the frightful noise.\n";
                break;
            default:
                msg = "Your eyes roll back in your head from the painful "
                + "sound.\n";
           
        }
        enemy->catch_msg(msg);
    }
    
    string heal_type = "";
    switch (heal)
    {
        case 0..100:
            heal_type = "barely";
            break;
        case 101..200:
            heal_type = "slightly";
            break;
        case 201..500:
            heal_type = "somewhat";
            break;
        case 501..750:
            heal_type = "";
            break;
        default:
            heal_type = "greatly";
            break;
    }
    tell_room(environment(), QCTNAME(this_object()) + " is " + heal_type + 
       " strengthened with the energy drawn by its beckoning call.\n");
        
    heal_hp(heal);
	
    return;
}



/*
 * Function name: special_attack
 * Description:   Called from the external combat object's heart_beat
 *                routine. By redefining this, monsters can easily attack
 *                with spells or take special actions when engaged
 *                in combat.
 * Arguments:     victim (the one we are fighting right now)
 * Returns:       0 - if we want the round to continue
 *                1 - if we are done with this round
 * Note:          By always returning 1 the mobile is unable
 *                to do an ordinary attack.
 */
int
special_attack(object victim)
{
    object     me,
              *enemies;
    int        i, con, s, sInt; 

    if (ENV(victim) != ENV(TO) || victim->query_ghost())
    {
        TO->stop_fight(victim);
        return 1;
    }

    // If we've got a team and the smallest one challenged it, reset.
    if (victim->query_average_stat() > o_stat)
        reconfig_me(victim);
    
    me = this_object();
    enemies = query_enemy(-1);

    switch (random(4))
    {
        case 0: do_push(victim);                
            return 0;
        case 1: do_roar(victim);
            return 0;        
        case 2: 
		    TO->set_intoxicated(intoxicated_max());
            return 0;    
		case 3: 
           return 0;
        default: 
    }
    return 0;
}


void
init_living()
{
    if (!objectp(query_attack()))
        reconfig_me(TP); 
}  

void
do_die(object killer)
{
   command("emote expands rapidly in all directions at once, dissipating "
       +"into nothingness.\nFor how long though?\n");
   ::do_die(killer);
}

