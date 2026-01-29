inherit "/std/door";

#include "/d/Rhovanion/defs.h"
#include <stdproperties.h>
#define CAVE_DIR ERE_DIR + "ere1/"

create_door()
{
set_door_id("Front_Gate");
set_pass_command(({"n","north"}));
set_door_name(({"steel gate", "gate","reinforced gate" }));
set_other_room(CAVE_DIR + "lm1c1");
set_lock_name("bolt");
set_lock_command("bolt");
set_unlock_command("unbolt");
set_open(1);
set_open_desc("The heavy steel gate leading north is wide ajar.\n");
set_closed_desc("The heavy steel gate leading north is firmly shut.\n");
set_door_desc(BS("It's a big, heavy steel gate. Big enough to let "+
              "a dragon pass.\n"));
set_fail_open(({"But it's already open!\n","It's firmly bolted.\n"}));
set_fail_close("Hmm, closing an already closed gate?\n");
set_lock_desc("It's a dark steel bolt.\n");
set_fail_pass("You ram the big gate, head first! Ouch! It hurts!\n");
set_lock_mess(({"bolts the gate.\n",BS("You hear a loud 'clang' "+
              "as the bolt slides into place.\n")}));
set_unlock_mess(({"unbolts the gate.\n",BS("You hear a loud 'clang' "+
              "as the bolt slides back.\n")}));
set_fail_lock(({"It's already bolted.\n",BS("Really, there's no need " +
              "for that, is it?\n")}));
set_fail_unlock("But the gate is already unbolted!\n");
set_str(60);

add_prop(OBJ_I_WEIGHT, 1600);
add_prop(OBJ_I_VOLUME, 3000);
add_prop(DOOR_I_HEIGHT, 500);
}

