/**
* Coded by Louie 2004
* 
* Design form
*
* This is the design form used to build a gnomish explosive device.
*
* The form is retrieved from the Design Room (expl3.c) and approved
* in the Approval Room (expl4.c) by an approval committee gnome (approve_gnome.c).
*
* In order to be approved it needs to have at least 1 of each category.
*
* A explosive device will really only possibly do two things, damage and/or
* disarm.
*
*/
#pragma strict_types

#include "../local.h"
#include <stdproperties.h>
#include <macros.h>

inherit "/std/object";

/** prototypes **/
int do_inspect(string str);
int do_add(string str);
public int is_approved();
public int eff_damage_ct();
public int eff_disarm_ct();
public int alarm_bell_ct();
public int alarm_whistle_ct();
public int damage_shrapnel_ct();
public int damage_chemical_ct();
public int combus_chemical_ct();
public int combus_mineral_ct();
public int delay_fuse_ct();
public int delay_timer_ct();
public int ignit_flint_ct();
public int ignit_steam_ct();
public int component_ct();
public int total_eff_ct();
public int total_damage_ct();
public int total_alarm_ct();
public int total_delay_ct();
public int total_ignit_ct();
public int total_combus_ct();
void remove_me();

/* Is this form approved?*/
int approved;

/*How many of each category? */
int eff_ct = 0;
int damage_ct = 0;
int alarm_ct = 0;
int delay_ct = 0;
int ignit_ct = 0;
int combus_ct = 0;

/*how many of each specific type? */
int eff_damage = 0;
int eff_disarm = 0;
int alarm_bell = 0;
int alarm_whistle = 0;
int damage_shrapnel = 0;
int damage_chemical = 0;
int combus_chemical = 0;
int combus_mineral = 0;
int delay_fuse = 0;
int delay_timer = 0;
int ignit_flint = 0;
int ignit_steam = 0;

/*
* Create
*/
void
create_object()
{

    set_name("form");
    add_name("design");
    set_short("gnomish explosive design form");
    set_adj("design");
    add_adj(({"gnomish","explosives","explosive"}));
    add_name("_gnome_design_form");
    set_long("This is a design form for an explosive device.  " +
    	"It comes from the Explosives Development Center of Gnomish "+
      "Industries, located in the gnomish colony in Krynn.  " +
      "It is possible to review the features of this design, " +
      "and to add features as desired.  " +
      "You can <inspect> (or <ginspect>) the design form for " +
      "more detailed information.  " +
      "\n");

    add_prop(OBJ_I_WEIGHT, 5);
    add_prop(OBJ_I_VOLUME, 1);
    add_prop(OBJ_I_VALUE, 0);

}

void
init()
{
	::init();
	add_action("do_inspect","inspect");
	add_action("do_inspect","ginspect");
	add_action("do_add","add");
}

/*
* Approve the design.  This is done in the approval room (expl4.c)
*/
void
approve()
{
	
    set_long(query_long() + 
      "It has been stamped with the official seal of " +
      "approval of the Explosives Development Center " +
      "of Gnomish Industries and can no longer be modified.\n");
    approved = 1;
}

public int
is_approved()
{
	return approved;
}

/*
* Look at the design to see what we have
*/
int
do_inspect(string str)
{
	string appDesc = "";
	
	if (!strlen(str) ||
		( !(str == "form") && !(str == "design form") &&
		  !(str == "the form") && !(str == "the design form")
		  && !(str == "design") && !(str == "the design") ) )
	{
		NF("Inspect the form?\n");
		return 0;
	}
	
	if (approved) {
		appDesc = "It has been stamped with the official seal of " +
			"approval of the Explosives Development Center " +
      		"of Gnomish Industries and can no longer be modified.";
    }
    
	write("You inspect the design form.  Glancing over the schematics "+
		"you can quickly see that this design contains:  " +
		"\n" +
		"\t" +
		"* " + eff_ct + " total different effects.  " +
		"\n" +
		
		"\t\t" +
		"- " + eff_damage + " damage.  " +
		"\n" +
		"\t\t" +
		"- " + eff_disarm + " disarm.  " +
		"\n" +
		
		"\t" +
		"* " + alarm_ct + " total alarm components.  " +
		"\n"+

		"\t\t" +
		"- " + alarm_bell + " bell.  " +
		"\n" +
		"\t\t" +
		"- " + alarm_whistle + " whistle.  " +
		"\n" +

		"\t" +
		"* " + combus_ct + " total combustion agents.  " +
		"\n" +

		"\t\t" +
		"- " + combus_chemical + " chemical.  " +
		"\n" +
		"\t\t" +
		"- " + combus_mineral + " mineral.  " +
		"\n" +
		
		"\t" +
		"* " + damage_ct + " total damaging agents.  " +
		"\n" +

		"\t\t" +
		"- " + damage_shrapnel + " shrapnel.  " +
		"\n" +
		"\t\t" +
		"- " + damage_chemical + " chemical.  " +
		"\n" +
		
		"\t" +
		"* " + delay_ct + " total delaying agents.  " +
		"\n" +

		"\t\t" +
		"- " + delay_fuse + " fuse.  " +
		"\n" +
		"\t\t" +
		"- " + delay_timer + " timer.  " +
		"\n" +
		
		"\t" +
		"* " + ignit_ct + " total ignition agents.  " +
		"\n" +

		"\t\t" +
		"- " + ignit_flint + " flint.  " +
		"\n" +
		"\t\t" +
		"- " + ignit_steam + " steam.  " +
		"\n" +
		
		"It is possible to <add components>.  " +
		"\n" +
		appDesc +
		"  " +
		"\n");
		
	return 1;
    
}

/*
* Add a component to the design.
* Adding is in the form of 'add' <category> <component>, such as 
* "add alarm bell"
*
* You only need 1 of each type, but it will hold up to 10 of each
* just to allow people to put whatever they want.
*/
int
do_add(string str)
{
	string cat, agent;
	
	if (!strlen(str)) 
	{
		NF("Add components?\n");
		return 0;
	}
	
	if (str == "components")
	{
		write("It is possible to add many types of components to the " +
			"design.  Each component belongs to a different category " +
			"of explosive agent.  To see the types of components under " +
			"each category, simply attempt to 'add' <category>.  " +
			"To add a specific agent under a category, use 'add' <category> " +
			"<component> (Example: 'add alarm' to see the list of alarms, " +
			"'add alarm bell' to add a bell alarm to the design).  " +
			"The possibly categories are:  " +
			"\n" +
			"\teffect\n" +
			"\talarm\n" +
			"\tcombustion\n" +
			"\tdamage\n" +
			"\tdelay\n" +
			"\tignition\n");
		return 1;
	}
	
	if (approved) {
		NF("The form has been approved and cannot be altered.\n");
		return 0;
	}
		
	if (sscanf(str, "%s %s", cat, agent) == 2)
	{
	
		switch (cat)
		{
			case "effect":
				
				if (eff_ct > 10) {
					NF("You cannot fit any more of that "+
						"component type into your design.\n");
					return 0;
				}
				
				switch (agent) {
					case "damage": 
						eff_damage += 1;
						eff_ct += 1;
						break;
					case "disarm": 
						eff_disarm += 1;
						eff_ct += 1;
						break;
					default:
						NF("That is not a valid effect.\n");
						return 0;
						break;
				}
				break;
				
			case "alarm":
				if (alarm_ct > 10) {
					NF("You cannot fit any more of that "+
						"component type into your design.\n");
					return 0;
				}
				
				switch (agent) {
					case "bell": 
						alarm_bell += 1;
						alarm_ct += 1;
						break;
					case "whistle": 
						alarm_whistle += 1;
						alarm_ct += 1;
						break;
					default:
						NF("That is not a valid alarm.\n");
						return 0;
						break;
				}
				break;
				
			case "combustion":
				if (combus_ct > 10) {
					NF("You cannot fit any more of that "+
						"component type into your design.\n");
					return 0;
				}
				
				switch (agent) {
					case "chemical": 
						combus_chemical += 1;
						combus_ct += 1;
						break;
					case "mineral": 
						combus_mineral += 1;
						combus_ct += 1;
						break;
					default:
						NF("That is not a valid combustion agent.\n");
						return 0;
						break;
				}
				break;
				
			case "damage":
				if (damage_ct > 10) {
					NF("You cannot fit any more of that "+
						"component type into your design.\n");
					return 0;
				}
				
				switch (agent) {
					case "shrapnel":
						damage_shrapnel += 1;
						damage_ct += 1;
						break;
					case "chemical":
						damage_chemical += 1;
						damage_ct += 1;
						break;
					default:
						NF("That is not a valid damage agent.\n");
						return 0;
						break;
				}
				break;
				
			case "delay":
				if (delay_ct > 10) {
					NF("You cannot fit any more of that "+
						"component type into your design.\n");
					return 0;
				}
				
				switch (agent) {
					case "fuse":
						delay_fuse += 1;
						delay_ct += 1;
						break;
					case "timer":
						delay_timer += 1;
						delay_ct += 1;
						break;
					default:
						NF("That is not a valid delay agent.\n");
						return 0;
						break;
				}
				break;
				
			case "ignition":
				if (ignit_ct > 10) {
					NF("You cannot fit any more of that "+
						"component type into your design.\n");
					return 0;
				}
				
				switch (agent) {
					case "flint":
						ignit_flint += 1;
						ignit_ct += 1;
						break;
					case "steam":
						ignit_steam += 1;
						ignit_ct += 1;
						break;						
					default:
						NF("That is not a valid ignition device.\n");
						return 0;
						break;
				}
				break;
				
			default:
				NF("That is not a valid category/agent combo.  Try 'add components' for details.\n");
				return 0;
				break;
		}
	}

	if (sscanf(str, "%s %s", cat, agent) != 2)
	{
		sscanf(str, "%s", cat);
		
		switch(cat) {
			case "effect":
				write("The possible effects are:  \n"+
					"\tdamage - damages target.\n" +
					"\tdisarm - disarms target.\n");
				return 1	;
				break;
			case "alarm":
				write("The possible alarms are:  \n" +
					"\tbell - a bell alarm.\n" +
					"\twhistle - a whistle alarm.\n");
				return 1;
				break;
			case "combustion":
				write("The possible combustion agents (that make the device " +
					"explode) are:  \n" +
					"\tchemical - a chemical explosion.\n" +
					"\tmineral - a mineral explosion.\n");
				return 1;
				break;
			case "damage":
				write("The possible damaging agents are:  \n"+
					"\tshrapnel - pieces of metal to cause damage.\n"+
					"\tchemical - a burning agent that dissolves flesh.\n");
				return 1;
				break;
			case "delay":
				write("The possible delay agents are:  \n" +
					"\tfuse - a bit fabric that delays as long as it takes to burn.\n" +
					"\ttimer - a complicated gizmo that is more reliable than a fuse.\n");
				return 1;
				break;
			case "ignition":
				write("The possible ignition agents are:  \n" +
					"\tflint - a spark ignites the combusion agent.\n" +
					"\tsteam - heat from steam ignites the explosive.\n");
				return 1;
				break;
			default:
				NF("Valid categories are effect, alarm, combustion, damage, " +
					"delay, and ignition.\n");
				return 0;
				break;
		}
	}
	
	write("You successfully add a component of category " + cat + 
		" and type " + agent + "." +
		"\n");
	return 1;
}		

public int 
eff_damage_ct()
{
	return eff_damage;
}

public int 
eff_disarm_ct()
{
	return eff_disarm;
}

public int 
alarm_bell_ct()
{
	return alarm_bell;
}

public int 
alarm_whistle_ct()
{
	return alarm_whistle;
}

public int 
damage_shrapnel_ct()
{
	return damage_shrapnel;
}

public int 
damage_chemical_ct()
{
	return damage_chemical;
}

public int 
combus_chemical_ct() 
{
	return combus_chemical;
}

public int 
combus_mineral_ct()
{
	return combus_mineral;
}

public int 
delay_fuse_ct()
{
	return delay_fuse;
}

public int 
delay_timer_ct()
{
	return delay_timer;
}

public int 
ignit_flint_ct()
{
	return ignit_flint;
}

public int 
ignit_steam_ct()
{
	return ignit_steam;
}
public int
component_ct()
{
	return eff_ct + damage_ct + alarm_ct + delay_ct + ignit_ct +combus_ct;
}

void
leave_env(object old, object dest)
{
	::leave_env(old, dest);
	set_alarm(0.5,0.0,"remove_me");
}

void
remove_me()
{
	if (!living(environment(TO)))
	{
		tell_room(environment(TO),"The " + query_short() +
			" gets caught by the wind and is lost.\n",0);
		remove_object();
	}
}

public int 
total_eff_ct()
{
	return eff_ct;
}

public int 
total_damage_ct()
{
	return damage_ct;
}

public int 
total_alarm_ct()
{
	return alarm_ct;
}

public int 
total_delay_ct()
{
	return delay_ct;
}

public int 
total_ignit_ct()
{
	return ignit_ct;
}

public int 
total_combus_ct()
{
	return combus_ct;
}