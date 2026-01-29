/* SARR */
#include "defs.h"
#define OTHER_ROOM MTRAIL_DIR + "true_room"
inherit SECRET_ROOM;

void
create_room()
{
    ::create_room();
    set_long("You are now in a small tunnel. It leads to the "+
    "east, where you can see some light. The tunnel runs straight " +
    "into the wall to your west.\n");
    add_item(({"wall", "west wall"}), "The edges of the wall are beveled. " +
      "At both the top and bottom, this reveals what looks like a shaft. " +
      "Perhaps the wall would rotate if you pushed it?\n");
    add_cmd_item(({"wall", "west wall"}), "push", "@@push_wall");
    add_exit(OTHER_ROOM,"west","@@exit_wall",1,1);
    add_exit(MTRAIL_DIR + "secret5","east",0);
}

void
wall_messages()
{
    object room = find_object(OTHER_ROOM);
    if (room)
    {
        TELL_CAN_SEE(room, "The east wall sudden swings around!\n");
        TELL_CANNOT_SEE(room,
          "You hear the grating noise of stone scraping stone.\n");
    }
    TELL(TP, "You push the wall and it swings around!\n");
    TELL_CAN_SEE_OTHER(TO, QCTNAME(TP) +
      " pushes the west wall and it swings around!\n", TP);
}

int
push_wall()
{
    wall_messages();
    TP->move_living("xxx", OTHER_ROOM);
    return 1;
}

int
exit_wall()
{
    wall_messages();
    return 0;
}

