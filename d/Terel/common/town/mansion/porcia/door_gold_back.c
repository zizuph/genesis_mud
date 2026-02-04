/* 921016: Dust: gold door for porcia quest */

inherit "/std/door";
#include "/d/Terel/common/terel_defs.h"
#define PORDIR TOWNDIR + "mansion/porcia/"



create_door() {

  ::create_door();
   set_door_id("golddoor");
   set_pass_command(({"s", "south"}));
   set_door_name(({"gold door", "door"}));
   set_other_room(PORDIR + "riddle_room");
   set_lock_command("lock");
   set_lock_name("lock");
   set_unlock_command("unlock");
   set_door_desc(break_string("This is a very ancient looking, richly " +
	"decorated door, made of pure gold. " +
	"Surely it's the work of an artist.\n",70));

   set_open(0);
   set_locked(0);

}


