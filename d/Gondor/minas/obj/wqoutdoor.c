inherit "/std/door";

#include <macros.h>
#include "/d/Gondor/defs.h"

void
create_door()
{
  ::create_door();
  set_door_id("wq_door");
  set_pass_command(({"n","north"}));
  set_door_name(({"wooden door","worn door","door"}));
  set_other_room("/d/Gondor/minas/houses/wqhouse2");
  set_door_desc("The wooden door looks worn out by weather, time and usage.\n"+
    "On it is written in Numenorean letters: HIR BELECTHOR \n");
  set_lock_command("lock");
  set_lock_name("lock");
  set_unlock_command("unlock");
  set_open(0);
  set_locked(0);
  set_key("wq_house_key");
}

void
init()
{
    ::init();

    add_action("do_knock", "knock");
}

int
do_knock(string str)
{
    object  tp = TP;

    if (str != "door" && str != "on door")
        NFN0("Knock on what?");

    if (open_status)
    {
        write("You knock on the open door. Stupid, isn't it?\n");
        say(QCTNAME(tp) + " knocks on the open door. Stupid, isn't it?\n");
        return 1;
    }
    write("You knock on the door.\n");
    say(QCTNAME(tp) + " knocks on the door.\n");
    other_room->load_me();
    tell_room(other_room, "Someone is knocking on the door.\n");

    set_alarm(1.0, 0.0, "do_reaction");

    return 1;
}

void
do_reaction()
{
    object  gilraen;

    if (!objectp(gilraen = present("gilraen", find_object(other_room))))
        return;

    gilraen->command("shout Who is it?");
    gilraen->command("shout Come in please, the door is unlocked!");
    tell_room(environment(this_object()),
        "A female human voice shouts from beyond the door: Who is it?\n" +
        "A female human voice shouts from beyond the door: " +
        "Come in please, the door is unlocked!\n");
}
