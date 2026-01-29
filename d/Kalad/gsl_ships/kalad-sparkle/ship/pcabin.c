#include <stdproperties.h>
#include "/d/Genesis/gsl_ships/ships.h";
#include "../ship.h"

inherit STDSHIPROOM;

void
create_room()
{
  ::create_shiproom();
    add_prop(ROOM_I_INSIDE,1);
    set_short("Captain's Private Cabin");
    set_long("These are the private chambers belonging to the "+
      "captain of this vessel. It is small and not too surprising "+
      "without elaborate displays. There is a lantern hanging from "+
      "the ceiling and a small cozy looking bed in the corner.\n");
    add_item(({"bed", "small bed", "cozy bed"}),
      "It is a small cozy bed. Not too soft but not too firm either.\n");
    add_item(({"bedding", "sheets", "sheet"}),
      "The bedding is a cream colour, which has seen better days.\n");
    add_item(({"pillow", "pillows"}),
      "There is just one pillow that has been fluffed up nicely.\n");
    add_item(({"iron lantern","lantern"}),"It fills the cabin with a soft "+
      "glowing light.\n");
    add_item(({"ceiling", "floor", "flooring", "wall", "walls"}),
      "It is plain hardwood.\n");
    add_exit(CABIN, "out");
}
