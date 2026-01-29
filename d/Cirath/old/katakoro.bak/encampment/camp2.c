inherit "/std/room.c";
#include "/d/Cirath/defs.h"
#include "/d/Cirath/katakoro/defs.h"

create_room()
{
  set_short("Barbarian camp");
   set_long("This is the outer border of the encampment.  Scattered "+
	"about this area are the guards as well as the men in charge "+
   "of the livestock that are grazing nearby.  Stubby grass has "+
	"begun breaking through the pitted crust of old snow, and the "+
	"ground is beginning to thaw and become muddy.  There are only "+
	"a few yurts in this area, scattered about in small clumps.\n");

  add_item("yurts","These round tents are made of thick felt that has "+
	"been pounded into rugs and stretched over wooden frames.   "+
	"The doorways, which all face southeast, are covered with a "+
  "loose felt rug, which can be moved to enter the yurt.  "+
     "The roofs of them are bulged at the top and trails of smoke "+
     "can be seen coming from the smokeholes.\n");
  add_item("smoke","The air is filled with the sharp scent of burning "+
	"dung.\n");

   add_exit(KAT_DIR+"encampment/camp1","south");
   add_exit(KAT_DIR+"encampment/camp3","north");
   add_exit(KAT_DIR+"encampment/yurts/yurt1","enter");

}
