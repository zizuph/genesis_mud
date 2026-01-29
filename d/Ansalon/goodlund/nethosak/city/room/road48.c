#include "/d/Ansalon/goodlund/nethosak/city/local.h"
#include <stdproperties.h>
inherit MITHAS_OUT;

void
create_mithas_room()
{
    set_short("Near the Adventures Guild");
    set_long("@@long_descr"); 

    add_item(({"volcano","volcanos"}), "The "+
          "four great peeks are located far to the south, you "+
          "think you can see something flying near them.\n");

    add_exit(MROOM + "ad_guild","east",0);
    add_exit(MROOM + "road3","north",0);
    add_exit(MROOM + "road47","south",0);    
   
}

string
long_descr()
{ 

   return tod_descr()+ "You are standing on a "+
          "street in the city of Nethosak. The road "+
          "here is paved with small rocks, and the buildings "+
          "are made out of grey stones. The road continues to the north "+
          "towards an intersection, and to the south further into the "+
          "city. To the east you notice the local adventures guild, where "+
          "travellers come to learn new skills and improve the old ones. "+    
          random_descr()+ " " +season_descr()+ "\n";

}

