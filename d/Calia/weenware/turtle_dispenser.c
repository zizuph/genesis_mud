// OBJECT:  turtle dispenser

    /* Calia Domain

    HISTORY

    [2002-10-31] Created by Uhclem from [C:\CALIA\WEENWARE\TURTLE_D.DOC].

    PURPOSE

    This invisible object is deployed in some beach rooms at Halloween to
    provide a steady supply of turtles.  Before the internet, where could I
    have written such a sentence and have it make any sense?  */

// INCLUSIONS AND DEFINITIONS

inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>
#include "defs.h"

// GLOBAL VARIABLES

object *Turtles_At_Large = ({});

// FUNCTIONS

// Function:  deploy_turtle()

/*

Purpose:  deploy a turtle in the room containing this object; called by
repeating alarm.

Arguments:  none.

Returns:  nothing.

*/

void
deploy_turtle()

{

    object room;
    object turtle;

    Turtles_At_Large -= ({0});  /*  remove any null elements  */

    if (sizeof(Turtles_At_Large) < 5)

    {

        room = environment();
        turtle = clone_object(TURTLE);
        turtle->move(room);
        Turtles_At_Large += ({turtle});

        tell_room(room,
            capitalize(LANG_ADDART(turtle->short())) +
            " emerges from the sea.\n");

    }

    else

    {

        /*
         *  If no new turtle is needed, move one of the existing ones and make 
         *  it disappear if it enters the sea.    
         */

        turtle = Turtles_At_Large[random(sizeof(Turtles_At_Large))];
        room = environment(turtle);

        if (room->query_prop(ROOM_I_IS))

        {

            turtle->command(({"n", "s", "e", "w", "ne", "sw",
                "se", "nw"})[random(8)]);

            room = environment(turtle);

            if (room->query_prop(ROOM_I_TYPE) == ROOM_IN_WATER
                ||
                room->query_prop(ROOM_I_TYPE) == ROOM_UNDER_WATER)

            {

                tell_room(room,
                    "The " + turtle->short() +
                    " disappears into the deep.\n");

                turtle->remove_object();

            }

        }

    }

}

// Function:  enter_env()

/*

Purpose:  called by system when this object moves to a new environment.

Arguments:  object moved to, object moved from.

Returns:  nothing.

*/

void
enter_env(object ob_to, object ob_from)

{

    ::enter_env(ob_to, ob_from);

    set_alarm(0.5, 188.8, deploy_turtle);

}

// Function:  create_object()

void
create_object()

{

    set_no_show();
    set_name("calia_turtle_dispenser");
    set_short("turtle dispenser");

    set_long("This invisible object is deployed at" +
        " Halloween to distribute turtles along the" +
        " beaches of Calia.\n");

    /*
     *  PROPERTIES    
     */

    add_prop(OBJ_I_WEIGHT, 1);
    add_prop(OBJ_I_VOLUME, 1);
    add_prop(OBJ_I_NO_STEAL, 1);
    add_prop(OBJ_I_NO_DROP, 1);
    add_prop(OBJ_I_NO_GET, 1);

    setuid();  /*  "uid" settings required for cloning. */
    seteuid(getuid());

}
