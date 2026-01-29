// file name:     barrow12.c
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
	    +" A faint breeze wafts toward you from the southeast, carrying " 
		+"with it the scent of the moors. "+gob_desc2[random(sizeof(gob_desc2))]);

    gob_exit("3","northwest");
    gob_exit("13","east");
    gob_exit("11","west");
    gob_exit("0", "southeast");
    reset_domain_room();
}
void
reset_domain_room()
 {
    set_searched(0);   ::reset_domain_room();
 }
