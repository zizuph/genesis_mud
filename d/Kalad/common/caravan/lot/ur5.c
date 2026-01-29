#include "../default.h"
inherit CVAN_ROOM;

void
create_cvan_room()
{
    add_prop(ROOM_I_INSIDE, 1);

    add_prop(ROOM_I_LIGHT, 0);

    add_prop(ROOM_S_DARK_LONG, "A dark area.\n");

    set_short("A bend in the underground passageway");
    set_long("You've reached a bend in the passageway.\n"+
      "You can barely see inside this dark and dismal passage. "+
      "From what little light there is you can see reeking piles of filth "+
      "scattered across the ground. The walls and ceiling, which are just "+
      "plain mud, are crawling with dozens of disgusting bugs. Dark "+
      "passages lead away to the north and northeast.\n");

    add_item(({ "filth" }),
      "It is so disgusting that it cannot be adequately described. It lies "+
      "in stinking piles all over the floor.\n");

    add_item(({ "walls", "ceiling", "wall" }),
      "The passage is entirely made up of mud. It surprises you that this "+
      "passageway has not collapsed, since no supports are visible. Upon "+
      "the walls and ceiling are dozens of disgusting bugs.\n");

    add_item(({ "bugs" }),
      "Filthy creatures! Many cockroaches, centipedes and other crawling "+
      "horrors can be seen wandering the entire passageway.\n");

    set_noshow_obvious(1);

    add_exit(CVAN + "lot/ur4", "north");
    add_exit(CVAN + "lot/ur6", "northeast");
}
