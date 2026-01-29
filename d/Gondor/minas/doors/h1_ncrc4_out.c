inherit "/std/door";

#include <macros.h>
#include "/d/Gondor/defs.h"

void
create_door()
{
    ::create_door();
    set_door_id("MT_h1_ncrc4");
    set_pass_command(({"n","north"}));
    set_door_name(({"wooden door", "door"}));
    set_other_room(MINAS_DIR + "houses/h1ncrc4");
    set_door_desc(BSN("The wooden door looks rather old, but it "
      + "obviously has been painted regularly so there is hardly "
      + "any wear visible. On it is written in Numenorean letters:")
      + "\t\tGIMILZOR\n");
    set_lock_command("lock");
    set_lock_name("lock");
    set_unlock_command("unlock");
    set_open(0);
    set_locked(1);
    set_key("MT_h1_ncrc4");
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

      return 1;
}

