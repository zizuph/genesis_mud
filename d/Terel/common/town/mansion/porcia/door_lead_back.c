/* 921016: Dust: lead door for porcia quest */

inherit "/std/door";
#include "/d/Terel/common/terel_defs.h"
#define PORDIR TOWNDIR + "mansion/porcia/"



create_door() {

  ::create_door();
   set_door_id("leaddoor");
   set_pass_command(({"n", "north"}));
   set_door_name(({"lead door", "door"}));
   set_other_room(PORDIR + "riddle_room");
   set_lock_command("lock");
   set_lock_name("lock");
   set_unlock_command("unlock");
   set_door_desc(break_string("This is a very ancient looking, richly " +
	"decorated door, made of lead. " +
	"Surely it's the work of an artist.\n",70));

   set_open(0);
   set_locked(0);

}


