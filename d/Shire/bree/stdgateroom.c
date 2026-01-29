/*
 * Standard gate of Bree
 * Copied from old Bree and updated
 * -- Finwe, April 2002
 *
 * 09 Sept 2003 Palmer left gates open until "wrongness"
 * bug is fixed.
 *
 * 25 July 2010 Lavellan - Noticed runtime when old players knock on
 * the gates.. Fixing this as well as reinstating closing of gates
 *
 * 2011/07/21 Lavellan - Inherit base_road, and changing create_room to 
                         create_road_room, to fix light and hopefully stop
 *                       disappearing room descriptions. no break_string!
 *
 */
//inherit "/d/Shire/common/lib/room";

#include "/d/Shire/sys/defs.h"
#include "defs.h"
#include <std.h>
#include <macros.h>
#include <stdproperties.h>

//inherit AREA_ROOM;
inherit "/d/Shire/bree/base_common";
inherit ROAD_BASE;


int gatestate;  /* 0 = closed, 1 = open */
string other_room, direction;
//create_room()
create_road_room()
{
    set_areadesc("large gate");
    set_area("outside");
    set_areaname("Bree");
    set_land("Eriador");

  gatestate = 1;
  add_item(({"gate", "gates"}), "@@my_gates@@");
  add_prop(OBJ_S_WIZINFO, "@@wizinfo@@");
  create_gateroom();
  add_exit(other_room, direction, "@@block@@");
}

create_gateroom() { }


init() {
  ::init();
  add_action("knock", "knock");
  check_gates();
}

knock(string str) {
  if (str != "gates" && str != "gate" && str != "on the gates" &&
    str != "on the gate" && str != "on gates" && str != "on gate") return 0;
  check_gates();
  if (gatestate) {
    write("You knock in the air wildly, just to discover that the gate is open.\n");
    return 1;
  }
  pass_msg();
  set_dircmd(str);
  this_player()->move_living(direction, other_room);
  return 1;
}

pass_msg()
{
    write("You knock loudly on the gates to wake up the hobbit guard.\n");
    write("The gates open and a sleepy guard lets you pass.\n");
    say(QCTNAME(TP) + " knocks loudly on the gates.\n");
    say("The gates open and a sleepy guard lets " +
        HIM_HER(TP) + " pass.\n");
}

my_gates()
{
    string str;

    check_gates();
    str = "The gates of Bree are made of wood and seem strong. ";
    if (gatestate) str += "They are currently open, to let good folk in. ";
    else str += "They are currently closed to keep ruffians out. ";
    str += "There is a sign. It says:\n\n"+
        "\tThe Gates open at 8 in the morning and\n"+
         "\tclose at 10 in the evening.\n";
    return str + "\nIt's now " +
        CLOCK->query_time_of_day() + ".\n";
}

block() {
  check_gates();
  if (gatestate) write("You pass the gates.\n");
  else {
    if (this_player()->query_wiz_level()) {
      pass_msg();
      return 0;
    }
    if (!IS_PLAYER_OBJECT(TP)) {
      // Allow non-players through (for now...)
      return 0;
    }
    write("You try desperately to get past the gates, but fail.\n");
    write("Maybe you should knock on the gates to wake up the guard...\n");
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
        "Gates close at:     10pm\n"+
        "Current gate state: " + str + ".\n";
}

check_gates() 
{
    int hour;

    hour = CLOCK->query_hour();
  
    if (hour < 8 || hour >= 22) 
        gatestate = 0;
    else 
        gatestate = 1;
}

query_state() { return gatestate; }

set_other_room(string str) { other_room = str; }
query_other_room() { return other_room; }

set_direction(string str) { direction = str; }
query_direction() { return direction; }
