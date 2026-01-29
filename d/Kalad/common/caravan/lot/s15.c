#include "../default.h"
inherit CVAN_ROOM;

void
create_cvan_room()
{
    set_hear_bell(1);

    add_prop(ROOM_I_INSIDE, 1);

    set_short("A wagon decorated in military style");
    set_long("You've entered the wagon with the unusual symbol.\n"+
      "Looking around "+
      "at your surroundings you note the militiary style in which this wagon "+
      "was decorated. There is a severe-looking desk opposite you, and a "+
      "small low-backed chair behind it. The rest of the wagon contains a "+
      "few uncomfortable looking chairs and some racks hung upon the wall.\n"+
      "A thin layer of dust covers everything.\n");

    add_item(({ "desk" }),
      "It is small and unaddorned, completely without style or taste, it is "+
      "merely functional.\n");

    add_item(({ "chair", "chairs" }),
      "The chair behind the desk and the ones around the wagon all look "+
      "the same, small and uncomfortable, yet functional.\n");

    add_item(({ "dust" }), "A fine coating that covers everything in this "+
      "wagon.\n");

    set_noshow_obvious(1);

    add_exit(CVAN + "lot/s12", "north");
}
