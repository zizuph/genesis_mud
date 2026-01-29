/*
 * Road in Bree
 * By Finwe, June  2001
 *
 * Gates fixed 2010/07/25 Lavellan
 *
 * 2011/07/21 Lavellan - Changed to use stdgateroom, commented out redundant
 *                       stuff here
 */
 
#include "/d/Shire/sys/defs.h" 
#include "defs.h"

//inherit ROAD_BASE;
inherit "/d/Shire/bree/stdgateroom.c";

object human;
//int gatestate;  /* 0 = closed, 1 = open */

//string other_room, direction;

string
gate_desc()
{
//    if (gatestate) return "The gate is open. ";
//    else return "The gate is closed to keep villains out. ";
    string str;
    if (gatestate) str = "The gates are open. ";
    else str = "The gates are closed to keep villains out. ";
    return "The road runs northwest out the gate and beyond, " +
        "presumably to Deadman's Dike. The North Gate is sturdy " +
        "looking. " + str + "The only thing of interest is a " +
        "stone wall that runs along the west side of the road.\n";
}

void
//create_road_room()
create_gateroom()
{
    string str;

    set_areadesc("quiet deserted road");
    set_area("inside the");
    set_areaname("North Gate");
    set_land("Bree");

//  if (gatestate) str = "The gates are currently open";
//  else str = "The gates are currently closed";
    set_vbfc_extra(gate_desc);

//    add_my_desc("The road runs northeast out the gate and beyond, " +
/*    add_my_desc("The road runs northwest out the gate and beyond, " +
        "presumably to Deadman's Dike. The North Gate is sturdy " +
        "looking. @@gate_desc@@The only thing of interest is a " +
        "stone wall that runs along the west side of the road.\n");*/
        

//    add_prop(OBJ_S_WIZINFO, "@@wizinfo");
//    add_item(({"gate", "gates"}), "@@my_gates");   
    add_item(({"gate", "gates", "north gate", "north gates"}), "@@my_gates");

    set_add_outside_smiths();
    set_add_hill();
    reset_shire_room();

//    gatestate = 1;

//    other_room = ROAD_DIR + "ngate";
    set_other_room(ROAD_DIR + "ngate");
//    direction = "west";
    set_direction("northwest");

    //add_exit(ROAD_DIR + "ngate", "northwest");
    add_exit(ROAD_DIR + "broad22", "southeast");
}


/*init()
{
    ::init();
    add_action("knock", "knock");
    check_gates();
}*/

void
reset_shire_room()
{
    setuid();
    seteuid(getuid());

    if(!objectp(human))
    {
        human = clone_object(NPC_DIR + "human");
        human->move(TO);
        human->set_restrain_path("/d/Shire/bree");
        human->set_random_move(2);

    }
}

/*knock(string str) {
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
    else str += "They are currently closed, to keep ruffians out. ";
    str += "There is a sign. It says:\n"+
        "The Gates Open At 8 In The Morning And "+
         "Close At 10 In The Evening.";
    return break_string(str + "\n", 70) + "It's now " +
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
    write("You try desperately to get past the gates, but fail.\n");
    write("Maybe you should knock on the gates to wake up the guard...\n");
  }
  return !gatestate;
}

wizinfo() {
  string str;
  check_gates();
  str = gatestate ? "Open" : "Closed";
  return "Current game time:  " + CLOCK->query_time() + "\n"+
         "Gates open at:      08:00\n"+
         "Gates close at:     22:00\n"+
         "Current gate state: " + str + ".\n";
}

check_gates() {
  int hour;

  hour = CLOCK->query_hour();
  if (hour < 8 || hour >= 22) gatestate = 0;
  else gatestate = 1;
}

query_state() { return gatestate; }

set_other_room(string str) { other_room = str; }
query_other_room() { return other_room; }

set_direction(string str) { direction = str; }
query_direction() { return direction; }
*/