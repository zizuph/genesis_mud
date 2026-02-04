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

init()
{
    ::init();
    start_room_tells();
}


public void
create_room()
{
    ::create_room();
    INSIDE;
    set_short("Stronghold passageway");
    set_long("The long passageway was carved into the " +
       "solid rock walls. Its archway design supported by " +
       "thick oak timbers looks quite sturdy. ");

    add_item(({"archway","passageway","walls","wall"}),
       "The passageway was carved into the solid rock walls. " +
       "Lit iron braziers hang from the supports providing light.\n");

    add_item(({"timbers","supports","oak timbers","timber"}),
       "The thick oak timbers add support to the ceiling " +
       "and walls of the passageway.\n");

    add_item(({"iron brazier","iron braziers","brazier","braziers"}),
       "Iron pot braziers containing some sort of slow burning " +
       "fuel provide light to the dim passageways.\n");

    add_item(({"floor","ceiling"}),"Carved from solid rock.\n");


    set_tell_time(200 + random(200));
    add_tell("The soft light from the braziers flicker slightly.\n");

    reset_room();

}


