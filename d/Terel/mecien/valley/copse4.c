inherit "std/room";
#include "/d/Terel/common/terel_defs.h"
#include <stdproperties.h>
#include <macros.h>

#define BS(message)     break_string(message,75)
#define PS(message)     process_string(message)
#define TP              this_player
#define TO	this_object()

object monster;

reset_room(arg){
   if(monster) return;
   monster = clone_object("/d/Terel/mecien/valley/guild/mystic5");
   monster->move_living("M", TO);
}

void
create_room(){
   
   set_short("Copse of Willow");
   set_long(
      "This is the east side of a small copse of willows. Their beautiful branches " +
      "draping down to the ground in open lamentation. The ground here is very wet, " +
      "becoming deep mud in all directions except westward.\n"
   )
   ;
   add_item("mud", "It is very thick and deep, suggesting a body of water nearby.\n");
   add_item("hole", "It is a large hole in the trunk of one of the great willows.\n");
   add_exit("/d/Terel/mecien/valley/copse2", "west", 0);
   add_item(({"trees","tree","willow","willows"}),break_string("These "
         + "majestic trees fill you with a sense of peace and serenity. Their "
         + "branches, which approach the thickness of the "
         + "trunk, root the ancient trees to the ground with such solidity you doubt a "
         + "hurricane could uproot them.\nOne tree has a large hole in "
         + "its trunk.\n",75));
   
   reset_room();
}


