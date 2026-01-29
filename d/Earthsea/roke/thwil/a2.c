#include "defs.h"
inherit THWIL_BASE_ROOM;

#define ROPE THWIL+"obj/rope"

int rope_found = 0;

void create_thwil_room()
{
   set_short("Alley");
   set_long("This is an alley in Thwil. Eastwards the alley "+
      "continues for some 50 meters before it ends in the harbour. "+
      "Southwards the city begins. "+
      "The air is cold and damp. There's a feeling of "+ 
      "magic surrounding you. "+
      "There's a trash can standing against the north wall.\n");
    add_item(({"wall", "walls", "north wall"}), "The walls of the " +
        "storage buildings rise towards the sky.\n");
   add_item(({"trash can", "can", "barrel", "litter", "trash"}),
	    "It's a barrel filled with litter.\n");
    add_item(({"building", "buildings", "storage building",
        "storage buildings", "warehouse", "warehouses"}),
        "The alley is surrounded by several small warehouses, " +
        "obviously servicing the port area.\n");
   
   add_exit(THWIL + "ta" , "south" , 0);
   add_exit(THWIL + "a3" , "east" , 0);

   add_prop(OBJ_S_SEARCH_FUN, "find_rope");
   add_prop(OBJ_I_SEARCH_TIME, 3);
 
   STREET;
}

public void
reset_room()
{
  rope_found = 0;
}

public string find_rope(object player, string str)
{
  object rope;
  /*
  if ((str == "trash can" || str == "barrel" ||
       str == "litter" || str == "can" || str == "trash") &&
      !rope_found)
    {
      rope = clone_object(ROPE);
      rope->move(player);
      rope_found = 1;
      return "You find a rope among the trash!\n";
    }
  */
  return "You find nothing but smelly trash.\n";
}
