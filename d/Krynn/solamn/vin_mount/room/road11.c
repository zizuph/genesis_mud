/* created by Aridor 06/19/93 */

#include "../local.h"

inherit ROOM_BASE

#include <ss_types.h>
#include <macros.h>

void
create_vin_mount_room()
{
    set_short("Halfway up the Top");
    set_long("@@my_long");

    OUTSIDE;

    add_exit(ROOM + "road8","down",0,15);
    add_exit(ROOM + "road12","up","@@can_climb",40);

    add_item("ledge",
         "This is a narrow ledge where you can rest before " +
        "attempting the second part of the climb.\n");
    add_item(({"track","ground","road","gravel","mountain track"}),
         "The track itself is simply " +
        "laid out with small stones and gravel.\n");
    add_item(({"mountains","mountain"}),
         "These are high mountains indeed, rocks and occasional " +
        "shrubs are scattered everywhere, it is definitely " +
        "a very hostile area.\n");
    add_item(({"shrubs","rocks"}),
         "The mountainsides are covered with rocks with a few " +
        "shrubs making their living in between.\n");
}

string
my_long()
{
    string desc = "You are on a small ledge where you can overlook "
          +       "the road below you. It leads to the northwest, "
          +       "then to the northeast down into a valley, and "
          +       "to the south the road goes south, then turns to "
          +       "the southeast into another valley.\n";
    return desc;
}

int
can_climb()
{
    if (TP->query_skill(SS_CLIMB) > 25)
      return 0;
    else
      {
      say(QCTNAME(TP) + " tried to climb up but failed.\n");
      write("You try to climb up but almost "
        + "break your limbs when you fall "
        + "back down.\n");
      return 1;
      }
}

