/**
* Coded by Louie 2004
* 
* Gnomish grenade/bomb/explosive device
*
* This is the quest reward for successfully designing and building
* an explosive device.
*
* It can be thrown to either cause damage, disarm, or both.
* Logic for success is in calculate_success().
*
* For disarming, it simply makes the target unwield all.  
*
* For damage, it does a random(max), where max is either 1/5 or 1/3 of
* either the enemies current health, or max health.  It's all random.
*
* Of course, it's a gnomish, so there's always a chance it fails :)
*
*/
#pragma strict_types

#include "../local.h"
#include <stdproperties.h>
#include <formulas.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <cmdparse.h> 


inherit "/std/object";
inherit "/cmd/std/command_driver";  

object grenade;
object target;
int size;
int do_disarm;
int do_damage;
int throwing;

/** prototypes **/
void do_really_throw();
void set_size(int i);
void set_do_disarm(int i);
void set_do_damage(int i);
string size_descrip();
void calculate_failure();
void calculate_success();

/*
* Create
*/
void
create_object()
{

	set_name("device");
    add_name(({"explosive","_gnome_grenade","grenade"}));
    set_short("gnomish explosive device");
    set_adj("gnomish");
    add_adj(({"gnomish","explosive"}));
    set_long("This is a gnomish explosive device created " +
    	"deep within the Gnomish Colony in Krynn.  " +
    	"The device is about the size of a" +
    	"@@size_descrip@@" +
    	".  " +
    	"It appears it can be thrown.  " +
    	"\n");
    
    size = 0;
    do_disarm = 0;
    do_damage = 1;
    throwing = 0;
    
    add_prop(OBJ_I_WEIGHT, 5);
    add_prop(OBJ_I_VOLUME, 1);
    add_prop(OBJ_I_VALUE, 0);

}


void
init()
{
	::init();
	add_action("do_throw","throw");
	add_action("do_throw","toss");
}

string
size_descrip()
{
	string str;
	
	if (size < 2)
	{
		return " small rock";
	} 
	
	if (size < 14)
	{
		return " fist";
	}
	
	return " cannon ball";

}

void
set_size(int i)
{
	size = i;
}

void
set_do_disarm(int i)
{
	do_disarm = i;
}

void
set_do_damage(int i)
{
	do_damage = i;
}

/*
* Attempt to throw the grenade at a target
*/	
int
do_throw(string str)
{

    //object target, enemy, *obj;
    object enemy, *obj;    
    	
		
	if (!strlen(str))
	{
		NF("Throw what at whom?\n");
		return 0;
	}
	
    /* What are we attacking anyway? */
    /*see if we're just trying to throw it at the (first) person */
    /*we're in combat with*/
    if ((str == "grenade" || str == "device" || str == "explosive device")
    	&&
    	(enemy = TP->query_attack())
    	)
    {
   		target = enemy;
    } 
    else if ((sizeof(obj = 
    	parse_this(str, "'grenade' [at] [the] %l")))
    	||
    	(sizeof(obj =
    	parse_this(str, "'device' [at] [the] %l")))
    	||
    	(sizeof(obj =
    	parse_this(str, "'gnomish device' [at] [the] %l"))))
    {
		target = obj[0];
    } 
    else 
    {
    	NF("Throw what at whom?\n");
    	return 0;
    }
	
	/*One last check to make sure we really have an enemy*/
	if (!target) {
		NF("Throw what at whom?\n");
		return 0;
	} 

	if (throwing)
	{
		NF("You're already in the process of throwing!\n");
		return 0;
	}
	
	throwing = 1;
		
	/* There's some issue with using query_the_name from this*/
	/*object.  Rather than figure it out I'm just not going to */
	/*refer to people directly :) */
	
	write("You prepare to throw your explosive device!\n");
			
	set_alarm(4.5,0.0, &do_really_throw());
	
	return 1;
}

/*
* Throw the grenade at a target
*/
void
do_really_throw()
{
	
	/*80 tohit = 75% chance according to 'man cb_tohit'*/
	int chance_to_hit = 80;
	object comobj;
	int hit;
	
	
	if (!target) 
	{
		NF("You have lost your target.\n");
		throwing = 0;
		return;
	}
	
	/*Ok we're throwing a grenade and we have a target*/

	comobj = TP->query_combat_object();
	
	if (!comobj)
	{
		NF("You have no combat object, aborting grenade throw.  "+
			"please <bug> the object with this message.\n");
		throwing = 0;
		return;
	}

	/** Gnomish object always fails sometimes :) **/
	if (!random(10))
	{
		calculate_failure();
		remove_object();
		return;
	}
	
	/** Really see if it worked **/
	/*30 weapon-to-hit is worse than the best store bought*/
	/*target is the thing we're throwing the grenade at.*/	
	if ((hit = comobj->cb_tohit(-1, 30, target)) > 0)
	{
		calculate_success();
		
	} else
	{
		calculate_failure();
	}
	
	remove_object();
	
}

/*
* Figure out a successful hit.
* It's a gnome device, who knows what the hell will happen
*/
void
calculate_success()
{
	int dam, maxdam, chance;
	
	chance = random(100);

	write("The gnomish device hits and explodes!\n");
	
	say(QCTNAME(TP) +
		" throws a gnomish-looking device through the air, which " +
		"explodes with a loud boom!\n", ({TP,target}));
		
	target->catch_msg(QCTNAME(TP) + 
		" throws a gnomish-looking device at you, which " +
		"explodes with a loud boom!\n");
	target->command("$scream");
				
	/*If we're disarming, it's more likely to succeed if */
	/*we're not also trying to do damage*/
	if (do_disarm)
	{
		if ((do_damage && random(3))
			||
			(!(do_damage) && random(5)))
		{
			target->command("$unwield all");
		}
			
	}
	
	/*If we're doing damage, figure out how much*/
	if (do_damage) {
		switch (chance)
		{
			case 0..79:
				maxdam = target->query_hp() / 3;
				dam = random(maxdam) + random(maxdam);
				break;
			case 80..94:
				maxdam = target->query_max_hp() / 5;
				dam = random(maxdam) + random(maxdam);
				break;
			case 95..100:
				maxdam = target->query_max_hp() / 3;
				dam = random(maxdam) + random(maxdam);
				break;
			default:
				dam = random(100) + 1;
				write("Bug while calculating damage, please report using <bug>.\n");
				break;
		}
	
		if (TP->query_wiz_level()) 
		{
			write("Grenade does damage: "+dam+".\n");
		}
		target->heal_hp(-dam);
		if (target->query_hp() < 1)
		{
			target->do_die(TP);
		}
	}
}

/*
* Failed to hit our target, so figure out what happened
*/
void
calculate_failure()
{
	int chance = random(100);
	
	switch (chance)
	{
		case 0..49:
			write("You throw the gnomish device but completely miss.\n");
			say(QCTNAME(TP) +
				" throws a gnomish-looking device "+
				"but fails to hit anything.\n", ({TP,target}));
			target->catch_msg(QCTNAME(TP) +
				" throws a gnomish-looking device at you, " +
				"but it does not even come close.\n");
			break;				
		case 50..100:
			write("The gnomish device makes a loud buzzing noise "+
				"and detonates in a massive explosion!\n");
			say(QCTNAME(TP) +
				" is suddenly engulfed in a massive explosion!\n");
			TP->heal_hp(-(random(TP->query_hp())));
			if (TP->query_hp() < 1)
			{
				TP->do_die(TP);
			}
			break;
		default:
			write("Bug while calculating failure, please report using <bug>.\n");
			break;
	}
}
		
				