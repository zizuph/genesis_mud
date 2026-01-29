/*
 *  /d/Sparkle/area/tutorial/obj/oil_lamp.c
 *
 *  This is an oil lamp which is sold at the General Store in Silverdell:
 *      /d/Sparkle/area/tutorial/town/general_store.c
 *
 *  It is modified from /d/Gondor/common/obj/oil_lamp.c
 *
 *  Created July 2005, by Cooper Sherry (Gorboth)
 */

inherit "/d/Sparkle/area/tutorial/obj/torch";
inherit "/lib/keep";

#include <cmdparse.h>
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>

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
    add_name("brass lamp");
    add_name("_gondorian_oil_lamp_");
    add_adj("brass");
    add_adj("oil");
    set_pname("lamps");
    add_pname("brass lamps");

    set_short("brass lamp");
    set_long("@@long_description");

    add_item("wick", "@@wick_description");
    add_item( ({ "glass", "glass bulb", "curved glass bulb", "curved bulb",
        "curved glass", "bulb" }),
        "@@glass_bulb_description");

    set_time(1000);
    set_time_left(0);
    set_strength(2);

    add_prop(OBJ_I_WEIGHT, "@@compute_weight");
    add_prop(OBJ_I_VOLUME, 800);
    add_prop(OBJ_I_VALUE, 80);
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
    string  longstr;

    if (!strlen(lamp_desc))
        longstr = "This is a " + cond + " lamp with a wick behind a "
          + bulb_desc + " glass bulb. ";
    else longstr = lamp_desc;

    if (Max_Time <= 0 ||
        !query_time_left())
    {
        longstr += "The brass lamp does not contain any oil. For it to"
          + " work, you will need to buy a flask of oil from the store,"
          + " and then <fill lamp with oil>. Then, you will be able to"
          + " <light lamp> to illuminate dark areas, and <extinguish"
          + " lamp> when you are back in the light.";
    }
    else
    {
        longstr += "The brass lamp contains some oil. You can <light lamp>"
          + " to illuminate a dark area. Don't forget to <extinguish> it"
          + " when you don't need its light anymore or it will soon"
          + " run out of oil.";
    }

    return longstr + "\n";
}

string
wick_description()
{
    return "You can see the wick of the brass lamp behind the "
      + bulb_desc + " glass bulb. " 
      + (query_prop(OBJ_I_LIGHT) ?
          "Flames are licking along the wick for the lamp is burning.\n" :
          "The wick is not lit.\n");
}

string
glass_bulb_description()
{
    return "Looking through the " + bulb_desc 
      + " glass bulb you see the "
      + (query_prop(OBJ_I_LIGHT) ? "burning " : "") 
      + "wick of the brass lamp. The glass itself is " 
      + bulb_desc + " and has an opening in the top to "
      + "allow oxygen to reach the wick.\n";
}

int
torch_value()
{
    /* The value of the lamp itself is 150 cc */
    /* Oil is worth 1 cc per 30 ml oil        */
    return 35 + (query_time_left() / 30);
}


int
do_refill(string str)
{
    string	flask_short;
    object	*oil_flasks,
		*all_inv;
    int		oil_amount,
		s;
    mixed	*oil_lamps;


    if (!objectp(this_player()) ||
	!objectp(environment(this_player())))
    {
	/* we could work around not having this_player() and environment here, but
	 * NORMAL_ACCESS expects to have them.
	 */
	return 0;
    }

    if (!strlen(str))
    {
        notify_fail(capitalize(query_verb()) + " what with what?\n");
        return 0;
    }

    all_inv = all_inventory(this_player());
    if (!parse_command(str, (all_inv + all_inventory(environment(this_player()))),
	    "[the] %i 'with' [lamp] 'oil' / 'lamp-oil' ", oil_lamps) ||
	!(s = sizeof(oil_lamps = NORMAL_ACCESS(oil_lamps, 0, 0))) ||
        oil_lamps[0] != this_object())
    {
        notify_fail(capitalize(query_verb()) + " what with what?\n");
        return 0;
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
	write("The brass lamp is broken. It cannot be filled.\n");
    }
    else if (time_left >= Max_Time)
    {
        write("The brass lamp is already filled with oil!\n");
    }
    else if ((time_left + oil_amount) >= Max_Time)
    {
        oil_flasks[0]->remove_oil(Max_Time - time_left);
        set_time_left(Max_Time);
        write("You fill the brass lamp with as much lamp-oil as it can hold.\n");
        say(QCTNAME(this_player()) + " fills the brass lamp with as much"
          + " lamp-oil as it can hold.\n");
    }
    else
    {
    	set_time_left(time_left + oil_amount);
    	oil_flasks[0]->remove_oil(oil_amount);
    	write("You fill the brass lamp with all the lamp-oil in the flask. The " +
        	"brass lamp is not completely filled with oil.\n");
        say(QCTNAME(this_player()) + " puts some extra lamp-oil into"
          + " the brass lamp.\n");
    }

    return 1;
}

public string
keep_obj_m_no_sell()
{
    return "You do not want to sell the brass lamp!\n";
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
    /*
     * You will get a pre-warning if low on oil.
     *
     * True that you won't get a flicker if you light a lamp that has almost
     * no oil left, but I am too lazy to add that.
     */
    if (query_time_left() > 30)
    {
        nloo_alarm = set_alarm(itof(query_time_left() - 30), 0.0, notify_low_on_oil);
    }

    return ::light_me_after_delay();
}

int
extinguish_me()
{
    object  env = environment(this_object());

    remove_alarm(nloo_alarm);
    nloo_alarm = 0;
    env->update_light();
    if (!env->query_prop(ROOM_I_IS) && objectp(env))
        environment(env)->update_light();

    return ::extinguish_me();
}

void
notify_low_on_oil()
{
    object env = environment(this_object());
    nloo_alarm = 0;
    if ((query_time_left() > 30) ||
        (Burn_Alarm == 0) ||
        (!objectp(env)))
    {
        return;
    }

    if (living(env))
    {
        env->catch_msg("Your brass lamp flickers briefly. It seems to be " +
            "running out of oil.\n");
        tell_room(environment(env), "The brass lamp that " + QCTNAME(env)
          + " holds flickers briefly. It seems to be running out of"
          + " oil.\n", env);
    }
    else if (env->query_prop(ROOM_I_IS))
    {
        tell_room(env, "The " + short() + " flickers briefly. It seems " +
            "to be running out of oil.\n");
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
    object env = environment(this_object());

    set_time_left(0);
    remove_prop(OBJ_I_LIGHT);
    remove_prop(OBJ_I_HAS_FIRE);
    env->update_light();

    if (!objectp(env))
    {
        return;
    }

    environment(env)->update_light();

    if (living(env))
    {
        env->catch_msg("Your brass lamp flickers and goes out. It ran out " +
            "of oil.\n");
        tell_room(environment(env), "The brass lamp that " + QCTNAME(env)
          + " holds flickers and goes out. It ran out of oil.\n", env);
    }
    else if (env->query_prop(ROOM_I_IS))
    {
	tell_room(env, "The " + short() + " flickers and goes out. It " +
            "ran out of oil.\n");
    }
}

int
compute_weight()
{
    /* 300 for the brass lamp and 2 grams per 6 ml oil */
    return 300 + (2 * query_time_left() / 6);
}

void
set_time_left(int t)
{
    time_left = t;
    ::set_time_left(t);

    if (Burn_Alarm)
    {
        remove_alarm(Burn_Alarm);
        Burn_Alarm = 0;
        if (nloo_alarm)
        {
            remove_alarm(nloo_alarm);
        }
        if (time_left > 30)
        {
            nloo_alarm = set_alarm(itof(time_left - 30), 0.0, notify_low_on_oil);
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
	skill = this_player()->query_skill(SS_APPR_OBJ);
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
