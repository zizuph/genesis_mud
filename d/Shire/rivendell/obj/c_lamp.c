/*
 * Oil lamp in Rivendell
 * -- Finwe, Nov 2004
 */

#include "/d/Shire/sys/defs.h"
#include <cmdparse.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

inherit "/d/Gondor/common/obj/oil_lamp";
inherit "lib/keep";

string lamp_desc,
       bulb_desc = "faceted",
       cond = "exquisite";
int    nloo_alarm,
       time_left;

create_torch()
{
    set_name("lamp");
    add_name("oil-lamp");
    add_name("_rivendell_lamp_");
    add_adj("crystal");
    add_adj("oil");
    set_pname("lamps");
    add_pname("lamps");

    set_short("crystal lamp");
    set_pshort("crystal lamps");
    set_long("@@long_description");

    add_item("wick", "@@wick_description");
    add_item( ({ "glass", "glass bulb", "curved glass bulb", "curved bulb",
        "curved glass", "bulb" }),
        "@@glass_bulb_description");

    set_time(1000);
    set_time_left(0);
    set_strength(5);

    add_prop(OBJ_I_WEIGHT, "@@compute_weight");
    add_prop(OBJ_I_VOLUME, 800);
}

string
long_description()
{
    string  longstr;

    if (!strlen(lamp_desc))
        longstr = "It is an " + cond + " " + short() + " made by the elves of Imladris. The lamp is round with a silver base that holds oil. The glass bulb is cut from a " + bulb_desc + " piece of glass and holds a silver wick. ";
    else longstr = lamp_desc;

    if (Max_Time <= 0 ||
        !query_time_left())
    {
        longstr += "The " + short() + " does not contain any oil. ";
    }
    else
    {
        longstr += "The " + short() + " contains some oil. ";
    }

    if (query_keep())
    {
        longstr += "Currently, you do not want to sell the " + short() + ". ";
    }
    else
    {
        longstr += "If you do not want to sell the " + short() + 
        ", then you may <keep lamp>. ";
    }

    return longstr + "\n";
}

string
wick_description()
{
    return "It is a long piece of silver string behind the "
      + bulb_desc + " glass bulb. " 
      + (query_prop(OBJ_I_LIGHT) ?
          "A hot flame dances along the wick, throwing bright light everywhere.\n" :
          "The wick is not lit.\n");
}

string
glass_bulb_description()
{
    return "It is cut from a single piece of glass. The glass has many " +
        "flat sides that catch the light and concentrates it and makes " +
        "it brighter. Looking through the " + bulb_desc + " glass bulb " +
        "you see the " + (query_prop(OBJ_I_LIGHT) ? "burning " : "") + 
        "wick of the " + short() + ". The bulb has an opening on the " +
        "top to allow air to enter and allow heat to leave the lamp.\n";
}


int
torch_value()
{
    /* The value of the lamp itself is 700 cc */
    /* Oil is worth 1 cc per 30 ml oil        */
    return 700 + (query_time_left() / 30);
}

do_refill(string str)
{
    string	flask_short;
    object	*oil_flasks,
		*all_inv;
    int		oil_amount,
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
        NF(CAP(query_verb()) + " what with what?\n");
        return 0;
    }

    all_inv = all_inventory(TP);
    if (!parse_command(str, (all_inv + all_inventory(ENV(TP))),
	    "[the] %i 'with' [lamp] 'oil' / 'lamp-oil' ", oil_lamps) ||
	!(s = sizeof(oil_lamps = NORMAL_ACCESS(oil_lamps, 0, 0))) ||
        oil_lamps[0] != TO)
    {
        NF(CAP(query_verb()) + " what with what?\n");
        return 0;
    }

    oil_flasks = filter(all_inv, &->id("_gondorian_flask_with_oil_"));
    if (!sizeof(oil_flasks))
    {
	/* no flasks at all */
        write("You have no oil to fill the lamp with.\n");
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
	write("The " + short() + " is broken. It cannot be filled.\n");
    }
    else if (time_left >= Max_Time)
    {
        write("The " + short() + " is already filled with oil!\n");
    }
    else if ((time_left + oil_amount) >= Max_Time)
    {
        oil_flasks[0]->remove_oil(Max_Time - time_left);
        set_time_left(Max_Time);
        write("You fill the " + short() + " with as much oil as it can hold.\n");
        SAY(" fills the " + short() + " with as much oil as it can hold.");
    }
    else
    {
    	set_time_left(time_left + oil_amount);
    	oil_flasks[0]->remove_oil(oil_amount);
    	WRITE("You fill the " + short() + " with all the oil in the flask. " +
            "The " + short() + " is not completely filled with oil.");
    	SAY(" fills extra oil into the " + short() + ".");
    }

    return 1;
}

public string
keep_obj_m_no_sell()
{
    return "You do not want to sell the " + short() + "!\n";
}

mixed
query_light_fail()
{
    if (!query_time_left())
    {
        return "You try to light your " + short() + ", but it does not " +
            "contain any oil!\n";
    }

    return ::query_light_fail();
}

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
        env->catch_msg("Your " + short() + " flickers briefly. It " +
            "seems to be running out of oil.");
        LTELL_ROOM(ENV(env), env, "The " + short() + " that ", " holds, " +
            "flickers briefly. It seems to be running out of oil.", env);
    }
    else if (env->query_prop(ROOM_I_IS))
    {
        tell_room(env, "The " + short() + " flickers briefly. It seems " +
            "to be running out of oil.");
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
void burned_out()
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
        env->catch_msg("Your " + short() + " flickers and goes out. " +
            "It ran out of oil.");
        LTELL_ROOM(ENV(env), env, "The " + short() + " that ", " holds, " +
            "flickers and goes out. It ran out of oil.", env);
    }
    else if (env->query_prop(ROOM_I_IS))
    {
	tell_room(env, "The " + short() + " flickers and goes out. It " +
            "ran out of oil.");
    }
}

