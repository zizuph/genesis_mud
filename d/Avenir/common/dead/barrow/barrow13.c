// file name:     barrow13.c
// creator(s):    Lilith, Aug 2021
// last update:
// purpose:       Camp for goblins working in the catacombs
// note:
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
		+" This is where two large, broad chambers seem to "
		+"intersect. A puff of fresh air comes from the south.");

    gob_exit("5","north");
    gob_exit("0","south");
    gob_exit("12","west");
    gob_exit("14","east");

    reset_domain_room();
}
void
reset_domain_room()
 {
    set_searched(0);   ::reset_domain_room();
 
 }
