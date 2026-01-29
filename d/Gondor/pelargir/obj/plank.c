/*
 * /d/Gondor/pelargir/obj/plank.c
 *
 * A wooden plank which can be used to repair a dock in Pelargir. 
 *
 * Olorin, January 1997
 *
 * Copyright (c) 1997 by Christian Markus
 *
 * Modification log:
 * Mirandus - April 6, 2015: Changed the plank so that you do not
 * have to wield the saw only have it in your inventory.
 * Cotillion - 2018-12-29
 * - Fixed weight update when sawing
 */
#pragma strict_types

inherit "/std/object.c";

#include <cmdparse.h>
#include <language.h>
#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "../lib/repair_dock.h"

#define THICK     5
#define WIDTH    30
// DENSITY in grams / liter:
#define DENSITY 750

// Prototypes:
public string  long_desc();
public int     volume();
public int     weight();

// Global variables:
static int     Length = 120;

public void
create_object()
{
    set_name("plank");
    add_name( ({ "board", "wood", "piece", }) );
    add_adj( ({ "wooden", "sturdy", "piece", "of", }) );
    set_long(long_desc);
    set_short("wooden plank");

    add_prop(OBJ_I_WEIGHT, weight);
    add_prop(OBJ_I_VOLUME, volume);
}

public string
long_desc()
{
    int    feet = (Length + 15) / 30;
    string desc = "The wooden plank is about two inches thick, a foot "
        + "in width and ";

    switch (feet)
    {
    case 0:
        desc += "less than a foot";
        break;
    case 1:
        desc += "about a foot";
        break;
    case 2..99:
    default:
        desc += "about " + LANG_WNUM(feet) + " feet";
        break;
    }
    desc += " in length.";

    if (query_prop(OBJ_I_BROKEN))
        desc += " It is broken.";

    return BSN(desc);
}

public int
query_length()
{
    return Length;
}

public int
set_length(int l)
{
    int     res;

    if (l > Length)
        res = 1;
    else if (l == Length)
        res = 0;
    else
        res = -1;

    mark_state();
    Length = l;
    update_state();

    return res;
}

public int
volume()
{
    return (THICK * WIDTH * Length);
}

public int
weight()
{
    return (volume() * DENSITY) / 1000;
}

/*
 * Function name: saw_plank
 * Description:   do the checks if we can saw the plank,
 *                and if we're successful, reduce length and create the
 *                second half of the plank.
 *                Note that we cannot use notify_fail messages for failures
 *                here, since if there is more than one plank, the second
 *                plank will overwrite the notify_fail message of the first.
 * Argument:      length in inches to cut off
 * Returns:       1/0 - success/failure
 */
private int
saw_plank(int short)
{
    int    feet = (short + 15) / 30;
    object tp = TP,
           saw,
           room,
           newp;

    if (!objectp(saw = present("saw", tp)))
    {
        write("You need a saw to saw!\n");
        return 0;
    }

    /*if (saw->query_wielded() != tp)
    {
        write("Wield your saw first!\n");
        return 0;
    }*/

    if (query_prop(OBJ_I_BROKEN))
    {
        write("The " + query_short() + " is broken, sawing it into even "
            + "smaller pieces won't help.\n");
        return 0;
    }

    if (!feet || (short > (Length - 30)))
    {
        write("You cannot saw the plank into so short pieces.\n");
        return 0;
    }

    write("You saw a piece about " + ((feet > 1) ? LANG_WNUM(feet) 
        + " feet" : "a foot") + " in length from the " 
        + query_short() + ".\n");
    say(QCTNAME(tp) + " saws a piece from the " + query_short() +
        ".\n");

    short += random(11) + random(11) - 10;
    mark_state();
    Length -= short;
    update_state();

    FIX_EUID;
    newp = clone_object(MASTER);
    newp->set_length(short);
    if (newp->move(room = ENV(TO)))
    {
        if (objectp(room = ENV(room)))
        {
            if (newp->move(room))
                newp->move(room, 1);
        }
        else
            newp->move(ENV(TO), 1);
    }
    seteuid(0);
    SET_STAGE(tp, REPAIR_SAW);

    return 1;
}

public int
do_saw(string str)
{
    int     li;
    int     result;
    object *what;
    string  lw,
            vb = query_verb();

    NFN(CAP(vb) + " what?\n" +
        "You can either \"saw plank in two\" or you can, e.g., " + 
        "\"saw two feet from plank\".");

    if (!strlen(str))
        return 0;

    str = LOW(str);
    if (str == "plank in two")
    {
        saw_plank(Length / 2);
        // We have to return 1 here.
        return 1;
    }

    if (!parse_command(str, ENV(TP), " %w 'foot' / 'feet' 'from' %i ",
        lw, what))
        return 0;

    if (!sizeof(what))
        return 0;

    what = NORMAL_ACCESS(what, 0, 0);
    if (member_array(TO, what) < 0)
        return 0;

    if (!(li = LANG_NUMW(lw)))
        return 0;

    saw_plank(li * 30);
    // We have to return 1 here.
    return 1;
}

public void
init()
{
    ::init();

    add_action(do_saw, "saw");
}
