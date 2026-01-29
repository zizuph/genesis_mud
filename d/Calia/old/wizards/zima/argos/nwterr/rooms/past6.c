/* inherits/includes */
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
 
object shepherd=0;
 
void
reset_room()
{
    if (shepherd) return;
    shepherd=clone_object(NPC_DIR+"shepherd");
    shepherd->move(THIS);
    tell_room(THIS, QCNAME(shepherd)+" chases a sheep back into the fold.\n");
}
 
 
/* room definition */
void
create_room()
{
   set_short("A green pasture");
   set_long(break_string(
       "You walk along the northern edge of a fenced-in pasture, covered " +
       "in short green grass.  You smell a distinctive odor here, and " +
       "see that it is coming from soft dark patties scattered about the " +
       "field.  A fence borders the pasture to the north, " +
       "running through a small pond used by the sheep to drink.\n",70));
 
    add_item("pond", break_string(
       "It is a small pond in a shallow dip in the pasture, a place " +
       "for the sheep to drink and to frolic in the waters. The water " +
       "looks incredibly clean.\n",70));
 
    add_item("water","The water in the pond looks remarkably clear.\n");
    add_cmd_item("water","drink","@@drink_water");
 
    add_item("bucket with water","What?\n");
    add_cmd_item("bucket with water","fill","@@fill_bucket");
 
    add_item("grass", break_string(
             "Lush green grass, kept short by grazing sheep, it covers " +
             "the gently rolling pasture.\n",70));
    add_item(({"pasture","field"}), break_string(
             "The pasture is covered with short green grass within " +
             "the fence, and stretches to the west, east and south.\n",70));
    add_item("fence", break_string(
             "A simple wooden fence, enclosing the field you are standing " +
             "in.  It borders the pasture to the north.\n",70));
    add_item("patties", break_string(
             "Dark mounds scattered around the field, tiny white wisps "+
             "rising from them, giving off a very unpleasant odor.\n",70));
 
    /* exits */
    add_exit(ROOM_DIR+"past3","south",0);
    add_exit(ROOM_DIR+"past5","west",0);
    add_exit(ROOM_DIR+"past7","east",0);
    reset_room();
}
 
int
fill_bucket() {
   object bucket;
   object player;
 
   player = this_player();
   bucket = present("_argos_shepherds_bucket",player);
   if (bucket) {
      bucket->add_prop("_argos_shepherds_bucket_full",1);
      write("You fill the bucket with clean water from the pond.\n");
   }
   else write("You don't have a proper container.\n");
   return 1;
}
 
int
drink_water() {
   write("You drink some clear water from the pond. It tastes bitter.\n");
   return 1;
}
