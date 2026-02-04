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
    set_long("The catwalk runs along atop the southern wall continuing " +
       "east and west. From here you have an excellent view of the " +
       "fields within the stronghold.\n");

    add_exit(MOUNTAIN_DIR + "stronghld/walk4","west",0,1);
    add_exit(MOUNTAIN_DIR + "stronghld/walk7","east",0,1);

    reset_room();

}


