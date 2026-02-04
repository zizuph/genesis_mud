inherit "/std/room";
#define PATH "/d/Terel/LoD/monster/"
object monster;
reset_room(){
if(present("warrior"))return;
monster=clone_object(PATH + "elf_grunt");
    monster->equip_me();
    monster->equip_actions();
monster->move(this_object());

monster=clone_object(PATH + "elf_grunt");
    monster->equip_me();
    monster->equip_actions();
monster->move(this_object());

monster=clone_object(PATH + "elf_grunt");
    monster->equip_me();
    monster->equip_actions();
monster->move(this_object());
}
#include "/d/Terel/common/terel_defs.h"

create_room() {

    set_short("Road");
   set_long("This is a road heading north on a general incline high "
    + "up into the\nrolling hills.  To the south, the road leads to a "
    + "cornerstone.  There is\nsnow all around, and it seems to be "     
    + "colder.\n");

   add_item(({"snow"}), "It makes you want to build a snowman.\n");

   add_item(({"hills", "rolling hills"}), "These hills go for as far as " 
    + "the eye can see.\n");
   add_exit("/d/Terel/common/road/cornerstone", "south", 0);
   add_exit("/d/Terel/common/road/road10", "north", 0, 3);
reset_room();
}

