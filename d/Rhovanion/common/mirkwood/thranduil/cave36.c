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
  set_long(" You stand in a corridor leading west and northeast, " +
	   " to the northeast you see a split in the corridor. " +
	   " \n");

  set_noshow_obvious(1);
  add_exit(THIS_DIR + "cave33","northeast",0,1);
  add_exit(THIS_DIR + "cave35","west",0,1,);

  call_out("reset_room",1);
}

void reset_room()
{
  elf = clone_object("/d/Rhovanion/common/npcs/elves/elf_med.c");
  elf -> arm_me();
  elf -> move_living("into a room", THIS_DIR + "cave36");
}
