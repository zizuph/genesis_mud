/*
 * Standard gate of Bree
 * Copied from old Bree and updated
 * -- Finwe, April 2002
 */
//inherit "/d/Shire/common/lib/room";

#include "/d/Shire/sys/defs.h"
#include "defs.h"
#include <std.h>
#include <macros.h>
#include <stdproperties.h>
inherit "/d/Shire/std/room/room_tell";
inherit "/lib/commands.c";
inherit "/d/Shire/bree/base_common";

inherit AREA_ROOM;

int gatestate;  /* 0 = closed, 1 = open */
string other_room, direction;

create_gateroom() { }
query_state() { return gatestate; }

set_other_room(string str) { other_room = str; }
query_other_room() { return other_room; }

set_direction(string str) { direction = str; }
query_direction() { return direction; }

create_area_room()
{
  gatestate = 1;
  add_item(({"gate", "gates"}), "@@my_gates");
  add_prop(OBJ_S_WIZINFO, "@@wizinfo");
  create_gateroom();
  add_exit(other_room, direction, "@@block");
}

init()
{
  ::init();
  add_action("knock", "knock");
  check_gates();
}

knock(string str)
{
    if (str != "gates" && str != "gate" && str != "on the gates" &&
        str != "on the gate" && str != "on gates" && str != "on gate") return 0;
    check_gates();
    if (gatestate) 
    {
        write("You knock in the air wildly, only to discover the " +
            "gate is open.\n");
    return 1;
    }
    pass_msg();
    set_dircmd(str);
    this_player()->move_living(direction, other_room);
    return 1;
}

pass_msg()
{
  write("You knock loudly on the gates to wake up the gatekeeper.\n");
  write("The gates open and a sleepy guard lets you pass.\n");
  say(QCTNAME(TP) + " knocks loudly on the gates.\n");
  say("The gates open and a sleepy guard lets " + HIM_HER(TP) + " pass.\n");
}

my_gates()
{
    string str;

    check_gates();
    str = "The gates of Bree are made of wood and seem strong. ";
    if (gatestate) str += "They are currently open, to let good folk in. ";
    else str += "They are currently closed, to keep ruffians out. ";
    str += "There is a sign. It reads:\n"+
        "\tThe Gates open at 8 in the morning and "+
        "close at 5 in the evening.\n";
    return str + "It's now " +CLOCK->query_time_of_day() + ".\n";
}

block()
{
  check_gates();
  if (gatestate) write("You pass the gates.\n");
  else 
  {
    if (this_player()->query_wiz_level()) {
      pass_msg();
      return 0;
    }
    write("You try desperately to get past the gates, but fail.\n");
    write("Maybe you should knock on the gates to wake up the gatekeeper.\n");
  }
  return !gatestate;
}

wizinfo()
{
    string str;

    check_gates();
    str = gatestate ? "Open" : "Closed";
    return "Current game time:  " + CLOCK->query_time() + "\n"+
           "Gates open at:      8am\n"+
           "Gates close at:     5pm\n"+
           "Current gate state: " + str + ".\n";
}

check_gates()
{
    int hour;

    hour = CLOCK->query_hour();
    if (hour < 8 || hour >= 22) gatestate = 0;
    else gatestate = 1;
}
