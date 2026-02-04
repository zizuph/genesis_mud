/* This comment tells emacs to use c++-mode -*- C++ -*- */

/*
 * farm1.c
 *
 * Calathin external house.
 * 11/21/1999 -- Tomas
 */

#include "/d/Terel/include/Terel.h"
#include <ss_types.h>
#include <cmdparse.h>
#include <composite.h>
#include "/d/Terel/include/herb_arrs.h"


inherit STDROOM;
inherit "/d/Terel/std/herbsearch.c";

#define  ONE_OF_LIST(array) ((array)[random(sizeof(array))])

object gate;
object pebble;

#include <stdproperties.h>


public void
create_room()
{
    ::create_room();
    set_short("Farm entrance");
    set_long("You stand before a large farm style gate. Large fields " +
       "can be seen to the north and south. The road leads east to the " +
       "farmhouses and west through the gate back towards town.\n");

    add_item(({"gate","fence"}),
        "Standard split-rail designed fence separates the rest of the " +
        "world from the farm. The gate seems to be the only proper way " +
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

    set_up_herbs( ({ ONE_OF_LIST(ANY_HERBS),
                     ONE_OF_LIST(ANY_HERBS),
                     ONE_OF_LIST(ANY_HERBS),
                  }),
                  ({"field","fields"}) , 3 );

    add_cmd_item(({"rocks","rock","pebble","pebbles"}),
                 ({"collect","gather","get"}),"@@get_pebble");
    
     add_exit(CALATHIN_DIR + "farms/farm2a","east",0,1);
    
     gate = clone_object(CALATHIN_DIR + "farms/obj/farm2_gate1");
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


