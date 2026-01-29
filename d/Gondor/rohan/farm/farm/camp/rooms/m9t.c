/*
 * Dunlending Camp Tent Room
 *
 * --Raymundo, March 2020
 */

#pragma strict_types

inherit "/d/Gondor/rohan/farm/farm/camp/lib/base_room";
inherit "/d/Gondor/rohan/farm/farm/camp/lib/base_include_objects";

#include <macros.h>
#include "/d/Gondor/defs.h"
#include "defs.h"

#define OUT "m9"
object crate;
object here;

void
create_dunlending()
{
    set_short(tent_short());
    set_long(tent_long());

    here = this_object();

    add_tent();
    add_guard_down();
 
    object crate = clone_object(CAMP_OBJ_DIR + "tent_crate");
    crate->move(TO);
    add_exit(CAMP_ROOM_DIR + OUT, "out");
}

void
reset_room()
{
    
  if(!present("dunlending", here))
    {
        add_guard_down();
    }
 
}



