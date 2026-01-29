
#include "/d/Ansalon/common/defs.h"
#include <stdproperties.h>
#include "/d/Ansalon/silvanesti/balinost/local.h"
#include <macros.h>

inherit BALINOST_IN;

reset_balinost_room()
{
    return;
}


create_balinost_room()
{
    set_short("Singing Blade Arms");
    set_long("This building was the site of the Singing Blade Arms "+
      "shop.  One of the first businesses to close in the city, the "+
      "store is covered with a thin layer of dust.  Empty racks fill "+
      "the room making it look like it has been deserted for years "+
      "when it really has only been a few months.  The door to the "+
      "storeroom is closed and appears locked.\n");

    add_exit(BROOM + "street16","east",0);
}
