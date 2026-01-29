inherit "/std/room.c";
#include "/d/Cirath/defs.h"
#include <ss_types.h>
#include <stdproperties.h>
#define PATH "/d/Cirath/katakoro/"
#include "/d/Cirath/common/mobber.h"

create_room()
{
  set_short("Barbarian camp");
   set_long("This is the eastern fringe of the encampment, there is "+
	"only a faint trail here, made by the guards that are assigned "+
	"to this area.  Patches of white snow, green grass and brown "+
	"dirt break up the uniformity of the rolling hillocks.\n");

  add_exit(PATH + "encampment/camp24","west");  
  add_exit(PATH + "encampment/camp19","east");

}

