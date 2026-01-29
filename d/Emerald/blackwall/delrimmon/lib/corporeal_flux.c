/*
 *  /d/Emerald/blackwall/delrimmon/lib/corporeal_flux.c
 *
 *  This is a module of functions which can be inherited by rooms
 *  which wish to use the enchanted portals. Please note - many
 *  of the functions needed for the code to work properly are not
 *  included, since there is no point in putting them here. Rather,
 *  for a complete example of how this code fits together, refer to:
 *
 *      /d/Emerald/blackwall/delrimmon/lakeside/east_overlook.c
 *
 *  Copyright (c) February 2002, by Cooper Sherry (Gorboth)
 */
#include <macros.h>
#include "/d/Emerald/blackwall/delrimmon/defs.h"

public int         corporeal_flux(object player);
public void        end_flux(object player);
public int         do_touch(string arg);
public int         door_exit();
public int         say_password(string arg);


/*
 * Function name:        door_exit
 * Description  :        check to see if the player is in corporeal
 *                       flux. If not, they cannot pass this way.
 * Returns      :        1 - cannot pass, 0 - may pass
 */
public int
door_exit()
{
    if (this_player()->query_prop(FLUX_PROP))
    {
        write("You walk through the stone door.\n");
        return 0;
    }

    write("The stone door blocks your path.\n");
    return 1;
} /* door_exit */


/*
 * Function name:        corporeal_flux
 * Description  :        if not already in this state, the player is
 *                       rendered non-corporeal, allowing him to pass
 *                       through the stone doorway into the room
 *                       beyond.
 * Arguments    :        object player - the player object
 * Returns      :        1 - do it, 0 - already done, so don't do it
 */
public int
corporeal_flux(object player)
{
    if (player->query_prop(FLUX_PROP))
    {
        player->catch_tell("You are already in flux!\n");
        return 0;
    }

    player->add_prop(FLUX_PROP, 1);
    player->catch_tell(
        "You say: " + CAP(MANAGER->query_password(player)) + "!\n"
      + "The door pulses briefly with a bright blue light, which travels"
      + " up your arm and over your whole body. You suddenly notice that"
      + " the breeze is no longer blowing against you, and that you do"
      + " not feel your weight upon the ground. Your hand moves forward"
      + " into the rock, disappearing beyond the surface of the door.\n");
    player->remove_prop(TOUCH_PROP);
    player->set_no_show_composite(1);
    player->set_invis(1);

    set_alarm(5.0, 0.0, &end_flux(player));

    return 1;
} /* corporeal_flux */


/*
 * Function name:        end_flux
 * Description  :        end the corporeal flux effect on the player
 * Arguments    :        object player - the player object
 */
public void
end_flux(object player)
{
    player->set_no_show_composite(0);
    player->set_invis(0);
    player->catch_tell("You feel the floor solidly against"
                     + " your feet once more as your corporeal form"
                     + " returns.\n");
    player->remove_prop(FLUX_PROP);
} /* end_flux */


/*
 * Function name:        do_touch
 * Description  :        allow the player to touch the door/emblem
 * Arguments    :        string arg - what the player typed
 * Returns      :        1 - success, 0 - failure
 */
public int
do_touch(string arg)
{
    if (!strlen(arg))
    {
        NFN0(CAP(QVB) + " what?");
    }

    if (!parse_command(arg, ({}),
        "[the] [east] [eastern] [stone] 'door' / 'doors' / 'doorway'"
      + " / 'emblem' / 'portal'"))
    {
        return 0; /* we don't like the syntax, send it to the mudlib */
    }

    if (this_player()->query_prop(TOUCH_PROP))
    {
        write("You are already touching the door.\n");
        return 1;
    }

    if (this_player()->query_prop(FLUX_PROP))
    {
        write("Your hand passes through the stone of the door as"
            + " you reach out to touch it.\n");
        return 1;
    }

    this_player()->add_prop(TOUCH_PROP, 1);
    write("You reach out, and touch the doorway.\n");

    return 1;
} /* do_touch */


/*
 * Function name:        say_password
 * Description  :        catch it if the player happens to speak the
 *                       password which he has been assigned for the
 *                       outpost doors
 * Arguments    :        string arg - what the player typed after 'say'
 * Returns      :        1 - success, 0 - failure
 */
public int
say_password(string arg)
{
    string  txt = LOW(arg);

    if (txt == MANAGER->query_password(this_player()) ||
        txt == MANAGER->query_password(this_player()) + "." ||
        txt == MANAGER->query_password(this_player()) + "!")
    {
        if (this_player()->query_prop(TOUCH_PROP))
        {
            corporeal_flux(this_player());
            return 1;
        }

        write("You say: "
          + CAP(MANAGER->query_password(this_player())) + "!\n"
          + "The stone door in the east wall of rock pulses briefly"
          + " with a bright blue light.\n");
        return 1;
    }

    return 0; /* let the mudlib take it from here */
} /* say_password */
