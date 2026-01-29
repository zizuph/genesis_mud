inherit "/std/room.c";
#include "/d/Cirath/defs.h"
#include <ss_types.h>
#include <stdproperties.h>
#define PATH "/d/Cirath/katakoro/"
#include "/d/Cirath/common/mobber.h"

create_room()
{
   set_short("Barbarian camp");
   set_long("This is deep within the encampment.  Yurts are scattered "+
   "everywhere.  All around, people are going about their business.  "+
   "To the northwest is an unusually large yurt.  Occasionally, "+
	"people will walk in and come out with various tools and "+
   "equipment.  Maybe it is some sort of merchant's residence.\n");

   add_item("yurt","This yurt is similar to the many others that are in "+
	"the area, being made of thick felt rugs.  However, this one "+
	"is strangely larger than the ones surrounding it.\n");

   add_exit(PATH + "encampment/camp3","south");
   add_exit(PATH + "encampment/camp5","north");
  add_exit(PATH + "encampment/yurts/yurt3","enter");

}

  
