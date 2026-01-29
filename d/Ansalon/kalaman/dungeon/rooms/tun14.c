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

#define T_OTHER SEWERS_FIRST + "s27"

create_dungeon_room()
{
   set_dungeon_type(ROOM_TUNNEL2);
   ::create_dungeon_room();

   set_long(get_long_desc() + " The only way that seems accessable from here " +
      "is to the southeast, anywhere else just seems too narrow. A narrow " +
      "hole seems to provide an opening to the west.\n");

   add_item(({"opening", "hole" }), "A narrow hole in the west wall provides " +
      "an opening just about enough to enter.\n");

   add_exit("tun15", "southeast", 0, 5, 1);
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
       write("You enter through the opening and fall out on the other side.\n");
       tell_room(ENV(TP), QCTNAME(TP) + " enters the opening in the west and " +
           "vanishes out of sight, you hear a slight noice from the opening.\n", TP);
       TP->move_living("M", T_OTHER, 1);
       tell_room(ENV(TP), QCTNAME(TP) + " falls out from the opening in the wall " +
           "and lands on the rough floor in a very unflattering way.\n", TP);
       return 1; 
    }

    return 0;
}
