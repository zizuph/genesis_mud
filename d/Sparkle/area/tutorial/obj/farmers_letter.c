/*
 *  /d/Sparkle/area/tutorial/obj/farmers_letter.c
 *
 *  This letter is given to players as part of the potion quest.
 *  Given by: /d/Sparkle/area/tutorial/npc/farmers_wife.c
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


/*
 * Function name:        create_object
 * Description  :        set up the object
 */
public void
create_object()
{
    set_name("letter");
    add_name( ({ "_tutorial_letter", "_tutorial_item" }) );

    add_adj( ({ "crumpled" }) );
    set_short("crumpled letter");
    set_long("The letter reads:\n\n"
      + "Dear Bibbiss,\n\n"
      + "Baron von Krolock has sent demons to eat our crops. Can you"
      + " think of anything which could help us?\n\n"
      + "Your friend,\n"
      + "Matilda\n\n");

    add_cmd_item( ({ "letter", "crumpled letter" }),
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
        return;

    if (!to->query_prop(ROOM_I_IS))
    {
        return;
    }

    set_alarm(1.0, 0.0, blow_away);
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

    tell_room(environment(this_object()), "The letter blows away in the"
      + " wind.\n");
    remove_object();
} /* blow_away */


