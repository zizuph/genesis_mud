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

    add_item(({"sign"}), "The sign reads: "+
          " -- The Imperial Armour Smith of Nethosak --\n");

    add_exit(MROOM + "road8","west",0);
    add_exit(MROOM + "road10","east",0);
    add_exit(MROOM + "armour_smith","north",0);        
   
}

string
long_descr()
{ 

   return tod_descr()+ "You are standing on the main "+
          "street in the city of Nethosak. The road "+
          "here is paved with small rocks, and the buildings "+
          "are made out of grey stones. The road continues to west "+
          "and east. Far the west you spot seaguls flying high "+
          "above the pier and to the south and west, beyond the "+
          "city you notice the four big volcano's." +random_descr()+
          " " +season_descr()+ "To the north a a large stone house "+
          "has been build. There's a sign here, above the door.\n";

}


