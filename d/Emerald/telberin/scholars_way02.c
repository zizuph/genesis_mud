#include "defs.h"

inherit TELBERIN_SCHOLARS_WAY;

public void
create_scholars_way()
{
    set_em_long("Scholars Way is at is easternmost arc here, curving"
    + " north and south in a narrow ellipse around the reflecting pool"
    + " to the west. Various buildings line the eastern side of the street,"
    + " most of them offering no clear idea of their function. One"
    + " building, directly to the east, has a different look from the"
    + " others. A sign hangs above its door.\n");

    add_item( ({ "building", "rounded building", "strange building",
                 "strange rounded building", "strange, rounded building",
                 "east", "apothecarium" }),
        "Just to the east, a strange, rounded building stands out from"
      + " the others beside it. A sign has been placed above its"
      + " entrance.\n");
    add_item( ({ "entrance", "door", "wooden door", "wood door",
                 "tall door", "tall wooden door" }),
        "A tall wooden door leads into the building. It has strange"
      + " symbols carved into its surface.\n");
    add_item( ({ "symbol", "symbols", "strange symbol",
                 "strange symbols" }),
        "Strange symbols are carved into the wood of the door which"
      + " leads into the building to the east. You have no idea what"
      + " they represent.\n");
    add_item( ({ "sign", "alabaster sign", "white sign" }),
        "The sign above the building to the east has been fashioned from"
      + " alabaster, or some similar white material. Large letters on it"
      + " read, 'Apothecarium.'\n");

    add_cmd_item( ({ "sign", "letters", "large letters", "alabaster sign",
                     "white sign" }),
                  ({ "read" }),
        "The sign reads: Apothecarium.\n");

    add_building("/d/Emerald/telberin/science/apothecarium");

    add_exit("/d/Emerald/telberin/science/apothecarium", "east", 0, 1, 1);
    add_exit("scholars_way03", "north");
    add_exit("scholars_way01", "south");
}
