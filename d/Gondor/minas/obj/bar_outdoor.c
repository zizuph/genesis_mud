inherit "/std/door";

#include <macros.h>
#include "/d/Gondor/defs.h"

void
create_door()
{
    ::create_door();
    set_door_id("baranor_door");
    set_pass_command(({"s","south"}));
    set_door_name(({"wooden door","brown door","door"}));
    set_other_room(MINAS_DIR + "houses/b_house");
    set_door_desc("The wooden door has been painted brown.\n"
      + "On it is written in Numenorean letters: HIR BARANOR\n");
    set_lock_command("lock");
    set_lock_name("lock");
    set_unlock_command("unlock");
    set_open(0);
    set_locked(0);
    set_key("baranor_house_key");
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
    object  baranor;

    if (!objectp(baranor = present("baranor", find_object(other_room))))
        return;

    baranor->command("shout Who is it?");
    baranor->command("shout Come in please, the door is unlocked!");
    tell_room(ENV(this_object()),
        "A male human voice shouts from beyond the door: Who is it?\n"
      + "A male human voice shouts from beyond the door: "
      + "Come in please, the door is unlocked!\n");
}
