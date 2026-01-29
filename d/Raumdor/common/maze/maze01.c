#include "defs.h"
inherit MAZE_ROOM;

void
create_room()
{
    ::create_room();
    set_short("Within a dark cave");
    set_long(
      "You are within a dark cave filled with spectral mist that clings to " +
      "the damp, black walls. The cave opens up to a large cavern to the " +
      "north.\n");
    add_item("walls", "The walls are of cold black stone.\n");
    add_exit(MAZE_DIR + "cave_entrance", "out");
    add_exit(MAZE_DIR + "maze03", "north");
}
