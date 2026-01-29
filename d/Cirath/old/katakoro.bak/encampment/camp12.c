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
	"the Khahan's tribe.  To the northwest there is a yurt with "+
	"large stacks of felt piled outside of it.  To the south the "+
	"sounds of loud carousing can be heard, as if a large group of "+
	"people were rather intoxicated.\n");
	
   add_item(({"felt","stacks"}),"These large stacks of felt look as "+
	"if they've been placed there for a purpose, possibly waiting "+
	"for a time when they can be put to use.\n"); 

   add_item("yurt","Hanging outside the yurt are several hides, which "+
	"look to be curing. There is also a small stack of felt rugs, "+
	"similar to the ones used in the building of yurts sitting to "+
	"one side of the doorway.  This looks like it could be the "+
	"residence of a clothworker.\n");

  add_exit(PATH + "encampment/camp13","south");  
  add_exit(PATH + "encampment/yurts/yurt7","enter");
  add_exit(PATH + "encampment/camp11","north");

}


