/*
 *  /d/Sparkle/area/tutorial/obj/rope.c
 *
 *  This is the rope that Farmer Brown makes from scavenged animal
 *  intestines that the player brings him. It can be joined together
 *  with claws to make a grapling hook.
 *
 *  Created September 2005, by Cooper Sherry (Gorboth)
 */
#pragma strict_types
#include "../defs.h"

inherit "/std/object";

#include <stdproperties.h>
#include <language.h>

/* Global Variables */
public int         Length = 10;   /* the starting length of the rope */
public int         Claws  = 0;    /* how many claws are attached? */

/* Prototypes */
public void        create_object();
public string      describe_short();
public string      describe_long();

public void        increase_claws()   { Claws++; }
public int         query_claws()      { return Claws; }
public void        increase_length()  { Length += 10; }
public void        decrease_length()  { Length -= 10; }
public int         query_length()     { return Length; }


/*
 * Function name:        create_object
 * Description  :        set up the rope
 */
public void
create_object()
{
    set_name("rope");
    add_name( ({ "_tutorial_rope", "_tutorial_item" }) );

    set_short(describe_short);
    set_long(describe_long);

    add_prop(OBJ_M_NO_DROP, "You should probably keep it.\n");
    add_prop(OBJ_M_NO_SELL, "The rope has no value.\n");
    add_prop(OBJ_M_NO_GIVE, "You figure the rope is too useful to give"
      + " away. You could probably <show> it to someone, though.\n");
    add_prop(OBJ_I_WEIGHT, Length);
    add_prop(OBJ_I_VOLUME, (Length * 3) / 2);
} /* create_object */


/*
 * Function name:        describe_short
 * Description  :        provide a Length dependant description
 * Returns      :        string - the short description
 */
public string
describe_short()
{
    string   txt = LANG_NUM2WORD(Length) + "-foot rope";

    if (Claws)
    {
        add_adj( ({ "hooked", "claw-hooked" }) );
        return "claw-hooked " + txt;
    }

    return txt;
} /* describe_short */


/*
 * Function name:        describe_long
 * Description  :        provide a Length dependant description
 * Returns      :        string - the long description
 */
public string
describe_long()
{
    string   txt = "This rope is about " + LANG_NUM2WORD(Length) + " feet"
          + " long. It appears to have been made from the gutstrings of"
          + " an animal. ";

    if (Length < 100)
    {
        return txt + "It would probably need to be a bit longer before"
          + " you could really use it for much of anything.\n";
    }

    if (Claws)
    {
        if (Claws == 2)
        {
            return txt + "There are two claws attached to the end.\n";
        }

        return txt + "There is a single claw attached to the end.\n";
    }

    return txt + "It looks long enough now to be useful. Perhaps you"
      + " should <show> it to Farmer Brown.\n";
} /* describe_long */
