inherit "/std/room";

#include "defs.h"

create_room() {
   set_short("Outside Hobbiton");
   set_long(break_string(
         "You are south of Hobbiton, standing between green pastures. "
         + "To the south the little road you are standing on merges into a "
         + "big east-west road.\n",70));
   
   add_item(({"pasture","pastures"}), break_string(
         "The pastures are green and pieces of them are filled with colourfull "
         + "flowers. They are pleasant for the eye.\n",70));
   
   add_exit (ER_DIR + "er13","south",0,1);
   add_exit("/d/Genesis/start/hobbit/v/h_lane3", "north", 0);
}
