/*
 * /d/Gondor/clubs/nisse/obj/stake.c
 *
 * This object is cloned into the room when the Nisse uses emotion
 * niward and has a leftover in her inventory.
 *
 * Deagol, August 2003
 */

#pragma strict_types
#pragma save_binary

inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>
#include <files.h>

#include "/d/Gondor/defs.h"

void
create_object()
{
    ::create_object();
    
    set_name("stake");
    add_name(({"trophy", "blooded"}));
    set_short("blooded trophy stake");
    set_long("You see a stake topped by a grisly trophy torn from the " +
        "kill, dried blood stains the stake.\n");

    add_prop(OBJ_M_NO_GET, "You cannot get the " + short() + " since it " +
        "has been thrusted into the ground.\n");
}

/*
 * Function name: decay
 * Description  : Removes this object from the room with a message.
 */
void
decay()
{
    tell_room(ENV(TO), "The " + query_short() + " decays and it " +
        "falls over blending into the other sticks and branches around.\n");
    remove_object();
}
