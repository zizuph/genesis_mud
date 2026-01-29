inherit "/std/room.c";
#include "/d/Cirath/defs.h"
#include <ss_types.h>
#include <stdproperties.h>
#define PATH "/d/Cirath/katakoro/"
#include "/d/Cirath/common/teamer.h"

create_room()
{
   bring_room_team(PATH+"NPC/kashik",1,4);

   set_short("Khahan's Stockade");
   set_long("This area within the Khahan's stockade has been given to "+
	"his bodyguards, the Kashik.  There is a large cooking fire "+
	"here, around which some of the kashik are standing.  To the "+
	"northwest is a large yurt, probably quarters for the men that "+
	"aren't currently on duty.\n");

   add_exit(PATH + "encampment/camp7","west");
  add_exit(PATH + "encampment/yurts/yurt5","enter");

}

  
