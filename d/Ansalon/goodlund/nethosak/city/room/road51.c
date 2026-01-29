#include "/d/Ansalon/goodlund/nethosak/city/local.h"
#include <stdproperties.h>
inherit MITHAS_OUT;

void
create_mithas_room()
{
    set_short("Northern road in Nethosak");
    set_long("@@long_descr"); 
   
    add_exit(MROOM + "road52","east",0);
    add_exit(MROOM + "road50","west",0);      
   
}

string
long_descr()
{ 

   return tod_descr()+
   "The road here is paved with small rocks, and the buildings "+
   "are made out of grey stones. A large stone statue decorate "+
   "the center of the street here. It's covered with moss and "+
   "partly eroded. To the northeast a huge building "+
   "has been build, and you realize that it must be where the "+
   "minotaur Emperor lives. "+
   "The road continues to the east towards the main gate to the "+
   "palace and to the west."+
   season_descr()+ "\n";

}


