/*
 *  /d/Emerald/blackwall/delrimmon/lakeside/caves/fallroom.c
 *
 *  This is the room we move players to who are falling down to the
 *  subterranian grotto.
 *
 *  Copyright (c) September 2001, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

inherit "/d/Emerald/blackwall/delrimmon/legacy/del_rimmon_room";
inherit "/d/Emerald/blackwall/delrimmon/lib/water_effects";

#include <stdproperties.h>
#include "/d/Emerald/blackwall/delrimmon/defs.h"

/* prototypes */
public void        create_del_rimmon();
public void        first_message(object who);
public void        second_message(object who);
public void        third_message(object who);
public void        fourth_message(object who);
public void        surface(object who);
public void        enter_inv(object ob, object from);


/*
 * Function name:        create_del_rimmon
 * Description  :        set up the room
 */
public void
create_del_rimmon()
{
    add_name("del_rimmon_fallroom");
    set_short("you peer frantically around. Dark shapes are whirling"
            + " past you as you fall");
    set_long(CAP(short()) + ".\n");

    add_item( ({ "shape", "shapes", "dark shapes" }),
        "You are too disoriented to focus your eyes on anything.\n");

    add_prop(ROOM_M_NO_TELEPORT,
        "A strange force prevents your travel.\n");
    add_prop(ROOM_I_INSIDE, 1);

    set_no_exit_msg( ({ "north", "northeast", "east", "southeast",
                        "south", "southwest", "west", "northwest",
                        "up", "down" }),
        "You flail violently with your arms and legs in a desperate"
      + " attempt to maneuver.\n");
} /* create_del_rimmon */


/*
 * Function name:        first_message
 * Description  :        first message for the falling player
 * Arguments    :        object who - the player
 */
public void
first_message(object who)
{
    who->catch_msg("Air rushes past you as you fall.\n\n");
    set_alarm(4.0, 0.0, &second_message(who));

    return;
} /* first_message */


/*
 * Function name:        second_message
 * Description  :        second message for the falling player
 * Arguments    :        object who - the player
 */
public void
second_message(object who)
{
    who->catch_msg("Your eyes begin to focus somewhat, and you"
      + " get the sense that you are falling down a long and dark"
      + " hole in the ground.\n\n");
    set_alarm(4.0, 0.0, &third_message(who));

    return;
} /* second_message */


/*
 * Function name:        third_message
 * Description  :        third message for the falling player
 * Arguments    :        object who - the player
 */
public void
third_message(object who)
{
    who->catch_msg("You pass through an opening and have just enough"
      + " time to see a streak of light in the distance before ...\n\n");
    set_alarm(4.0, 0.0, &fourth_message(who));

    return;
} /* third_message */


/*
 * Function name:        fourth_message
 * Description  :        fourth and final message for the falling
 *                       player. here, we move them to the cave
 * Arguments    :        object who - the player
 */
public void
fourth_message(object who)
{
    douse_flames(who);
    who->catch_msg("You strike cold water! Sinking beneath the waves,"
      + " you notice a dim light above and struggle to reach the"
      + " surface.\n\n");
    set_alarm(4.0, 0.0, &surface(who));

    return;
} /* fourth_message */


/*
 * Function name:        surface
 * Description  :        move the player to the new room
 * Arguments    :        object who - the player
 */
public void
surface(object who)
{
    who->move_living("M",
        DELRIMMON_DIR + "lakeside/caves/under_lake");
    return;
} /* surface */


/* 
 * Function name: enter_inv
 * Description:   Called when objects enter this container or when an
 *                object has just changed its weight/volume/light status.
 * Arguments:     ob: The object that just entered this inventory
 *                from: The object from which it came.
 */
public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    set_alarm(2.0, 0.0, &first_message(ob));
    return;
} /* enter_inv */
