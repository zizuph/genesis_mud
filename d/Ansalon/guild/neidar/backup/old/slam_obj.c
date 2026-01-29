/*
Stun/slow special for dwarven guild

Idea from dragon fear coded by Erine & Jeremiah.

Coded : 4/97 by Arman
*/


inherit "/std/object";
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <stdproperties.h>
#include <cmdparse.h>
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/pax/local.h"

private int attacker_skill = 0;
private int attacker_str = 0;
private int shield_ac = 0;
int amount_affected;

int time;

object victim;


create_object() 
{
    seteuid(getuid());
    set_name("dwarven_special_obj");

    add_prop(OBJ_I_VOLUME, 0);
    add_prop(OBJ_I_WEIGHT, 0);
    add_prop(OBJ_I_NO_DROP, 1);
    add_prop(OBJ_I_NO_GIVE, 1);
    add_prop(OBJ_I_VALUE, 0);

    set_no_show();
}

/*
init()
{
    ::init();
}
*/


void
remove_slam(object victim)
{
    object vict = victim; 

    victim->remove_stun();
    if(amount_affected > 0 || !P("dwarven_special_obj", victim))
    {
	vict->catch_msg("You feel you have recovered from " +
	  "the slam attack.\n");
	tell_room(E(vict), QCTNAME(vict) + " seems to have " +
	  "recovered from the slam attack.\n",victim,TO);
    }

    remove_object();
}

set_slam(int new_level)
{
    attacker_skill = new_level;
}

set_shield_ac(int ac)
{
    shield_ac = ac;
}

int
query_shield()
{
    return shield_ac;
}

int
query_level()
{
    return attacker_skill;
}

set_attacker_str(int new_str)
{
    attacker_str = new_str;
}

int
query_attacker_str()
{
    return attacker_str;
}


void
do_slam()
{
    int time;
    int formula;
    int victim_str, victim_dex, victim_con;
    int victim_head;

    if(victim->query_humanoid() == 0)
    {
	victim_head = 40;
    }
    else
    if(TP->query_armour(TS_HEAD) == 0)
	victim_head = 1;
    else
	victim_head = TP->query_armour(TS_HEAD)->query_ac();


    victim_str = victim->query_stat(SS_STR);

    victim_dex = victim->query_stat(SS_DEX);

    victim_con = victim->query_stat(SS_CON);

    formula = (query_level() + query_attacker_str() + query_shield() +
      random(100) + 1) -
    (victim_str + victim_head + random(200) + 1);


    if(formula > 0)
    {
	if(formula > 10)
	{
	    if(formula > 50)
	    {
		if(formula > 100)
		{
		    amount_affected = 100;
		}
		else
		    amount_affected = 40;
	    }
	    else
		amount_affected = 20;
	}
	else
	    amount_affected = 10;
    }
    else
	amount_affected = 0;


    victim->add_stun();


    if(amount_affected == 0)
    {
	victim->catch_msg("You are unaffected by his attack.\n");
	tell_room(E(victim), QCTNAME(victim)+ " looks " +
	  "unaffected, shrugging off the attack effortlessly.\n",
	  victim, TO);
	time = 1;
    }
    else
    if(amount_affected == 10)
    {
	victim->catch_msg("You stumble, knocked slightly off balance " +
	  "by the attack.\n");
	tell_room(E(victim), QCTNAME(victim)+ " stumbles, " +
	  "knocked slightly off balance by the attack.\n",victim,TO);
	time = 10;
    }
    else
    if(amount_affected == 20)
    {
	victim->catch_msg("You struggle to keep your " +
	  "feet after the mighty attack.\n");
	tell_room(E(victim), QCTNAME(victim) + " struggles " +
	  "to keep " +HIS(victim)+ " footing.\n",victim, TO);
	time = 20;
    }
    else
    if(amount_affected == 40)
    {
	if(victim->query_humanoid())
	{
	    victim->catch_msg("Your knees buckle and you " +
	      "fall backwards, unable to keep your footing.\n");
	    tell_room(E(victim), QCTNAME(victim)+ "'s knees " +
	      "buckle, forcing " +HIM(victim)+ " backwards onto the ground.\n",victim,TO);
	    time = 30;
	}
	else
	{
	    victim->catch_msg("You retreat backwards fearfully " +
	      "after such a hard hit!\n");
	    tell_room(E(victim), QCTNAME(victim) + " retreats " +
	      "backwards fearfully after such a mighty hit!\n", victim, TO);
	    time = 30;
	}
    }
    else
    if(amount_affected == 100)
    {
	victim->catch_msg("You feel dizzy... Is that the " +
	  "ground coming up to meet you?\n");
	tell_room(E(victim), QCTNAME(victim)+ " collapses to the " +
	  "ground, dazed and totally unaware of " +HIS(TP)+
	  " surroundings.\n", victim, TO);
	time = 40;
    }


    set_alarm(itof(time), 0.0, "remove_slam", victim);
    time = 0;
}


void
enter_env(object to, object from)
{
    ::enter_env(to, from);
    if(!objectp(to))
    {
	remove_object();
	return;
    }

    if(!living(to))
    {
	remove_object();
	return;
    }

    victim = to;
    do_slam();
}
