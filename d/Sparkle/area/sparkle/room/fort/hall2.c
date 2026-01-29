/* Vladimir 8-09-94 */

#pragma strict_types

inherit "/std/room";

#include <macros.h>
#include <stdproperties.h>
#include <filter_funs.h>

#include "defs.h"

void
create_room()
{
    set_short("Fortress hallway");
    set_long(
        "This passageway leads north along a rough walkway. You can barely\n"
        + "make out the ceiling above you. The walls are bereft of everything\n"
        + "except their sickening odor.\n");

    add_item(({"walkway", "passageway"}),
             break_string("The floor here is tricky to walk on "+
                          "due to the uneveness of the whole room.\n", 70));
    add_item(({"ceiling", "up"}),
             break_string("you can not seem to make out any details of "+
                          "the ceiling.\n", 70));
    add_item(({"wall", "walls"}),
             break_string("The walls are bare. They do exude a particularly "+
                          "nausiating odor though.\n", 70));
    add_prop(ROOM_I_INSIDE, 1);
    add_exit("hall3", "north");
    add_exit("hall1", "south");

    add_cmd_item(({"odor", "walls"}), "smell", "@@smell");
    add_cmd_item("odor","smell","@@smell");
}

string
smell()
{
  write("You inhale and smell the disgusting odor more deeply, it\n"
      + "makes you extremely sick to your stomache.\n");
  say(QCTNAME(TP) + " inhales deeply and turns green.\n");
  TP->command("choke");
  TP->command("puke");
  return "";
}

