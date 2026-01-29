inherit "/std/room.c";
#include "/d/Cirath/defs.h"
#include <ss_types.h>
#include <stdproperties.h>
#define PATH "/d/Cirath/katakoro/"
#include "/d/Cirath/common/mobber.h"

create_room()
{
   set_short("Barbarian camp");
   set_long("This area is surrounded by yurts of various shapes and "+
	"sizes.  For the most part these are homes to the members of "+
	"the Khahan's tribe.  In the northwest there is a yurt "+
	"attached to the smith's wagon.\n");

  add_exit(PATH + "encampment/camp15","north");  
  add_exit(PATH + "encampment/yurts/yurt9","enter");

}

