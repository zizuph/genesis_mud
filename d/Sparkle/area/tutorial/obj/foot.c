/*
 *  /d/Sparkle/area/tutorial/obj/rabbit_foot.c
 *
 *  These rabbits feet are meant to teach newbies the value of two
 *  things. Number one, looting corpses. Number two, the trading
 *  skill.
 *
 *  Created August 2005, by Cooper Sherry (Gorboth)
 *
 *  Doubled the value of lucky feet, Cherek, Mars 2015
 *
 */
#pragma strict_types
inherit "/std/object";

#include <ss_types.h>
#include <stdproperties.h>

/* global variables */
public string      Foot_Type = "";

/* prototypes */
public void        create_foot();
nomask void        create_object();
public mixed       check_steal();
public void        config_foot(string type);

public void        set_foot_type(string s) { Foot_Type = s; }
public string      query_foot_type() { return Foot_Type; }


/*
 * Function name:        create_foot
 * Description  :        a dummy function to be used by inheriting files
 */
public void
create_foot()
{
} /* create_foot */


/*
 * Function name:        create_object
 * Description  :        set up the rabbit foot
 */
nomask void
create_object()
{
    set_name("foot");
    set_pname("feet");
    add_name("_tutorial_item");

    add_prop(OBJ_I_WEIGHT, 5);
    add_prop(OBJ_I_VOLUME, 30);
    add_prop(OBJ_M_NO_STEAL, check_steal);

    create_foot();
    config_foot(Foot_Type);
} /* create_object */


/*
 * Function name:        check_steal
 * Description  :        this foot should not be stolen from the
 *                       animal who owns it (duh)
 * Returns      :        1: cannot steal
 *                       0: okay to steal
 */
public mixed
check_steal()
{
    if (!living(environment(this_object())))
    {
        return 0;
    }

    if (environment(this_object())->id("_tutorial_bunny"))
    {
        return "Live animals do not typically give up their feet.\n";
    }

    return 0;
} /* check steal */


/*
 * Function name:        config_foot
 * Description  :        set up the foot based on the Bunny Type
 * Arguments    :        string type - the type of foot we want
 */
public void
config_foot(string type)
{
    Foot_Type = type;

    switch(Foot_Type)
    {
        case "baby":
            set_short("baby bunny foot");
            set_pshort("baby bunny feet");
            add_adj( ({ "baby", "bunny" }) );
            add_prop(OBJ_I_VALUE, 5 + random(4));
            break;
        case "bunny":
            set_short("bunny foot");
            set_pshort("bunny feet");
            add_adj( ({ "bunny" }) );
            add_prop(OBJ_I_VALUE, 7 + random(4));
            break;
        case "rabbit":
            set_short("rabbit foot");
            set_pshort("rabbit feet");
            add_adj( ({ "rabbit" }) );
            add_prop(OBJ_I_VALUE, 10 + random(4));
            break;
        case "large":
            set_short("large rabbit foot");
            set_pshort("large rabbit feet");
            add_adj( ({ "large", "rabbit" }) );
            add_prop(OBJ_I_VALUE, 12 + random(4));
            break;
        case "jack":
            set_short("jackrabbit foot");
            set_pshort("jackrabbit feet");
            add_adj( ({ "jackrabbit" }) );
            add_prop(OBJ_I_VALUE, 15 + random(4));
            break;
        case "lucky":
            set_short("lucky rabbit foot");
            set_pshort("lucky rabbit feet");
            add_adj( ({ "lucky", "rabbit" }) );
            add_prop(OBJ_I_VALUE, 300 + random(30));
            break;
    }

    set_long("This " + short() + " is soft and furry. Farmer Brown has"
      + " struck a deal with the Greenhollow General Store so that you"
      + " will be able to sell these there for some money.\n");

    if (Foot_Type == "lucky")
    {
        set_long("Oho! You've found a lucky rabbit foot. These are quite"
          + " rare, and therefore sell for quite a bit of money back in"
          + " town. You should sell this and train your skills.\n");
    }
} /* config_foot */
