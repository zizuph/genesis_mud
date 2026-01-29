// Navarre May 6th 2009, fix non-resetting quest item.

#include "/d/Ansalon/goodlund/nethosak/forest/local.h"
#include "/d/Ansalon/common/defs.h"
#include <stdproperties.h>
#include <macros.h>
inherit MITHAS_IN;
inherit "/lib/unique.c";

object chest,treasure;

void
reset_mithas_room()
{
   if(!objectp(chest))
   {
      chest = clone_object(MOBJ + "chest");
      chest->move(TO);
   }
   if(!present(treasure, chest))
   {
       treasure = clone_unique(MWEP + "seeker",2,MWEP + "seeker2",0,100);
       treasure->move(chest,1);
   }
}


void
create_mithas_room()
{
    set_short("Dark hole");
    set_long("@@long_descr"); 

    add_prop(ROOM_I_LIGHT,0);
    add_prop(ROOM_M_NO_TELEPORT, 1);
    add_prop(ROOM_M_NO_TELEPORT_TO, 1);
    add_prop(ROOM_M_NO_TELEPORT_FROM, 1);

    add_item(({"stones","walls", "wall"}),
      "The walls looks very old, there's a small "+
      "hole in the side of the wall here.\n");

    add_cmd_item(({"hole"}),({"crawl", "enter"}),
      "@@enter_hole");
    reset_mithas_room();
}

string
long_descr()
{ 
    return
    "You are standing in a small natural made cave beneath "+
    "the forest of Mithas. Thick roots from the trees above "+
    "have made their way down here, and they form an "+
    "impressive ceiling. This place is quite empty, except for "+
    "a heavy iron and oak chest in the middle of the room.\n";
}

int
enter_hole()
{
    TP->move_living("crawls into a small hole in the wall",MROOM + "cellar",0,0);
    return 1;
}
