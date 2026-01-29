inherit "/std/room";
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

create_room()
 {
  set_short("Ballroom");
  set_long("You are at the southwestern end of the ballroom. "
	+"The ballroom is a large long room, dominated by a "
	+"beautiful chandelier made of what appears to be glass.  There "
	+"are lights circling the chandelier like will o' the wisps, "
	+"shedding the perfect amount of light on the beautifully "
	+"polished agafari hardwood floors.  Scattered along the edge "
	+"of the room area a variety of chairs for people to sit in "
	+"between dances or to relax in.  One of the most impressive "
	+"things here along with the chandelier is a large "
	+"fountain.  It has crystal clear water rushing from the top "
	+"into a basin at its base.\n");
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
  add_item("fountain","It stands about 12 feet high and is made mostly of "
	+"stone.  Crystal clear water is pouring from the top into a "
	+"large basin at the bottom where there is some sort of creature "
	+"swimming in the water.  It is a beautiful, yet wasteful, "
	+"addition to the room.\n");
  add_item("creature","The creature in the water is scaled and has some "
	+"strangely placed fins on it, which apparently help it move through "
	+"the water.\n");

  ADD_SUN_ITEM
  ADD_ZIG_ITEM
  INSIDE

  add_exit(TZ_MINTHOR + "mh21","northeast",0);
  add_exit(TZ_MINTHOR + "mh23","southeast",0);
   reset_room();
}


