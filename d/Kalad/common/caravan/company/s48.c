#include "../default.h"
inherit CVAN_ROOM;

void
create_cvan_room()
{
    set_hear_bell(1);

    add_prop(ROOM_I_INSIDE, 1);

    set_short("The Library");
    set_long("This enormous room is filled with dozens, if not hundreds "+
      "of books. Little can be seen of the walls because huge bookshelves "+
      "filled to the brim with books, are lined all along them. A luxuriant "+
      "rug blankets the marble floor. Strategically placed candles provide "+
      "comfortable illumination for this huge area. The rest of the "+
      "library can be seen to the south.\n");

    add_item(({ "books" }), "A myriad amount and variety of books are placed "+
      "inside the bookshelves, some of which are so exotic in nature that "+
      "little can be deciphered of them. Most of the books however seem to "+
      "describe Kabal and the surrounding area.\n");

    add_item(({ "bookshelves" }), "Massive wooden shelves that line all the "+
      "walls within this room.\n");

    add_item(({ "rug" }), "An exotic-looking rug that is decorated with "+
      "a myriad number of images, many of which are unfamiliar to you.\n");

    add_item(({ "floor" }), "Brilliantly white marble tiles that have been "+
      "so thoroughly polished, your reflection is clearly visible.\n");

    add_item(({ "candles" }), "Delicate and tapered wax candles. Many have "+
      "been placed all over the room to help provide adequate light for "+
      "reading.\n");

    add_exit(CVAN + "company/s49", "south");

    clone_object(CVAN + "door/tcdoor3")->move(TO);
}
