/*
 * Original idea and coding by Lord Elessar Telcontar
 * Recoded for use with /std/torch by Mercade, 10.30.1993.
 *
 * Revision history:
 * 11.18.95 Copied/modified to make brass lamp in Calia/Argos by Zima.
 * 06.16.96 Bugs corrected, keep added by Maniac.
 * 05.04.06 Changed to be hooded lantern sold by general equipper
 *   Manny of Aesthetics quarter of Palanthas.
 *
 * Mortis 05.2006
 *
 * Lunatari 2008-03-04
 * Fixed a tell_room that also told the holder.
 */

inherit "/std/torch";
inherit "/lib/keep"; 

#include "../../local.h"
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
 
string lamp_desc;
 
int oil_alarm; 


void
create_torch()
{
    set_name("lantern");
    add_name(({"oil-lamp","_gondorian_oil_lamp_", "_argosian_brass_lamp",
		"_palanthian_oil_lamp", "lamp"}));
    add_adj("hooded");
    add_adj("oil");
    set_pname("lanterns");
    add_pname(({"oil-lamps", "lamps"}));
 
    set_short("hooded lantern");
    set_pshort("hooded lanterns");
    set_long("@@long_description");
 
    add_item("wick", "@@wick_description");

    set_time(1200);
    set_time_left(1);
    set_strength(2);

    add_prop(OBJ_I_WEIGHT, "@@compute_weight");
    add_prop(OBJ_I_VOLUME, 850);
    set_keep(1); 
}

void
init()
{
    ::init();
 
    add_action("do_refill", "fill");
    add_action("do_refill", "refill");
}
 
string
long_description()
{
    string longstr;

    if (!strlen(lamp_desc))
        longstr = "Five panes of glass spaced by low-grade steel are set "
		+ "into a flat base containing a concealed oil reservoir and wick.  "
		+ "Topped with a thin, angled roof, the lantern has a handle "
		+ "attached for easy carrying.  ";
	
    else
		longstr = lamp_desc;
 
    if (!query_time(1))
    {
        longstr += "The hooded lantern does not contain any oil. ";
    }

    else
    {
        longstr += "The hooded lantern contains some oil. ";
    }
 
    return (longstr + "\n");
}
 

string
wick_description()
{
    return ("The wick of the hooded lantern sticks out from a raised "
	+ "pillar of low-grade steel in the center of the lantern's base.  "
	+ (query_prop(OBJ_I_LIGHT) ? "A steady flame burns along the length "
	+ "of the wick.\n" : "The wick is unlit.\n"));
}
 

int
torch_value()
{
	// Oil is worth 1 cc per 30 ml oil
	return 216 + (query_time(1) / 30);
}

int
light_me_after_delay()
{
     ::light_me_after_delay();
     TO->oil_alarm_check();  
}

int
extinguish_me()
{
    int r;

    r = ::extinguish_me(); 
    if (r) {
        remove_alarm(oil_alarm);
        oil_alarm = 0; 
    }
    return r;
}


void
set_time_left(int time)
{
    int l = (query_lit(0) != 0); 

    /* Next two lines update the burn out alarm. */ 
    if (l)  
        extinguish_me(); 

    ::set_time_left(time); 

    if (l) 
        command_light();
}


int
do_refill(string str)
{
	object oil_flask;
 
	NF(C(query_verb()) + " what with what?\n");
	if (!strlen(str))
		return 0;

	NF(C(query_verb()) + " what with what?\n");
	if (!parse_command(str, TP, "[the] [hooded] [oil] 'lamp' / 'oil-lamp' / "
	+ "'lantern' [with] [lamp] [lantern] [oil] [lamp-oil] [lantern-oil]"))
		return 0;
	
	NF("You have no extra oil with which to fill the lantern.\n");
	if (!objectp(oil_flask = present("_gondorian_flask_with_oil_", TP)))
		return 0;

	NF("The " + oil_flask->short() + " is empty.");
	if (!(oil_flask->query_amount()))
		return 0;

	NF("The hooded lantern is already filled with oil.\n");
	if (query_time(1) == query_max_time())
		return 0;

	if ((query_time(1) + oil_flask->query_amount()) > query_max_time())
	{
		oil_flask->remove_oil(query_max_time() - query_time(1));
		set_time_left(query_max_time());

		write("You fill the hooded lantern with as much oil as it can "
		+ "hold.\n");
		say(QCTNAME(TP) + " fills the hooded lantern with as much oil "
		+ "as it can hold.\n");
 
		return 1;
    }

	set_time_left(query_time(1) + oil_flask->query_amount());
	oil_flask->remove_oil(oil_flask->query_amount());

	write("You fill the hooded lantern with all the oil in your "
	+ "flask, but it is not completely full.\n");
	say(QCTNAME(TP) + " pours more oil into the hooded lantern.\n");

	return 1;
}




mixed
query_light_fail()
{
	if (!query_time(1))
	{
		return "You try to light your " + short() + ", but it does not "
		+ "contain any oil.\n";
	}

	return ::query_light_fail();
}

 
/*
 * fixed tell_room so it doesnt tell the holder. /Lunatari
 */
void
notify_low_on_oil()
{
	object env = E(TO);
 
	if ((query_time(1) > 30) || (!query_lit(0)) || (!objectp(env)))
		return;

	if (living(env))
	{
		env->catch_msg("Your hooded lantern flickers briefly. It seems to be "
		+ "running out of oil.\n");
		tell_room(E(env), "The hooded lantern held by " + QTNAME(env)
		+ " flickers briefly.  It seems to be running out of oil.\n", env);
	}

	else if (env->query_prop(ROOM_I_IS))
	{
		tell_room(env, "The " + short() + " flickers briefly.  It seems "
		+ "to be running out of oil.\n");
	}
}


int
compute_weight()
{
	/* 320 for the oil-lamp and 2 grams per 6 ml oil */
	return 320 + (2 * query_time(1) / 6);
}
 

void
oil_alarm_check()
{
	if (!query_lit(0)) 
		return;

	if (query_time(1) > 30)
	{
		remove_alarm(oil_alarm); 
		oil_alarm = 
			set_alarm(itof(query_time(1) - 30), 0.0, notify_low_on_oil);  
	}
}


void
appraise_object(int num)
{
	int perc = ((query_time(1) * 100) / query_max_time());
	int skill;
	int seed;
	string extra_desc = "is empty.";
 
	::appraise_object(num);
 
	if (!num)
		skill = TP->query_skill(SS_APPR_OBJ);

	else
		skill = num;
 
	sscanf(OB_NUM(TO), "%d", seed);
	skill = random((1000 / (skill + 1)), seed);
	perc = cut_sig_fig(perc + (skill % 2 ? -skill % 70 : skill) * perc / 100);
 
	if (perc >= 100)
		extra_desc = "is completely filled with oil.";
	else if (perc > 80)
		extra_desc = "is almost completely filled with oil.";
	else if (perc > 60)
		extra_desc = "is about two-thirds full of oil.";
	else if (perc > 40)
		extra_desc = "is about half-full of oil.";
	else if (perc > 20)
		extra_desc = "is about one-third full of oil.";
	else if (perc > 0)
		extra_desc = "contains hardly any oil.";
 
	write("You appraise that it " + extra_desc + "\n");
}

string
query_recover()
{
	return MASTER + ":" + query_torch_recover() + query_keep_recover();
}

void
init_recover(string arg)
{
	string foobar;
 
	init_torch_recover(arg);
	init_keep_recover(arg); 
}

void
set_lamp_desc(string str)
{
	if (stringp(str) && strlen(str))
		lamp_desc = str;
}
