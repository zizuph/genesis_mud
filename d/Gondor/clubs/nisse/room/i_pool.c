/*
 *  /d/Gondor/clubs/nisse/room/i_pool.c
 *
 *  In the ceremony pool of the Nisse Ohtar. This room cannot be entered.
 *  The applicant is moved here when she throws a stone into the pool and
 *  all the test pass.
 *
 *  Deagol, March 2003
 */

#pragma save_binary
#pragma strict_types

inherit "/d/Gondor/std/room";

#include <stdproperties.h>
#include <macros.h>

#include "/d/Gondor/defs.h"
#include "../nisse_defs.h"

void
create_gondor()
{
    ::create_gondor();
    
    set_short("In the pool");
    set_long("In the ceremony pool.\n");
    
    add_prop(ROOM_I_INSIDE,1);
}
