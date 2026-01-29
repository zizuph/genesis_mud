/*
 * /d/Gondor/common/obj/oil_lamp.c
 *
 * It is an oil-lamp that needs oil to burn on. If you have a flask of oil
 * with you, you may fill the lamp with oil and light it.
 *
 * Original idea and coding by Lord Elessar Telcontar
 * Recoded for use with /std/torch by
 *
 * /Mercade, 30 October 1993
 *
 * Revision history:
 *	2-Oct-1998, Gnadnar: re-do handling of "fill lamp with oil" so
 *		that we don't get conflicting calls to notify_fail()
 *		from other objects that allow "fill" (e.g., backpacks)
 *	3-Oct-1998, Gnadnar: fix appraise to not divide by zero if
 *		Max_Time somehow is cleared. (i think this can happen
 *		if you swim in the fountain in avenir, perhaps ...)
 *	19-Feb-1999, Gnadnar: mask decay_torch() so empty oil lamps
 *		don't rot
 *      August 2003, Copied to use in Emerald - Gorboth
 */

inherit "/d/Emerald/obj/torch";
inherit "lib/keep";

#include <cmdparse.h>
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include "/d/Gondor/defs.h"

string lamp_desc,
       bulb_desc = "curved",
       cond = "very nice";
int    nloo_alarm,
       time_left;

/*
 * Prototypes
 */
void set_time_left(int time);
int  query_time_left();
void notify_low_on_oil();
void decay_torch();

void
create_torch()
{
    set_name("lamp");
    add_name(({"oil-lamp","_gondorian_oil_lamp_","_argosian_brass_lamp"}));
    add_adj("terra cotta");
    add_adj("oil");
    set_pname("lamps");
    add_pname("oil-lamps");
 
    set_short("terra cotta oil-lamp");
    set_pshort("terra cotta oil-lamps");
    set_long("@@long_description");

    add_item("wick", "@@wick_description");
    add_item( ({ "glass", "glass flute", "curved glass flute", "curved flute",
        "curved glass", "flute" }),
        "@@glass_bulb_description");

    set_time(1000);
    set_time_left(0);
    set_strength(2);

    add_prop(OBJ_I_WEIGHT, "@@compute_weight");
    add_prop(OBJ_I_VOLUME, 800);
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
        longstr = "It is an oil-lamp. The oil container is "+
                  "a terra cotta vase with a hole at the top. The wick "+
                   "goes through the hole and a tall glass flute "+
                   "covers the wick to protect against the wind. "+
                   "A metal handle is attached to both sides "+
                   "of the vase for ease of use.\n";

    else longstr = lamp_desc;
 
    if (!query_time(1))
    {
        longstr += "The terra cotta lamp does not contain any oil. ";
    }
    else
    {
        longstr += "The terra cotta lamp contains some oil. ";
    }
 
    return (longstr + "\n");
}

string
wick_description()
{
    return BS("You can see the wick of the oil-lamp behind the "
      + bulb_desc + " glass flute. " 
      + (query_prop(OBJ_I_LIGHT) ?
          "Flames are licking along the wick for the lamp is burning.\n" :
          "The wick is not lit.\n"));
}

string
glass_bulb_description()
{
    return BS("Looking through the " + bulb_desc 
      + " glass flute you see the "
      + (query_prop(OBJ_I_LIGHT) ? "burning " : "") 
      + "wick of the oil-lamp. The glass itself is " 
      + bulb_desc + " and has an opening in the top to "
      + "allow oxygen to reach the wick.\n");
}

int
torch_value()
{
    /* The value of the lamp itself is 150 cc */
    /* Oil is worth 1 cc per 30 ml oil        */
    return 150 + (query_time_left() / 30);
}


int
do_refill(string str)
{
    string	flask_short;
    object	*oil_flasks,
		*all_inv;
    int		oil_amount,
		time_left,
		s;
    mixed	*oil_lamps;


    if (!objectp(TP) ||
	!objectp(ENV(TP)))
    {
	/* we could work around not having TP and ENV here, but
	 * NORMAL_ACCESS expects to have them.
	 */
	return 0;
    }

    if (!strlen(str))
    {
        NF0(CAP(query_verb()) + " what with what?\n");
    }

    all_inv = all_inventory(TP);
    if (!parse_command(str, (all_inv + all_inventory(ENV(TP))),
	    "[the] %i 'with' [lamp] 'oil' / 'lamp-oil' ", oil_lamps) ||
	!(s = sizeof(oil_lamps = NORMAL_ACCESS(oil_lamps, 0, 0))) ||
        oil_lamps[0] != TO)
    {
        NF0(CAP(query_verb()) + " what with what?\n");
    }

    oil_flasks = filter(all_inv, &->id("_gondorian_flask_with_oil_"));
    if (!sizeof(oil_flasks))
    {
	/* no flasks at all */
        write("You have no oil with which to fill the lamp.\n");
	return 1;
    }

    flask_short = oil_flasks[0]->short();
    oil_flasks = filter(oil_flasks, &->query_amount());
    if (!sizeof(oil_flasks))
    {
	/* no flasks with any oil */
        write("The " + flask_short + " is empty.\n");
	return 1;
    }

    /* ok, they have at least one flask with oil -- use the first one */
    oil_amount = oil_flasks[0]->query_amount();
    time_left = query_time_left();
    if (Max_Time <= 0)
    {
	write("The oil-lamp is broken. It cannot be filled.\n");
    }
    else if (time_left >= Max_Time)
    {
        write("The oil-lamp is already filled with oil!\n");
    }
    else if ((time_left + oil_amount) >= Max_Time)
    {
        oil_flasks[0]->remove_oil(Max_Time - time_left);
        set_time_left(Max_Time);
        write("You fill the oil-lamp with as much lamp-oil as it can hold.\n");
        SAY(" fills the oil-lamp with as much lamp-oil as it can hold.");
    }
    else
    {
    	set_time_left(time_left + oil_amount);
    	oil_flasks[0]->remove_oil(oil_amount);
    	WRITE("You fill the oil-lamp with all the lamp-oil in the flask. The " +
        	"oil-lamp is not completely filled with oil.");
    	SAY(" fills extra lamp-oil into the oil-lamp.");
    }

    return 1;
}

public string
keep_obj_m_no_sell()
{
    return "You do not want to sell the oil-lamp!\n";
}

mixed
query_light_fail()
{
    if (!query_time_left())
    {
        return "You try to light your " + short() +
            ", but it does not contain any oil!\n";
    }

    return ::query_light_fail();
}

int
light_me_after_delay()
{
    int i = query_time_left() - 30;

    /*
     * You will get a pre-warning if low on oil.
     *
     * True that you won't get a flicker if you light a lamp that has almost
     * no oil left, but I am too lazy to add that.
     */
    if (query_time_left() > 30)
    {
        nloo_alarm = set_alarm(itof(i), 0.0, notify_low_on_oil);
    }

    return ::light_me_after_delay();
}

int
extinguish_me()
{
    object  env = ENV(TO);

    remove_alarm(nloo_alarm);
    nloo_alarm = 0;
    env->update_light();
    if (!env->query_prop(ROOM_I_IS))
    if (objectp(env))
        ENV(env)->update_light();

    return ::extinguish_me();
}

void
notify_low_on_oil()
{
    object env = ENV(TO);
    nloo_alarm = 0;
    if ((query_time_left() > 30) ||
        (Burn_Alarm == 0) ||
        (!objectp(env)))
    {
        return;
    }

    if (living(env))
    {
        env->catch_msg(BSN("Your oil-lamp flickers briefly. It seems to be " +
            "running out of oil."));
        LTELL_ROOM(ENV(env), env, "The oil-lamp that ", " holds, flickers " +
            "briefly. It seems to be running out of oil.", env);
    }
    else if (env->query_prop(ROOM_I_IS))
    {
        tell_room(env, BSN("The " + short() + " flickers briefly. It seems " +
            "to be running out of oil."));
    }

    if (query_time_left() >= 10)
    {
        nloo_alarm = set_alarm(10.0, 0.0, notify_low_on_oil);
    }
}

/*
 * Function name: burned_out
 * Description:	  If this function is called the torch has burned out.
 */
void
burned_out()
{
    object env = ENV(TO);

    set_time_left(0);
    remove_prop(OBJ_I_LIGHT);
    remove_prop(OBJ_I_HAS_FIRE);
    env->update_light();

    if (!objectp(env))
    {
        return;
    }

    ENV(env)->update_light();

    if (living(env))
    {
        env->catch_msg(BSN("Your oil-lamp flickers and goes out. It ran out " +
            "of oil."));
        LTELL_ROOM(ENV(env), env, "The oil-lamp that ", " holds, flickers " +
            "and goes out. It ran out of oil.", env);
    }
    else if (env->query_prop(ROOM_I_IS))
    {
	tell_room(env, BSN("The " + short() + " flickers and goes out. It " +
            "ran out of oil."));
    }
}

int
compute_weight()
{
    /* 300 for the oil-lamp and 2 grams per 6 ml oil */
    return 300 + (2 * query_time_left() / 6);
}

void
set_time_left(int time)
{
    time_left = time;
    ::set_time_left(time);

    if (Burn_Alarm)
    {
        remove_alarm(Burn_Alarm);
        Burn_Alarm = 0;
        if ((time_left > 30) &&
            (nloo_alarm))
        {
            remove_alarm(nloo_alarm);
            nloo_alarm = set_alarm(itof(query_time_left() - 30), 0.0, notify_low_on_oil);
        }

        if (time_left > 0)
        {
            Burn_Alarm = set_alarm(itof(time_left), 0.0, burned_out);
        }
    }
}

int
query_time_left()
{
    if (Max_Time > 0)
    {
        if (Burn_Alarm)
	{
            time_left = ftoi(get_alarm(Burn_Alarm)[2]);
	}
        else
	{
            time_left = query_time(1);
	}
    }
    else
    {
	time_left = 0;
    }
    return time_left;
}

void
appraise_object(int num)
{
    int perc;
    int skill;
    int seed;
    string extra_desc = "is empty.";

    if (Max_Time > 0)
    {
	perc = ((query_time_left() * 100) / Max_Time);
    }
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
    if (perc)
    {
        perc = cut_sig_fig(perc +
			   (skill % 2 ? -skill % 70 : skill) *
			   perc / 100);
    }

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
    init_torch_recover(arg);
    init_keep_recover(arg);
}

void
set_lamp_desc(string str)
{
    if (stringp(str) && strlen(str))
        lamp_desc = str;
}

void
set_time(int time)
{
    ::set_time(time);
    if (Max_Time <= 0)
    {
	extinguish_me();
	bulb_desc = "cracked";
	cond = "battered";
    }
    else
    {
	if (bulb_desc == "cracked")
	{
	    bulb_desc = "curved";
	    cond = "very nice";
	}
    }
}

void decay_torch() { }

