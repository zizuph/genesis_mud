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
    set_short("Stronghold barracks");
    set_long("The large room is home to several small sized " +
       "yet sturdy wooden pallets which line up against either " +
       "side of the walls. At the foot of the beds are long " +
       "wooden benches and stools aligned lengthwise " +
       "in the middle of the room. The room is lit by " +
       "iron braziers suspended from the ceiling by chains. ");

    add_item(({"walls","ceiling","floor"}),
       "The room like the rest of the stronghold was mined out of " +
       "solid rock. The walls are sparten, and bare. The floor " +
       "is kept clean of any debris.\n");

    add_item(({"pallet","pallets","wooden pallets","bed","beds"}),
       "The small wooden pallets are of a practical design. " +
       "Furs and warm woolen blankets cover the straw filled " +
       "mattresses.\n");

    add_item(({"benches","bench","stool","stools","chairs","table",
               "tables"}),
               "The benches and stools are made of sturdy " +
               "oak wood. The design is functionable yet plain by " +
               "design much like you would find in any military " +
               "installation.\n");

    add_item(({"iron brazier","iron braziers","brazier","braziers"}),
       "Iron pot braziers containing some sort of slow burning " +
       "fuel provide light to the barracks.\n");

    set_tell_time(200 + random(200));
    add_tell("The soft light from the braziers flicker slightly.\n");

    reset_room();

}


