#include "defs.h"
inherit STD_ROOM;

void
create_room()
{
    add_prop(ROOM_I_INSIDE, 1);
    ::create_room();
    set_short("At the entrance of a dark cave");
    set_long(
      "You are at the entrance to what appears to be a dark cave. A pile of " +
      "huge, weed-covered rocks sits on the ground before you, at the center " +
      "of which yawns a large, eerie black hole. The area around you is flat " +
      "and endless, spotted with other piles of rocks and hills.\n");
    add_item(({"pile", "rocks"}),
      "A large pile of weed-covered rocks that is about as high as you are, " +
      "in the center of which yawns a large, eerie black hole.\n");
    add_item("hole",
      "The black hole is just the right size for you to squeeze in, if you " +
      "dare.\n");
    add_item("plains", "The plains stretch around you for miles on end.\n");
    add_item(
      "hills", "The hills around you roll as far as the eye can see.\n");
    add_cmd_item(({"cave","hole"}), "enter", "@@do_enter@@");
    add_exit(PLAINS_DIR + "beastruin1", "south", 0, 1);
}

string
do_enter()
{
    TP->move_living("in", MAZE_DIR + "maze01");
    return "";
}

int *
query_coordinates()
{
    return ({52, 0, 0});
}
