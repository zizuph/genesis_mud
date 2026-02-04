// modifications:
// Lilith Jan 2022: updated room desc

inherit "/std/room";
#include "/d/Terel/common/terel_defs.h"
#define PATH "/d/Terel/LoD/monster/"

object monster;

reset_room()
{
    if(present("warrior"))return;
    monster=clone_object(PATH + "elf_grunt");
    monster->equip_actions();
    monster->move(this_object());
    monster=clone_object(PATH + "elf_grunt");
    monster->equip_actions();    
    monster->move(this_object());
}

create_room() {

    set_short("Road");
   set_long("This is a road heading north on a steep incline high "
    + "up into the rolling hills. There is snow all around, and it "
    + "seems to grow colder with every step you take north. To "
    + "the south, the road leads to a cornerstone, and safety.\n");

   add_item(({"snow"}), "It makes you want to build a snowman.\n");

   add_item(({"hills", "rolling hills"}), "These hills go for as far as " 
    + "the eye can see.\n");
	
   add_exit("/d/Terel/common/road/cornerstone", "south", 0);
   add_exit("/d/Terel/common/road/road10", "north", 0, 3);
reset_room();
}

