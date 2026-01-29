inherit "/std/room.c";
#include "/d/Cirath/defs.h"
#define PATH "/d/Cirath/katakoro/"
#include "/d/Cirath/common/teamer.h"

create_room()
{
   bring_room_team(PATH+"npc/kashik",1,1);

   set_short("Khahan's Stockade");
   set_long("This area is right outside of the Khahan's yurt.  There are "+
	"two members of the Kashik standing here as a final guard before "+
	"the entrance.  Also outside the entrance is a tall pole which "+
	"looks like a standard of some sorts.\n");

  add_item(({"pole","standard"}),"This pole stands nearly 15 feet tall "+
	"and has a crossbrace at the top and from the arms of the brace"+
	"hang black horsetail plums.  Sitting atop the pole is a skull, "+
	"under which hangs a golden plaque.  At the base of the standard "+
	"sit small dolls made of red cloth.\n");
   add_item("dolls","These small dolls look vaguely humanoid and have "+
	"bits of hair and leather stuck all about them.\n");

   add_exit(PATH + "encampment/camp7","south");
  add_exit(PATH + "encampment/yurts/yurt6","enter");

}

  
