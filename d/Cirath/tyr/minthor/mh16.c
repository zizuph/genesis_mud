inherit "/std/room";
#include "/d/Cirath/common/defs.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "defs.h"
create_room()
 {
  set_short("Small Hallway");
  set_long("A small hallway stretches out before you. It seems too "
	+"small to be used by guests, maybe you shouldn't be here. "
	+"The marble floor is covered by a thin rug that leads "
	+"westwards, and to the south lies a grand ballroom. Small "
	+"globes line the wall, somehow managing to emit a steady "
	+"light.\n");
  add_item("ballroom","It is to the south.\n");
  add_item("hallway","It is around you.\n");
  add_item(({"globe","globes"}),"They line the hallway, and magically "
	+"emanate a steady light.\n");
  add_item(({"chair","chairs"}),"There is a row of them under the "
	+"window. They look small and uncomfortable, yet expensive.\n");
  add_item("floor","It is made of a highly polished marble, but here "
	+"is covered by a narrow rug.\n"); 
  add_item("rug","It is narrow, and doesn't appear that nice. It "
	+"covers the center of the floor.\n");
  add_item(({"house","mansion"}),"You are inside of it.\n");
  ADD_SUN_ITEM
  ADD_ZIG_ITEM
  INSIDE
  add_exit(TZ_MINTHOR + "mh17","west", 0);
  add_exit(TZ_MINTHOR + "mh15","south", 0);
}

