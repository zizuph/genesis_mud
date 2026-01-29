#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/taman_busuk/neraka/local.h"

/* Carridin */

inherit OUTER_OUT;

void
create_neraka_room()       
{
	set_short("A road in the Red Quarter, just north of the market square");
    set_extra_long("Here, a road branches off to the west, while the marketplace " +
        "lies due south of here. You can see many merchants and soldiers " +
        "crowding the area.  Even further south lies the Red Dragon Army camp.");
    set_quarter(RED);
    add_item("marketplace","The marketplace lies just south of here with it's various " +
		"shops and establishments.");
    add_item("merchants","The square suffers no lack of merchants and peddlers.\n");
    add_item_dirtroad();
    add_item_sidewalks();
    add_item_buildings();
    
    add_exit(NOUTER+"red/r5","north",0,0,0);
    add_exit(NOUTER+"red/r24","west",0,0,0);
    add_exit(NOUTER+"red/r7","south",0,0,0);
}

