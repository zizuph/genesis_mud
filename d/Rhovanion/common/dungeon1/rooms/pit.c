inherit "/std/room.c";
#include "/d/Rhovanion/defs.h"
static int counter=0;
mixed enemy;
void
create_room() {
   set_short("Heaven\n");
   set_long("This is a round pit of large, stone blocks " +
      "at least ten feet in diameter.  The walls bear countless " +
      "chips and scratches from where weapons have pounded " +
      "the surface, but it is relatively clean here though " +
      "it smells a little of blood mixed with an odd " +
      "reptilian odour.\n");
   add_item(({"block","blocks"}),"These are large, dark blocks of stone " +
      "all bearing the numerous scars of past battles.\n" +
      "     One of the blocks in the east is sticking out " +
      "a few inches like it has been pulled out.\n");
   add_cmd_item("block","push","@@push_block");
   clone_object("/d/Rhovanion/common/dungeon1/living/wguard7.c")
   ->move(TO);
   add_exit("/d/Rhovanion/common/dungeon1/rooms/guard7","out");
}
push_block() {
   enemy = TP->query_enemy();
   if (enemy)
      {
      if (counter > 0)
         {
         write("The block is still sliding out.\n" +
            "There's nothing to push now.\n");
         return 1;
       }
      write("You push the block back into the wall " +
         "with a low, grating noise...\n");
      say(QCTNAME(TP) + " pushes a block back into the " +
         "wall with a low, grating noise...\n");
      set_alarm(2.0,0.0,"push_block2", this_player());
      return 1;
   }
   write("You push the block back into the wall " +
      "with a low, grating noise...\n");
   say(QCTNAME(TP) + " pushes a block back into the " +
      "wall with a low, grating noise...\n");
   set_alarm(2.0,0.0,"no_enemy", this_player());
   return 1;
}
push_block2() {
   write("The block suddenly shoots back into the wall!\n");
   say(QCTNAME(TP) + " watches as the block suddenly " +
      "shoots back into the wall!\n");
   set_alarm(1.0,0.0,"push_block3");
   return 1;
}
push_block3() {
   write("A block suddenly shoots out of a different " +
      "section of the wall and slams into " + QCTNAME(enemy) + ".\n");
   say(QCTNAME(TP) + " smiles pleasedly as a block " +
      "suddenly shoots out of a different section of the all " +
      "and slams into his opponent!\n");
   enemy[0]->heal_hp(-25);
   counter++;
   set_alarm(25.0,0.0,"reset_block");
   return 1;
}
reset_block() {
   counter--;
   return 1;
}
no_enemy() {
   write("A block on the other side of the room shoots " +
      "out from the wall!  If you were fighting someone and " +
      "had him positioned right you could probably use this " +
      "to your advantage.\n");
   say(QCTNAME(TP) + " gets a devious grin on his face " +
      "as he watches a block on the other side of the room " +
      "shoot out with great force from the wall!\n");
   return 1;
}
