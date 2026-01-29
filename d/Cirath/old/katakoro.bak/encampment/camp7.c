inherit "/std/room.c";
#include "/d/Cirath/defs.h"
#include <ss_types.h>
#include <stdproperties.h>
#define PATH "/d/Cirath/katakoro/"
#include "/d/Cirath/common/teamer.h"

create_room()
{
   bring_room_team(PATH+"NPC/kashik",1,3);

   set_short("Khahan's Stockade");
   set_long("This is a guard post within the stockade of the "+
	"Khahan.  Four kashik guards are posted here to ensure the "+
	"the security of the area.  There is very little activity "+
	"within the stockade and only members of the Kashik can be "+
	"seen walking around.\n");

   add_exit(PATH + "encampment/camp6","south");
   add_exit(PATH + "encampment/camp10","north");
   add_exit(PATH + "encampment/camp8","east");
   add_exit(PATH + "encampment/camp9","west");

}

  
