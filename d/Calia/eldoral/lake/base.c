/*
 * base.c
 * 
 * This is the baseroom for the 'water' rooms in the lake.
 * They aren't meant for players, just a way for the skiff
 * to get from one shore to another.
 * 
 * Khail - Feb 24/97
 */
#pragma strict_types

#include "defs.h"
#define DENSITY 1

inherit STDROOM;

string extra;

public int
player_knows_eldoral()
{
    if (TP->query_skill(SK_ELDORAL_CASTLE_NAME) &
        SK_ELDORAL_NAME_VALUE)
        return 1;
    return 0;
}

/*
 * Function name: exit_block
 * Description  : Delivers a message a blocks certain exits.
 * Arguments    : n/a
 * Returns      : 1
 */
public int
exit_block()
{
    write("You feel compelled not to swim in that direction.\n");
    return 1;
}

/*
 * Function name: modify_long
 * Description  : Modifies the long desc so there are different results
 *                for players looking at the water and player in the
 *                water.
 * Arguments    : n/a
 * Returns      : Appropriate long desc.
 */
public string
modify_long()
{
    if (environment(TP) == TO)
    {
        return "You are floating in the frigid, but calm, waters " +
            "of a dark, fog-cloaked lake. The water itself is " +
            "dark, but due only to it's depth and the darkness " +
            "caused by the fog. It is, however, very clean, but " +
            "extremely cold, and you can feel numbness setting " +
            "into your limbs. The view, however, is largely " +
            "obscured by the thick fog which blankets the waters. ";
    }
    else
    {
        return "You look out across the calm, dark waters of the " +
            "lake, but see very little due to the thick blanket of " +
            "fog which permeates the air. The surface of the lake " +
            "is very calm, but you can feel the damp chill rising " +
            "off the water, causing you to huddle slightly. ";
    }
}

/*
 * Function name: create_lake
 * Description  : Turns this room into a lake.
 * Arguments    : n/a
 * Returns      : n/a
 */
public void
create_lake()
{
    set_short("upon a fog-covered lake");
    set_long("@@modify_long@@" +
        (stringp(extra) ? extra : "") + "\n\n");

    add_exit(MASTER, "northeast", "@@exit_block");
    add_exit(MASTER, "east", "@@exit_block");
    add_exit(MASTER, "southeast", "@@exit_block");
    add_exit(MASTER, "southwest", "@@exit_block");
    add_exit(MASTER, "west", "@@exit_block");
    add_exit(MASTER + "northwest", "@@exit_block");
    add_exit(MASTER + "down", "@@exit_block");
    set_noshow_obvious(1);

    add_item(({"water", "waters", "calm waters", "lake"}),
        "The waters of the lake are cold and clear, but the " +
        "overcast sky and the apparent depth of the lake give the " +
        "water a dark black appearance. While cold, the water is " +
        "quite calm, and except for the occasional ripple of a " +
        "wave, it looks much like being in the middle of a huge " +
         "mirror.\n");
    add_item(({"sky", "clouds"}),
        "Above your head, you can see through the low-lying " +
        "blanket of mist dark, slowly churning clouds covering " +
        "the sky. While not particularly gloomy, this isn't " +
        "one of the most cheerful places you've been.\n");
    add_item(({"mist", "fog"}),
        "Cold and damp, the mist over the waters of the lake " +
        "hangs suspended like a giant blanket of delicate cobwebs, " +
        "covering the view like a wall of stone, yet as " +
        "insubstantial as a summer's breeze.\n");

    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);
}

/*
 * Function name: create_shore
 * Description  : Adds a shoreline to the long desc.
 * Arguments    : where - The direction of the shoreline.
 *                far - If true, the shore is far away.
 * Returns      : n/a
 */
public varargs void
create_shore(string where, int far)
{
    if (!stringp(extra))
        extra = "";

    if (far)
    {
        extra += "Far off to the " + where + ", you discover that " +
            "dimly make out a dark outline through the heavy fog, " +
            "possibly a shoreline, but you're still to far away " +
            "to tell for sure. ";
        add_item(({"outline", "dark outline", "shoreline"}),
            "From here it's hard to judge for sure. The shape is " +
            "little more than a bluish-grey outline against the " +
            "solid grey background of the mist, but it could " +
            "very well be a small landmass.\n");
    }
    else
    {
        extra += "Despite the heaviness of the fog, you can see " +
            "to the " + where + " the dark outline of a forested " +
            "shoreline, but details are hard to make out, as the " +
            "fog keeps shifting under the pressure of a light " +
            "breeze which brushes the lake. ";
        add_item(({"outline", "dark outline"}),
            "The shifting mist partially obscures the shoreline " +
            "from this vantage point, however it is more of a veil " +
            "than a barrier from here. The swirling grey cloak " +
            "passes among the upper reaches of dark green evergreens " +
            "which comprise almost everything you can see of the " +
            "shoreline from here. At the base of the trees, a " +
            "narrow strip of shore holds the waters of the lake " +
            "at bay.\n");
        add_item(({"trees", "forest", "evergreens"}),
            "Trees of such heights, you feel sure their age transcends " +
            "the age of Caliana herself. They appear to be " +
            "evergreens of some sort, though it's impossible to " +
            "tell for sure, as even at this distance the fog " +
            "hides all but their most obvious details.\n");
        add_item(({"shoreline", "shore"}),
            "Between the trees and the water's edge, a narrow " +
            "grey strip of land stretches in and out of view " +
            "to the east and the west.\n");
    }
}

/*
 * Function name: enter_inv (MASK)
 * Description  : Called when an object enters our inventory.
 *                Used here to make non-living objects float if 
 *                they are lighter than water, or sink otherwise.
 * Arguments    : ob - Object pointer to the incominb object.
 *                from - Object pointer to 'ob's last environment.
 * Returns      : n/a
 */
public void
enter_inv(object ob, object from)
{
    int vol,
        wght;

    ::enter_inv(ob, from);

    if (MASTER_OB(ob) == (OBJ + "skiff"))
        return;

    if (living(ob) && !interactive(ob))
    {
        tell_room(TO, QCTNAME(ob) + " thrashes for a moment, then sinks " +
            "slowly out of sight, beneath the cold waters of " +
            (player_knows_eldoral() ? "Lake Eldoral" : "the lake") +
            ".\n");
        ob->move(LAKE + "sank");
    }
    else if (interactive(ob))
    {
        tell_object(ob, "The water here is _very_ cold. You suspect it " +
            "be prudent to find a way to land as fast as possible.\n");
    }
    else if (!living(ob))
    {
        wght = ob->query_prop(OBJ_I_WEIGHT);
        vol = ob->query_prop(OBJ_I_VOLUME);
        if (vol && (!wght || wght/vol <= DENSITY))
        {
            tell_room(TO, "The " + ob->short() + " floats.\n");
        }
        else
        {
            tell_room(TO, "The " + ob->short() + " sinks quickly " +
                "beneath the waters of the lake.\n");
            ob->move(LAKE + "sank");
        }
    }
}
