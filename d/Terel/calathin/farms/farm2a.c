/*
 * farm2a.c
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
    set_short("Farm road");
    set_long("The dirt road continues east through the fields of rye " +
      "to the farmhouses which can be seen to the northeast of here. " +
      "The main gate leading back to the main road is to the west. " +
      "A metal and wooden grate spans across the road here.\n");

    add_item(({"metal grate","grate"}),
      "The metal grate makes an effective barrier to keep the hooved livestock " +
      "from going further west. Its possible to step on or over the " +
      "grate providing you dont have small hooves for feet.\n");

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

    add_exit(CFARMS + "farm2","west", "@@livestock");
    add_exit(CFARMS + "farm2b","east",0,1);

    add_field_herbs();
    add_pebbles();
}

public int
livestock()
{
    return TP->id("livestock");
}
