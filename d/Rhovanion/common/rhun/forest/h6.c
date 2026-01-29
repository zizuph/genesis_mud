#include "def.h"
inherit THIS_DIR+"edge";
#include "/d/Rhovanion/defs.h"

void create_room()
{
  set_short("Forest edge");
  set_long("This is the edge of the forest.  To the "
    +"south"
    +" are the vastly-stretching plains that make up most of Rhun."
    +"  It is also possible to follow this outer line of trees, "
    +"either to the "
    +"west or southeast"
    +"."
	+"  There is also a road just to the"
	+" north."
     +"\n");

  add_exit(RHUN_DIR+"forest/g6","west",0);
  add_exit(RHUN_DIR+"forest/i7","southeast",0);
  add_exit(RHUN_DIR+"roads/section8/e","north",0);
  add_stuff();
}
