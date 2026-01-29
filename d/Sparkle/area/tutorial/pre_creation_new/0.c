/*
 *  /d/Sparkle/area/tutorial/pre_creation_new/0.c
 *
 *  This is the room players go immediately following login the first time
 *  they play the game. It transports them to an instance of the pre-
 *  creation sequence.
 *
 *  Created May 2011, by Cooper Sherry (Gorboth)
 */
#pragma strict_types
#include "../defs.h"

inherit "/std/room";
inherit LIB_DIR + "skip";

#include <macros.h>
#include <stdproperties.h>

/* prototypes */
public void        create_room();
public void        transfer(object who);
public void        enter_inv(object ob, object from);


/*
 * Function name:        create_room
 * Description  :        set up the room
 */
public void
create_room()
{
    set_name("0");
    set_short("energy flashes briefly! ... and then ..");
    set_long(capitalize(short()) + ".\n");

    add_prop(ROOM_M_NO_TELEPORT,
        "A strange force prevents your travel.\n");
    add_prop(ROOM_I_INSIDE, 1);

    setuid();
    seteuid(getuid());
} /* create_room */


/*
 * Function name:        transfer
 * Description  :        move the player to the new room
 * Arguments    :        object who - the player
 */
public void
transfer(object who)
{
    object room = clone_object(
        "/d/Sparkle/area/tutorial/pre_creation_new/1");

    log_move("1");
    who->move_living("M", room);

    return;
} /* transfer */


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

    set_alarm(0.0, 0.0, &transfer(ob));
    return;
} /* enter_inv */
