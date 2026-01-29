#include "/d/Ansalon/goodlund/nethosak/city/local.h"
#include <stdproperties.h>
inherit MITHAS_IN;

object seer;

void 
reset_mithas_room()
{
    if(!objectp(seer))
    {
      seer = clone_object(MNPC + "dawn");
      seer -> move(this_object());
   }
}
void
create_mithas_room()
{
   set_short("Dawn's wagon");
   set_long("@@long_descr");

   add_exit(MROOM + "wagon1","out","@@guard_exit",0); 
   reset_mithas_room();
}

string
long_descr()
{ 
   return "You are standing inside an old wagon. The smell "+
    "of dust and moisture fills the air. The entire "+
    "wagon consists of only one room, where a large "+
    "crystal ball dominate the center of it. A few "+
    "shelves has been build next to the western "+
    "wall and several jars and vials have been "+
    "placed on them. A thick wool carpet is lying on "+
    "the floor and a brass lamp covers the room in "+
    "a warm yellow glow.\n";
}

int
guard_exit()
{
   write("You carefully open the wooden door, and leave the wagon.\n");
   return 0;
}

