#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/taman_busuk/neraka/local.h"

/* Carridin */

inherit OUTER_OUT;

void
create_neraka_room()
{
	set_short("A road in the Red Quarter");
    set_extra_long("You stand upon a small dirt road lined by wooden " +
    	"sidewalks. The road leads west towards the Green Quarter, " +
		"while just east of here, it meets another road.");
	set_quarter(RED);
    add_item_dirtroad();
    add_item_sidewalks();
    add_item_buildings();
    
    add_exit(NOUTER+"red/r9","west",0,0,0);
    add_exit(NOUTER+"red/r6","east",0,0,0);
}

