/**
* Coded by Louie 2004
* 
* Prototype explosive device.
* Updated by Mirandus to allow for some other sytaxes - March 23, 2015
* This is a prototype explosive device that a player can build inside
* of the manufacturing room (expl9.c).  It holds a couple of variables
* (damage/disarm) related to the final bomb.
*
* The player can insert the ignition device into the prototype and 
* attempt to make an explosive.  The chance of success is based on:
*
* - if the player had the designer gnome (design_gnome.c) in the design
* room (expl3.c) approve their request form (wavier.c).
* - if the player had the design (design.c) approved by the gnomish
* committee (approve_gnome.c) in the approval room (expl4.c)
* - if the player is inside the Arming Room of the gnomish explosive center.
* - Randomness.  It's a gnome invention after all :)
*
*/
#pragma strict_types

#include "../local.h"
#include <stdproperties.h>
#include <macros.h>
#include <cmdparse.h> 


inherit "/std/object";

/*prototypes*/
void set_chance(int i);
int get_chance();
void set_do_damage(int i);
int get_do_damage();
void set_do_disarm(int i);
int get_do_disarm();


int perc_chance_succeed;
int do_damage;
int do_disarm;
int verified;

/*
* Create
*/
void
create_object()
{

	set_name("prototype");
    add_name(({"explosive","_gnome_prototype","grenade","device"}));
    set_short("gnomish explosive device prototype");
    set_adj("gnomish");
    add_adj(({"gnomish","explosive","device","prototype"}));
    set_long("This is a prototype of a gnomish explosive device created " +
    	"deep within the Gnomish Colony in Krynn.  " +
    	"It is currently disarmed. The wires of the ignition component are "+
    	"disconnected and hang from the device.  " +
    	"Connecting the wires to the ignition component of the prototype would "+
    	"arm the potentially powerful explosive device.  " +
    	"\n");
    	
    add_item(({"ignition","ignition component","component",
    	"wires","string"}),
    	"The wires of the ignition component hang outside of the device.  " +
    	"You could likely connect the wires to the device in order "
		+"to arm it.\n");
    	
    perc_chance_succeed = 0;
    do_damage = 0;
    do_disarm = 0;
    verified = 0;
    
 seteuid(getuid());
    add_prop(OBJ_I_WEIGHT, 5);
    add_prop(OBJ_I_VOLUME, 1);
    add_prop(OBJ_I_VALUE, 0);

}

void
init()
{
	::init();
	add_action("do_insert","connect");
	
}

/*
* Attempt to turn the prototype into an explosive device.
* It helps if they had their request form approved by the designer gnome,
* had their design approved by the approval committee, and are in the
* Arming Room of the gnomish explosives center.
*/
int
do_insert(string str)
{
	int xp;
	object bomb, request, design;
	
	if (!strlen(str)) 
	{
		NF("Connect the wires to the device?\n");
		return 0;
	}
	
	if (!(str == "wires to the device") &&
		!(str == "wires") &&
		!(str == "wires to the prototype") &&
		!(str == "wires to grenade") &&
		!(str == "wires into prototype") &&
		!(str == "wires prototype")
		)
	{
		NF("Connect the wires to the device?\n");
		return 0;
	}
	
	if (!(verified) &&
		!(environment(TP)->query_short() == 
			"Arming Room in the Explosives Development Center")) {
		write("You pause, uncertain if it is wise to arm the "+
			"device outside of the Arming Room of Gnomish Industries.  "+
			"You know that if you attempt to connect the wires again, "+
			"there will be no going back.  "+
			"\n");
		verified = 1;
		return 1;
	}
	
	/**base 40% chance**/
	perc_chance_succeed = 40;
	
	/**start calculating xp while we're here**/
	xp = GNOME_BOMB_QUEST_XP;
	
	/**If the gnome committee approved their design, bonus**/
	if (TP->query_prop(LIVE_I_DESIGN_APPROVED))
	{
		perc_chance_succeed += 15;
		xp += GNOME_BOMB_QUEST_BONUS_XP;
	}
	
	/**If the gnome approved their request form, bonus**/
	if (TP->query_prop(LIVE_I_WAIVER_APPROVED))
	{
		perc_chance_succeed += 15;
		xp += GNOME_BOMB_QUEST_BONUS_XP;
	}
	
	/**If they are in the arming room, bonus**/
	if (environment(TP)->query_short() ==
			"Arming Room in the Explosives Development Center")
	{
		perc_chance_succeed += 15;
	}
	
	if (TP->query_wiz_level())
	{
		write("Wizinfo: Percent chance to succeed:"+perc_chance_succeed+".\n");
	}
	
	if (random(100) < perc_chance_succeed)
	{
		write("You connect the wires of the ignition component to "+
			"the device, successfully creating a "+
			"gnomish explosive device.\n");
		
		bomb = clone_object(GNOME_OBJ+"grenade");
		bomb->set_do_disarm(do_disarm);
		bomb->set_do_damage(do_damage);
		bomb->move(TP);
		
		
		if (!TP->test_bit(GNOME_DOM, GNOME_GRP, GNOME_BIT))
		{
			write("You feel more experienced!\n");
			TP->add_exp_quest(xp, 0);
			TP->set_bit(GNOME_GRP, GNOME_BIT);
			K_QUEST_LOG("quest","Gnome Explosives", TP, xp);
		}

            K_QUEST_LOG("gnome_explosive_built","Gnome Explosive Built", TP, 0);
		
		
	} else
	{
		write("You connect the wires of the ignition component to "+
			"the explosive device and it immediately starts "+
			"smoking and implodes - it appears you failed.\n");
		
	}
	
	TP->remove_prop(LIVE_I_WAIVER_APPROVED);
	TP->remove_prop(LIVE_I_DESIGN_APPROVED);
	
	/**Since we're removing the props we should also remove the**/
	/**design and request form so people have to do the entire **/
	/**quest again to get another bomb, rather than just running**/
	/**back and getting more parts**/

	write("Since you no longer need it, you throw away whatever "+
		"paperwork you may be carrying.\n");
			
	if (request = present("_gnome_request_form", TP))
	{
		request->remove_object();
	}
	
	if (design = present("_gnome_design_form", TP))
	{
		design->remove_object();
	}
	
	remove_object();
	
	return 1;
	
}

void
set_chance(int i)
{
	if (i < 0)
	{
		i = 0;
	}
	
	perc_chance_succeed = i;
}

int
get_chance()
{
	return perc_chance_succeed;
}

void
set_do_damage(int i)
{
	do_damage = i;
}

int
get_do_damage()
{
	return do_damage;
}

void set_do_disarm(int i)
{
	do_disarm = i;
}

int
get_do_disarm()
{
	return do_disarm;
}

void
leave_env(object old, object dest)
{
	::leave_env(old, dest);
	set_alarm(0.5, 0.0, "remove_me");
}

void
remove_me()
{
	tell_room(environment(TO),"The " + query_short() +
		" makes a humming noise and is consumed in a small "+
		"ball of flame and smoke.\n",0);
	remove_object();

}
