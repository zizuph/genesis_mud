inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
#define SHDIR(ob)    "/d/Kalad/common/guilds/shadow_walkers/ob"

/* The Shadows Walkers of Kabal Guild Hall , Sarr */

void
create_room()
{
   set_short("In a dark tunnel");
   set_long("You now stand at the end of a dark tunnel. "+
      "There is a rusty, old ladder leading up to the surface. "+
      "The smell here is evil, and dark as well as putrid. "+
      "Water drips from the ceiling, and the walls are cold "+
      "and hard. The tunnel continues on to the north into "+
      "darkness.\n");
   add_item("ladder","The ladder is made of iron, but time "+
      "has made it rusty and old.\n");
   add_item("walls","The walls are carved from stone, and they "+
      "radiate an aura of darkness.\n");
   INSIDE;
   add_prop(ROOM_I_LIGHT,0);
   add_exit(SHDIR(t2),"north",0,-1,1);
   add_exit(TRADE(sewers/s8),"up",0,-1,1);
}

