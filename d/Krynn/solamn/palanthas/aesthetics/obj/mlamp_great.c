/*
 * Original idea and coding by Lord Elessar Telcontar
 * Recoded for use with /std/torch by Mercade, 10.30.1993.
 *
 * Revision history:
 * 11.18.95 Copied/modified to make brass lamp in Calia/Argos by Zima.
 * 06.16.96 Bugs corrected, keep added by Maniac.
 * 
 * Changed to be great lamp sold by general equipper Manny
 * of Aesthetics quarter of Palanthas.  The lamp is double
 * strength, as large as a vase, and designed to light a
 * room for a long time.  It is too heavy for mobile use.
 *
 * Mortis 05.2006
 *
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
    set_name("lamp");
    add_name(({"oil-lamp","_gondorian_oil_lamp_", "_argosian_brass_lamp",
		"_palanthian_oil_lamp"}));
    add_adj("great");
    add_adj("oil");
    set_pname("lamps");
    add_pname(({"oil-lamps"}));
 
    set_short("great lamp");
    set_pshort("great lamps");
    set_long("@@long_description");
 
    add_item("wick", "@@wick_description");

    set_time(12000);
    set_time_left(1);
    set_strength(4);

    add_prop(OBJ_I_WEIGHT, "@@compute_weight");
    add_prop(OBJ_I_VOLUME, 7250);
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
        longstr = "With a body like a vase this three foot high lamp is "
		+ "made from low-grade, hammered steel and holds a great reservoir "
		+ "of oil.  A large, thick wick rises from the latched lid and "
		+ "is surrounded by a cylindrical, white paper shade.  There are "
		+ "handles on either side of the body for lifting.  ";
	
    else
		longstr = lamp_desc;
 
    if (!query_time(1))
    {
        longstr += "The great lamp does not contain any oil. ";
    }

    else
    {
        longstr += "The great lamp contains some oil. ";
    }
 
    return (longstr + "\n");
}
 

string
wick_description()
{
    return ("The wick of the great lamp sticks out from a raised "
	+ "pillar of low-grade steel in the center of the lamp's lid and is "
	+ "surrounded by a cylindrical, white paper shade.  The oversized, "
	+ "thick wick is capable of supporting a large flame.  "
	+ (query_prop(OBJ_I_LIGHT) ? "A strong flame burns along the length "
	+ "of the wick brightly and evenly lighting the entire area"
	+ ".\n" : "The oversized, thick wick is unlit.\n"));
}
 

int
torch_value()
{
	// Oil is worth 1 cc per 30 ml oil
	return 864 + (query_time(1) / 30);
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

    if (r)
	{
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
	if (!parse_command(str, TP, "[the] [great] 'lamp' / 'oil-lamp' "
	+ "[with] [lamp] [oil] [lamp-oil]"))
		return 0;
	
	NF("You have no extra oil with which to fill the lamp.\n");
	if (!objectp(oil_flask = present("_gondorian_flask_with_oil_", TP)))
		return 0;

	NF("The " + oil_flask->short() + " has nothing left.\n");
	if (!(oil_flask->query_amount()))
		return 0;

	NF("The great lamp is already filled with oil.\n");
	if (query_time(1) == query_max_time())
		return 0;

	if ((query_time(1) + oil_flask->query_amount()) > query_max_time())
	{
		oil_flask->remove_oil(query_max_time() - query_time(1));
		set_time_left(query_max_time());

		write("You fill the great lamp with as much oil as it can "
		+ "hold.  Its vast reservoir is finally full.\n");
		say(QCTNAME(TP) + " fills the great lamp with as much oil "
		+ "as it can hold.  Its vast reservoir is finally full.\n");
 
		return 1;
    }

	set_time_left(query_time(1) + oil_flask->query_amount());
	oil_flask->remove_oil(oil_flask->query_amount());

	write("You fill the great lamp with all the oil in your "
	+ "flask, but it is not completely full.\n");
	say(QCTNAME(TP) + " pours more oil into the great lamp.\n");

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

 

void
notify_low_on_oil()
{
	object env = E(TO);
 
	if ((query_time(1) > 30) || (!query_lit(0)) || (!objectp(env)))
		return;

	if (living(env))
	{
		env->catch_msg("Your great lamp flickers briefly. It seems to be "
		+ "running out of oil.\n");
		tell_room(E(env), "The great lamp held by " + QTNAME(env)
		+ " flickers briefly.  It seems to be running out of oil.\n");
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
	// 4250 for the oil-lamp and 2 grams per 6 ml oil
	return 4250 + (2 * query_time(1) / 6);
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
