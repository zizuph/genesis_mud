inherit "/std/room.c";
#include "/d/Cirath/defs.h"
#include <ss_types.h>
#include <stdproperties.h>
#define PATH "/d/Cirath/katakoro/"
#include "/d/Cirath/common/teamer.h"

create_room()
{
   bring_room_team(PATH+"npc/eguard",1,3);

   set_short("Empress' camp");
   set_long("This is a guard post located outside the yurt of the "+
	"Khahan's wife.  Four guards are posted here to ensure the "+
	"security of the area.  There is very little activity; "+
	"Only other guards can be seen walking around.\n");

   add_exit(PATH + "encampment/camp19","southeast");
   add_exit(PATH + "encampment/camp21","north");
   add_exit(PATH + "encampment/yurts/yurt10","enter");

}
  
