/*
 *  /d/Sparkle/area/tutorial/obj/potion.c
 *
 *  This potion is given to players as part of the potion quest.
 *  Given by: /d/Sparkle/area/tutorial/npc/magic_trainer.c
 *
 *  Created August 2005, by Cooper Sherry (Gorboth)
 */
#pragma strict_types
#include "../defs.h"

inherit "/std/object";

#include <stdproperties.h>

/* prototypes */
public void        create_object();
public void        leave_env(object from, object to);
public void        blow_away();
public void        blow_up(object from, object to);

/*
 * Function name:        create_object
 * Description  :        set up the object
 */
public void
create_object()
{
    set_name("potion");
    add_name( ({ "_tutorial_potion", "vial", "_tutorial_item" }) );

    add_adj( ({ "light", "blue" }) );
    set_short("light blue potion");
    set_long("The blue liquid of the potion bubbles somewhat in its"
      + " vial. Attached to the potion is a note which reads:\n\n"
      + "Matilda, make a broth from this potion, and find a way to feed"
      + " it to the mother demon. -Bibbiss\n\n");

    add_cmd_item( ({ "note" }),
                  ({ "read" }), long);

    add_prop(OBJ_I_WEIGHT, 10);
    add_prop(OBJ_I_VOLUME, 7);
} /* create_object */


/*
 * Function name:        leave_env
 * Description  :        we don't want these piling up anywhere, so we
 *                       have them vanish if the player drops them
 * Arguments    :        object from - where it came from
 *                       object to   - where it went
 */
public void
leave_env(object from, object to)
{
    ::leave_env(from, to);

    if (!objectp(from) || !objectp(to) || !living(from))
    {
        return;
    }

    if (to->query_prop(ROOM_I_IS))
    {
        set_alarm(0.0, 0.0, blow_away);
        return;
    }

    if (!to->id("_tutorial_farmers_wife"))
    {
        if (!from->id("_tutorial_potion_giver"))
        {
            set_alarm(0.0, 0.0, &blow_up(from, to));
        }
    }

    return;
} /* leave_env */


/*
 * Function name:        blow_away
 * Description  :        give a delay before we blow the map away. Also
 *                       check to see if anyone has picked it up first.
 */
public void
blow_away()
{
    if (interactive(environment(this_object())))
    {
        return;
    }

    tell_room(environment(this_object()), "The vial shatters as the"
      + " potion hits the ground!\n");
    remove_object();
} /* blow_away */


/*
 * Function name:        blow_up
 * Description  :        destroy the potion if a player tries to give
 *                       it to another player
 * Arguments    :        object from - the giver,
 *                       object to   - the receiver
 */
public void
blow_up(object from, object to)
{
    from->catch_tell("Oops! You fumbled the potion! It explodes as"
      + " it hits the ground.\n");
    to->catch_tell("Oops! A fumble! The potion explodes as it hits"
      + " the ground.\n");
    remove_object();
} /* blow_up */

