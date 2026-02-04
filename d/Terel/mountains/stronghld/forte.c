/* This comment tells emacs to use c++-mode -*- C++ -*- */

/*
 *
 * Dwarven Stronghold
 * Tomas  -- Jan. 2000
 */

#include "/d/Terel/include/Terel.h"
#include <ss_types.h>
#include <cmdparse.h>
#include <composite.h>
#include <stdproperties.h>

inherit STDROOM;
inherit MOUNTAIN_DIR + "stronghld/passageway";

public void
create_room()
{
    ::create_room();
    INSIDE;
    set_short("Staircase");
    set_long(query_long() + "A stone staircase leading " +
       "to the level above has been carved from the rock face " +
       "against the far wall. The passageway to the east " +
       "leads back to the gate.\n");

    add_item(({"stairs","staircase"}),"The stone staircase was " +
       "carved from the rock face against the far wall.\n");

    add_exit(MOUNTAIN_DIR + "stronghld/fortb","east",0,1);
    add_exit(MOUNTAIN_DIR + "stronghld/fortf","up",0,1);

    
    reset_room();

}


