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
inherit "/d/Terel/std/room_tell.c";

object commander;


init()
{
    ::init();
    start_room_tells();
}

reset_room()
{
    if (!commander) 
    {
        commander=clone_object(MOUNTAIN_DIR + "stronghld/npc/commander");
        commander->move(this_object());
    }
}


public void
create_room()
{
    ::create_room();
    INSIDE;
    set_short("Officers quarters");
    set_long("The officers quarters are basically as spartan " +
       "as the rest of the Stronghold living quarters. Plain " +
       "pieces of furniture can seen such as a round " +
       "table which sits in the middle of the room.\n");

    add_item(("furniture"),"Plain yet functionable furniture " +
       "such as a stool, nightstand and a bed can be seen.\n");

    add_item(({"walls","ceiling","floor"}),
       "The room like the rest of the stronghold was mined out of " +
       "solid rock. The walls are sparten, and bare. The floor " +
       "is kept clean of any debris.\n");

    add_item(({"iron brazier","iron braziers","brazier","braziers"}),
       "Iron pot braziers containing some sort of slow burning " +
       "fuel provide light to the barracks.\n");

    set_tell_time(200 + random(200));
    add_tell("The soft light from the braziers flicker slightly.\n");

    add_exit(MOUNTAIN_DIR + "stronghld/fortk","west",0,1);



    reset_room();

}


