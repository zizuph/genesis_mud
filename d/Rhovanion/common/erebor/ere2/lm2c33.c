inherit "/d/Rhovanion/common/erebor/caves.c";

#include "/sys/macros.h"
#include "/d/Rhovanion/defs.h"
#include <filter_funs.h>
#define CAVE_DIR ERE_DIR + "ere2/"
 
object gate, dwarf1, dwarf2, dwarf3, dwarf4;
 
void reset_room();
 
void
create_cave()
{

  reset_room();
  set_rock_type("dark granite");
  set_cave_name("the Lonely Mountain");
  set_region("western");
  set_cave("Erebor");
  set_cave_type(1);
  set_long("You have reached two huge irongates leading east. "
        + "The area in front of the gates has been opened up a bit "
        + "so the corridor is wider than the normal size here in "
        + "Erebor. You wonder why, but realize quickly that its "
        + "probably made this way, because of some kind "
        + "of defensive strategy for defending the gates."
        + "\n");

  gate = clone_object(CAVE_DIR + "gate");
  gate->move(TO);
 
  add_exit(CAVE_DIR + "lm2c32","west",0,1);
}
 
void
reset_room()
{

    if(sizeof(FILTER_LIVE(all_inventory(TO))))
    {
      return;
    }
    dwarf1 = clone_object(NPC_DIR+"dwarves/dwarf_sup");
    dwarf1->arm_me();
    dwarf1->move_living("xxx", this_object());
 
    dwarf2 = clone_object(NPC_DIR+"dwarves/dwarf_sup");
    dwarf2->arm_me();
    dwarf2->move_living("xxx", this_object());
 
    dwarf3 = clone_object(NPC_DIR+"dwarves/dwarf_sup");
    dwarf3->arm_me();
    dwarf3->move_living("xxx", this_object());
 
    dwarf4 = clone_object(NPC_DIR+"dwarves/dwarf_sup");
    dwarf4->arm_me();
    dwarf4->move_living("xxx", this_object());
 
        dwarf1->team_join(dwarf2); /* dwarf1 will be the leader */
        dwarf1->team_join(dwarf3); /* dwarf1 will be the leader */
        dwarf1->team_join(dwarf4); /* dwarf1 will be the leader */
 
}
