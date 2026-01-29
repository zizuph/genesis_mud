#include "/d/Krynn/common/defs.h"
#include "/d/Ansalon/kalaman/sewers/local.h"

inherit DWARF_TUNNEL;

#define DUNGEON_LINK DROOM + "tun13"

create_sewer_room()
{
    ::create_sewer_room();

    add_item(({"opening", "hole" }), "A narrow hole in the floor seems to be " +
      "a tunnel that leads downwards.\n");

    add_prop(OBJ_S_WIZINFO, "This is a link to the dungeon area, rooms/tun13.c");

    add_exit(SECOND + "s4", "east");
    add_exit(SECOND + "s2", "northwest");
    add_exit(SECOND + "s7", "southwest");
}

init()
{
  ::init();
  add_action("enter_opening", "enter");
  add_action("climb_opening", "climb");
}

int
enter_opening(string str)
{
    notify_fail("Enter what?\n");

    if (!str) return 0;

    if (parse_command(str, ({ }),"[the] 'hole' / 'opening'"))
    {
       write("You enter through the opening and fall all the way down.\n");
       tell_room(ENV(TP), QCTNAME(TP) + " enters the opening in the floor and " +
           "vanishes out of sight, you hear a loud noise from bellow.\n", TP);
       TP->move_living("M", DUNGEON_LINK, 1);
       tell_room(ENV(TP), QCTNAME(TP) + " falls out from the opening in the ceiling " +
           "and lands on the rough floor in a very unflattering way.\n", TP);
       TP->set_hp(TP->query_hp() - (TP->query_hp()/5));
       return 1; 
    }

    return 0;
}

int
climb_opening(string str)
{
    notify_fail("Climb what?\n");

    if (!str) return 0;

    if (parse_command(str, ({ }),"[the] 'down' / 'hole' / 'opening'"))
    {
       write("You carefully climb down through the opening and reach the other side.\n");
       tell_room(ENV(TP), QCTNAME(TP) + " carefully climbs down the narrow tunnel and " +
           "vanishes out of sight, you hear a slight noice from bellow.\n", TP);
       TP->move_living("M", DUNGEON_LINK, 1);
       tell_room(ENV(TP), QCTNAME(TP) + " arrives climbing down the tunnel " +
           "and lands on the floor, not falling.\n", TP);
       return 1; 
    }

    return 0;
}
