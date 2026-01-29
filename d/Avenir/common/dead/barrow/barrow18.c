// file ngob_exite: marsh18
// creator(s): Ilyian (24 August, 1995)
// last update:
// purpose:
// note:
// bug(s):
// to-do:

inherit "/d/Avenir/common/dead/barrow_base";
#include "../dead.h"

create_barrow_room()
{
/* most details are in dead.h */
    gob_long(gob_desc[random(sizeof(gob_desc))] 
	    +" This area appears to have been intended as place "
		+"of eternal rest, but it looks like a few people "
		+"use it for sleeping. "+ gob_desc2[random(sizeof(gob_desc2))]);


    gob_exit("6","south"); 

    reset_domain_room();
}
void
reset_domain_room()
 {
    set_searched(0);   ::reset_domain_room();
 }
