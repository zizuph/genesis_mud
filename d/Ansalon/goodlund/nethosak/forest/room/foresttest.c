#include "/d/Ansalon/goodlund/nethosak/forest/local.h"
#include "/d/Ansalon/common/defs.h"
#include <stdproperties.h>
#include <macros.h>

inherit MITHAS_OUT;

void
create_mithas_room()
{
     set_short("Underground workroom");
     set_long("You are standing in a underground workroom. "+
       "This is a VERY messy room, there are "+
        "scrolls and parchments all over the floor. "+
        "The eastern part of the room is covered by "+
        "a furry carpet, you almost feel the urge to "+ 
        "crawl down to take a nap. A big and decorated "+
        "desk are located on the western wall.\n");

     add_item(({"scrolls", "parchments"}), "The scrolls and "+
		"parchments are blueprints of architectural and "+
		"mechanical scructures.\n");
     add_item("carpet", "The carpet are big and furry.\n");
     add_item("desk","The desk are decorated with various "+
		 "symbols and signs. You notice a small drawer on "+
		 "the right side.\n");
    add_item("drawer","It's a ordinary drawer used for\n");
    add_search(({"desk"}),10,"search_desk",1);
}

string
long_descr()
{ 
    return tod_descr()+ "" +season_descr()+
    "You stand within a gloomy forest in the southern part of "+
    "Mithas. The air here is filled with the smell of "+
    "decomposing wood and leaves. Only a few trees are left "+
    "here, most of them have died. Their rotten logs lie all "+
    "over the place, all of them filled with moss and fungus.\n";
}




string
search_desk(object searcher, string str)
{
    if (CAN_SEE_IN_ROOM(this_player()))
      {
          if (str == "desk")
            {
                return ("you find a old tattered scroll.\n");
            }
      }
  return 0;
}

