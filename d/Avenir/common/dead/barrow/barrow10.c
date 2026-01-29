// file name:     barrow10.c
// creator(s):    Lilith, Aug 2021
// last update:
// purpose:       Camp for goblins working in the catacombs
// note:          This is their trash chute. It empties into 
//                 the Pit of Despair in the catacombs
// bug(s):
// to-do:

inherit "/d/Avenir/common/dead/barrow_base";
#include "../dead.h"

void
create_barrow_room()
{
/* most details are in dead.h */
    gob_long(gob_desc[random(sizeof(gob_desc))] 
	    +" "+ gob_desc2[random(sizeof(gob_desc2))]
		+" There is a terrible stench here, a smell so awful it "
		+"makes your eyes water and your throat start to close. "
		+"It seems to emanate from a hole in the floor.");
    add_item(({"hole", "hole in the floor"}), "It is darker than "
	   +"dark, a hole that appears to have no end. And though "
	   +"you are certain it does end, you aren't sure you want "
	   +"find out where. If you do, there is only one way to "
	   +"find out. Jump!\n");
// add exit to falling and the pit of despair.
    gob_exit("1","northeast");
    add_exit(CRYPT+"pit_falling", "down", 0, 0, 1);
    add_exit(CRYPT+"pit_falling", "hole", 0, 0, 1);
    add_exit(CRYPT+"pit_falling", "climb", 0, 0, 1);
    add_exit(CRYPT+"pit_falling", "jump", 0, 0, 1);
    add_exit(CRYPT+"pit_falling", "enter", 0, 0, 1);  
    reset_domain_room();
}

void
reset_domain_room()
{
    set_searched(0);   ::reset_domain_room();
}
