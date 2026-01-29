// file name:     barrow2.c
// creator(s):    Lilith, Aug 2021
// last update:
// purpose:       Camp for goblins working in the catacombs
// note:
// bug(s):
// to-do:


inherit "/d/Avenir/common/dead/barrow_base";
#include "../dead.h"

create_barrow_room()
{
/* most details are in dead.h */
    gob_long(gob_desc[random(sizeof(gob_desc))] 
	    +" "+ gob_desc2[random(sizeof(gob_desc2))]);

    gob_exit("3","east");
    gob_exit("1","west");
	gob_exit("16","north");
    reset_domain_room();
}
void
reset_domain_room()
{
    set_searched(0);   ::reset_domain_room();
}
