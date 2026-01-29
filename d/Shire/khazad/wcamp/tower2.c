inherit "/d/Shire/khazad/moria_room";
#include <stdproperties.h>
#include <macros.h>
#include "/d/Shire/defs.h"
 
create_room()
{
  set_short("On the ground floor of the tower");
  set_long("You stand within a large circular room on the ground floor "+
     "of the tower. A crumbled staircase across the room led to the "+
     "upper floors at one point. At the center of the room a twisting "+
     "staircase leads down.\n");

/*
  add_items
*/
 
  clone_object("/d/Shire/khazad/obj/tower_door_b")->move(TO);
}
 
int
do_up()
{
  write("You try to go up but the stone staircase has been "+
        "destroyed.\n");
  return 1;
}
 
void
init()
{
  ::init();
  add_action(do_up,"up");
  add_action(do_up,"u");
}
