/* This comment tells emacs to use c++-mode -*- C++ -*- */
// Southern road traversing between southern terel and the 
// Dwarven Stronghold.
// Tomas  -- Jan 2000

#include "/d/Terel/include/Terel.h"
#include <ss_types.h>
#include <cmdparse.h>
#include <composite.h>
#include <macros.h>

inherit STDROOM;
inherit "/d/Terel/std/room_tell.c";
inherit "/d/Terel/mountains/sforest/include/cold_fatigue.c";

#include <stdproperties.h>

#define DEFAULT    MOUNTAIN_DIR + "sforest/road/"

object pebble;

init()
{
    ::init();
    add_action("do_smell",  "smell",  0);
    start_room_tells();
}


public string
smell_desc()
{
    return "The air smells of fresh evergreens.\n";
}


/*
 * Function name: do_smell
 * Description:   Handle the smell action
 * Returns:       1/0
 */ 
public int
do_smell(string str)
{
    NF("Smell what?\n");
    if (!strlen(str))
        return 0;
    
    if (str == "air" || str == "scent" || str == "strange scent") {
        write(smell_desc());
        return 1;
    }
    return 0;
}


public void
create_room()
{
    ::create_room();
    set_short("Snow covered road");
    set_long("You are travelling upon a snow covered road " +
       "leading through the forest. Dense trees are on either " +
       "side of the road. ");

    add_item(({"snow covered road","snowy road","road"}),
       "The snow covered road leads north and southward "+
       "through a densely populated forest, which grows " +
       "on either side of the road.\n");

    add_item(({"forest","trees","undergrowth", "bushes",
               "shrubs","plants","evergreens","floor",
               "ground","shrub","plant","evergreen",
               "bush"}),
       "The evergreens loom high overhead creating a " +
       "semi-shaped canopy over the road. Dense undergrowth " +
       "covers the forest floor on either sides of the road.\n");


    set_tell_time(300 + random(200));
    add_tell("You hear birds chirping off in the distance.\n");

    add_cmd_item(({"rocks","rock","pebble","pebbles"}),
                 ({"collect","gather","get"}),"@@get_pebble");
    
  
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

