/* This comment tells emacs to use c++-mode -*- C++ -*- */

/*
 * Riders of Last Ranch
 * road01.c
 *
 * April 2000 -- Tomas
 */

#include "/d/Terel/include/Terel.h"
#include <ss_types.h>
#include <cmdparse.h>
#include <composite.h>

inherit STDROOM;

object gate;
object pebble;

#include <stdproperties.h>


public void
create_room()
{
    ::create_room();
    set_short("Rider ranch road");
    set_long(".\n");

    add_item(({"gate","fence"}),
        "Standard split-rail designed fence separates the rest of the " +
        "world from the ranch. The gate seems to be the only proper way " +
        "through.\n");

    add_item(({"track"}), "It's a small track, but it appears to be used " +
        "every now and then.\n");

    add_item(({"farm"}), "The farm consists of three separate " +
        "houses, placed around a farmyard.\n");

    add_item(({"field", "fields"}), "The fields are now covered" +
        " with snow, but still, some kind of rye grow there.\n");

    add_item(({"snow"}), "It's pure snow.\n");

    add_item(({"rye"}), "This kind of rye must be quite tough " +
        "since it endures this harsh climate.\n");

    add_item(({"farmhouses","farmhouse","houses","house"}),
       "Three small houses can be seen beyond the snow covered fields to the " +
       "northeast.\n");

    add_cmd_item(({"rocks","rock","pebble","pebbles"}),
                 ({"collect","gather","get"}),"@@get_pebble");
    
     add_exit(DEFAULT + "road02","west",0,1);
    
     gate = clone_object(DEFAULT + "obj/road01_gate1");
     gate->move(TO);

     reset_room();

}


get_pebble()
{
    object pebble;

    seteuid(getuid(TO));
    pebble = clone_object(CALATHIN_DIR + "houses/obj/pebble");
    pebble->move(TP);
    write("You pickup a pebble from the ground.\n");
       say(QCTNAME(TP) + " reaches down and picks up a pebble.\n");
    return 1;
}


