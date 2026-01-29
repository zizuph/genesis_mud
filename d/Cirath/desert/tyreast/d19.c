inherit "/std/room";
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "defs.h"
#include "/d/Cirath/common/defs.h"
#include "/d/Cirath/common/mobber.h"

void
reset_room()
{
    object npc = present ("gaj",TO);
    if(!objectp(npc))
    {
	   bring_room_mob("gaj", DES_NPC+"gaj",1,1);
    }
}

void
create_room()
 {
  set_short("Rocky Dead-End");
  set_long("The desert fades into a rocky alcove here.  The "
  	+"rocks form a shelter from the winds that scream across "
  	+"the desert.  As you look around, you see things "
  	+"indicative of something living here.  Bones, tattered "
  	+"cloth, some chitin, whatever was here ravaged some "
  	+"creature completely.\n");
    add_item(({"bone","bones"}),"You see pieces of bone from a "
    	+"variety of creatures, upon inspection, you notice a fair "
    	+"number of human, elven, and dwarven bones mixed in as "
    	+"well.\n");
    add_item("cloth","This appears to be half digested pieces of "
    	+"clothing is basically all that remains of whatever "
    	+"victims have fallen prey to the creature that resides "
    	+"here.\n");
    add_item("chitin","Shards of broken insect chitin lay strewn "
    	+"about the area, the remnants of some epic battle.\n");
    add_exit(DESERT + "d18","southwest");
    add_exit(DESERT + "cave","east","@@block");
    set_alarm(1.0,0.0,"reset_room");
}

int
block()
{
    object guard = present ("gaj",TO);
  if(objectp(guard))
  {
TP->catch_msg(QCTNAME(guard)+ " blocks the entrance to the cave.\n");
      return 1;
    }
  return 0;
}

