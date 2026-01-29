inherit "/d/Rhovanion/lib/caves.c";
#include "/d/Rhovanion/defs.h"
#include "def.h"
#include "/sys/macros.h"
#include "door.h"

create_cave()
{
  object door, key;
  
  set_rock_type("soluble limestone");
  set_cave_name("Thranduil's Caverns");
  set_region("northern");
  set_cave("Mirkwood");
  set_cave_type(4);
  set_long(" This is a cell in which Thranduil throws those who are "
	   + "not obeying his laws.");
  
  door = clone_object(THIS_DIR + "C2_doori");
  door -> move(TO);
  
  
  door -> set_key(IRON);
  key -> move(TO);
}
