// modifications:
// Lilith Jan 2022: updated room desc

inherit "/std/room";
#include "/d/Terel/common/terel_defs.h"
#define PATH "/d/Terel/LoD/monster/"

object monster1, monster2;

reset_room(){
   if (!monster1) {
       monster1=clone_object(PATH + "elf_korporal");
      monster1->move(this_object());
   }
   if (!monster2) {
       monster2=clone_object(PATH + "elf_korporal");
      monster2->move(this_object());
   }
}

create_room() {
   
   set_short("Road");
   set_long("You are now on a north-south road, but the "
      + "wind and snow have wiped out all traces of the road north. "
      + "The traveling conditions are so bad that you dare not "
      + "attempt to go any further. The smart thing to do would "
      + "be to head back south, toward safety.\n");
   

   add_item(({"snow"}), "It makes you want to build a snowman.\n");
   add_item(({"hills", "rolling hills"}), "These hills go for as far as " 
    + "the eye can see.\n");   
   add_item(({"mountain", "mountains"}), "These snow capped "
      + "mountains reach high into the sky. They spread out "
      + "to the north and west as far as your eyes can see. "
      + "They are known as the Dragon Mountains.\n");
	  
   add_exit("/d/Terel/common/road/road10", "south", 0);
   
   reset_room();
}
