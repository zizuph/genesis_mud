/*
 *  /d/Sparkle/area/city/obj/gnome/gear.c
 *
 *  This is a standard gear for gnomish machinery.
 *
 *  Created October 2008, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

inherit "/d/Sparkle/area/city/obj/gnome/gnome_machinery";

#include <macros.h>

/* Global Variables */
public int         Clockwise = 0; /* true if clockwise = forward movement */

/* Prototypes */
public void        create_machine();
public void        set_clockwise(int i);
public void        configure_clockwise();
public string      get_the_desc();

public int         query_clockwise() { return Clockwise; }


/*
 * Function name:        create_machine
 * Description  :        set up the construct
 */
public void
create_machine()
{
    add_name("gear");
    set_adj( ({ "small", "complex" }) );
    set_short("@@get_the_desc@@" + "gear");
    set_desc("This gear is clearly of Gnomish design. It just ..."
      + " well, it seems to have altogether too many teeth for its"
      + " own good.");

    set_forward("turning "
      + ((Clockwise) ? "" : "counter-") + "clockwise");
    set_f_forward("still");
    set_backward("turning "
      + ((Clockwise) ? "counter-" : "") + "clockwise");
    set_f_backward("still");

    set_immediate(1);
    set_stop_next(1);
} /* create_machine */


/*
 * Function name:        set_clockwise
 * Description  :        set which direction the gear rotates
 * Arguments    :        int i: 1 - clockwise, 0 - counter-clockwise
 */
public void
set_clockwise(int i)
{
    Clockwise = i;
    configure_clockwise();
} /* set_clockwise */


/*
 * Function name:        configure_clockwise
 * Description  :        set up the rotation for this gear
 */
public void
configure_clockwise()
{
    set_forward("turning "
      + ((Clockwise) ? "" : "counter-") + "clockwise");
    set_f_forward("still");
    set_backward("turning "
      + ((Clockwise) ? "counter-" : "") + "clockwise");
    set_f_backward("still");
} /* configure_clockwise */


/*
 * Function name:        get_the_desc
 * Description  :        Make use of any externally set adjectives in
 *                       the description of the gear.
 */
public string
get_the_desc()
{
    switch (sizeof(query_adj(1)))
    {
        case 0:
            return "";
            break;
        case 1:
            return query_adj() + " ";
            break;
        default:
            return query_adj(1)[0] + " " + query_adj(1)[1] + " ";
    }
} /* get_the_desc */