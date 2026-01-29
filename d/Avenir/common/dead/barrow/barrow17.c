// file name:     barrow17.c
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
    gob_long("There is a slab in the center of the room, "
	+"but the remains that would normally be resting there "
    +"are missing. "+ gob_desc[random(sizeof(gob_desc))] 
	    +" "+ gob_desc2[random(sizeof(gob_desc2))]);
    add_item(({"slab", "stone slab"}), "It is a long, low "
	    +"stone slab, the kind that corpses and coffins are "
		+"usually placed on.\n");
    gob_exit("4","south");
    reset_domain_room();
}
void
reset_domain_room()
 {
    set_searched(0);   ::reset_domain_room();
 }
