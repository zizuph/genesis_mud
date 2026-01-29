#include "defs.h"

inherit TELBERIN_ARTISANS_WAY;

public void
create_artisans_way()
{
    set_em_long("The long arc of Artisans Way, extending out from the " +
        "city center to the east, turns in more strongly here, leading " +
        "north past the west gate of Telberin and making a wide loop, " +
        "turning back in toward the Royal Circle.  A long pool extends " +
        "down the center of the elliptical boulevard, its glimmering, " +
        "crystal-blue water draws the eye down its length and east, " +
        "toward the grand royal palace. Bounding the outer side of the " +
        "roadway, the shops and offices of the mercantile quarter create " +
        "a labyrinth of passages and alleyways which wind through the " +
        "quarter. Just to the south, a large building looms above those"
      + " around it. A fine oval plaque rests above its entrance.\n");

    add_item( ({ "shop", "shops", "office", "offices",
                 "shops and offices" }),
        "The Mercantile Quarter is characterized by its numerous"
      + " offices and shops which are crammed so thickly together"
      + " in some places as to almost appear comical.\n");
    add_item( ({ "labyrinth", "passages", "passage", "alley",
                 "alleys", "alleyway", "alleyways",
                 "passages and alleyways",
                 "labyrinth of passages",
                 "labyrinth of passages and alleyways" }),
        "One could easily get lost off of the main road. The number"
      + " of passages and alleyways is quite a sight to behold.\n");
    add_item( ({ "building", "bank", "large building",
                 "bank of telberin" }),
        "The large building to the south looks quite formidable. Two"
      + " armed guards stand post at the doorway, surveying the street"
      + " vigilantly.\n");
    add_item( ({ "guard", "guards", "armed guard", "armed guards" }),
        "Guards have been posted to guard the bank ever since the recent"
      + " raids which brought ruin to much of the city.\n");
    add_item( ({ "plaque", "oval plaque", "fine plaque",
                 "fine oval plaque" }),
        "The plaque is made of some kind of white stone or ceramic,"
      + " and has been painted with elegant black letters. The letters"
      + " read: 'The Bank of Telberin.'\n");

    add_cmd_item( ({ "plaque", "oval plaque", "fine plaque",
                     "fine oval plaque", "letters", "words" }),
                  ({ "read" }),
        "The plaque reads: 'The Bank of Telberin.'\n");

    add_exit("artisans_way06", "east");
    add_exit("artisans_plaza", "northwest");
    add_exit("/d/Emerald/telberin/mercantile/bank", "south", 0, 1, 1);

    add_building("mercantile/bank");
}
