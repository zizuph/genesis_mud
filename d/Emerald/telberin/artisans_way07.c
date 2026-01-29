#include "defs.h"

inherit TELBERIN_ARTISANS_WAY;

public void
create_artisans_way()
{
    set_em_long("Artisans Way joins with the Royal Circle just to"
      + " the northeast. Westward, it curves in a gentle arc through"
      + " the Mercantile Quarter of Telberin, passing numerous"
      + " business offices, shops, and outdoor markets along its southern"
      + " edge. North, a sprawling green extends the entire length of"
      + " the quarter. Standing tall and proud over the street to the"
      + " south, a broad, green-roofed building looks onto the"
      + " street, an oval plaque mounted near its entrance.\n");

    add_item( ({ "green", "sprawling green" }),
        "The grass of the lawn is exquisitely green, adding a fresh"
      + " color for backdrop behind the business of the quarter.\n");
    add_item( ({ "building", "broad building",
                 "green-roofed building",
                 "broad, green-roofed building",
                 "store", "general store", "general store of telberin",
                 "shop", "south" }),
        "To the south, a broad, green-roofed building looks onto the"
      + " street. It has a very practical look, with little time spent"
      + " on finer details. A wide oval plaque rests above its"
      + " entrance.\n");
    add_item( ({ "plaque", "oval plaque", "sign", "wide plaque",
                 "wide oval plaque" }),
        "The plaque reads: 'The General Store of Telberin.'"
      + " The plain letters have been carved into a wide oval surface"
      + " which appears to be made of some kind of white material.\n");
    add_item( ({ "entrance", "door", "doors", "doorway" }),
        "The doors to the south are made of a oak. They are wide and"
      + " appear to be able to accomodate large items coming in and"
      + " out of the store.\n");
    add_item( ({ "office", "offices", "business", "businesses",
                 "business office", "business offices", "buildings" }),
        "Many of the buildings in this quarter have the look of"
      + " some form of business or another. You see suppliers travelling"
      + " to and fro, coming and going in their various deliveries to"
      + " the various establishments.\n");
    add_item( ({ "suppliers" }),
        "These people are everywhere, bringing their varied goods and"
      + " services to the businesses of the quarter.\n");
    add_item( ({ "market", "markets", "outdoor market",
                 "outdoor markets" }),
        "A number of merchants have set up outdoor markets to offer"
      + " their goods to the public. Their many colored awnings run"
      + " the length of the boulevard to the east and west.\n");
    add_item( ({ "awning", "awnings", "colored awning",
                 "colored awnings", "merchant", "merchants" }),
        "The awnings of the merchants add a distinct flavor to the"
      + " boulevard, their many colors waving in the occasional"
      + " breeze.\n");

    add_cmd_item( ({ "plaque", "oval plaque", "sign", "fine plaque",
                     "fine oval plaque", "letters", "words" }),
                  ({ "read" }),
        "The plaque reads: 'The General Store of Telberin.'\n");

    add_building("/d/Emerald/telberin/mercantile/general_store");

    add_exit("/d/Emerald/telberin/mercantile/general_store", "south",
        0, 0, 1);
    add_exit("royal_circle01", "northeast");
    add_exit("artisans_way06", "west");
    add_exit("channelers_way01", "southeast");
}
