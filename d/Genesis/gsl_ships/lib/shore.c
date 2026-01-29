/*
 * Standard shore - library form
 * TAPAKAH, 2008
 */

#include "../ships.h"

public void
initialize_shore()
{
    this_object()->add_prop(ROOM_I_IS_SHORE, 1);
    this_object()->add_prop(ROOM_I_DIVING_DIFFICULTY, 0);
}