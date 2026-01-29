/*
 * It is an oil-lamp that needs oil to burn on. If you have a flask of oil
 * with you, you may fill the lamp with oil and light it.
 *
 * Original idea and coding by Lord Elessar Telcontar
 * Recoded for use with /std/torch by
 *
 * /Mercade, 30 October 1993
 *
 * Revision history:
 * 11/18/95 Copied/Modified to make brass lamp in Calia/Argos (Zima)
 * 16/6/96  bugs corrected, keep added         Maniac
 * borrowed from Gondor via Calia with permission 2/98 (Amelia)
 *  fixed bug (wouldn't light) -- Amelia 6-11-98
 */

inherit "/std/torch";
inherit "/lib/keep"; 

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include "/d/Gondor/defs.h"

string lamp_desc;

int oil_alarm; 


void
create_torch()
{
    set_name("lamp");
    add_name(({"oil-lamp","_gondorian_oil_lamp_","_argosian_brass_lamp"}));
    add_adj("brass");
    add_adj("oil");
    set_pname("lamps");
    add_pname("oil-lamps");

    set_short("brass oil-lamp");
    set_pshort("brass oil-lamps");
    set_long("@@long_description");

    add_item("wick", "@@wick_description");

    set_time(1000);
    set_time_left(0);
    set_strength(2);

    add_prop(OBJ_I_WEIGHT, "@@compute_weight");
    add_prop(OBJ_I_VOLUME, 800);
    set_keep(1); 
}

void
init()
{
    ::init();

    add_action("do_refill", "fill");
    add_action("do_refill", "refill");
    add_action("light_lamp", "light");
}


int
light_lamp(string str)
{

    object tp = this_player();
    if (str != "lamp" && str != "oil lamp")
    {
	notify_fail("Light what?\n");
	return 0;
    }

    if (query_time(1))
    {
	light_me_after_delay();
	tp->catch_msg("You light the oil lamp.\n");
	return 1;
    }

    tp->catch_msg(query_light_fail());
    return 1;
}

string
long_description()
{
    string longstr;
    if (!strlen(lamp_desc))
	longstr = "It is a brass oil-lamp made in the shape of an oblong "+
	"bowl with a lid. It has a wick on one end and a curved "+
	"handle on the other. ";
    else longstr = lamp_desc;

    if (!query_time(1))
    {
	longstr += "The brass lamp does not contain any oil. ";
    }
    else
    {
	longstr += "The brass lamp contains some oil. ";
    }

    return (longstr + "\n");
}


string
wick_description()
{
    return ("The wick of the brass oil-lamp sticks out from a hole in "+
      "one end. " + (query_prop(OBJ_I_LIGHT) ?
	"Flames are licking along the wick for the lamp is burning.\n" :
	"The wick is not lit.\n"));
}


int
torch_value()
{
    /* The value of the lamp itself is 150 cc */
    /* Oil is worth 1 cc per 30 ml oil        */
    return 150 + (query_time(1) / 30);
}

int
light_me_after_delay()
{
    ::light_me_after_delay();
    this_object()->oil_alarm_check();  
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
	light_me(); 
}


int
do_refill(string str)
{
    object oil_flask;

    if (!strlen(str))
    {
	NFN0(CAP(query_verb()) + " what with what?");
    }

    if (!parse_command(str,TP," [the] [brass] [oil] 'lamp' / 'oil-lamp' "+
	"[with] [lamp] [oil] / [lamp-oil] "))
    {
	NFN0(CAP(query_verb()) + " what with what?");
    }

    if (!objectp(oil_flask = present("_gondorian_flask_with_oil_", TP)))
    {
	NFN0("You have no extra oil to fill the lamp with!");
    }

    if (!(oil_flask->query_amount()))
    {
	NFN0("The " + oil_flask->short() + " is empty.");
    }

    if (query_time(1) == query_max_time())
    {
	NFN0("The brass lamp is already filled with oil!");
    }

    if ((query_time(1) + oil_flask->query_amount()) > query_max_time())
    {
	oil_flask->remove_oil(query_max_time() - query_time(1));
	set_time_left(query_max_time());

	WRITE("You fill the brass lamp with as much lamp oil as it can hold.");
	SAY(" fills the brass lamp with as much lamp oil as it can hold.");

	return 1;
    }

    set_time_left(query_time(1) + oil_flask->query_amount());
    oil_flask->remove_oil(oil_flask->query_amount());

    WRITE("You fill the brass lamp with all the lamp oil in the flask. The " +
      "oil-lamp is not completely filled with oil.");
    SAY(" fills extra lamp oil into the brass lamp.");

    return 1;
}




string
query_light_fail()
{
    if (!query_time(1))
    {
	return "You try to light your " + short() +
	", but it does not contain any oil!\n";
    }
    if (query_lit(0) != 0)
    {
	return "Your " + short() + " is already lit.\n";
    }

    return "";
}



void
notify_low_on_oil()
{
    object env = ENV(TO);

    if ((query_time(1) > 30) ||
      (!query_lit(0)) ||
      (!objectp(env)))
    {
	return;
    }

    if (living(env))
    {
	env->catch_msg("Your brass lamp flickers briefly. It seems to be " +
	  "running out of oil.\n");
	LTELL_ROOM(ENV(env), env, "The brass lamp that ", " holds, flickers " +
	  "briefly. It seems to be running out of oil.", env);
    }
    else if (env->query_prop(ROOM_I_IS))
    {
	tell_room(env, "The " + short() + " flickers briefly. It seems " +
	  "to be running out of oil.\n");
    }
}


int
compute_weight()
{
    /* 300 for the oil-lamp and 2 grams per 6 ml oil */
    return 300 + (2 * query_time(1) / 6);
}


void
oil_alarm_check()
{
    if (!query_lit(0)) 
	return;

    if (query_time(1) > 30) {
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
    {
	skill = TP->query_skill(SS_APPR_OBJ);
    }
    else
    {
	skill = num;
    }

    sscanf(OB_NUM(this_object()), "%d", seed);
    skill = random((1000 / (skill + 1)), seed);
    perc = cut_sig_fig(perc + (skill % 2 ? -skill % 70 : skill) * perc / 100);

    if (perc >= 100)
	extra_desc = "is completely filled with lamp-oil.";
    else if (perc > 80)
	extra_desc = "is almost completely filled with lamp-oil.";
    else if (perc > 60)
	extra_desc = "filled with lamp-oil for about two-thirds.";
    else if (perc > 40)
	extra_desc = "is about half-full of lamp-oil.";
    else if (perc > 20)
	extra_desc = "filled with lamp-oil for about one-third.";
    else if (perc > 0)
	extra_desc = "hardly contains any lamp-oil.";

    write (BSN("You appraise that it " + extra_desc));
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
    if (stringp(str) && strlen(str)) lamp_desc = str;
}

