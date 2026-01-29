/*
 *  /d/Sparkle/area/city/obj/gnome/lever.c
 *
 *  This is a standard lever for gnomish machinery.
 *
 *  Created October 2008, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

inherit "/d/Sparkle/area/city/obj/gnome/gnome_machinery";

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
    add_name("lever");
    set_adj( ({ "brightly", "painted" }) );
    set_short(get_the_desc() + "lever");
    set_desc("This " + get_the_desc() + "lever looks as if you could"
      + " <pull> or <push> it. But you'd better be careful, it"
      + " has a definitely gnomish look to it, so you never know what"
      + " might happen!");

    set_f_delay(5.0);
    set_b_delay(5.0);

    set_forward("sliding slowly forward in its slot");
    set_f_forward("still, at an upright angle");
    set_backward("sliding slowly backward in its slot");
    set_f_backward("still, at an upright angle");
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
    if (!strlen(arg))
    {
        notify_fail("What do you want to " + query_verb() + "?\n");
        return 0;
    }

    if (!parse_command(arg, ({}),
        "[the] [" + query_adj(1)[0] + "] [" + query_adj(1)[1] + "]"
      + " 'lever'"))
    {
        notify_fail("Do you want to " + query_verb() + " the lever"
          + " perhaps?\n");
        return 0;
    }

    switch(query_activity())
    {
        case "moving_forward":
        case "moving_backward":
            write("The lever is already in motion, and does not"
              + " respond to your efforts.\n");
            return 1;
            break;
        default:
            break;
    }

    switch(Lever_Position)
    {
        case "forward":
            switch(query_verb())
            {
                case "push":
                    write("The lever does not seem to be able to move"
                      + " any further forward in its slot, no matter how"
                      + " hard you push it.\n");
                    return 1;
                    break;
                case "pull":
                    write("You pull hard on the lever.\n");
                    trigger_backward();
                    set_f_backward("still, at an upright angle");
                    Lever_Position = "middle";
                    set_do_trigger(1);
                    set_stop_next(1);
                    return 1;
                    break;
            }
            break;
        case "middle":
            switch(query_verb())
            {
                case "push":
                    write("You push hard on the lever.\n");
                    trigger_forward();
                    set_f_forward("still, at a forward angle");
                    Lever_Position = "forward";
                    set_do_trigger(1);
                    set_stop_next(0);
                    return 1;
                    break;
                case "pull":
                    write("You pull hard on the lever.\n");
                    trigger_backward();
                    set_f_backward("still, at a backward angle");
                    Lever_Position = "backward";
                    set_do_trigger(1);
                    set_stop_next(0);
                    return 1;
                    break;
            }
            break;
        default:
        case "backward":
            switch(query_verb())
            {
                case "pull":
                    write("The lever does not seem to be able to move"
                      + " any further backward in its slot, no matter how"
                      + " hard you pull it.\n");
                    return 1;
                    break;
                case "push":
                    write("You push hard on the lever.\n");
                    trigger_forward();
                    set_f_forward("still, at an upright angle");
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

    add_action(mess_with_lever, "push");
    add_action(mess_with_lever, "pull");
} /* init */