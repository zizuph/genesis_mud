inherit "/std/room.c";
#include "/d/Cirath/defs.h"
#include <ss_types.h>
#include <stdproperties.h>
#define PATH "/d/Cirath/katakoro/"
#include "/d/Cirath/common/teamer.h"

create_room()
{

   bring_room_team(PATH+"NPC/kashik",1,1);

   set_short("Barbarian camp");
   set_long("This is at the base of a small hill within the valley.  "+
	"Below and to the south stretches the entire camp, with only "+
   "a stockade guarded by two men to the north.\n");

   add_item("stockade","The wooden posts of this stockade seem to be "+
	"placed more as a decoration than as fortification.  While "+
	"certainly capable of blocking entry to individuals, they "+
	"would be no defense against a determined attack.\n");

   add_exit(PATH + "encampment/camp4","south");
   add_exit(PATH + "encampment/camp6","north");
   add_exit(PATH + "encampment/camp14","west");
   add_exit(PATH + "encampment/camp11","east");

}

  
