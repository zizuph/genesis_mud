/* 
 * Mortis 03.2006
 *
 * This is the weapon base for the bows prepared at the
 * bowyer outside the Arms district of Palanthas.
 *
 */

inherit "/std/bow.c";
inherit "/lib/keep";

#include <formulas.h>
#include <filter_funs.h>
#include <stdproperties.h>
#include <macros.h>
#include <cmdparse.h>
#include <language.h>
#include <composite.h>
#include <options.h>
#include <wa_types.h>
#include <ss_types.h>
#include "../../local.h"

/* Prototypes */
string long_desc();
string recover_string;
string *command_array;
string adjsty1, adjsty2, namedri;
string make_shortwep(string dri, string wfull);
string make_shortsty(string sty1, string sty2);
void add_some_names();
public varargs void did_parry(object att, int aid, int dt);
public void snap_string_custom();
public void tell_archer_load(object archer, object target, object projectile,
							 string adj_desc);
public void tell_others_load(object archer, object target, object projectile,
							 string adj_desc);
public void tell_target_load(object archer, object target, object projectile);
public void tell_archer_miss(object archer, object target, object projectile,
							 string adj_room_desc);
public void tell_target_miss(object archer, object target, object projectile,
							 string adj_room_desc, string org_room_desc);
public void
tell_others_miss(object archer, object target, object projectile,
				 string adj_room_desc, string org_room_desc);
public void 
tell_archer_bounce_armour(object archer, object target, object projectile,
						  string adj_room_desc, object armour);
public void 
tell_target_bounce_armour(object archer, object target, object projectile,
						  string adj_room_desc, string org_room_desc,
						  object armour);
public void 
tell_others_bounce_armour(object archer, object target, object projectile,
						  string adj_room_desc, string org_room_desc,
						  object armour);
public void tell_archer_hit(object archer, object target, object projectile,
							string adj_room_desc, string hdesc, int dt,
							int phurt, int dam, int hid);
public void tell_target_hit(object archer, object target, object projectile,
							string adj_room_desc, string org_room_desc,
							string hdesc, int dt, int phurt, int dam, int hid);
public void tell_others_hit(object archer, object target, object projectile,
							string adj_room_desc, string org_room_desc,
							string hdesc, int dt, int phurt, int dam, int hid);

int bowskill;
string how, sty1, sty2, wep, wfull, shortwep, shortsty, shortcolour;

mapping wep_to_realname = (["bow":"bow", "shortbow":"shortbow",
	"longbow":"longbow"]);

mapping wep_to_pluralname = (["bow":"bows", "shortbow":"shortbows",
	"longbow":"longbows"]);

mapping wep_to_long = (["bow":"medium sized bow",
	"shortbow":"short bow",
	"longbow":"long bow"]);
mapping bow_desc_values = (["style1":({"black", "blue", "dark", "dark-brown",
	"dark-green", "golden", "grey", "pale", "polished", "plain", "red",
	"shaded", "silvery", "white", "yellow"}),
	"style2":({"composite", "darkwood", "horseman", "hunting", "lacquered",
	"mahogany", "oaken", "ornate", "pinewood", "poplar"}),
	"weapon":({"bow", "longbow", "shortbow"})]);

mapping sty_to_long = (["black":"stained so darkly it appears black with "
	+ "barely a hint of its wood grains",
	"blue":"stained a deep, night sky blue",
	"dark":"stained to a dark wooden hue",
	"dark-brown":"stained a rich, dark brown",
	"dark-green":"stained a foresty, dark green",
	"golden":"coated with a golden finish",
	"grey":"coated with a soft grey finish",
	"pale":"stained with a natural, pale hue",
	"polished":"polished to a beautiful shine",
	"plain":"possesses a simple, natural beauty",
	"red":"coated with a deep, natural red finish",
	"shaded":"stained darker at its handle fading to a natural, lighter "
	+ "hue at its tips",
	"silvery":"treated with silver solutions to gleam in silvery hues",
	"white":"treated with a bleaching solution to bring it to a bone white "
	+ "hue",
	"yellow":"stained a natural, pale yellow",
	"composite":"has been recurved on each end for a stronger pull",
	"darkwood":"has been crafted from darkwood",
	"horseman":"has a handle set lower than its center allowing it to be "
	+ "fired more easily from horseback or while kneeling",
	"hunting":"is crafted in a style popular with hunters",
	"lacquered":"has been lacquered for a gleaming shine and added protection",
	"mahogany":"has been crafted from dark, rich mahogany",
	"oaken":"has been crafted from sturdy oak",
	"ornate":"has ornate carvings up and down its length depicting vines, "
	+ "dense vegetation, and watchful eyes",
	"pinewood":"has been crafted from pinewood",
	"poplar":"has been crafted from pale poplar"]);

mapping col_to_short = (["black":"black",
	"blue":"blue",
	"dark":"dark",
	"dark-brown":"dark brown",
	"dark-green":"dark green",
	"golden":"golden",
	"grey":"grey",
	"pale":"pale",
	"polished":"polished",
	"plain":"plain",
	"red":"red",
	"shaded":"shaded",
	"silvery":"silvery",
	"white":"white",
	"yellow":"yellow"]);

void
create_bow()
{
	set_hit(40);
	set_pen(40);
    set_wf(TO);
    set_shoot_command("shoot");
    set_drawn_weapon(1);
    stringed = 1;

    add_prop(OBJ_I_WEIGHT, 1000 + random(200));
    add_prop(OBJ_I_VOLUME, 700 + random(175));
	set_keep(1);

    set_valid_projectile_function("is_arrow");

	seteuid(getuid(TO));
}

void
set_weapon_data(string data)
{
	string* txt = explode(data,"&&");
	sty1 = txt[0];
	sty2 = txt[1];
	wep = txt[2];
	wfull = wep_to_realname[wep];
	shortcolour = col_to_short[sty1];
	shortwep = make_shortwep(wep, wfull);
	shortsty = make_shortsty(shortcolour, sty2);

	recover_string = data;

    set_name(wep);
	set_pname(wep_to_pluralname[wep]);
	add_name(wfull);
	add_adj(sty1);
    add_adj(sty2);
	set_short(shortsty + " " + shortwep);
    set_long("@@long_desc");

	command_array = TO->query_names();

	add_some_names();
}

string long_desc()
{
	string ldesc = "Smooth with sharply defined, functional curves, this "
	+ wep_to_long[wep] + " " + sty_to_long[sty2] + " and " + sty_to_long[sty1]
	+ ".  The " + wep + "'s handle bears a circular seal.\n";

	return ldesc;
}

string make_shortwep(string wep, string wfull)
{
	if (wep == wfull)
	{
		return wep;
	}
	return wep + " " + wfull;
}

string make_shortsty(string st1, string st2)
{
	if (st1 == st2 || st1 == "plain")
	{
		return st2;
	}
	return st1 + " " + st2;
}

void
add_some_names()
{
	if (sty1 == "dark-brown")
		add_adj(({"dark", "brown"}));

	if (sty1 == "dark-green")
		add_adj(({"dark", "green"}));
}

public varargs void
did_parry(object att, int aid, int dt)
{
    if (stringed && !random(F_BOWSTRING_SNAP_CHANCE))
    {
	snap_string_custom();
    }
}

public void
snap_string_custom()
{
    object archer = query_wielded();
    object *bystanders = FILTER_LIVE(all_inventory(E(archer))) -
	({ archer });
	
    bystanders =
	filter(FILTER_IS_SEEN(archer, bystanders), &->can_see_in_room());

    tell_object(query_wielded(), "As you parry a blow, the bowstring of your "
	+ short() + " snaps!\nYour " + short() + " is now unstrung.");

    if (sizeof(bystanders))
    {
		bystanders->catch_msg("As " + QTNAME(archer) + " parries a blow, the "
		+ "bowstring of " + HIS(archer) + " " + short() + " snaps!\n");
    }

    unstring_bow();
    bowstring = 0;
}

public void 
tell_archer_load(object archer, object target,
		 object projectile, string adj_desc)
{
    if (E(archer) == E(target))
    {
        tell_object(archer, "You nock " + 
		    LANG_ADDART(projectile->singular_short())
		    + " against the string of your " + short() + ", aiming " + how
			+ " at " + target->query_the_name(archer) + ".\n");
    }
    else
    {
        tell_object(archer, "You nock " +
		    LANG_ADDART(projectile->singular_short())
		    + " against the string of your " + short() + ", aiming " + how
			+ " at " + target->query_the_name(archer) + " " + adj_desc
			+ ".\n");
    }
}

public void 
tell_others_load(object archer, object target, object projectile,
				 string adj_desc)
{
	if (E(archer) == E(target))
	{
		tell_bystanders_miss(QCTNAME(archer) + " nocks " +
		LANG_ADDART(projectile->singular_short()) +
		" against the string of " + HIS(archer) + " " + short() + ", aiming "
		+ how + " at " + QTNAME(target) + ".\n",

		QCTNAME(archer) + " nocks " + LANG_ADDART(projectile->singular_short())
		+ " against the string of " + HIS(archer) + " " + short()
		+ ", aiming " + how + " at something.\n",

		0, 0, archer, target, E(archer));
	}

    else
    {
        tell_bystanders_miss(QCTNAME(archer) + " nocks "
		+ LANG_ADDART(projectile->singular_short()) + " against the string of "
		+ HIS(archer) + " " + short() + ", aiming " + how + " at "
		+ QTNAME(target) + " " + adj_desc + ".\n",
			     
		QCTNAME(archer) + " nocks " + LANG_ADDART(projectile->singular_short())
		+ " against the string of " + HIS(archer) + " " + short() +
		", aiming " + how + " at something " + adj_desc + ".\n",
			     
		0, 0, archer, target, E(archer));
    }
}		     

public void
tell_target_load(object archer, object target, object projectile)
{
	if (E(archer) == E(target) &&
	CAN_SEE(target, archer) && CAN_SEE_IN_ROOM(target))
	{
		tell_object(target, archer->query_The_name(target) + " nocks " +
		LANG_ADDART(projectile->singular_short()) + " against the string of "
		+ HIS(archer) + " " + short() + ", aiming " + how + " at you.\n");
	}
}

public void
tell_archer_miss(object archer, object target, object projectile,
		 string adj_room_desc)
{
    if (archer->query_npc() || archer->query_option(OPT_GAG_MISSES))
        return;
 
    if (E(archer) == E(target))
    {
        if (CAN_SEE(archer, target) && CAN_SEE_IN_ROOM(archer))
			archer->catch_msg("You shoot an arrow at " +
			target->query_the_name(archer) + ", but miss.\n");

		else
		{
			if (archer->query_met(target))
			archer->catch_msg("You shoot blindly at " +
					target->query_met_name() + ".\n");

			else
			archer->catch_msg("You shoot blindly at the " +
					target->query_race_name() + ".\n");
		}
	}

    else
    {
        if (check_remote_seen(archer, target))
			tell_object(archer, "You shoot an arrow at " +
			target->query_the_name(archer) + " " +
			adj_room_desc + ", but miss.\n");

		else
		{
			if (archer->query_met(target))
				tell_object(archer, "You shoot blindly at " +
				target->query_met_name() + " " +
				adj_room_desc + ".\n");

			else
				tell_object(archer, "You shoot blindly at the " +
				target->query_race_name() + " " +
				adj_room_desc + ".\n");
		}
    }
}

public void
tell_target_miss(object archer, object target, object projectile,
		 string adj_room_desc, string org_room_desc)
{
    if (target->query_npc() || target->query_option(OPT_GAG_MISSES))
        return;
    
    if (E(archer) == E(target))
    {
        if (CAN_SEE(target, archer) && CAN_SEE_IN_ROOM(archer))
			tell_object(target, archer->query_The_name(target) 
			+ " shoots an arrow at you, but misses.\n");

		else
			tell_object(target, "You hear an arrow whizz past you.\n");
    }

    else
    {
        if (check_remote_seen(target, archer))
			tell_object(target, archer->query_The_name(target) +
			" shoots an arrow at you from " +
			org_room_desc + ", but misses.\n");

		else if (CAN_SEE_IN_ROOM(target))
	    tell_object(target, "Someone shoots an arrow at you," +
			" but misses.\n");

		else
			tell_object(target, "You hear an arrow whizz past you.\n");
    }
}

public void
tell_others_miss(object archer, object target, object projectile,
		 string adj_room_desc, string org_room_desc)
{
    if (E(archer) == E(target))
    {
	
		tell_bystanders_miss(QCTNAME(archer) + " shoots an arrow at "
		+ QTNAME(target) + ", but misses.\n",

		QCTNAME(archer)
		+ " shoots an arrow at something.\n",
		"An arrow flies past " + QTNAME(target) + ".\n",
		"You hear an arrow whizz through the air.\n",
		archer, target, E(archer));
    }
    
    else
    {
		tell_bystanders_miss(QCTNAME(archer)
		+ " shoots an arrow at " + QTNAME(target) + " " + adj_room_desc
		+ ", but misses.\n",

		QCTNAME(archer) + " shoots an arrow at something "
		+ adj_room_desc + ".\n",

		"Someone shoots an arrow at " + QTNAME(target)
		+ " " + adj_room_desc + ", but misses.\n",
			     
		"You hear an arrow whizz through the air.\n",

		archer, target, E(archer));

		tell_bystanders_miss(QCTNAME(archer) + " shoots an arrow at "
		+ QTNAME(target) + " from " + org_room_desc + ", but misses.\n",

		QCTNAME(archer) + " shoots an arrow at something.\n",

		"Someone shoots an arrow at " + QTNAME(target) + ", but misses.\n",
			     
		"You hear an arrow whizz through the air.\n",

		archer, target, E(target));
    }

    return;
}

public void 
tell_archer_bounce_armour(object archer, object target, object projectile,
						  string adj_room_desc, object armour)
{
    string armour_desc;
    
    if (archer->query_npc() || archer->query_option(OPT_GAG_MISSES))
        return;

    if (armour)
		armour_desc = ", but the arrow glances off " +
		HIS(target) + " " + armour->short() + ".\n";

    else
		armour_desc = ", but the arrow glances off " +
		HIM(target) + " harmlessly.\n";
	
    if (E(archer) == E(target))
    {
        if (CAN_SEE(archer, target) && CAN_SEE_IN_ROOM(archer))
			tell_object(archer, "You shoot an arrow at "
			+ QTNAME(target) + armour_desc);

		else
		{
			if (archer->query_met(target))
				tell_object(archer, "You shoot blindly at "
				+ target->query_met_name() + ".\n");

			else
				tell_object(archer, "You shoot blindly at the "
				+ target->query_race_name() + ".\n");
		}
	}

    else
    {
        if (check_remote_seen(archer, target))
			tell_object(archer, "You shoot an arrow at "
			+ QTNAME(target) + " " + adj_room_desc + armour_desc);

		else
		{
			if (archer->query_met(target))
				tell_object(archer, "You shoot blindly at "
				+ target->query_met_name() + " " + adj_room_desc + ".\n");

			else
			tell_object(archer, "You shoot blindly at the " +
					target->query_race_name() + " " +
					adj_room_desc + ".\n");
		}
    }
}

public void 
tell_target_bounce_armour(object archer, object target, object projectile,
			  string adj_room_desc, string org_room_desc,
			  object armour)
{
    string armour_desc;
    
    if (target->query_npc() || target->query_option(OPT_GAG_MISSES))
        return;

    if (armour)
		armour_desc = ", but the arrow glances off your "
		+ armour->short() + ".\n";

    else
		armour_desc = ", but the arrow glances off harmlessly.\n";

    if (E(archer) == E(target))
    {
        if (CAN_SEE(target, archer) && CAN_SEE_IN_ROOM(archer))
		    tell_object(target, archer->query_The_name(target)
			+ " shoots an arrow at you" + armour_desc);

		else
		    tell_object(target, "From out of nowhere an arrow strikes you, "
			+ "but harmlessly glances off"
			+ (armour ? " your " + armour->short() + ".\n" : " you.\n"));
    }

    else
    {
		if (check_remote_seen(target, archer))
			tell_object(target, archer->query_The_name(target) 
			+ " shoots an arrow at you" + armour_desc);

		else if (CAN_SEE_IN_ROOM(target))
			tell_object(target, "Someone shoots an arrow at you from "
			+ org_room_desc + armour_desc);

		else
			tell_object(target, "From out of nowhere an arrow strikes you, "
			+ "but harmlessly glances off"
			+ (armour ? " your " + armour->short() + ".\n" : " you.\n"));
    }
}

public void 
tell_others_bounce_armour(object archer, object target, object projectile,
			  string adj_room_desc, string org_room_desc,
			  object armour)
{
    string armour_desc;

    if (armour)
		armour_desc = ", but the arrow glances off " + HIS(target) + " "
		+ armour->short() + ".\n";

    else
		armour_desc = ", but the arrow glances off " + HIM(target)
		+ " harmlessly.\n";
    
    if (E(archer) == E(target))
		tell_bystanders_miss(QCTNAME(archer) + " shoots an arrow at " +
		QTNAME(target) + armour_desc,

		QCTNAME(archer) + " shoots an arrow at something. You hear a thud "
		+ "as the arrow hits something.\n",

		"An arrow hits " + QTNAME(target) + armour_desc,

		"You hear an arrow whizz through the air followed by a thud as it "
		+ "hits something.\n",

		archer, target, E(archer));

    else
	{
		tell_bystanders_miss(QCTNAME(archer) + " shoots an arrow at "
		+ QTNAME(target) + " " + adj_room_desc + armour_desc,
			     
		QCTNAME(archer) + " shoots an arrow at something" + adj_room_desc
		+ ".\n",

		"Someone shoots an arrow at " + QTNAME(target) + " " + adj_room_desc
		+ armour_desc,
			     
		"You hear an arrow whizz through the air.\n",

		archer, target, E(archer));


		tell_bystanders_miss(QCTNAME(archer) + " shoots an arrow at "
		+ QTNAME(target) + " from " + org_room_desc + armour_desc,
				 
		QCTNAME(archer) + " shoots an arrow at something.  You hear a thud as "
		+ "the arrow hits something.\n",

		"Someone shoots an arrow at " + QTNAME(target) + " from " + org_room_desc
		+ armour_desc,
					 
		"You hear the whizz of an arrow flying through followed by a thud as it "
		+ "hits something.\n",

		archer, target, E(target));
	}

	return;
}

public void 
tell_archer_hit(object archer, object target,
		object projectile, string adj_room_desc,
		string hdesc, int dt, int phurt, int dam, int hid)
{
    string damage_desc = query_damage_desc(archer, target, projectile, phurt);
    
    if (archer->query_npc())
        return;

    if (E(archer) == E(target))
    {
		if (CAN_SEE(archer, target) && CAN_SEE_IN_ROOM(archer))
			tell_object(archer, "You shoot an arrow at "
			+ target->query_the_name(archer) + ". The arrow" + damage_desc
			+ target->query_the_possessive_name(archer) + " " + hdesc + ".\n");

		else
		{
			if (archer->query_met(target))
				tell_object(archer, "You shoot blindly at "
				+ target->query_met_name() + ".  You hear a thud as the "
				+ "arrow hits.\n");

			else
				tell_object(archer, "You shoot blindly at the "
				+ target->query_race_name() + ".  You hear a thud as the "
				+ "arrow hits.\n");
		}
    }

    else
    {
        if (check_remote_seen(archer, target))
		    tell_object(archer, "You shoot an arrow at " +
			target->query_the_name(archer) + " " + adj_room_desc + ".  The "
			+ "arrow" +	damage_desc + target->query_the_possessive_name(archer)
			+ " " + hdesc + ".\n");

		else
		{
			if (archer->query_met(target))
				tell_object(archer, "You shoot blindly at "
				+ target->query_met_name() + " " + adj_room_desc + ".\n");
	
			else
				tell_object(archer, "You shoot blindly at the "
				+ target->query_race_name() + " " + adj_room_desc + ".\n");
		}
    }
}

public void
tell_target_hit(object archer, object target, object projectile,
		string adj_room_desc, string org_room_desc, string hdesc,
		int dt, int phurt, int dam, int hid)
{
    string damage_desc = query_damage_desc(archer, target, projectile, phurt);

    if (target->query_npc())
        return;

    if (E(archer) == E(target))
    {
		if (CAN_SEE(target, archer) && CAN_SEE_IN_ROOM(archer))
			tell_object(target, archer->query_The_name(target)
			+ " shoots an arrow at you.  The arrow" + damage_desc
			+ "your " + hdesc + ".\n");

		else
			tell_object(target, "From out of nowhere an arrow" + damage_desc
			+ "your " + hdesc + ".\n");
    }

    else
    {
		if (check_remote_seen(target, archer))
			tell_object(target, archer->query_The_name(target)
			+ " shoots an arrow at you from " + org_room_desc
			+ ". The arrow" + damage_desc + "your " + hdesc + ".\n");

		else if (CAN_SEE_IN_ROOM(target))
			tell_object(target, "Someone shoots an arrow at you from "
			+ org_room_desc + ". The arrow" + damage_desc + "your "
			+ hdesc + ".\n");

		else
			tell_object(target, "From out of nowhere an arrow" + damage_desc
			+ "your " + hdesc + ".\n");
    }
}

public void
tell_others_hit(object archer, object target, object projectile,
		string adj_room_desc, string org_room_desc, string hdesc,
		int dt, int phurt, int dam, int hid)
{
    string damage_desc = query_damage_desc(archer, target, projectile, phurt);

	if (E(archer) == E(target))
    {
		tell_bystanders_hit(QCTNAME(archer) + " shoots an arrow at " +
		QTNAME(target) + ". The arrow" + damage_desc + QTPNAME(target) + " "
		+ hdesc + ".\n",

		QCTNAME(archer) + " shoots an arrow at something.  You hear a thud "
		+ "as the arrow hits something.\n",

		"An arrow hits " + QTNAME(target) + ". The arrow" + damage_desc
		+ QTPNAME(target) + " " + hdesc + ".\n",

		"You hear an arrow whizz through the air followed by a thud as it "
		+ "hits something.\n",
			    
		archer, target, E(archer));
    }
    
    else
    {
		tell_bystanders_hit(QCTNAME(archer) + " shoots an arrow at " +
		QTNAME(target) + " " + adj_room_desc + ".  The arrow" + damage_desc
		+ QTPNAME(target) + " " + hdesc + ".\n",
			    
		QCTNAME(archer) + " shoots an arrow at something " + adj_room_desc
		+ ".\n",
			    
		"Someone shoots an arrow at " + QTNAME(target) + " " + adj_room_desc
		+ ".  The arrow" + damage_desc + QTPNAME(target) + " " + hdesc + ".\n",
			     
		"You hear an arrow whizz through the air.\n",
			    
		archer, target, E(archer));


		tell_bystanders_hit(QCTNAME(archer) + " shoots an arrow at " +
			    QTNAME(target) + " from " + org_room_desc +
			    ". The arrow" + damage_desc + QTPNAME(target) +
			    " " + hdesc + ".\n",			     

		QCTNAME(archer) + " shoots an arrow at something.  You hear a thud "
		+ "as the arrow hits something.\n",

		"Someone shoots an arrow at " + QTNAME(target) + " from "
		+ org_room_desc + ". The arrow" + damage_desc + QTPNAME(target)
		+ " " + hdesc + ".\n",			     
			     
		"You hear an arrow whizz through the air followed by a thud as it "
		+ "hits something.\n",
			    
		archer, target, E(target));
    }
    return;
}

public string
query_damage_desc(object archer, object target, object projectile, int phurt)
{    
    switch (phurt)
    {
		case 0..1:
			return " just glances off ";
			break;          
		case 2..4:
			return " swiftly grazes ";
			break;
		case 5..8:
			return " impacts ";
			break;
		case 9..17:
			return " sinks into ";
			break;
		case 18..33:
			return " impacts forcefully into ";
			break;
		case 34..51:
			return " sinks with a sickening \"Splitch\" into ";
			break;
		case 52..90:
			return " drills a chasmal hole through ";
			break;
		default:
			return " blasts a gore-spurting hole through ";
			break;
    }
}

void
init()
{
    ::init();
	ADD("exa_handle", "exa");
	ADD("exa_handle", "examine");
}

int exa_handle(string arg)
{
	if (strlen(arg) && !parse_command(arg, ({}), "[the] 'seal' / 'handle' [of] [the] [bow] [shortbow] [longbow]"))
        return 0; // The player used syntax with which we do not agree. 
	
	write("The handle of this " + wep + " has been stamped with a circular "
	+ "seal.  Inside the indented circular seal is an \"A\" formed by three "
	+ "arrows.\n");
	return 1;
}

public mixed
wield(object obj)
{
	bowskill = TP->query_skill(SS_WEP_MISSILE);

	switch (bowskill)
	{
		case 0-30:
			how = "carefully";
			break;
		case 31-50:
			how = "skillfully";
			break;
		case 51-75:
			how = "with precision";
			break;
		case 76-90:
			how = "with lethal precision";
			break;
		case 91-100:
			how = "with a deadly gaze";
			break;
		default:
			how = "with care";
			break;
	}

    return 0;
}

public mixed
unwield(object obj)
{
    return 0;
}

string
query_recover()
{
	return MASTER + ":" + recover_string;
}

void
init_recover(string arg)
{
    ::init_keep_recover(arg);
	set_weapon_data(arg);
}
