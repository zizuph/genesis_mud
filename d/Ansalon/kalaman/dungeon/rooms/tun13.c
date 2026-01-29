#include "local.h"

inherit DUNGEON_IN;

#define SEWER_LINK SROOM+"second/s3"

create_dungeon_room()
{
   set_dungeon_type(ROOM_TUNNEL1);
   ::create_dungeon_room();

   set_long(get_long_desc() + " A narrow opening in the ceiling seems " +
      "lead westards in a rising tunnel. The only way that seems " +
      "accessable from here is to the southeast, anywhere else just " +
      "seems too narrow.\n");

   add_item(({"tunnel", "opening", "hole"}), "The opening seems to lead " +
      "into a tunnel that rises up towards the west. Based on the shape " +
      "and texture of the wall inside the tunnel it does seem possible " +
      "to climb upwards here.\n");

   add_exit("tun12", "southeast", 0, 5, 1);
}

init()
{
  ::init();

  add_action("tunnel_climb", "climb");
}

int
tunnel_climb(string str)
{
    notify_fail("Climb what, where?\n");

    if (!str) return 0;

    if (parse_command(str, ({ }),"[the] 'up' / 'tunnel' / 'hole' / 'opening'"))
    {
       write("You climb up through the opening and stand up on the other side.\n");
       tell_room(ENV(TP), QCTNAME(TP) + " climbs up the opening in the ceiling and " +
           "vanishes out of sight.\n", TP);
       TP->move_living("M", SEWER_LINK, 1);
       tell_room(ENV(TP), QCTNAME(TP) + " arrives climbing up through a small " +
           "opening in the floor and stands up.\n", TP);
       return 1;
    }

    return 0;
}
