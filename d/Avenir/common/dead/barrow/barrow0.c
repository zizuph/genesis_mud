// file name:     barrow0.c
// creator(s):    Lilith, Aug 2021
// last update:
// purpose:       Camp for goblins working in the catacombs
// note:
// bug(s):
// to-do:

inherit "/d/Avenir/common/dead/barrow_base";
#include "/d/Avenir/smis/sys/statserv.h"
#include "../dead.h"
void
create_barrow_room()
{
    gob_long(gob_desc[random(sizeof(gob_desc))] 
	    +" "+ gob_desc2[random(sizeof(gob_desc2))]
	    +" Puffs of fresh air flow past you through the gap "
		+"between two stones southeast of you.");

	gob_exit("12","northwest");
	gob_exit("13","north");
	gob_exit("14","northeast");
	add_exit(MARSH +"marsh70", "southeast");
    reset_domain_room();
}

void
reset_domain_room()
{
    set_searched(0);   ::reset_domain_room();
}

void 
enter_inv(object ob, object from)
{

    ::enter_inv(ob, from);
	
	if (!interactive(ob))
		return;
    STATSERV_LOG_EVENT("necronisi", "Barrow entered");
}