/*
 *  /d/Emerald/herbs/darkroot_pulp.c
 *
 *  This is the object that is cloned into the player's inventory when
 *  they chew the darkroot. It adds a heavy layer of
 *  darkness levels to the room, but lasts only for a very brief
 *  while before it is gone.
 *
 *  Copyright (c) March 2002, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

inherit "/std/object";

#include <const.h>
#include <stdproperties.h>

#define DARKROOT_DURATION 30.0

/* prototypes */
public void        create_object();
public void        remove_pulp();

public int dest_alarm = 0;

/*
 * Function name:        create_object
 * Description  :        set up the object
 */
public void
create_object()
{
    set_name("em_darkroot_pulp");
    add_name("pulp");
    set_short("pulp");
    set_long("pulp\n");

    dest_alarm = set_alarm(DARKROOT_DURATION, 0.0, remove_pulp);

    set_no_show();
    add_prop(OBJ_I_LIGHT, DARKNESS_TEMPORARY);
} /* create_object */

public void
extend_duration()
{
    mixed *alarm_data;
    float time_remaining, time_extension;

    if (dest_alarm && (alarm_data = get_alarm(dest_alarm)))
    {
        time_remaining = alarm_data[2];
        remove_alarm(dest_alarm);
        // Using multiple darkroots in a short duration is not as effective.
        // Reduce the extended duration by 15% of the current time remaining,
        // up to 50% of the standard duration.
        time_extension = max(DARKROOT_DURATION / 2.0, DARKROOT_DURATION - time_remaining * 15.0 / 100.0);
        set_alarm(time_remaining + time_extension, 0.0, remove_pulp);
    }
}

/*
 * Function name:        remove_pulp
 * Description  :        remove this object
 */
public void
remove_pulp()
{
    // We don't want any errors removing the pulp, so be extra careful to
    // make sure the environment is correct before giving a message.
    object env = environment(this_object());

    if (env && (env = environment(env)))
    {
        tell_room(env, "The darkness in the area suddenly lifts.\n");
    }

    this_object()->remove_object();
} /* remove_pulp */
