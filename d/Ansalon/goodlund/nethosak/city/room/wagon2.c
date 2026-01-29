#include "/d/Ansalon/goodlund/nethosak/city/local.h"
#include <stdproperties.h>
inherit MITHAS_OUT;

object smith;

void 
reset_mithas_room()
{
   if(!objectp(smith))
   {
      smith = clone_object(MNPC + "wep_smith");
      smith->move(this_object());
   }
}

void
create_mithas_room()
{
    set_short("Weapon smith's wagon");
    set_long("@@long_descr"); 
    add_exit(MROOM + "square1","back",0);

    add_item(({"sign"}),"The sign reads:\n"+
    "----------------------------------------------------------\n"+
    "| Here you can 'order' weapons or 'collect' them if you  |\n"+
    "| already have ordered one. The weapons can be made out  |\n"+
    "| of these materials:Bronze, Iron, Silver, Gold, Steel   |\n"+
    "| and Tempered.                                          |\n"+
    "| You can also choose between these blades:Short, Broad, |\n"+
    "| Long and Serrated.                                     |\n"+
    "| If you for example wish to order a sword, you could    |\n"+
    "| 'order sword from steel with broad blade'              |\n"+
    "----------------------------------------------------------\n");
    reset_mithas_room();
}

string
long_descr()
{ 
   return tod_descr()+
    "You are standing next to a small wooden wagon in "+
    "the market square of Nethosak. The wagon looks "+
    "like is has been here for many years, and thick "+
    "green grass cover the wheels of the wagon. A long "+
    "red cloth covers the entrance to the wagon, "+
    "preventing you from going that way. A small tent "+
    "has been build next to the entrance to provide some "+
    "shade from the sun. You can always go back to the "+
    "market square again. A huge iron anvil rest on a wooden "+
    "block, and a barrel filled with water stands next to it "+
    season_descr()+ "\n"+
    "A sign has been placed here.\n";
}


