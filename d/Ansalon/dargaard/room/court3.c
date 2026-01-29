
/************************************************************
 * Area: Dargaard Keep.
 * By  : Ruben
 * Date: August 2001
 * Desc: court3
 *
 *
 *
 ************************************************************/


/**  DARGAARD OUTSIDE ROOM **/

#include "/d/Ansalon/dargaard/local.h"
#include "/d/Ansalon/common/defs.h"
#include <stdproperties.h>

inherit DARGAARD_OUT;

object zombie;


void
reset_dargaard_room()
{
   if(!objectp(zombie))
   {
      zombie = clone_object(DNPC + "zombie");
      zombie->move(TO);
   }
}

void
create_dargaard_room()
{
    set_short("Northwestern part of the Courtyard of Dargaard Keep");
    set_long(tod_descr()+ "" +season_descr()+ "You are in the courtyard"+
 		             " of Dargaard Keep, standing in front of the main castle"+
		             " The structure is imposing and must have once been"+
		             ", both practical and beautiful. The walls are blackened"+
		             " as the courtyard's walls. The strange sounds you have"+
		             " heard earlier are more audible now. However, you"+
		             " cannot locate their origin. "+
	 	             "The courtyard continues to the west, southwest and southeast.\n"); 

    add_exit(DROOM + "court2","west",0);
    add_exit(DROOM + "court5","southwest",0);	
    add_exit(DROOM + "court6","southeast",0);



    add_item(({"wall", "walls", "castle"}),
      "The castle seems to be affect by the environment as well. Some of the finer ornaments"+
      " and structures have partly crumbled. Some of the outcroppings are the homes of "+
      " several plants. However, there are no animals like birds nearby.\n");

    reset_dargaard_room();
}


