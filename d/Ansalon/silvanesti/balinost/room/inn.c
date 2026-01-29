
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
    set_short("The Sweet Dreams Inn");
    set_long("The Sweet Dreams Inn is also seeing rather good "+
      "business despite the hard times the city of Balinost faces.  "+
      "The reason for this is people have come from throughout "+
      "Silvanesti to Balinost to leave for Southern Ergoth.  Since "+
      "the boat to Ergoth takes a few months to arrive, people from "+
      "out of the city need to stay at the Inn until the next ship "+
      "arrives.\nThis is a rather extravagant inn, having all the "+
      "trappings of a high class owner.  Paintings and tapestries "+
      "line the walls, although not for much longer since even "+
      "the inn must shut down eventually.  A small fire burns in "+
      "the lobby's fireplace.  A sign hangs behind the counter "+
      "giving the price of a room for the night.\n");

    add_exit(BROOM + "street08","west",0);
}
