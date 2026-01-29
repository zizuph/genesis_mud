
/**  DARGAARD KEEP ROOM **/

#include "/d/Ansalon/dargaard/local.h"
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/guild/dknights/local.h"
#include <stdproperties.h>

inherit DARGAARD_IN;

object skeleton;
object skeleton2;


void
reset_dargaard_room()
{
   if(!objectp(skeleton))
   {
      skeleton = clone_object(DNPC + "skeleton");
      skeleton->move(TO);
   }
   if(!objectp(skeleton2))
   {
      skeleton2 = clone_object(DNPC + "skeleton");
      skeleton2->move(TO);
   }
}

void
create_dargaard_room()
{
    set_short("A ruinded corridor in Dargaard Keep");
    set_long("You are standing in a ruined corridor in Dargaard "+
             "Keep. The floor is littered with rubble and to make "+
             "things worse, layer over layer of cobwebs are hanging "+
             "everywhere. You wonder about the size of the spiders "+
             "because you see also some rats entangled in the webs. "+
             "However, someone seems to come this way now and then "+
             "because their is a small path through the webs and the "+
             "rubble.\n"); 

    add_exit(GUILD_ROOM + "room1","west",0);
    add_exit(DROOM + "room8","northeast",0);

    add_item(({"stones","walls", "wall"}),
      "The walls are covered with moss and charred black by "+
      "an intense fire many years ago.\n");

    add_item(({"web"}), 
     "An ordinary web of a pesky spider.\n"); 

    add_item(({"brown mud"}), 
     "This mud seems to hold still some moisture. You"+ 
     " can make out small marks of rat-feet and an"+ 
     " imprint of a booted foot. Someone must have"+ 
     " come this way not all too long ago.\n"); 

    add_item(({"mist"}), 
     "It is a fine, silky mist. It seems to touch you with cold, wet fingers.\n"); 

    add_item(({"stone floor", "floor"}), 
     "This floor is made of ordinary stone. It seems that because of"+ 
     " practicality normal stone was used in this corridor. Probably"+ 
     " the precious but more delicate stones would have been damaged"+ 
     " in no time.\n"); 

    reset_dargaard_room();
}

