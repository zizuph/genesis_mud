#include "/d/Ansalon/goodlund/nethosak/city/local.h"
#include <stdproperties.h>
inherit MITHAS_OUT;

void
create_mithas_room()
{
    set_short("Northern road in Nethosak");
    set_long("@@long_descr"); 
   
    add_exit(MROOM + "road58","north",0);
    add_exit(MROOM + "road15","south",0);     
   
}

string
long_descr()
{ 

    return tod_descr()+ "You are standing on "+
         "a crowded road in the city of Nethosak. "+
         "The road here is made out of grey stone "+
         "the different minotaur buildings that towers "+
         "up on both sides of the street, are all made "+
         "out of the same stone, making it seem like "+
         "the road and the buildings have been fused together "+
         "The road continues to the north and south. "+
         season_descr()+ "\n";
}


