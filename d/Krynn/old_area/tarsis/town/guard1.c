#include "/d/Krynn/common/defs.h" 
#include "/d/Krynn/tarsis/local.h"   
#include <macros.h>

#define LIV_PATH "/d/Krynn/solamn/splains/living/"

inherit  INROOM

object kapak, kapak1, sivak;

void
reset_tarsis_room()
{
	if (!kapak) 
		{	
		kapak=clone_object(LIV_PATH + "kapak.c");
		kapak->move(TO);
		}
	if (!kapak1)
		{
		kapak1=clone_object(LIV_PATH + "kapak.c");
		kapak1->move(TO);
		}
	if (!sivak)
		{
		sivak=clone_object(LIV_PATH + "sivak.c");
		sivak->move(TO);
		}		
}


create_tarsis_room()
{
    set_short("Guardroom of Tarsis.\n");
    set_long("You are now standing inside a guardroom. This is the place where the guard " +
	"force sleeps and eats, while they are on duty. In the middle of the room are a desk " +
	"and along the walls there are several beds.\n");  

    
    add_item("desk","This desk is almost crushed. You understand that there must have been a " +
	"fight in here.\n");
    add_item(({"beds","bed"}),"Theese beds seem to be recently used, but all sheets and blankets " +
	"are removed and there are hay laying in them instead.\n");   
    add_exit(TOWN + "tarsis1", "west");
    reset(); 
}


