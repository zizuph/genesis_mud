#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/taman_busuk/neraka/local.h"

/* Carridin */

inherit OUTER_OUT;

object soldier1,soldier2;
void reset_neraka_room();

void
create_neraka_room()
{
	set_short("A road in the Red Quarter");
    set_extra_long("You stand upon a small dirt road lined by wooden " +
    	"sidewalks. South of here, you can see a westward branch and further " +
    	"down the road the square and the Red Dragon Army camp, while " +
    	"north will take you to the inner city.");
	set_quarter(RED);
    add_item_dirtroad();
    add_item_sidewalks();
    add_item_buildings();

    add_exit(NOUTER+"red/r4","north",0,0,0);
    add_exit(NOUTER+"red/r6","south",0,0,0);
    reset_neraka_room();
}

void
reset_neraka_room()
{
    if(!soldier1)
        soldier1 = clone_npc(NNPC+"humsoldier","red");
    if(!soldier2)
    {
    	soldier2 = clone_npc(NNPC+"humsoldier","red");
    	soldier1->team_join(soldier2);    	
    }
}

