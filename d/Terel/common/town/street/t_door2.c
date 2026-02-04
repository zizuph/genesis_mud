inherit "/std/door";

#include <stdproperties.h>

#define PATH "/d/Terel/common/town/"
create_door() {
   
   ::create_door();
   
   set_door_id("tower door");
   
   set_pass_command(({"e", "east", "out", "exit", "leave" }));
   
   set_door_desc("A silver-white door inscribed with a cresent moon\n" +
      "leads out of the tower. The door is wood and metal.\n");
   
   set_door_name(({"white door", "door", "tower door", "wooden door"}));
   
   set_other_room(PATH + "street/tower_entrance");
   
   set_lock_command("lock");
   set_lock_name("lock");
   set_unlock_command("unlock");
   
   set_open(0);
   set_locked(0);
}

void
do_open_door(string mess)
{
    ::do_open_door(mess);
    environment()->add_prop(ROOM_I_LIGHT,
        environment()->query_prop(ROOM_I_LIGHT) + 2);
}

void
do_close_door(string mess)
{
    ::do_close_door(mess);
    environment()->add_prop(ROOM_I_LIGHT,
        environment()->query_prop(ROOM_I_LIGHT) - 2);
}

public int
open_door(string str)
{
    int val;

    // The door should remain locked, but one should be able to open it
    // regardless
    set_locked(0);
    val = ::open_door(str);
    set_locked(1);
    return val;
}
