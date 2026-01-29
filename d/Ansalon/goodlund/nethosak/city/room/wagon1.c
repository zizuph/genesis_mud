#include "/d/Ansalon/goodlund/nethosak/city/local.h"
#include "/d/Ansalon/common/defs.h"
#include <stdproperties.h>
inherit MITHAS_OUT;

void
create_mithas_room()
{
    set_short("Next to an old rotten wagon");
    set_long("@@long_descr");  
    add_exit(MROOM + "square1","back",0);
    add_cmd_item("door",({"enter","open"}),"@@enter_wagon");
    add_item(({"sign"}),"The sign is decorated with a large "+
                        "eye. Below the eye the words: "+
                        "'Lady Dawn the Fortune Teller' "+
                        "has been written.\n");

}

string
long_descr()
{ 
   return tod_descr()+
   "You are standing next to a old wooden wagon. "+
   "The tall grass surrounding the wagon has been "+
   "trampled down making a small path towards the "+
   "door. On both sides of the wagon two dusty "+
   "windows makes it possible for the inhabitant "+
   "to glance out at the rest of the marketsquare. "+
    season_descr()+ "\n"+
    "A sign adorns the side of the wagon.\n";
}

string
enter_wagon()
{
    write("You open the rotten oakwood door and step into " +
      "the wagon.\n");
    TP->move_living("into the wagon",
      MROOM + "wagon_inside.c",1,0);
    return "";
}
