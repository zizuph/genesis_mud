#include "../default.h"
inherit CVAN_ROOM;

void
create_cvan_room()
{
    set_hear_bell(1);

    add_prop(ROOM_I_INSIDE, 1);

    set_short("Underground room");
    set_long("This room seems to have been artificially created, since "+
      "the walls are too smooth to have been carved by nature. The room is "+
      "bare of any items save for a few pieces of trash here and there.\n");

    add_item(({ "walls" }),
      "The walls are rough by normal standards but are too fine to have been "+
      "carved by natural forces. They are all at a ninety degree angle to "+
      "one another, giving the room a square shape.\n");

    add_item(({ "trash" }),
      "You see a few bits of wood and some scrap metal, but nothing of real "+
      "value to you.\n");

    add_item(({ "scrap metal" }),
      "One piece in particular catches your attention. In the far corner a "+
      "piece of scrap metal covers what appears to be a small hole.\n");

    add_item(({ "small hole" }),
      "It is dark, cramped and filthy. If you wished, you could probably "+
      "crawl your way inside.\n");

    set_noshow_obvious(1);

    add_exit(CVAN + "slave/s4a", "up");
    add_exit(CVAN + "sewers/arslave", "hole", "@@block@@");
}

int
block()
{
    write("The way is not open yet.\n");
    return 1;
}
