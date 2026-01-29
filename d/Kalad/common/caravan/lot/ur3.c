#include "../default.h"
inherit CVAN_ROOM;

void
create_cvan_room()
{
    add_prop(ROOM_I_INSIDE, 1);

    add_prop(ROOM_I_LIGHT, 0);

    add_prop(ROOM_S_DARK_LONG, "A dark place.\n");

    set_short("An underground passage");
    set_long("You are travelling down a dark passage.\n"+
      "You can barely see inside this dark passageway. From what little "+
      "light there is you can see, and smell several reeking piles of filth scattered "+
      "across the ground. The walls and ceiling, which are made entirely "+
      "of mud, are crawling with dozens of bugs. Dark passages lead away "+
      "towards the north and south.\n");

    add_item(({ "filth" }),
      "It is so disgusting that it cannot be adequately described. It lies "+
      "in stinking piles all over the floor, forcing you to watch your step, "+
      "lest you fall into one.\n");

    add_item(({ "walls", "ceiling", "wall" }),
      "This entire passage is made solely of mud. It surprises you that the "+
      "passage has not collapsed, since there are no supports visible "+
      "anywhere. Dozens of disgusting bugs are crawling all over the "+
      "passageway.\n");

    add_item(({ "bugs" }),
      "Filthy creatures! Covering the passage walls, and even ceiling are "+
      "dozens of cockroaches, centipedes and other crawling nasties.\n");

    set_noshow_obvious(1);

    add_exit(CVAN + "lot/ur2", "north");
    add_exit(CVAN + "lot/ur4", "south");
}
