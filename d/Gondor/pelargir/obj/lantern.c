/*
 * /d/Gondor/pelargir/obj/lantern.c
 *
 * This is the lantern from the Pelargir lighthouse. It is basically
 * a larger version of an oil-lamp that needs oil to burn on. It can be
 * filled with oil and lit.
 *
 * Original idea and coding by Lord Elessar Telcontar
 * Recoded for use with /std/torch by Mercade, 30 October 1993
 *
 * Revision history: Modified into lantern for Pelargir lighthouse
 *                   quest by Tyr, August 20, 1998
 *
 * N.B. we're letting this slide re coding standards because it's
 *      old code.  this is not a general license :-)   gnad
 * Cotillion - 2020-09-29
 * - Fixed type confusion
 */

inherit "/d/Gondor/common/obj/torch";
inherit "lib/keep";

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include "/d/Gondor/defs.h"
#include "/d/Gondor/pelargir/beacon_defs.h"

public string lamp_desc;
public int    nloo_alarm,
       time_left;

/*
 * Prototypes
 */
public void            create_torch();
public void            init();
public string          long_description();
public string          wick_description();
public string          glass_bulb_description();
public int             torch_value();
public int             do_refill(string str);
public string          keep_obj_m_no_sell();
public mixed           query_light_fail();
public int             light_me_after_delay();
public int             extinguish_me();
public void            notify_low_on_oil();
public void            burned_out();
public int             compute_weight();
public void            set_time_left(int time);
public int             query_time_left();
public void            appraise_object(int num);
public string          query_recover();
public void            init_recover(string arg);
public void            set_lamp_desc(string str);

public void
create_torch()
{
    set_name("lantern");
    add_name(LANTERN_NAME);
    add_name("lantern");
    add_adj("brass");
    add_adj("oil");
    set_pname("lantern");

    set_short("brass lantern");
    set_long(long_description);

    add_item("wick", wick_description);
    add_item( ({ "glass", "glass bulb", "curved glass bulb", "curved bulb",
        "curved glass", "bulb" }),
        glass_bulb_description);

    set_time(4000);
    set_time_left(0);
    set_strength(2);

    add_prop(OBJ_I_WEIGHT, compute_weight);
    add_prop(OBJ_I_VOLUME, 3200);
} /* end create_torch */


public int  query_torch_may_decay()    { return 0; }

public void
init()
{
    ::init();

    add_action(do_refill, "fill");
    add_action(do_refill, "refill");
} /* end init */

public string
long_description()
{
    string  longstr;

    if (!strlen(lamp_desc))
        longstr = "This huge brass lantern is both too large and too "+
            "heavy for casual personal use. More likely, the ferrules "+
            "on the sides of its housing fit into a hole or bracket "+
            "in a mechanism built to hold an object of this size. ";
    else longstr = lamp_desc;

    if (!query_time_left())
    {
        longstr += "The lantern does not contain any oil. ";
    }

    else
    {
        longstr += "The lantern contains some oil. ";
    }

    if (query_keep())
    {
        longstr += "At present, you do not want to sell the lantern.";
    }

    return BSN(longstr);
} /* end long_string */

public string
wick_description()
{
    return BS("You can see the wick of the lantern behind the curved "
      + "glass bulb. " + (query_prop(OBJ_I_LIGHT) ?
        "Flames are lick up and down the lantern's wick, producing "+
        "a strong, steady light." :
        "The wick is not lit."));
} /* end wick_description */

public string
glass_bulb_description()
{
    return BS("Looking through the curved glass bulb you see the "
      + (query_prop(OBJ_I_LIGHT) ? "burning " : "") + "wick of the "
      + "The glass itself is curved and has an opening in the top to "
      + "allow air to reach the wick.");
} /* end glass_bulb_description */

public int
torch_value()
{
    /* The value of the lantern itself is 500 cc */
    /* Oil is worth 1 cc per 30 ml oil        */
    return 550 + (query_time_left() / 30);
} /* end torch_value */


public int
do_refill(string str)
{
    object oil_flask;

    if (!strlen(str))
    {
        NFN0(CAP(query_verb()) + " what with what?");
    }

    if (!parse_command(str, TP, " [the] [oil] 'lantern' / 'lantern' 'with' " +
        " [lamp] 'oil' / 'lamp-oil' "))
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

    if (query_time_left() == Max_Time)
    {
        NFN0("The lantern is already filled with oil!");
    }

    if ((query_time_left() + oil_flask->query_amount()) > Max_Time)
    {
        oil_flask->remove_oil(Max_Time - query_time_left());
        set_time_left(Max_Time);

        WRITE("You fill the lantern with as much lamp-oil as it can hold.");
        SAY(" fills the lantern with as much lamp-oil as it can hold.");

        return 1;
    }

    set_time_left(query_time_left() + oil_flask->query_amount());
    oil_flask->remove_oil(oil_flask->query_amount());

    WRITE("You fill the lantern with all the lamp-oil in the flask. "+
        "The lantern is not completely filled with oil.");
    SAY(" adds extra lamp-oil to the lantern.");

    return 1;
} /* end do_refill */

public string
keep_obj_m_no_sell()
{
    return "You do not want to sell the lantern!\n";
} /* keep_obj_m_no_sell */

public mixed
query_light_fail()
{
    if (!query_time_left())
    {
        return "You try to light the " + short() +
            ", but it does not contain any oil!\n";
    }

    return ::query_light_fail();
} /* end query_light_fail */

public int
light_me_after_delay()
{
    int i = query_time_left() - 30;

    /*
     * You will get a pre-warning if low on oil.
     *
     * True that you won't get a flicker if you light a lamp that has
     * almost no oil left, but I am too lazy to add that.
     */
    if (query_time_left() > 30)
    {
        nloo_alarm = set_alarm(itof(i), 0.0, notify_low_on_oil);
    }

    return ::light_me_after_delay();
} /* end light_me_after_delay */

public int
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
} /* end extinguish_me */

public void
notify_low_on_oil()
{
    object env = ENV(TO);
    nloo_alarm = 0;
    if ((query_time_left() > 30) ||
        (Burn_Alarm != 0) ||
        (!objectp(env)))
    {
        return;
    }

    if (living(env))
    {
        env->catch_msg(BSN("The lantern flickers briefly. It seems to "+
            "be running out of oil."));

        tell_room(ENV(env), "The lantern flickers briefly. It "+
            "seems to be running out of oil.", ({ env }));
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
} /* end notify_low_on_oil */

/*
 * Function name: burned_out
 * Description:   If this function is called the lantern has burned out.
 */

public void
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
        env->catch_msg(BSN("The lantern flickers and goes out. It ran "+
            "out of oil."));
        tell_room(ENV(env), "The lantern flickers and goes out. "+
            "It ran out of oil.", ({ env }));
    }
    else if (env->query_prop(ROOM_I_IS))
    {
        tell_room(env, BSN("The " + short() + " flickers and goes out. It " +
            "ran out of oil."));
    }
} /* end burned_out */

public int
compute_weight()
{
    /* 1200 for the oil-lamp and 2 grams per 6 ml oil */
    return 1200 + (2 * query_time_left() / 6);
} /* end compute_weight */

public void
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
} /* end set_time_left */

public int
query_time_left()
{
    if (Burn_Alarm)
        time_left = ftoi(get_alarm(Burn_Alarm)[2]);

    else
        time_left = query_time(1);
    return time_left;
} /* end query_time_left */

public void
appraise_object(int num)
{
    int perc = ((query_time_left() * 100) / Max_Time);
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
} /* end appraise_object */

public string
query_recover()
{
    return MASTER + ":" + query_torch_recover() + query_keep_recover();
} /* end query_recover */

public void
init_recover(string arg)
{
    init_torch_recover(arg);
    init_keep_recover(arg);
} /* end init_recover */

public void
set_lamp_desc(string str)
{
    if (stringp(str) && strlen(str))
        lamp_desc = str;
} /* end set_lamp_desc */
