#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/taman_busuk/neraka/local.h"

/* Carridin */

inherit OUTER_OUT;

void
create_neraka_room()
{
	set_short("A road in the Red Quarter");
    set_extra_long("You stand upon a small dirt road lined by wooden " +
    	"sidewalks. The road leads northwest towards the Green Quarter " +
		"while to the northeast it bends towards the center of the Red " +
		"Quarter.");
	set_quarter(RED);
    add_item_dirtroad();
    add_item_sidewalks();
    add_item_buildings();
    
    add_exit(NOUTER+"red/r14","northwest",0,0,0);
    add_exit(NOUTER+"red/r15","northeast",0,0,0);
}

