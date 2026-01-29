#include "/d/Ansalon/goodlund/nethosak/city/local.h"
#include <stdproperties.h>
inherit MITHAS_OUT;

object dwarf;

void 
reset_mithas_room()
{
    if(!objectp(dwarf))
    {
      dwarf = clone_object(MNPC + "female_g_dwarf");
      dwarf->move(this_object());
   }
}

void
create_mithas_room()
{
    set_short("Main Street in Nethosak");
    set_long("@@long_descr"); 

    add_item(({"volcano","volcanos"}), "The "+
          "four great peeks are located far to the south, you "+
          "think you can see something flying near them.\n");

    add_exit(MROOM + "road11","west",0);
    add_exit(MROOM + "road13","east",0);    
    reset_mithas_room();
}

string
long_descr()
{ 

   return tod_descr()+ "You are standing on the main "+
          "street in the city of Nethosak. The road "+
          "here is paved with small rocks, and the buildings "+
          "are made out of grey stones. The road continues to west "+
          "and east. Loud chatter can be heard from the east, where "+
          "a large marketplace has been build. Far to the east you "+
          "see the great plains and forests that surround this "+
          "city." +season_descr()+ "\n";

}

