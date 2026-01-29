
/************************************************************
 * Area: Dargaard Keep.
 * By  : Ruben
 * Date: August 2001
 * Desc: court7 
 *
 *
 *
 ************************************************************/


/**  DARGAARD OUTSIDE ROOM **/

#include "/d/Ansalon/dargaard/local.h"
#include "/d/Ansalon/common/defs.h"
#include <stdproperties.h>

inherit DARGAARD_OUT;

object skeleton;


void
reset_dargaard_room()
{
   if(!objectp(skeleton))
   {
      skeleton = clone_object(DNPC + "skeleton");
      skeleton->move(TO);
   }
}

void
create_dargaard_room()
{
    set_short("Southwestern part of the Courtyard of Dargaard Keep");
    set_long(tod_descr()+ "" +season_descr()+ "You are in the courtyard"+
 		             " of Dargaard Keep. The black walls and ramparts"+
  		             " loom over you. Suddenly you feel very small and"+
  		             " vulnerable."+
	 	             " The area is filled with rubble and debris. However,"+
     		         " fresh tracks and paths in the rubble clearly show"+
		             " that someone is inhabiting the castle. Strange sounds"+
 		             " can be heard, carried to you on the seemingly, ever-blowing"+
		             " wind."+
		             " The courtyard extends to the northeast, northwest and east."+
		             " To the southeast is the castle's main gate to the"+
		             " mountains.\n"); 

    add_exit(DROOM + "court4","northwest",0);
    add_exit(DROOM + "court5","northeast",0);
    add_exit(DROOM + "court8","east",0);	
    add_exit(DROOM + "court0","southeast",0);



    add_item(({"rubble", "debris", "courtyard"}),
      "The courtyard is littered by rocks and pieces of old, rotting wood."+
      " Some of the chunks of rock seems to have been moved lately in "+
      " order to create small paths. For whom or what you do not know "+
      " nor can you guess.\n");

    reset_dargaard_room();
}
