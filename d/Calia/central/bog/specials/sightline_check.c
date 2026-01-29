// OBJECT:  sightline_check.c

    /* Calia Domain

    HISTORY

    [99-06-02] Created by Uhclem from
    [D:\CALIA\CENTRAL\BOG\SPECIALS\SIGHTLIN.DOC].

    PURPOSE

    This is an invisible object that is cloned into a hill room and registers
    it with the appropriate fortress rooms; that is, rooms that have direct
    'sight lines' to the room that sent this object (and rooms in between).
    The fortress rooms can then observe activity in the registered hill rooms,
    and players in this room can see activity on the fortress wall.  All of the
    functions to produce this effect are in the hill and fortress rooms; this
    object merely shuttles between them to ensure that all the relevant rooms
    are loaded.  */

// INCLUSIONS AND DEFINITIONS

inherit "/std/object";

#include <stdproperties.h>
#include "defs.h"

// OBJECT DEFINITION

void
create_object()

    {

    set_name("checker");
    set_short("calian sightline checker");
    set_long("This object is invisible.\n");

    /*  PROPERTIES  */

    add_prop(OBJ_I_VOLUME, 1);
    add_prop(OBJ_I_WEIGHT, 1);
    add_prop(OBJ_I_INVIS, 100);

    add_prop(OBJ_S_WIZINFO,
        "This object performs important tasks in" +
        " Calia. It does not interact with mortals and" +
        " should never be detected by them.\n");

    }
