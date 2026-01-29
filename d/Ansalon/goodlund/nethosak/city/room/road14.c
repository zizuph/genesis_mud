#include "/d/Ansalon/goodlund/nethosak/city/local.h"
#include <stdproperties.h>
inherit MITHAS_OUT;

void
create_mithas_room()
{
    set_short("Main Street in Nethosak");
    set_long("@@long_descr"); 

    add_item(({"volcano","volcanos"}), "The "+
          "four great peeks are located far to the south, you "+
          "think you can see something flying near them.\n");

    add_exit(MROOM + "road13","west",0);
    add_exit(MROOM + "road15","east",0);

}

string
long_descr()
{ 

   return tod_descr()+ "You are standing on the main "+
          "street in the city of Nethosak. The road "+
          "here is paved with small rocks, and the buildings "+
          "are made out of grey stones. The road continues to west "+
          "and east where you notice a large intersection."+
          season_descr()+ "\n";

}

