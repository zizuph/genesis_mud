/*
 *  /d/Sparkle/guilds/new_merc/dummy_startloc.c
 *
 *  This is the actual startlocation room for all Mercenaries who
 *  decide to bunk at the guild. It performs a check on their
 *  alignment, and then sends them to the appropriate faction
 *  bunk room.
 *
 *  Created May 2009, by Cooper Sherry (Gorboth)
 */
#pragma strict_types
#include "../merc_defs.h"

inherit MERC_ROOM_BASE;

#include <macros.h>
#include <stdproperties.h>

/* Prototypes */
public void        create_merc_room();


/*
 * Function name:        create_merc_room
 * Description  :        set up the room with area presets
 */
public void
create_merc_room()
{
    object   door;

    set_short("you wake up from your sleep and get up from your"
      + " bunk");
    set_long(capitalize(short()) + ".\n\n");

    add_prop(ROOM_I_INSIDE, 1);

    setuid();
    seteuid(getuid());
} /* create_room */


/* 
 * Function name: enter_inv
 * Description:   Called when objects enter this container or when an
 *                object has just changed its weight/volume/light status.
 * Arguments:     ob: The object that just entered this inventory
 *                from: The object from which it came.
 *
 * This function is masked to send players immediately to their
 * appropriate location when logging in.
 */
public void
enter_inv(object ob, object from)
{
    object   destination = safely_load_master_file(
                               ROOM_DIR + "neutral_start");
    int      align;

    ::enter_inv(ob, from);

    if (!interactive(ob))
    {
        return;
    }

    align = ob->query_alignment();

    if (align < -619)
    {
        destination = safely_load_master_file(ROOM_DIR + "evil_start");
    }

    if (align > 549)
    {
        destination = safely_load_master_file(ROOM_DIR + "good_start");
    }

    ob->move_living("M", destination, 1, 1);

    /* If the player just logged in, they shouldn't have a last
     * room, in which case we have them stretch, etc. But ... if
     * they didn't just log in, we don't want to do those things.
     */
    if (from)
    {
        return;
    }

    set_alarm(0.1, 0.0, &tell_room(destination, QCTNAME(ob)
      + " wakes up and rises from " + ob->query_possessive()
      + " bunk.\n", ob));
    set_alarm(1.0, 0.0, &ob->command("$stretch"));
} /* enter_inv */
