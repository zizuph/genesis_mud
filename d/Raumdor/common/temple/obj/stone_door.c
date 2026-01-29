#pragma strict_types

#include "defs.h"
inherit "/std/door";

void
create_door()
{
    set_door_name(({"heavy stone door", "door", "stone door", "heavy door"}));
    set_open(1);
    set_open_command(({"open", "push"}));
    set_door_desc(
      "This thick door is made of the same dark stone as the walls. There is " +
      "an inscription carved into the door.\n");
    set_no_pick();
    set_knock_command(({"knock", "pound", "bang"}));
    set_knock_resp(
      ({"The sound of your knocking seems to be swallowed up by the dark " +
        "stone.\n",
        QTNAME(TP) + " knocks hard on the door, but the sound is swallowed " +
                     "up by the dark stone.\n",
        ""}));
    add_item("inscription", "@@read_inscription@@");
    add_cmd_item(({"inscription"}), ({"read"}), "@@read_inscription@@");
}

string
read_inscription()
{
    return "The lettering is ornamental, yet harsh and jagged. You cannot " +
           "read it.\n";
}

int
open_door(string arg)
{
    if (!this_door(arg))
    {
        notify_fail(capitalize(query_verb()) + " what?\n", );
        return 0;
    }

    write("You push on the " + short() + ", but nothing happens.\n");
    say(QCTNAME(this_player()) + " pushes on the " + short() +
        ", but nothing happens.\n");
    return 1;
}
