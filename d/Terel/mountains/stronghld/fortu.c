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
    set_short("Passageway");
    set_long(query_long() + "To the north and west are some barracks. " +
       "The passageway continues west and east.\n");


    add_exit(MOUNTAIN_DIR + "stronghld/forts","east",0,1);
    add_exit(MOUNTAIN_DIR + "stronghld/fortt","north",0,1);
    add_exit(MOUNTAIN_DIR + "stronghld/fortv","west",0,1);

    reset_room();

}


