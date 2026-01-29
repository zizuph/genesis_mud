#include "defs.h"
inherit STD_ROOM;

mapping xGrid = ([
    "dock4": -3,
    "dock3": -2,
    "dock2": -1,
]);



void
create_room()
{
    ::create_room();
    set_short("Dreary docks");
    add_item(({"docks", "pier"}),
      "The pier is made of old, cracked wood. It squeaks under the slightest " +
      "movement.\n");
    add_item(({"forest"}), "It is dark, if not gloomy.\n");
    add_item(({"sea"}),
      "The sea stretches far in all westerly directions, the wind gently " +
      "rolling the waves.\n");
    add_item(({"waves"}),
      "They gently lap against the pier, a comfort against the otherwise " +
      "eerie silence.\n");
    add_item(({"shore", "beach"}),
      "A rocky beach lies between you and the foreboding forest.\n");
    add_item(({"planks"}),
      "They look like they could shatter under a heavy step.\n");
    add_item(({"piling", "pilings"}),
      "The pilings hold the dock above the sea. They look to be the " +
      "sturdiest part of the pier, but are old and grey like the rest of " +
      "it.\n");
    add_item(({"coast"}),
      "The coast stretches far to the north and south before bending out of " +
      "sight.\n");
    add_item("land",
      "Land lies east, first to a cold-looking beach and then a " +
      "dreadful-looking forest, lined north and south by a rocky coast.\n");
}

int *
query_coordinates()
{
    string room = extract(MASTER_OB(TO), strlen(BEACH_DIR));
    return ({xGrid[room], 0, 0});
}
