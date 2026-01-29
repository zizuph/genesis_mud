inherit "/std/room.c";
#include "/d/Cirath/defs.h"
#include <ss_types.h>
#include <stdproperties.h>
#define PATH "/d/Cirath/katakoro/"
#include "/d/Cirath/common/teamer.h"

create_room()
{
   bring_room_team(PATH+"NPC/kashik",1,3);

   set_short("Barbarian camp");
   set_long("Midway up this small hill within the valley stands a "+
	"large gate, the only noticable entry into the stockade "+
	"beyond.  Four Kashiks stand guard, allowing only those "+
	"worthy of the Khahan's time to pass.\n");

   add_item("gate","This gate is mostly a formal affair as it really "+
	"could not stand up to a determined assault.\n");

   add_exit(PATH + "encampment/camp5","south");
   add_exit(PATH + "encampment/camp7","north");

}

  
