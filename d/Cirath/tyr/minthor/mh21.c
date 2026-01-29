inherit "/std/room";
#include "/d/Cirath/common/defs.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "defs.h"
#include "/d/Cirath/common/mobber.h"

void
reset_room()
{
    object npc = present ("jeeves", TO);
    if(!objectp(npc))
    {
        npc=clone_object(TZ_MINTHOR+"npc/butler.c");
        npc->arm_me();
        npc->move_living("into the room", TO);
    }
}


void
create_room()
 {
  set_short("Ballroom");
  set_long("The ballroom is a large long room.  It is dominated by a "
	+"beautiful chandelier made of what appears to be glass.  There "
	+"are lights circling the chandelier like will o' the wisps, "
	+"shedding the perfect amount of light on the beautifully "
	+"polished agafari hardwood floors.  There are some chairs "
	+"positioned around the room, and to your southwest you think "
	+"you can see what appears to be a fountain.  The exit for the "
	+"room lies to the east.\n");
  add_item("wall","The wall is off to your side.\n");
  add_item("hallway","It leads in all directions.\n");
  add_item("ceiling","It is above you.\n");
  add_item(({"house","mansion"}),"You are inside of it.\n");
  add_item(({"chair","chairs","padded chairs","padded chair"}),"These "
        +"chairs are very soft and comfortable, they seem to almost mold "
        +"to your body.\n");
  add_item("chandelier","It appears to be made from carefully blown and "
	+"shaped glass.  It has magically created lights circling it "
	+"that provide the illumination for this room.\n");
  add_item(({"floor","floors","hardwood floor","hardwood floors"})," The "
	+"floor in here has been polished so well you can almost see your "
	+"reflection in it.  It is made from the wood of the agafari tree "
	+"which is renowned for its strength and durability.\n");
  add_item("fountain","There looks to be one to your southwest.\n");
  ADD_SUN_ITEM
  ADD_ZIG_ITEM
  INSIDE

   add_exit(TZ_MINTHOR + "mh22","southwest",0);
  add_exit(TZ_MINTHOR + "mh20","east",0);
  set_alarm(1.1,0.0,"reset_room");
}

