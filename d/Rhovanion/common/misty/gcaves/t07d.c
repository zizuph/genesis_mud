/* goblin caves */
/*

Created: Probably Milan@Genesis
Modified: Dimitry@Igor
Date: 04-Feb-2001
Information: a room with retired Angmarim Captain Tao.
             You can find a neat club here. (One south
             from the big intersection.)

*/


inherit "/d/Rhovanion/common/misty/gcaves/room_g";
#include "/d/Rhovanion/defs.h"

#define CAVE_DIR MISTY_DIR + "gcaves/"

object tao;

void create_cave()
{
  add_exit(CAVE_DIR + "t07", "north");
  set_guards(4);

if (!objectp(tao));
 {
 tao=clone_object("/d/Rhovanion/common/npcs/goblins/tao.c");
 tao->arm_me();
 tao->move(TO); 
 }
}

