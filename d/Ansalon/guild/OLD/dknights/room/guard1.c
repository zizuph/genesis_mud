
/**  DARGAARD KEEP ROOM **/

#include "/d/Ansalon/dargaard/local.h"
#include "/d/Ansalon/common/defs.h"
#include <stdproperties.h>

inherit GUILD_IN;

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
    set_short("Eastern guardroom in Dargaard Keep");
    set_long("You are standing in eastern guardroom in Dargaard "+
             "Keep.\n"); 

    add_exit(DROOM + "dar02","west",0);

    add_item(({"stones","walls", "wall"}),
      "The walls are covered with moss and charred black by "+
      "an intense fire many years ago.\n");

    reset_dargaard_room();
}
