/*
 *  /d/Sparkle/area/tutorial/obj/map.c
 *
 *  This is a map of Greenhollow that is part of the tutorial
 *  for new players in Genesis.
 *
 *  Obtained at: /d/Sparkle/area/tutorial/town/silverdell_4.c
 *
 *  Created August 2004, by Cooper Sherry (Gorboth)
 */
#pragma strict_types
#include "../defs.h"

inherit "/std/object";

#include <stdproperties.h>

/* prototypes */
public void        create_object();
public void        leave_env(object from, object to);
public string      describe();
public void        blow_away();


/*
 * Function name:        create_object
 * Description  :        set up the object
 */
public void
create_object()
{
    set_name("map");
    add_name( ({ "_greenhollow_map", "_tutorial_item" }) );

    add_adj( ({ "greenhollow", "old", "paper" }) );
    set_short("old paper map");
    set_long(describe);

    add_cmd_item( ({ "map", "greenhollow map", "map of greenhollow" }),
                  ({ "read" }), describe);

    setuid();
    seteuid(getuid());

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
 * Function name:        describe
 * Description  :        read the map picture from a file for the long
 *                       description
 * Returns      :        string - the text
 */
public string
describe()
{
    return read_file(TEXT_DIR + "greenhollow_map", 0);
} /* describe */


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

    tell_room(environment(this_object()), "The map blows away in the"
      + " wind.\n");
    remove_object();
} /* blow_away */

