inherit "/d/Shire/room";

#include "/d/Shire/common/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"

static object cook, stove;
void reset_room();
void
create_room()
{
add_prop(ROOM_S_MAP_FILE, "michel_delving.txt");
  set_short("The kitchen of the Pipe and Fork");
  set_long("It takes little time to discover the purpose of this place.  "+
   "Apart from the pots and dirty plates and utensils piled in the sink, "+
   "the heat here is sweltering.  A large oven provides most of the heat, "+
   "while a stove nearby certainly does not cool the place.  A thick curtain "+
   "divides this part of the inn from the dining area.\n");

   add_item(({"pots","plates","utensils","pot","plate","utensil"}),
   "They are all piled awkwardly in the small sink.\n");

   add_item(({"sink","small sink"}),
   "The sink has pots, plates, and utensils piled in it.  At the bottom of all "+
   "that, you think you see some brown dirty dishwater.\n");

   add_item(({"brown dishwater","water","dirty dishwater","dishwater"}),
   "The brown dirty dishwater looks very unappetizing and smells horribly!\n");

   add_item(({"large oven","oven"}),
   "The oven's door is firmly closed and the outside of it is quite dirty.\n");

   add_item(({"curtain","thick curtain"}),
   "This curtain is of a thick canvas that seems to keep the heat in here and "+
   "out of the way of the customers in the main inn.\n");

  add_prop(ROOM_I_INSIDE,1);
  add_exit(MICH_DIR + "inn","east");
 
  reset_room();
}

void
reset_room() 
{
  if (!cook) cook = clone_object(MICH_DIR + "npc/cook");
  if (!present(cook)) cook->move(this_object());
  if(!stove)
  {
    stove = clone_object(MICH_DIR + "obj/stove");
    stove->move(TO);
   }
}

