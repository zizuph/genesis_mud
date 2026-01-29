/*
 * Tunnel 14
 * 
 * Leads into the sewers of Kalaman.
 * Location of the thieves hideout is in Tunnel 18
 *
 * Lunatari of Krynn
 * 2008-02-02
 */
#include "local.h"

inherit DUNGEON_IN;

#define T_OTHER DROOM + "thief1"

create_dungeon_room()
{
   set_dungeon_type(ROOM_TUNNEL2);
   ::create_dungeon_room();

   set_long(get_long_desc() + " The only way that seems accessable from here " +
      "is to the south, anywhere else just seems too narrow. In the eastern " +
      "wall an opening has been carved out that continues further in to the " +
      "dark.\n");

   add_item(({"opening", "hole" }), "A narrow hole in the east wall provides " +
      "an opening just about enough to enter.\n");

   add_exit("tun15", "south", 0, 25, 1);
}

init()
{
  ::init();
  add_action("enter_opening", "enter");
}

int
enter_opening(string str)
{
    notify_fail("Enter what?\n");

    if (!str) return 0;

    if (parse_command(str, ({ }),"[the] 'hole' / 'opening'"))
    {
       write("You enter through the opening and step out on the other side.\n");
       tell_room(ENV(TP), QCTNAME(TP) + " enters the opening in the east and " +
           "vanishes out of sight.\n", TP);
       TP->move_living("M", T_OTHER, 1);
       set_dircmd("opening");
       tell_room(ENV(TP), QCTNAME(TP) + " steps out from the opening in the wall " +
           "and stretches " + HIS(TP) + " body.\n", TP);
       return 1; 
    }

    return 0;
}
