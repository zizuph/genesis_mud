#include "defs.h"
inherit DOCK_ROOM;

void
create_room()
{
    ::create_room();
    set_long(
      "You are on a stretch of dreary docks that extend from the shore just " +
      "to the east and stretch a ways west. Beyond the rocky coast, a large " +
      "forest consumes the land. The planks here groan under your weight.\n");
    /* We should do something with this
    add_item(({"plank", "planks"}),
      "They look rather old and one seems to have given way exposing an " +
      "opening below.\n");
    */
    add_exit(BEACH_DIR + "dock3", "west");
    add_exit(BEACH_DIR + "beach1", "east");
    // add_exit(BEACH_DIR + "beach1","east", "@@block@@");
    // clone_object("/d/Raumdor/common/obj/garg_statue")->move(this_object(),
    // 1);
}

int
block()
{
    write(
      "Raumdor is currently under mainentance. Please come back later.\n");
    return 1;
}
