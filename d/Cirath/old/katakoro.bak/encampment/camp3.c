inherit "/std/room.c";
#include "/d/Cirath/defs.h"
#include <ss_types.h>
#include <stdproperties.h>
#define PATH "/d/Cirath/katakoro/"
#include "/d/Cirath/common/mobber.h"

void
reset_room()
{
     bring_room_mob("kid",KAT_DIR+"npc/kids.c",2,1);
}

create_room()
{
   set_short("Barbarian camp");
   set_long("Moving deeper into the encampment, the frequency of yurts "+
	"increases.  All around people are going about their business, "+
	"some tending to the drying meats, others caring for their "+
	"horses and a few warrior are working with their weapons.  To "+
	"the northwest is a particularly busy yurt, there is something "+
	"hanging from the doorway, that may explain it's purpose.\n");

   add_item("yurt","This yurt is similar to the many others that are in "+
	"the area, being made of thick felt rugs.  However, this one "+
	"has a dull white tone about it from chalk that was pounded in, "+
	"when the yurt was made.\n");
   add_item("doorway","Hanging over the doorway into the yurt is a long "+
	"string of intricately designed beads.  Each one looks to have "+
	"been individually carved with great care.  It is possible that "+
	"a beadworker lives and works in this yurt.\n");

   add_exit(PATH + "encampment/camp2","south");
   add_exit(PATH + "encampment/camp4","north");
  add_exit(PATH + "encampment/yurts/yurt2","enter");

   reset_room();
}

