#include "/d/Ansalon/goodlund/nethosak/city/local.h"
#include <stdproperties.h>
inherit MITHAS_OUT;

void
create_mithas_room()
{
    set_short("South of the Imperial Castle");
    set_long("@@long_descr"); 
   
    add_exit(MROOM + "road54","east",0);
    add_exit(MROOM + "road68","west",0);
    add_exit(MROOM + "road60","south",0);      
   
}

string
long_descr()
{ 

   return tod_descr()+
   "The road here is paved with small rocks, and the buildings "+
   "are made out of grey stones. Heavy stone statues dominate "+
   "these roads, they have been placed alongside the road with "+
   "some trees and a few bushes. A bit to the east, a large "+
   "iron gate prevents passage to the castle. The road stretches "+
   "itself to the east towards the gate, to the west and to the "+
   "south towards the center of Nethosak. "+
   season_descr()+ "\n";

}
