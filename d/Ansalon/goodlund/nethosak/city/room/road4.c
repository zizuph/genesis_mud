#include "/d/Ansalon/goodlund/nethosak/city/local.h"
#include <stdproperties.h>
inherit MITHAS_OUT;

void
create_mithas_room()
{
    set_short("Near the board in Nethosak");
    set_long("@@long_descr"); 
   
    add_exit(MROOM + "road5","north",0);
    add_exit(MROOM + "board_room","east",0);
    add_exit(MROOM + "road3","south",0);    
    
   
}

string
long_descr()
{ 

   return tod_descr()+ "You are standing on "+
          "a road in the city of Nethosak. To "+
          "the east, a large board has been placed, "+
          "and to the north the road continues. Far "+
          "to the south tall trees and a few mountain "+
          "peaks can be seen. " +season_descr()+ "\n";

}

