/*
 * Farm2b.c   Tomas  -- Jan 2000
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
    set_long("The dirt road continues northeast through the fields of rye " +
      "to the farmhouses which can be seen to the northeast of here. " +
      "To the west is the main entrance to the farm. A small cobblestoned " +
      "path leads to a small fenced area to the southeast.\n");

    add_item(({"gate","fence"}),
      "You can barely make out the fence and gate west of here. There " +
      "is also a small circular fence at the end of the cobbled path " +
      "towards the southwest.\n");

    add_item(({"cobblestone path","path"}),
      "A small cobblestoned path leads to a small fenced area towards " +
      "the southeast.\n");

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

    add_exit(CFARMS + "farm2a","west",0,1);
    add_exit(CFARMS + "farm2c","northeast",0,1);
    add_exit(CFARMS + "farm2g","southeast",0,1);

    add_field_herbs();
    add_pebbles();
}
