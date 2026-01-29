// file name:     barrow16.c
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
	    +" This appears to be an individual tomb "
		+"that was converted into a private chamber "
        +"for some of the residents. "+
		gob_desc2[random(sizeof(gob_desc2))]);


    gob_exit("2","south");

    reset_domain_room();  
}

void
reset_domain_room()
{
    set_searched(0);   ::reset_domain_room();
}
