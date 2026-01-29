#include "/d/Ansalon/goodlund/nethosak/forest/local.h"
#include "/d/Ansalon/common/defs.h"
#include <stdproperties.h>
inherit MITHAS_IN;

object dragon;

void
reset_mithas_room()
{
   if(!objectp(dragon))
   {
      dragon = clone_object(MNPC + "b_dragon");
      dragon->move(this_object());
   }
}

void
create_mithas_room()
{
    set_short("Dark swampy cave");
    set_long("@@long_descr"); 

    add_exit(MROOM + "swamp2","out",0);

   add_exit(MROOM + "main_cave","east","@@main_cave_entry", 0);

    add_item(({"walls", "wall"}),
      "The walls here consists of walls and dried mud, that "+
      "is held together by strong roots. The walls that leads "+
      "further into the cave, seems to be made completely out of "+
      "stone, and looks much more stable.\n");

    add_item(({"root","roots"}),
      "The roots here are from the tall trees from above. Some of "+
      "them are rotten but most of them looks quite heathy.\n");

    add_item(({"bones","wolves", "deers", "floor"}),
      "The different bones here that cover the floor must be from "+
      "the poor creatures that has fallen down here from the "+
      "forest above.\n");

    reset_mithas_room();
}

string
long_descr()
{ 
    return
    "You find yourself inside in an underground cave. This place smells "+
    "very rotten and a strong stench of sulphur fills the motionless air. "+
    "Above you the ceiling is filled with stalactites and water continuously "+
    "falls down from above. The floor here is littered with leaves and "+
    "bones of deers and wolves. The cave continues further downwards to the "+
    "east.\n";
}

int
main_cave_entry()
{
   if(objectp(dragon) && E(dragon) == this_object())
   {
       write("It is impossible to sneak past the black dragon.\n");
       return 1;
   }
   write ("You quickly move further into the cave.\n");
   return 0;
}
