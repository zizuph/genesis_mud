/*
 *  /w/aeg/sparkle/bank/obj/screw.c
 *
 *  This is a standard screw for gnomish machinery.
 *  This is a screw that generally connects to gears
 *  to show the mechanical energy transferred across the room
 *  or to another room.
 *
 *  Created Feb 2009, Aeg (Matthew Morin)
 *  Honours to Gorboth (Cooper Sherry)
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
    add_name("screw");
    set_adj( ({ "metallic" }) );
    set_short("@@get_the_desc@@" + "screw");
    set_desc("This is a metallic screw that is mounted to allow movement.");

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
 * Description  :        set which direction the screw rotates
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
 * Description  :        set up the rotation for this screw.
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
 *                       the description of the screw.
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