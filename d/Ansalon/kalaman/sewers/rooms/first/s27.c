#include "/d/Krynn/common/defs.h"
#include "../local.h"

#include <macros.h>

inherit SEWER_IN;

//#define S_OTHER DROOM + "tun14"

#define ENV(x)          environment(x)

void
create_sewer_room()
{
    ::create_sewer_room();
    add_exit(FIRST + "s28", "northeast");
    add_exit(FIRST + "s26", "northwest");

    add_item(({"opening", "hole" }), "A narrow hole in the west wall seems to " +
      "provide just about enough space that one could try and enter it.\n");

    add_search(({"wall","walls"}), 20, "search_walls");
}

init()
{
  ::init();
  add_action("enter_opening", "enter");
}

mixed
search_walls(object player, string arg)
{
   return "You notice a small opening in the west wall that seems to lead " +
    "further into a small cave.";
}

int
enter_opening(string str)
{
    notify_fail("Enter what?\n");

    if (!str) return 0;

    if (parse_command(str, ({ }),"[the] 'hole' / 'opening'"))
    {
       write("You enter through the opening and step out on the other side.\n");
       tell_room(ENV(TP), QCTNAME(TP) + " enters the opening and " +
           "vanishes out of sight.\n", TP);
    //   TP->move_living("M", S_OTHER, 1);
       tell_room(ENV(TP), QCTNAME(TP) + " crawls in from opening in the east.\n", TP);
       return 1;
    }

    return 0;
}
