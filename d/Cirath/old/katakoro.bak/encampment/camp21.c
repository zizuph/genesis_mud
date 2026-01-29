inherit "/std/room.c";
#include "/d/Cirath/defs.h"
#include <ss_types.h>
#include <stdproperties.h>
#define PATH "/d/Cirath/katakoro/"

#include "/d/Cirath/common/teamer.h"

create_room()
{
   bring_room_team(PATH+"npc/eguard",1,1);

   set_short("Empress' camp");
   set_long("This area is right outside of the Empress' yurt.  There are "+
	"two members of her guard standing here before final entrance "+
	"to her home.  Also outside the entrance is a tall pole which "+
	"looks like a standard of some sorts.\n");

  add_item(({"pole","standard"}),"This pole stands nearly 15 feet tall "+
	"and has a crossbrace at the top and from the arms of the brace"+
	"hang white horsetail plums.\n");

   add_exit(PATH + "encampment/camp20","south");
   add_exit(PATH + "encampment/yurts/yurt11","enter");

}

  
