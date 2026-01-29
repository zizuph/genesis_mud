/*
 *  /d/Sparkle/area/city/obj/gnome/lever.c
 *
 *  This is a steering wheel for gnomish machinery.
 *
 *  Created October 2008, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

inherit "/d/Sparkle/area/city/obj/gnome/gnome_machinery";

#include "../../defs.h"

/* Global Variables */
public string      Lever_Position = "middle";

/* Prototypes */
public void        create_machine();
public string      get_the_desc();
public int         mess_with_lever(string arg);
public void        init();


/*
 * Function name:        create_machine
 * Description  :        set up the construct
 */
public void
create_machine()
{
    add_name("wheel");
    set_adj( ({ "chrome", "steering" }) );
    set_short("@@get_the_desc@@" + "wheel");
    set_desc("This " + get_the_desc() + "wheel could probably be"
      + " given a <turn> to the right or the left. Hard to know what"
      + " would happen as a result.");

    set_f_delay(1.5);
    set_b_delay(1.5);

    set_forward("turning");
    set_f_forward("fixed in place, angled straight up and down");
    set_backward("turning");
    set_f_backward("fixed in place, angled straight up and down");
} /* create_machine */


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


/*
 * Function name:        mess_with_lever
 * Description  :        allow the player to mess with the lever
 * Arguments    :        string arg - what was typed after the verb
 * Returns      :        int 1 - success, 0 - failure
 */
public int
mess_with_lever(string arg)
{
    string    steer;

    if (!strlen(arg))
    {
        notify_fail("What do you want to " + query_verb() + "?\n");
        return 0;
    }

    if (!parse_command(arg, ({}),
        "[the] [" + query_adj(1)[0] + "] [" + query_adj(1)[1] + "]"
      + " 'wheel' %s", steer))
    {
        notify_fail("Do you want to " + query_verb() + " the wheel"
          + " perhaps?\n");
        return 0;
    }
    else if (parse_command(arg, ({}),
               "[the] [" + query_adj(1)[0] + "] [" + query_adj(1)[1] + "]"
             + " 'wheel'"))
    {
        notify_fail("Do you want to " + query_verb() + " the wheel"
          + " to the right or the left?\n");
        return 0;
    }

    if (steer != "right" && steer != "left")
    {
        notify_fail("You can only " + query_verb() + " the wheel to"
          + " the right or the left.\n");
        return 0;
    }

    switch(query_activity())
    {
        case "moving_forward":
        case "moving_backward":
            write("The wheel is currently being turned. Patience!\n");
            return 1;
            break;
        default:
            break;
    }

    switch(Lever_Position)
    {
        case "right":
            switch(steer)
            {
                case "right":
                    write("The wheel does not seem to be able to be"
                      + " turned any farther to the right.\n");
                    return 1;
                    break;
                case "left":
                    write("You crank the wheel hard to the left.\n");
                    trigger_backward();
                    set_f_backward("fixed in place, angled straight"
                      + " up and down");
                    Lever_Position = "middle";
                    set_do_trigger(1);
                    set_stop_next(1);
                    return 1;
                    break;
            }
            break;
        case "middle":
            switch(steer)
            {
                case "right":
                    write("You crank the wheel hard to the right.\n");
                    trigger_forward();
                    set_f_forward("fixed in place, angled to the right");
                    Lever_Position = "right";
                    set_do_trigger(1);
                    set_stop_next(0);
                    return 1;
                    break;
                case "left":
                    write("You crank the wheel hard to the left.\n");
                    trigger_backward();
                    set_f_backward("fixed in place, angled to the left");
                    Lever_Position = "left";
                    set_do_trigger(1);
                    set_stop_next(0);
                    return 1;
                    break;
            }
            break;
        default:
        case "left":
            switch(steer)
            {
                case "left":
                    write("The wheel does not seem to be able to be"
                      + " turned any farther to the left.\n");
                    return 1;
                    break;
                case "right":
                    write("You crank the wheel hard to the right.\n");
                    trigger_forward();
                    set_f_backward("fixed in place, angled straight"
                      + " up and down");
                    Lever_Position = "middle";
                    set_do_trigger(1);
                    set_stop_next(1);
                    return 1;
                    break;
            }
            break;
    }

    return 1;
} /* mess_with_lever */

public void
init()
{
    ::init();

    add_action(mess_with_lever, "turn");
    add_action(mess_with_lever, "crank");
    add_action(mess_with_lever, "steer");
} /* init */