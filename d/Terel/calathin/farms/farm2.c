/*
 * farm2.c
 *
 * Calathin external house.
 * 11/21/1999 -- Tomas
 *
 * Lucius - Feb 2021
 *    Cleaned and modernized.
 */
#include "farm.h"
inherit FARMRM;

public void
create_terel_room()
{
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

    add_exit(CFARMS + "farm2a","east",0,1);

    room_add_object(CFARMS + "obj/farm2_gate1");

    add_field_herbs();
    add_pebbles();
}
