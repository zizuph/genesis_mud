inherit "/d/Shire/room";
#include "/d/Shire/common/defs.h"

void
create_room()
{
   set_short("Hallway");
   set_long("This hallway is strangely quiet except for some "+
   "low grunting sounds, you think you heard them coming "+
   "from the south. North is what looks like another guard room and west is yet another guard room. "+
   "Water drips down from the ceiling into puddles on the floor.\n");

   add_item(({"water","ceiling","puddles","puddle","floor"}),
   "The water dripping from the ceiling is clear, compared "+
   "to that in the puddles, which is all cloudy and smelly. "+
   "The ceiling and floor are carved of some soft rock.\n");


   add_item(({"hallway","sounds","here"}),
   "This hallway is carved right out of the earth by very unskilled "+
   "hands. Scratch marks cover the room. Low grunting sounds echo "+
   "through this hall, they must come from oone of the exits.\n");
   add_item(({"guardroom","north room","south room","west room"}),
   "You can't tell from here what lies in the guard rooms.\n");


   add_exit(TROLLSH_DIR + "n_groom1","north",0,2);
   add_exit(TROLLSH_DIR + "s_groom1","south",0,1);
      add_exit(TROLLSH_DIR + "empty","west",0,1);
   add_exit(TROLLSH_DIR + "hall_room","east",0,1);


}
