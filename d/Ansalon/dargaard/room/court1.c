
/************************************************************
 * Area: Dargaard Keep.
 * By  : Ruben
 * Date: August 2001
 * Desc: court1
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
              " The structure is imposing and must have once both been"+
              " practical and beautiful. The castle is blackened"+
              " as the courtyard's walls. The strange sounds you have"+
              " heard earlier are more audible now. However, you"+
              " can not locate their origin."+
              " West of you is the main entrance to the castle."+
              " To the southeast and southwest the courtyard continues.\n");

    add_exit(DROOM + "court2","east",0);
    add_exit(DROOM + "court5","southeast",0);	
    add_exit(DROOM + "court4","southwest",0);



    add_item(({"wall", "walls", "castle"}),
      "The castle seems to be affect by the environment as well. Some of the finer ornaments"+
      " and structures have partly crumbled. Some of the outcroppings are the homes of "+
      " several plants. However, there are no animals like birds nearby.\n");

    reset_dargaard_room();
}


