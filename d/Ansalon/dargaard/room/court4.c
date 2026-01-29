
/************************************************************
 * Area: Dargaard Keep.
 * By  : Ruben
 * Date: August 2001
 * Desc: court4
 *
 *
 *
 ************************************************************/


/**  DARGAARD OUTSIDE ROOM **/

#include "/d/Ansalon/dargaard/local.h"
#include "/d/Ansalon/common/defs.h"
#include <stdproperties.h>

inherit DARGAARD_OUT;

object wraith;


void
reset_dargaard_room()
{
}

void
create_dargaard_room()
{
    set_short("Western part of the Courtyard of Dargaard Keep");
    set_long(tod_descr()+ "" +season_descr()+ "You are in the western part of the courtyard"+
             " of Dargaard Keep."+
             " Next to you are the blackened walls. Stairs, however now crumbled"+
             " and impassable, line in regular intervalls the mighty structure."+
             " In some place grow moss and sickly-looking plants."+
             " The courtyard continues to the east and northeast."+
             " To the southeast is the castle's main gate to the"+
             " wilderness.\n"); 

    add_exit(DROOM + "court7","southeast",0);
    add_exit(DROOM + "court1","northeast",0);
    add_exit(DROOM + "court5","east",0);	

    add_item(({"wall"}),
      "The wall is covered with soot of a huge fire. Awkwardly you cannot scrap it of the"+
      " wall's stones.\n");

     add_item(({"stairs", "stair"}),
      "Heavily damaged by the fire the stairs weren't able to withstand the rough environment"+
      " all these centuries. Climbing these walls would be suicide.\n");

    reset_dargaard_room();
}


