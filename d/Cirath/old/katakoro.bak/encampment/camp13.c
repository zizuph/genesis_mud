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
	"the Khahan's tribe.  In the northwest there is a large "+
	"sturdy looking yurt with several of soldiers passed out "+
	"in front of it.  The sounds coming from the inside suggest "+
	"the presence of bar of some sorts.\n");
	
   add_item("yurt","This yurt looks to have been built a bit better "+
	"than those surrounding it, suggesting that it sees some "+
	"rough handling from time to time.  The unique smell of "+
	"fermented mares milk, or kumiss, a favored drink among "+
	"these people, floats on the gentle breeze.\n");

  add_exit(PATH + "encampment/camp12","north");  
  add_exit(PATH + "encampment/yurts/yurt8","enter");

}

