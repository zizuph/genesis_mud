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
    set_long(query_long() + "To the south is the pub. " +
       "some sort of office can be seen to the north. " +
       "The passageway continues west and east.\n");


    add_exit(MOUNTAIN_DIR + "stronghld/fortk","north",0,1);
    add_exit(MOUNTAIN_DIR + "stronghld/fortf","west",0,1);
    add_exit(MOUNTAIN_DIR + "stronghld/forti","south",0,1);
    add_exit(MOUNTAIN_DIR + "stronghld/fortm","east",0,1);

    reset_room();

}


