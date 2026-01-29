#include "/d/Ansalon/goodlund/nethosak/city/local.h"
#include <stdproperties.h>
inherit MITHAS_OUT;

void
create_mithas_room()
{
    set_short("Northern road in Nethosak");
    set_long("@@long_descr"); 
   
    add_exit(MROOM + "road56","northwest",0);
    add_exit(MROOM + "road58","southeast",0);     
   
}

string
long_descr()
{ 
   return tod_descr()+
   "The road here is paved with small rocks, and the buildings "+
   "are made out of grey stones. Heavy stone statues dominate "+
   "these roads, they have been placed alongside the road with "+
   "some trees and a few bushes. "+
   "The road continues to the northwest to the northern part "+
   "of the city and southeast further down the road. "+
   season_descr()+ "\n";

}

