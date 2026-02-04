/*
 * Farm2g.c   Tomas  -- Jan 2000
 *
 * Lucius - Feb 2021
 *    Cleaned and modernized.
 */
#include "farm.h"
inherit FARMRM;
inherit (STD_DIR + "room_tell");

public void
create_terel_room()
{
    set_short("cobblestone path");
    set_long("The small cobblestoned path leads to a fenced chicken coop. " +
      "A small mesh gate stands before you. To the northwest is the " +
      "cobblestoned path leading back to the farm road.\n");

    add_item(({"gate","fence","coop"}),
      "The coop is made from wire woven together to create a strong " +
      "barrier keeping unfriendly animals out and the chickens in. " +
      "There is a small meshed gate before you.\n");

    add_item(({"cobblestone path","path"}),
      "A small cobblestoned path ends before a chicken coop. The farm " +
      "road is back towards the northwest.\n");

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

    set_tell_time(100 + random(200));
    add_tell("You hear scratching from inside the coop.\n");
    add_tell("Cluck! Cluck! Cluck!.\n");

    add_exit(CFARMS + "farm2b","northwest",0,1);

    room_add_object(CFARMS + "obj/farm2g_gate");

    add_pebbles();
}

public void
init()
{
    ::init();
    start_room_tells();
}
