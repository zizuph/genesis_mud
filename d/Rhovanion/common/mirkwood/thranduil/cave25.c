inherit "/d/Rhovanion/lib/caves.c";

#include "def.h"
#include "/sys/macros.h"
#include "/d/Rhovanion/defs.h";

object elf;

create_cave()
{
  set_rock_type("soluble limestone");
  set_cave_name("Thranduil's Caverns");
  set_region("northern");
  set_cave("Mirkwood");
  set_cave_type(1);
  set_long("You are standing in a crossroad in the caves, to the north "
	   + "you see the party halls of Thranduil, and corridors are "
	   + "leading east, south and west."
	   + " \n");

  set_noshow_obvious(1);
  add_exit(THIS_DIR + "cave22","north",0,1);
  add_exit(THIS_DIR + "cave20","west",0,1);
  add_exit(THIS_DIR + "cave26","east",0,1);
  add_exit(THIS_DIR + "cave27","south",0,1);
  call_out("reset_room",1);
}

void reset_room()
{
  elf = clone_object("/d/Rhovanion/common/npcs/elves/elf_high.c");
  elf -> arm_me();
  elf -> move_living("into a room", THIS_DIR + "cave25");
}
