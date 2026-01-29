/*
 * Phosphent torch sold in General EQ store off Jems Court
 * in Aesthetics quarter of Palanthas.  Business end is
 * covered in cultured Phosphentus fungus from deep
 * subterranean caves.
 *
 * When lit, phosphentus burns a brilliant white.  When
 * extinguished, the fungus will slowly regrow.  If doused
 * with alcohol, the fungus goes from flammable to explosive.
 * When lit, it will explode for up to 500hp of damage.
 *
 * Will be part of a quest to get past a guard whom you cannot
 * eliminate conventionally or arcanely who likes to light
 * torches (BOOM!).
 *
 * NOT MAGICAL!  Magic info added to give info to people with
 * identify spells or spell-like abilities.
 *
 * Mortis 04.2006
 *
 * Taken from /std/torch and modified.
 *
 * Navarre March 4th 2008. Fixed runtime with torch
 * 
 * Cotillion - 2020-11-28
 * - Fixed creation of alot of growing back alarms
 * - Modified grow time so it takes longer to grow back than
 *   to burn it up.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/object";
inherit "/lib/keep"; 

#include "../../local.h"
#include <cmdparse.h>
#include <composite.h>
#include <files.h>
#include <macros.h>
#include <stdproperties.h>

#define DECAY_TIME (300.0)
 
/*
 * Prototypes:
 */
public void set_strength(int strength);
public void set_value(int value);
public void set_time(int time);
public int torch_value();
public void burned_out();
public void stop_growing();

int adjust_drink_heap(object drink);

/*
 * Global variables:
 */
private int Torch_Value,	// The max value of the torch.
            Light_Strength,	// How strongly the 'torch' will shine
            Time_Left;		// How much time is left?
static  int Burn_Alarm,		// Alarm used when the torch is lit
            Decay_Alarm,    // Alarm used when the torch decays
            Max_Time,		// How much is the max time (start time)
			Fung_Growing;	// Alarm used when fungus regrows
int doused = 0, alco;
string drinkr;

/*
 * Function name: create_torch
 * Description:   The standard create. This has some standard settings on
 *		  long and short descriptions, but don't be afraid to change
 *		  them.
 *                The pshort has to be set to some value, otherwise the short
 *                description of several objects will look ugly.
 */
void
create_torch()
{
	set_name("torch");
	set_pname("torches");
	add_name("_pal_ptorch");
	set_adj("white");
	set_short("white torch");
	set_pshort("white torches");
	set_long("With a short handle of pale, hollow clay the torch's "
	+ "tip has been wrapped in thin leather bands upon which grows "
	+ "a fuzzy, white fungus.  The fungus is dotted with small, "
	+ "round pustules filled with white ooze, and has "
	+ "@@race_long@@" + "." + "@@fungus_left@@" + "\n");

	set_keep(1);

    seteuid(getuid(TO));
}

/*
 * Function name: create_object
 * Description:   The standard create routine.
 */
nomask void
create_object()
{
    add_prop(OBJ_I_LIGHT,     0);
    add_prop(OBJ_I_WEIGHT,  650);
    add_prop(OBJ_I_VOLUME,  950);
    add_prop(OBJ_I_VALUE,  torch_value);

    add_prop(MAGIC_AM_ID_INFO, ({"The unique, pungent smell of this torch "
	+ "is from a flammable fungus called Phosphentus, a deep cave growth "
	+ "that is dangerously flammable, explosive when <douse>d in alcohol, "
	+ "and grows back at an alarming rate when not completely burnt "
	+ "out.\n", 20}));
    add_prop(OBJ_S_WIZINFO, "NOT MAGICAL!  Magic info added to give info "
	+ "to people with identify spells or spell-like abilities.\n");

    set_time(1500);
    set_strength(2);
    set_value(120);

    create_torch();
}

/*
 * Function name: reset_torch
 * Description  : Since you may not mask reset_object() in torches, you have
 *                to redefine this function. Use enable_reset() to make the
 *                torch actually reset itself.
 */
public void
reset_torch()
{
}

/*
 * Function name: reset_object
 * Description:   Reset the object. Since this function is nomasked, you
 *                must redefine reset_torch() to make the torch reset.
 */
public nomask void
reset_object()
{
    reset_torch();
}

void 
init()
{    
    ::init();
	ADA("douse");
}

/*
 * Function name: torch_value
 * Description:   A VBFC gets here when someone wants to know the value of
 *		  the value of this object, default setting
 * Returns:	  The value
 */
public int
torch_value()
{
    int v;

    if (!Max_Time)
    	return 0;

    if (Burn_Alarm && sizeof(get_alarm(Burn_Alarm)))
	v = ftoi(get_alarm(Burn_Alarm)[2]);
    else
	v = Time_Left;

    return (v * (Torch_Value - 5)) / Max_Time + 5;
}

string
race_long()
{
	string tlong;
	string trace = QRACE(TP);

	if (TP->query_guild_name_occ() == "Vampires of Emerald")
	{
        return "the uniquely pungent smell of a flammable fungus";
	}

	else if (TP->query_guild_name_occ() == "Morgul Mages")
	{
        return "the uniquely pungent smell of a flammable fungus";
	}

	else if (TP->query_guild_name_race() == "Noldor of Imladris")
	{
        return "the uniquely pungent smell of a flammable fungus";
	}

	else

	switch(trace)
	{

		case "human":
			tlong = "a uniquely pungent fiery smell";
			break;

		case "elf":
			tlong = "the uniquely pungent smell of a flammable fungus";
			break;

		case "goblin":
			tlong = "a uniquely pungent fiery smell that your "
			+ "goblin nostrils can't get enough of";
			break;

		case "dwarf":
			tlong = "the uniquely pungent smell of a flammable fungus";
			break;

		case "hobbit":
			tlong = "a pungent fiery smell that makes your nose itch";
			break;

		case "gnome":
			tlong = "the distinct, pungent smell of a flammable fungus "
			+ "called Phosphentus.  Why are these humans using that?  "
			+ "It's dangerously flammable, explosive when doused in "
			+ "alcohol, and grows at an alarming rate";
			break;

		case "minotaur":
			tlong = "a uniquely pungent fiery smell";
			break;

		case "half-human":
			tlong = "a uniquely pungent fiery smell";
			break;

		case "half-elf":
			tlong = "a uniquely pungent fiery smell";
			break;

		case "orc":
			tlong = "a uniquely pungent fiery smell that your "
			+ "orcish nostrils can't get enough of";
			break;

		case "hobgoblin":
			tlong = "the uniquely pungent smell of a flammable fungus";
			break;

		case "kender":
			tlong = "a pungent fiery smell that makes your nose itch";
			break;

		case "drow":
			tlong = "the distinct, pungent smell of a flammable fungus "
			+ "called Phosphentus.  How did these humans acquire this deep "
			+ "cave grown growth?  It's dangerously flammable, explosive "
			+ "when doused in alcohol, and grows like the plague";
			break;

		case "noldor":
			tlong = "the uniquely pungent smell of a flammable fungus";
			break;

		case "uruk":
			tlong = "a uniquely pungent fiery smell that your uruk "
			+ "nostrils can't get enough of";
			break;

		case "presence":
			tlong = "a fiery smell you can't quite appreciate in your "
			+ "current form";
			break;

		default:
			tlong = "a uniquely pungent fiery smell";
			break;
    }
	
    return tlong;
}

string
fungus_left()
{
	string fung_desc = "";

	if (Burn_Alarm)
		return fung_desc;

	switch (Time_Left)
	{
		case 0:
			fung_desc = "";
			break;
		case 1..300:
			fung_desc = "Though mostly burnt, a few bits of fungus are "
			+ "still left around the leather bands";
			break;
		case 301..850:
			fung_desc = "Though mostly burnt, the fungus covers over a "
			+ "quarter of the leather bands";
			break;
		case 851..1400:
			fung_desc = "Though somewhat burnt, the fungus covers more "
			+ "than half of the leather bands";
			break;
		case 1401..1499:
			fung_desc = "The fungus almost completely covers the "
			+ "leather bands";
			break;
		case 1500:
			fung_desc = "The fungus is fully grown around the leather bands";
			break;
		default:
			fung_desc = "Uh-oh, Mail Krynn";
			break;
	}

	if (doused == 0)
		return "  " + fung_desc + ".";

	return "  " + fung_desc + ".  The fungus is strangely puffed up.";
}
 
/*
 * Function name: short, pshort, long
 * Description:   We change the short, plural short and long description of
 *		  the torch if it's lit, default settings.
 * Returns:	  The description.
 */
public varargs string
short(object for_obj)
{
    string tmp = ::short(for_obj);
   
    if (Burn_Alarm)
    	return "brilliantly burning " + tmp;
    
    if (!Time_Left)
    	return "burnt out " + tmp;
    
    return tmp;
}

/*
 * Function name: short, pshort, long
 * Description:   We change the short, plural short and long description of
 *		  the torch if it's lit, default settings.
 * Returns:	  The description.
 */
public varargs string
plural_short(object for_obj)
{
    string tmp = ::plural_short(for_obj);

    if (!stringp(tmp))
		return 0;
    
    if (Burn_Alarm)
    	return "brilliantly burning " + tmp;
    
    if (!Time_Left)
    	return "burnt out " + tmp;
    
    return tmp;
}

/*
 * Function name: short, pshort, long
 * Description:   We change the short, plural short and long description of
 *		  the torch if it's lit, default settings.
 * Returns:	  The description.
 */
public varargs string
long(object for_obj)
{
	string tmp = ::long(for_obj);
    
    if (Burn_Alarm)
		return tmp + "It is lit and burning with a brilliant, white light.\n";
    
    if (!Time_Left || Time_Left == 0)
		return "With a short handle of pale, hollow clay the torch's "
		+ "tip has been wrapped in thin leather bands that have burned "
		+ "black and brittle with a thin layer of greyish black residue "
		+ "left on them.\nIt has burned out completely.\n";

    return tmp;
}

/*
 * Function name: set_time
 * Description:   Set how long time the torch can burn.
 * Arguments:     int t - the time in seconds.
 */
public void
set_time(int t)
{
    Max_Time = t;
    Time_Left = t;
}

/*
 * Function name: query_max_time
 * Description:	  Query the original burn time of the torch.
 * Returns:       the time
 */
public int
query_max_time()
{
    return Max_Time;
}

/*
 * Function name: query_time
 * Description:	  Query how long time the torch can burn
 * Argument:      flag: if true, then return the time until the
 *                torch burns out if the torch is lit
 * Returns:       int - the time left in seconds.
 */
public int
query_time(int flag = 0)
{
    mixed   alarm;

    if (flag && Burn_Alarm && sizeof(alarm = get_alarm(Burn_Alarm)))
	return ftoi(alarm[2]);
    return Time_Left;
}

/*
 * Function name: query_lit
 * Description:   Query of the torch is lit.
 * Argument:      flag - if set, return id of the alarm to the function
 *                that is called when the torch burns out.
 * Returns:       0        - if torch is not lit,
 *                -1       - if torch is lit,
 *                alarm id - if torch is lit and flag was set.
 */
public int
query_lit(int flag)
{
    if (flag)
	return Burn_Alarm;
    else
	return (!Burn_Alarm ? 0 : -1);
}

/*
 * Function name: set_time_left
 * Description:   Set how long time the torch can burn.
 *                Use this for 'torches' that can be refilled, like oil lamps.
 * Arguments    : int left - the time left.
 */
public void
set_time_left(int left)
{
    Time_Left = ((left < Max_Time) ? left : Max_Time);

    /* If lit, then also update the alarm. */
    if (Burn_Alarm)
    {
		remove_alarm(Burn_Alarm);
		Burn_Alarm = set_alarm(itof(Time_Left), 0.0, burned_out);
    }
}

/*
 * Function name: set_strength
 * Description:   Set the light strength of this 'torch'
 * Arguments:     int strength - the light value.
 */
public void
set_strength(int strength)
{
    Light_Strength = strength;
}

/*
 * Function name: query_strength
 * Description:   Query how strongly the torch will shine
 * Returns:       int - the light value.
 */
public int
query_strength()
{
    return Light_Strength;
}

/*
 * Function name: set_value
 * Description:   Set the max value of the torch (i.e. unused value).
 * Arguments:     int value - the max value.
 */
public void
set_value(int value)
{
    Torch_Value = value;
}

/*
 * Function name: query_torch_may_decay
 * Description  : This function will indicate whether the torch may decay or not
 *                after it burns out. By default it returns 1, but if you do not
 *                want to have it decay, you must redefine this function to make
 *                it return 0. This is especially true for oil lamps.
 * Returns      : int 1 - always.
 */
public int
query_torch_may_decay()
{
    return 1;
}

/*
 * Function name: light_me_after_delay
 * Description  : Routine that actually lights the torch after a delay. Why
 *                exactly this is used, I don't know. Maybe to let the
 *                previous command finish with the old light value?
 * Returns      : int 1 - no reason, really, since it's called from an alarm.
 */
public int
light_me_after_delay()
{
    remove_prop(TEMP_STDTORCH_CHECKED);

    stop_growing();

	if (doused != 0)
	{
		write("\n"
		+ " ____     ___     ___    __  __   _ \n"
		+ "| __ )   / _ \\   / _ \\  |  \\/  | | |\n"
		+ "|  _ \\  | | | | | | | | | |\\/| | | |\n"
		+ "| |_) | | |_| | | |_| | | |  | | |_|\n"
		+ "|____/   \\___/   \\___/  |_|  |_| (_)\n\n"
		+ "The brilliantly lit, white torch erupts in a ball of "
		+ drinkr + " light nearly blowing you to bits!\n");
		say("\n ____     ___     ___    __  __   _ \n"
		+ "| __ )   / _ \\   / _ \\  |  \\/  | | |\n"
		+ "|  _ \\  | | | | | | | | | |\\/| | | |\n"
		+ "| |_) | | |_| | | |_| | | |  | | |_|\n"
		+ "|____/   \\___/   \\___/  |_|  |_| (_)\n\n"
		+ "The brilliantly lit, white torch erupts in a ball of "
		+ drinkr + " light nearly blowing " + QTNAME(TP) + "'s face off!\n"
		+ QCTNAME(TP) + " staggers to and fro in a daze.\n");
		TP->command("$blink");

		alco = alco * 10 * Time_Left / Max_Time;
		if (alco > 500)
			alco = 500;

		TP->heal_hp(-alco);
		if (TP->query_hp() <= 0)
			TP->do_die(TO);

		clone_object(MONKS + "obj/sub_ptorch")->move(TP);

		burned_out();
		return 1;
	}

    add_prop(OBJ_I_LIGHT, Light_Strength);
    add_prop(OBJ_I_HAS_FIRE, 1);
    Burn_Alarm = set_alarm(itof(Time_Left), 0.0, burned_out);
	write("The torch bursts into brilliant white light.\n");
	say("The torch held by " + QTNAME(TP) + " bursts into brilliant "
	+ "white light.\n");

    return 1;
}

/*
 * Function name: query_light_fail
 * Description  : Routine that returns why this torch cannot be lit.
 * Returns      : string - descriptive error message.
 *                int 0 - the torch can be lit.
 */
public string
query_light_fail()
{
    if (environment(this_player())->query_prop(ROOM_I_TYPE) ==
	ROOM_UNDER_WATER)
    {
	return "You are currently submerged.\n";
    }
 
    if (!Time_Left)
    {
        return "You try to light the " + short() + ", but fail... " +
	    "It's useless!\n";
    }

    if (Burn_Alarm || query_prop(TEMP_STDTORCH_CHECKED))
    {
        return "The " + short() + " is already lit.\n";
    }

    return 0;
}

/*
 * Function name: light_me
 * Description:   Actual routine to light this torch.
 * Returns:       1/0 - success/failure
 */
public int
light_me()
{
    if (!Time_Left || Burn_Alarm)
        return 0;

    add_prop(TEMP_STDTORCH_CHECKED, 1);
    set_alarm(0.0, 0.0, light_me_after_delay);
    return 1;
}

/*
 * Function name: command_light
 * Description:   light this torch
 * Returns:       string - an error message (failure)
 *                1 - torch successfully lit
 */
public mixed
command_light()
{
    mixed fail;

    if (stringp(fail = query_light_fail()))
        return fail;

    return light_me();
}

void
stop_growing()
{
    if (get_alarm(Fung_Growing))
        remove_alarm(Fung_Growing);
    Fung_Growing = 0;
}

void
growing_back()
{
    Time_Left = Time_Left + 44440;

    if (Time_Left >= Max_Time)
    {
        Time_Left = 1500;
        stop_growing();
    }
}

void
start_growing()
{
    stop_growing();
    Fung_Growing = set_alarm(60.0, 60.0, &growing_back());
}

/*
 * Function name: extinguish_me
 * Description:   Actual routine to extinguish this torch.
 * Returns:       1/0 - success/failure
 */
int
extinguish_me()
{
    mixed *alarm;

    if (!Burn_Alarm)
        return 0;

    if (sizeof(alarm = get_alarm(Burn_Alarm)))
    {
		Time_Left = ftoi(get_alarm(Burn_Alarm)[2]);
		remove_alarm(Burn_Alarm);
    }

    Burn_Alarm = 0;
    remove_prop(OBJ_I_LIGHT);
    remove_prop(OBJ_I_HAS_FIRE);

    write("The brilliant white light of the torch fizzles out.\n");
    say("The brilliant white light of the torch held by " + QTNAME(TP)
            + " fizzles out.\n");

    start_growing();

    return 1;
}

/*
 * Function name: command_extinguish
 * Description:   Extinguish this torch.
 * Returns:       string - an error message (failure)
 *                1 - torch successfully extinguished
 */
public mixed
command_extinguish()
{
    if (!Burn_Alarm)
		return "The " + short() + " isn't lit.\n";

	return extinguish_me();
}

/*
 * Function name: decay_torch
 * Description  : This function is called with a delay to destruct the
 *                torch after burning out. Notice that the check for
 *                query_torch_may_decay() must done before calling this
 *                function.
 */
void
decay_torch()
{
    object env = environment();
    string tmp = short();

    if (living(env))
    {
	tell_object(env, "The remains of the " + tmp + " fall apart.\n");
	tell_room(environment(env), "The remains of the " + tmp + " that " +
	    QTNAME(env) + " is holding fall apart.\n", env);
    }
    else if (env->query_prop(ROOM_I_IS))
    {
	tell_room(env, "The remains of the " + tmp + " fall apart.\n");
    }

    remove_object();
}

#if 0
/*
 * Function name: hook_torch_burned_out
 * Description  : This function is called in the ENVIRONMENT of the torch when
 *                it burns out. This can be a living or a room. The purpose of
 *                this hook is that livings or rooms may trigger on the event.
 * Arguments    : object torch - the torch that burnt out.
 */
public void
hook_torch_burned_out(object torch)
{
}
#endif

/*
 * Function name: burned_out
 * Description:	  If this function is called when the torch has burned out.
 */
public void
burned_out()
{
    object env = environment();
    string tmp = ::short();

    Time_Left = 0;
    Burn_Alarm = 0;

    remove_prop(OBJ_I_LIGHT);
    remove_prop(OBJ_I_HAS_FIRE);

    set_adj("out");
    set_adj("burnt");

    if (!objectp(env))
		return;
    
    if (living(env))
    {
		tell_object(env, "The " + tmp + " goes out.\n");
		tell_room(environment(env), "The " + tmp + " that " +
	    QTNAME(env) + " is holding goes out.\n", env);
    }
    
	else if (env->query_prop(ROOM_I_IS))
    {
		tell_room(env, "The " + tmp + " goes out.\n");

        if (query_torch_may_decay())
			Decay_Alarm = set_alarm(DECAY_TIME, 0.0, decay_torch);
    }

    /* Call this in the environment to let it trigger on the event. */
    env->hook_torch_burned_out(this_object());
}

int
douse(string str)
{
	int qlit = query_lit(0);
	object *drink;
	string drinkname, drink_exists, *drinkmaybe, *drinkadjs;

	NF("Douse torch with what?\n");
	if (!str)
		return 0;

	if (sscanf(str, "torch with %s", drinkname) != 1)
		return 0;

	NF("Douse your torch with what?  You don't have any " + drinkname
	+ ".\n");
//	if (!(drink = FIND_STR_IN_OBJECT(drinkname, TP)) || !sizeof(drink))
//		return 0;  This doesn't keep heap_size.

	drink = filter(all_inventory(TP), &->id(drinkname));

        if(!drink)
        {
            NF("Douse what?\n");
            return 0;
        }
	drinkmaybe = drink[0]->query_names();
	drink_exists = function_exists("create_drink", drink[0]);

	NF("You have no cause to \"pour\" your " + drinkname + " on your "
	+ "torch.  Are you feeling alright?\n");
	if (drinkmaybe[1] != "drink" && !drink_exists)	//Confirm
		return 0;

	alco = drink[0]->query_alco_amount();

	if (!alco || alco == 0)
	{
		if (qlit != 0)
		{
			write("You pour your " + drinkname + " all over your torch.  "
			+ "Not the most efficient way to put it out, but it works "
			+ "just the same.\n");
			say("Feeling creative, " + QTNAME(TP) + " pours " + HIS(TP)
			+ " " + drinkname + " all over a white torch.\n");
			adjust_drink_heap(drink[0]);
			return extinguish_me();
		}

		write("You pour your " + drinkname + " all over your torch.  It "
		+ "was somehow less satisfying than you thought it would be.\n");
		say(QCTNAME(TP) + " pours " + HIS(TP) + " " + drinkname + " all "
		+ "over a white torch.  " + HE(TP) + " seems somewhat "
		+ "disappointed.\n");
		adjust_drink_heap(drink[0]);
		return 1;
	}

	drinkadjs = drink[0]->query_adjs();
	drinkr = one_of_list(drinkadjs);

	if (qlit != 0)
	{
		write("You pour your " + drinkname + " all over your lit torch.\n\n"
		+ " ____     ___     ___    __  __   _ \n"
		+ "| __ )   / _ \\   / _ \\  |  \\/  | | |\n"
		+ "|  _ \\  | | | | | | | | | |\\/| | | |\n"
		+ "| |_) | | |_| | | |_| | | |  | | |_|\n"
		+ "|____/   \\___/   \\___/  |_|  |_| (_)\n\n"
		+ "The brilliantly lit, white torch erupts in a ball of " + drinkr
		+ " light nearly blowing you to bits!\n");
		say("In an act of questionable intelligence, " + QTNAME(TP)
		+ " pours " + HIS(TP) + " " + drinkname + " all over a lit, white "
		+ "torch.\n\n"
		+ " ____     ___     ___    __  __   _ \n"
		+ "| __ )   / _ \\   / _ \\  |  \\/  | | |\n"
		+ "|  _ \\  | | | | | | | | | |\\/| | | |\n"
		+ "| |_) | | |_| | | |_| | | |  | | |_|\n"
		+ "|____/   \\___/   \\___/  |_|  |_| (_)\n\n"
		+ "The brilliantly lit, white torch erupts in a ball of "
		+ drinkr + " light nearly blowing " + HIS(TP) + " face off!\n"
		+ QCTNAME(TP) + " staggers to and fro in a daze.\n");
		TP->command("blink");

		alco = alco * 10 * Time_Left / Max_Time;
		if (alco > 500)
			alco = 500;

		TP->heal_hp(-alco);
		if (TP->query_hp() <= 0)
			TP->do_die(TO);

		clone_object(MONKS + "obj/sub_ptorch")->move(TP);

		adjust_drink_heap(drink[0]);

	    if (Burn_Alarm)
			remove_alarm(Burn_Alarm);

		burned_out();
		return 1;
	}

	if (doused != 0)
	{
		if (alco > doused)
		{
			write("You pour your " + drinkname + " all over your torch.\n"
			+ "The white fungus covering the leather bands around the torch's "
			+ "tip sizzle and puff up a little more.\n");
			say(QCTNAME(TP) + " pours " + HIS(TP) + " " + drinkname + " all "
			+ "over a white torch.\nThe white fungus covering the leather "
			+ "bands around the torch's tip sizzle and puff up a little "
			+ "more.\n");
			doused = alco;
			adjust_drink_heap(drink[0]);
			return 1;
		}

		write("You pour your " + drinkname + " all over your torch.\n"
		+ "What fun!\n");
		say(QCTNAME(TP) + " pours " + HIS(TP) + " " + drinkname + " all "
		+ "over a white torch.\n" + HE(TP) + " really appears to be "
		+ "enjoying " + HIMSELF(TP) + "!\n");
		adjust_drink_heap(drink[0]);
		return 1;
	}

	write("You pour your " + drinkname + " all over your torch.\nThe white "
	+ "fungus covering the leather bands around the torch's tip sizzle and "
	+ "puff up.\n");
	say(QCTNAME(TP) + " pours " + HIS(TP) + " " + drinkname + " all over a "
	+ "white torch.\nThe white fungus covering the leather bands around the "
	+ "torch's tip sizzle and puff up.\n");
	doused = alco;
	adjust_drink_heap(drink[0]);
	return 1;
}

int
adjust_drink_heap(object drink)
{
	int dnumnew, dnum = drink->num_heap();

	if (dnum <= 1)
	{
		drink->remove_object();
		return 1;
	}

	dnumnew = dnum - 1;
	drink->set_heap_size(dnumnew);
	return 1;
}

/*
 * Function name: enter_env
 * Description  : A torch that is burned out will decay after some time. The
 *                decaying starts when the object is put in a room, and it
 *                stops again when picked up. Check query_torch_may_decay()
 *                to see if it is allowed to decay.
 * Arguments    : object to - where the torch is going.
 *                object from - where the torch comes from.
 */
public void
enter_env(object to, object from)
{
    ::enter_env(to, from);

    if (Decay_Alarm)
    {
        if (!to->query_prop(ROOM_I_IS))
        {
            /* Don't bother to keep track of the decay time it has already
             * had. When it is dropped again, simply start counting anew.
             */
            remove_alarm(Decay_Alarm);
            Decay_Alarm = 0;
        }
    }
    else if (!Time_Left && query_torch_may_decay())
    {
        Decay_Alarm = set_alarm(DECAY_TIME, 0.0, decay_torch);
    }
}

/*
 * Function name: query_torch_recover
 * Description:   Return the recover string for changing tourch values
 * Returns:	  string - part of recover string
 */
public string
query_torch_recover()
{
    int tmp;

    if (Burn_Alarm && sizeof(get_alarm(Burn_Alarm)))
    {
	tmp = ftoi(get_alarm(Burn_Alarm)[2]);
    }
    else
    {
	tmp = Time_Left;
    }

    return "#t_t#" + tmp + "#t_l#" + query_prop(OBJ_I_LIGHT) + "#";
}

/*
 * Function name: init_torch_recover
 * Description:   Initialize the torch variables at recover.
 * Arguments:     string arg - The recover string as recieved from
 *			query_torch_recover()
 */
public void
init_torch_recover(string arg)
{
    string foobar;
    int tmp;

    sscanf(arg, "%s#t_t#%d#%s", foobar, Time_Left, foobar);
    sscanf(arg, "%s#t_l#%d#%s", foobar, tmp, foobar);
    if (tmp > 0)
    {
	add_prop(OBJ_I_LIGHT, tmp);
	add_prop(OBJ_I_HAS_FIRE, 1);
	Burn_Alarm = set_alarm(itof(Time_Left), 0.0, burned_out);
    }
}

/*
 * Function name: query_recover
 * Description:   A default query_recover() for torches.
 * Returns:	  A default recovery string.
 */
public string
query_recover()
{
    return MASTER + ":" + query_torch_recover();
}

/*
 * Function name: init_recover
 * Description:   A default init_recover() for torches.
 * Arguments:	  arg - String with variables to recover.
 */
public void
init_recover(string arg)
{
    init_torch_recover(arg);
}
