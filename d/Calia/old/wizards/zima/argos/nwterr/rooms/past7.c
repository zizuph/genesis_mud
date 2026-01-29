/* inherits/includes */
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
#include "stepdung.h"  /* this is for the stepping in sheep dung action */
 
int are_shroom=1;
 
void
reset_room()
{
   are_shroom=1;
}
 
/* room definition */
void
create_room()
{
   set_short("A green pasture");
   set_long(break_string(
       "You walk along the northern edge of a fenced-in pasture, covered " +
       "in short green grass.  The ground is almost covered with the " +
       "steaming dark patties here, and it would be very easy to " +
       "misstep and hit one.  " +
       "The fence borders the pasture to the north and east, " +
       "allowing you to walk south and west. A small fold has "+
       "been built of sticks in this corner.\n",70));
 
    add_item(({"pasture","field"}), break_string(
             "The pasture is covered with short green grass within " +
             "the fence, and stretches to the west, east and south.\n",70));
    add_item("grass", break_string(
             "Lush green grass, kept short by grazing sheep, it covers " +
             "the gently rolling pasture.\n",70));
    add_item("fence", break_string(
             "A simple wooden fence, enclosing the field you are standing " +
             "in.  It borders the pasture to the north and east.\n",70));
    add_item("patties", "@@exa_patties");
    add_item("mushroom","@@exa_shroom");
    add_cmd_item("mushroom","pick","@@pick_shroom");
    add_item("fold","It is a low shelter made of sticks where the sheep "+
             "go for protection from the weather. There is a small "+
             "hole in the fold.\n");
    add_item("hole","It is an entrance to the little hut. Perhaps "+
             "you can crawl into the fold through it.\n");
    add_item(({"into fold","into the fold"}), "What?\n");
    add_cmd_item(({"into fold","into the fold"}), "crawl", "@@enter_fold");
 
    /* exits */
    add_exit(ROOM_DIR+"past4","south",0);
    add_exit(ROOM_DIR+"past6","west",0);
    reset_room();
}
 
string
exa_patties() {
   if (are_shroom)
      return break_string(
      "They are dark mounds scattered around the field, tiny white whisps " +
      "rising from them, giving off a very unpleasant odor. You see a " +
      "purple striped mushroom growing on one of the heaps.\n",70 );
   else
      return break_string(
      "They are dark mounds scattered around the field, tiny white whisps " +
      "rising from them, giving off a very unpleasant odor.\n",70);
}
 
string
exa_shroom() {
   if (are_shroom)
      return
      "A striped purple mushroom is growing on one of the dark mounds.\n";
   else
      return "You find no mushroom, but you think they would grow here.\n";
}
 
int
pick_shroom() {
   object shroom;
 
   if (are_shroom) {
      shroom=clone_object(OBJ_DIR+"ccshroom");
      shroom->move(this_player());
      write ("You pick the mushroom from the nasty mound.\n");
      are_shroom=0;
   }
   else
      write ("You find no mushroom.\n");
   return 1;
}
 
int enter_fold() {
    write("You crawl through the hole and enter the fold.\n");
   this_player()->move_living("into the fold",ROOM_DIR+"fold");
   return 1;
}
