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
inherit MOUNTAIN_DIR + "stronghld/catwalk";

public void
create_room()
{
    ::create_room();
    INSIDE;
    set_short("Catwalk");
    set_long(query_long() +"The catwalk runs north and south.\n");

    add_exit(MOUNTAIN_DIR + "stronghld/walk16","north",0,1);
    add_exit(MOUNTAIN_DIR + "stronghld/walk14","south",0,1);


    reset_room();

}


