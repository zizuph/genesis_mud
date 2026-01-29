inherit "/d/Rhovanion/common/erebor/caves.c";

#include "/sys/macros.h"
#include "/d/Rhovanion/defs.h"
#include <filter_funs.h>
#include "door.h"
#define CAVE_DIR ERE_DIR + "ere2/"

 
int window_is_clean;
 
object east_door;
object key;
object dwarf1, dwarf2;
 
void reset_room();

void create_cave()
{

  set_rock_type("cold grey granite");
  set_cave_name("the Lonely Mountain");
  set_region("northern");
  set_cave("Erebor");
  set_cave_type(1);
  set_long("Here you see the cave widen up. "
        + "To the west seems to be a house and to the right "
        + "is a bigger construction. You can see a window in it "
        + "that might be worth an examination.\n");

  add_exit(CAVE_DIR + "lm2c6","north",0,1);
  add_exit(CAVE_DIR + "lm2c8","west",0,1);
  add_exit(CAVE_DIR + "lm2c12","south",0,1);
 
 
  east_door = clone_object(CAVE_DIR + "door_lm2c9");
  east_door->move(TO);
 
  key = clone_object(CAVE_DIR + "small_key");
  key->set_key(SMALL);
  east_door->set_key(SMALL); /* Tells the door which key fits. */
 
  add_item("sign","The sign reads:   SCHOOLHOUSE\n");
  add_item("window", "@@window_desc");
 
   reset_room();
 
}
 
void
reset_room()
{

    if(sizeof(FILTER_LIVE(all_inventory(TO))))
    {
      return;
    }
    dwarf1 = clone_object(NPC_DIR+"dwarves/dwarf_high");
    dwarf1->arm_me();
    dwarf1->move_living("xxx", this_object());
        dwarf2 = clone_object(NPC_DIR+"dwarves/dwarf_low");
        dwarf2->arm_me();
        dwarf2->move_living("xxx", this_object());
        dwarf1->team_join(dwarf2);
 
    window_is_clean = 0;
}
 
init()
{
    ::init();
    add_action("clean_window", "clean");
}
 
int
clean_window(string arg)
{
    if(window_is_clean) return 0;
    if(arg != "window") return 0;
    TP->catch_msg("You breath on the window "
    + "and rub it with your sleeve. It works!\n");
    say(QCTNAME(TP)+" breethes on the dusty window and rubs "
    + "it slowly to clean it.\n");
    window_is_clean = 1;
    return 1;
}
 
 
string
window_desc() {
  if(present("_ere_dwarf_", TO))
    return "It is small window in the wall. The dwarf will not "+
           "let you see through it. It must be some important "+
           "things in there.\n";
  if(!window_is_clean)
     return "You cant see through the window now. Its to dusty " +
            "from months passing by.\n";
    return "You look through the clean window. Inside you " +
           "see a classroom with desks, the first one smaller " +
           "than the second lined up in long perfect rows. " +
           "It reminds you of your schooldays and you feel " +
           "warm inside.\n";
} 
