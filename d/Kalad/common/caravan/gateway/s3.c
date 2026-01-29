#include "../default.h"
inherit CVAN_ROOM;

void
create_cvan_room()
{
    set_short("Gateway lane");
    set_long("This is Gateway Lane in northeastern Kabal, to the north "+
      "you can clearly see the massive city walls of Kabal, in the south "+
      "there can be seen several tightly packed buildings. There is animal "+
      "refuse lying here.\n");

    add_item( ({ "wall", "walls", "city walls" }),
      "These walls encircle the huge city of Kabal protecting it from a "+
      "myriad of threats. To properly protect the city the walls have been "+
      "constructed of the finest stone and built to a height of thirty "+
      "feet.\n");

    add_item( ({ "building", "buildings" }),
      "The buildings to the south are in a variety of shapes and sizes, "+
      "some of them are homes, while others are businesses.\n");

    add_item( ({ "refuse" }),
      "These are the decaying remains of dung left behind by the many "+
      "animals brought by merchants to the city.\n");

    add_exit(CVAN + "alley_gate", "west");
    add_exit(CVAN + "gateway/s4", "east");
}
