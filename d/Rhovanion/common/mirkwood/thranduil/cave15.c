inherit "/d/Rhovanion/lib/caves.c";

#include "def.h"
#include "/sys/macros.h"
#include "/d/Rhovanion/defs.h";

create_cave()
{
  set_rock_type("soluble limestone");
  set_cave_name("Thranduil's Caverns");
  set_region("northern");
  set_cave("Mirkwood");
  set_cave_type(1);
  set_long(" The corridor continues west and southeast. "
	   + " \n");

  set_noshow_obvious(1);
  add_exit(THIS_DIR + "cave14","west",0,1);
  add_exit(THIS_DIR + "cave16","southeast",0,1);

  /*  add_item("door","@@exa_door"); */
}

init()
{
  ::init();
    /*    add_action("try_north","n");
     *    add_action("try_north","north");
     */
  }

/* try_north()
 * {
 *   if (TP->query_race()=="elf") 
 *   {
 *     write("You see a door, which you enter.\n");
 *     say(QCTNAME(TP)+" disappears in a puff of smoke.\n",TP);
 *     TP->move_living("north","/d/Rhovanion/common/guild/eguild/boardroom");
 *     TP->init_command("look");
 *     return 1;
 *   }
 *   write("You feel that they don`t want anyone else but elves there. \n");
 *   return 1;
 * }
 */

exa_door()
{
  if (TP->query_race()=="elf") 
 return write("There is an old door leading north, it seems to be closed. \n");
  return write("You see nothing special. \n");
}
