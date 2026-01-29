// file name:     barrow11.c
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
		+" This is a private little room in the western end "
		+"of a wide central chamber.");
		
    gob_exit("12","east");

    reset_domain_room();
}
void
reset_domain_room()
 {
    set_searched(0);   ::reset_domain_room();
 }
