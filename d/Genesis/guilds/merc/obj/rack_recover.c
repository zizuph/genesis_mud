/*
 *  /d/Genesis/guilds/merc/obj/rack_reocver.c
 *
 *  Special object that is used during recovery. It will recover the
 *  real equipment and put the armoury stamp on it.
 *
 *  Created by Eowul, 20-9-2003
 */

#include "../merc.h"

inherit "/std/object";

// Variables
object  equipment;

/*
 * Function name: create_object
 * Description  : Constructor
 */
void create_object()
{
    set_short("mercenary equipment");
}

/*
 * Function name: init_arg
 * Description  : Called during the recovery, will create the real piece
 *                of equipment and put the armoury mark on it.
 */
void init_recover(string arg)
{
    object  shadow;
    string  filename, args;

    // See if we have an argument
    if(!strlen(arg))
        return;

    // Split the argument
    sscanf(arg, "%s:%s", filename, args);

    // See if we have a filename
    if(!strlen(filename))
        return;

    // Set permissions
    seteuid(getuid());

    // Create the equipment
    equipment = clone_object(filename);
    equipment->init_recover(args);

    // Clone the shadow with the mark
    shadow = clone_object(MOBJ + "rack_shadow");

    // Shadow the equipment
    shadow->shadow_me(equipment);

    // Set our own short description
    set_short(equipment->query_short());
}

/*
 * Function name: enter_env
 * Description  : Enter our environment, move the real EQ there
 */
void enter_env(object to, object from)
{
    // Move first
    ::enter_env(to, from);

    // Check if we need to move the equipment
    if(objectp(to) && objectp(equipment))
    {
        equipment->move(to, 1);
    }

    // Remove outselves
    set_alarm(1.0, 0.0, remove_object);
}
