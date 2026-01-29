#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/taman_busuk/neraka/local.h"

/* Carridin */

inherit OUTER_OUT;

object ob;

void
reset_neraka_room()
{
    if(!ob)
        ob = clone_npc(NNPC + "baaz","red");
}

void
create_neraka_room()
{
	set_short("Market square in the Red Quarter");
    set_extra_long("You are in the center of the market square. " +
    	"Apart from the merchants who wander the marketplace, various shops " +
		"and establishments line the square. Looking west, you spot a purveyor " +
		"of exotic animals as well as a smithy, while eastwards you find the local " +
		"pub. Somewhat south of here lies a pawnshop as well a jewelry shop.");
	set_quarter(RED);
    add_item_sidewalks();
    add_item_buildings();
    add_item_market("square");

    add_exit(NOUTER+"red/r7","north",0,0,0);
    add_exit(NOUTER+"red/r13","east",0,0,0);
    add_exit(NOUTER+"red/r16","south",0,0,0);
    add_exit(NOUTER+"red/r11","west",0,0,0);
    reset_room();
}



