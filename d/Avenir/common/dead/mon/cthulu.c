 //                  (/d/Avenir/common/dead/mon/crypt_monster
 //                  based on /d/Avenir/common/port/mon/octopus
 // creator(s):       Ibun Mars -04   (Lilith Sept, 2021)
 // last update:
 // purpose:          A little something Lovecraftian and Cthulu-ish
 // note:
 // bug(s):
 // to-do:

inherit "/std/creature";
inherit "/std/combat/unarmed";
inherit "/std/act/action";
inherit "/d/Genesis/specials/npc/stat_based_specials";
#include "/d/Avenir/smis/sys/statserv.h"
#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include <filter_funs.h>
#include "../dead.h"

#define DEATH_LOG "/d/Avenir/log/deaths/revenant"
#define A_ARM8  0
#define A_ARM1  1
#define A_ARM2  2
#define A_ARM3  3
#define A_ARM4  4
#define A_ARM5  5
#define A_ARM6  6
#define A_ARM7  7

#define H_HEAD 8
#define H_ARM1 1
#define H_ARM2 2
#define H_ARM3 3
#define H_ARM4 4
#define H_ARM5 5
#define H_ARM6 6
#define H_ARM7 7
#define H_ARM8 0

int arms = 8;

void
create_creature()
{
	set_living_name("cthulujr");
    set_name(({"monster", "creature", "_spawn_of_cthlulu"}));
    set_race_name("abomination");
	set_adj(({"eldritch", "tentacled", "bizarre"}));
    set_short("eldritch abomination");
	set_long("There are no words to adequately describe the horror that "
	   +"towers over you in its incomprehensible form. Lumpy and glistening, "
	   +"with a body covered in scales and something that looks like fins "
	   +"or vestigial wings on its back, this creature has dozens of feelers, "
	   +"tendrils, and tentacles swarming out from its stumpy head. Some of "
	   +"the tendrils have forked ends with needle-like projections, whilst "
       +"tentacles like thick, muscular arms covered in suckers slide toward "
       +"you. The entire abomination is purest white, which somehow makes it "
	   +"seem even more otherworldly and bizarre.\n");	   
	set_gender(G_NEUTER);
    set_alignment(0); 
    default_config_npc(200 +random(50));
    set_skill(SS_SWIM,             90);
	set_skill(SS_AWARENESS,       100); 
    set_skill(SS_DEFENCE,         100); // reduce melee damage 	
    set_skill(SS_ACROBAT,         100); // reduce melee damage
	set_skill(SS_UNARM_COMBAT,    100);
    set_skill_extra(SS_UNARM_COMBAT, 50);	
    set_skill(SS_BLIND_COMBAT,    100); 
	set_skill(SS_SPELLCRAFT,      100); // reduce caster damage
	set_skill(SS_FORM_ABJURATION, 100); // reduce caster damage

    set_attack_unarmed(A_ARM1,  65, 45, W_BLUDGEON, 50, "feeler");
    set_attack_unarmed(A_ARM2,  65, 45, W_BLUDGEON, 50, "tentacle");
    set_attack_unarmed(A_ARM3,  65, 45, W_BLUDGEON, 50, "tendril");
    set_attack_unarmed(A_ARM4,  65, 45, W_BLUDGEON, 50, "tentacle");
    set_attack_unarmed(A_ARM5,  65, 45, W_BLUDGEON, 50, "feeler");
    set_attack_unarmed(A_ARM6,  65, 45, W_BLUDGEON, 50, "feeler");
    set_attack_unarmed(A_ARM7,  65, 45, W_BLUDGEON, 50, "tendril");
    set_attack_unarmed(A_ARM8,  65, 45, W_BLUDGEON, 50, "tentacle");

    set_hitloc_unarmed(H_HEAD,  ({ 50, 40, 50 }), 15, "head");
    set_hitloc_unarmed(H_ARM1,  ({ 50, 35, 50 }), 10, "feeler");
    set_hitloc_unarmed(H_ARM2,  ({ 50, 35, 50 }), 10, "tentacle");
    set_hitloc_unarmed(H_ARM3,  ({ 50, 35, 50 }), 10, "tendril");
    set_hitloc_unarmed(H_ARM4,  ({ 50, 35, 50 }), 15, "tentacle");
    set_hitloc_unarmed(H_ARM5,  ({ 50, 35, 50 }), 10, "feeler");
    set_hitloc_unarmed(H_ARM6,  ({ 50, 35, 50 }), 10, "feeler");
    set_hitloc_unarmed(H_ARM7,  ({ 50, 35, 50 }), 10, "tendril");
    set_hitloc_unarmed(H_ARM8,  ({ 50, 35, 50 }), 10, "tentacle");

	add_prop(MAGIC_I_RES_MAGIC, 38 +(random(5))); //38-42
	add_prop(LIVE_I_SEE_DARK, 100); 
    add_prop(NPC_I_NO_RUN_AWAY,1);
    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(MAGIC_I_BREATH_WATER, 1);
	add_prop(CONT_I_HEIGHT, (TO->query_average_stat() * 2));
	add_prop(CONT_I_WEIGHT, (TO->query_average_stat() * 500);
    add_prop(NPC_I_NO_FEAR, 1);
    add_prop(NPC_I_NO_LOOKS, 1);
	add_prop(NPC_I_NO_RUN_AWAY, 1);
	add_prop(LIVE_I_NEVERKNOWN, 1);
	add_prop(OBJ_I_INVIS, 1);
	seteuid(getuid(TO));
  
}

public nomask void
cr_got_hit(int hid, int ph, object att, int aid, int dt, int dam)
 /*
    hid:   The hitloc id        ph:    The %hurt
    att:   Attacker            aid:   The attack id
     dt:    The damagetype     dam:   The damage in hit points   */

{
   object arm;

   if(arms && dam>50 && dt==W_SLASH)
   {
      arm=clone_object(OBJ +"tentacle");
      arm->move(environment(TO));
      set_alarm(0.1,0.0,"remove_stuff",arms);
      tell_room(ENV(TO), QCTNAME(att) + " cuts a tentacle off the eldritch creature!\n", 
          att, TO);
      att->catch_msg("You cut a tentacle off the eldritch creature!\n");
 
      ENV(TO)->let_go(att, arms); 
      arms=arms-1;   
   }
   ::cr_got_hit( hid, ph, att, aid, dt, dam);
}

void
remove_stuff(int n)
{
   remove_hitloc(n);
   remove_attack(n);
}

/*
 * Function name:   do_entangle
 * Description:     Called from special_attack, adds attack delay.
 * Arguments:       player / attacker
 */
private int
do_entangle(object victim)
{
   object robe = victim->query_armour(A_ROBE);
      
   if(!present(victim, environment(TO)) )
   {
      return 0;
   }

   if (robe->id("_oilskin_cloak_"))
   {
	    victim->catch_msg("The "+ short() +" tries to grab you " +
	        "but the tentacles and feelers slip off your cloak.\n");
	return 1;
   }
   
   victim->add_attack_delay(10);
   victim->catch_msg("The "+short()+" wraps a tentacle around your torso, "+
      "squeezing you tightly.\n");
   return 1;	  
}

/*
 * Function name:   do_push
 * Description:     Called from special_attack, used to reduce # of attackers.
 * Arguments:       victim / attacker
 */
private void
do_push(object victim)
{
    mixed enemies = query_enemy(-1); 
    string *exit_cmds;
    string exit, dest;
    int    ind;
  
    if (!environment() || !sizeof(enemies))
        return;

    exit_cmds = environment()->query_exit_cmds();
    if (!sizeof(exit_cmds))
        return;
  
    ind = random(sizeof(exit_cmds));
    exit = exit_cmds[ind];
    dest = (environment()->query_exit_rooms())[ind];
  
    tell_watcher("One of the "+ short() +"'s huge tendrils slams into "+ QNAME(victim) + 
        ", who flies " + exit + "!\n", this_object(), victim);
  
    victim->catch_msg("You've been struck with a huge tendril! It sends you flying "+ 
        exit +"!\n");
  
    /* Move them, make peace with them */
    victim->move_living(exit, dest, 1);
    victim->stop_fight(TO);
}

private int
do_needles(object victim)
{
    // Choose power of hit based on mob stat size.
    hitresult = do_stat_based_attack(TO, victim, W_BLUDGEON);
	
	// The attack was evaded
	if (intp(hitresult))
		return 1;
	
    if (hitresult[0] <= 0)
    {
        // Handle misses.
        query_combat_object()->tell_watcher(QCTNAME(TO) + " tries to bite " + QTNAME(victim) +
	        " with one of its tendrils but misses completely.\n", victim);
        victim->catch_msg(QCTNAME(TO) + " tries to bite you with one of its "
		    +"tendrils but misses completely!\n");
        return 1;
    }
    // hitresult as percentage of health
    how = "unharmed";
    if (hitresult[0] > 0)
	how = "a slight scrape of your skin.";
    if (hitresult[0] > 5)
	how = "a prickle where the needles grazed you.";
    if (hitresult[0] > 10)
	how = "a surge of pain where the needles landed.";
    if (hitresult[0] > 25)
	how = "an angry burning pain shooting through you!";
    if (hitresult[0] > 50)
	how = "agony as poison seeps into you from a hundred needles!";

    hdesc = hitresult[1];
    query_combat_object()->tell_watcher(QCTNAME(TO) + " snakes a tendril toward "+ 
	    QTNAME(victim) + " that sinks needles into "+victim->query_possessive() +" "+ hdesc 
		+"\n", victim); 
    victim->catch_msg(QCTNAME(TO) + " snakes a tendril toward you, and its needles "
	    +"sink into your "+ hdesc +"!\n");
    victim->catch_msg("You feel " + how + "\n");
	
	//The poison is mostly a nuisance. 
	if (random(5) == 0)
	{
	    poison = clone_object(OBJ +"bite_poison");
        poison->reconfig_me(10 +random(40));
        poison->move(victim, 1);
        poison->start_poison();
	}

    return 1;
}


/* which enemies are in the room with me?*/
public mixed
query_p_enemies(void)
{
    return TO->query_enemy(-1) &
	filter(all_inventory(environment(TO)), living);
}

public int
special_attack(object victim)
{
    object *enemies = query_p_enemies();
    object enemy = one_of_list(enemies); 	
    mixed * hitresult;
	int avg_stat, hurt;
    string how, hdesc;
	
    if (ENV(victim) != ENV(TO) || victim->query_ghost())
    {
        TO->stop_fight(victim);
        return 1;
    }
	
    switch(random(4))
	{
		case 0: return 0; 
		case 1: do_entangle(enemy); return 1;
		case 2: do_push(enemy);     return 0;
		case 3: do_needles(enemy);  return 0;
		default: return 0;
	}
	
	return 0;
}


void
init_living()
{
   add_action("do_search","search");
   
    /* If the living is a player and player can see me */
    if (interactive(TP) && CAN_SEE(TP, TO))
        command("kill "+ TP->query_name());
	
   ::init_living();
}


public void
do_die(object killer)
{
    object *foos = query_enemy(-1);
    string *killers;
	
    if (query_hp() > 0)
        return;
	
	if (!present("_av_eldritch_tentacle"))
		clone_object(OBJ +"tentacle")->move(TO, 1);
	
    if (!killer)
        killer = previous_object();
	
    foos -= ({ killer });
    killers = (foos)->query_name();
	STATSERV_LOG_EVENT("crypt", "spawn of Cthulu killed");
    /* Logging death for various reasons */
    SCROLLING_LOG(DEATH_LOG, "Cthulu-spawn ("+ TO->query_average_stat() +") by "+
	killer->query_name() +"("+ killer->query_average_stat() +") "+
	(sizeof(killers) ? "with "+ COMPOSITE_WORDS(killers) : "solo"));

    ::do_die(killer);
}

int
do_search()
{
   remove_prop(OBJ_I_INVIS);
   TP->catch_msg("An inconceivably bizarre creature arises from the pool of "+
      "water, flailing masses of tentacles and feelers toward you.\n");
   command("kill "+TP->query_name());
   STATSERV_LOG_EVENT("crypt", "spawn of Cthulu awakened");
   return 1;
}

void
attacked_by( object ob )
{
   ::attacked_by(ob);
   if (random(3))
        do_entangle(ob);
}

