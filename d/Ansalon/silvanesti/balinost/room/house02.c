
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
    set_short("An occupied house");
    set_long("This is a typical house in Balinost.  It was shaped "+
      "from marble and looks nice dispite its sparse furnishings.  "+
      "Boxes lay in stacks in various places around the house.  "+
      "The owners must be preparing to leave the city soon.  It "+
      "doesn't look like it will be too long before this house is "+
      "as empty as the rest.\n");

    add_item(({"box","boxes"}),"The boxes are all around the house. "+
      " They contain the possessions of the people who live here.  "+
      "A few of them are open and empty, this is where the remaining "+
      "objects will be placed.\n");

    add_exit(BROOM + "street19","north",0);
}
