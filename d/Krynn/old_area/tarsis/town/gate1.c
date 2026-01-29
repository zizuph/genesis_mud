/* Gates of Tarsis */

#include "/d/Krynn/common/defs.h" 
#include "/d/Krynn/tarsis/local.h"   

#define LIV_PATH "/d/Krynn/solamn/splains/living/"

inherit OUTROOM

object guard1, guard2, guard3, guard4, commander;

void
reset_tarsis_room()
{
	if(!guard1)
		{
		guard1=clone_object(LIV_PATH + "kapak.c");
		guard1->move(TO);
		}
	if(!guard2)
		{
		guard2=clone_object(LIV_PATH + "kapak.c");
		guard2->move(TO);
		}
	if(!guard3)
		{
		guard3=clone_object(LIV_PATH + "sivak.c");
		guard3->move(TO);
		}
	if(!guard4)
		{
		guard4=clone_object(LIV_PATH + "sivak.c");
		guard4->move(TO);
		}
	if(!commander)
		{
		commander=clone_object(LIV_PATH + "aurak.c");
		commander->move(TO);
		}
}

create_tarsis_room()
{
    set_short("Main Gates of Tarsis.\n");
    set_long("You are standing in front of the mighty gate of Tarsis. The walls around " +
	"this city are about 20 feets high and you can see the guard towers high above them. " +
	"This city must have been unbreachable before the cataclysm, when it had a sea west " +
	"of it. Now it is only remains left of it.\n");  

    add_item("gate", "This huge gate is splittered and you can see that something has " +
		"burned it severely.\n");
    add_item("tower", "You can see that some of the towers are crashed. You wonder, what kind " +
	"of strenght you need to break a tower like those.\n");

    add_exit(TOWN + "tarsis1", "south");
    add_exit(TOWN + "trail1", "north");
    reset();
}


