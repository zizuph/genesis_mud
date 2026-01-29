// an empty commercial building
#include "defs.h"
inherit  ROOM+"home";
#define  EXIT_DIR "east"
 
void create_khalakhor_room()
{
   create_home(EXIT_DIR);
   add_exit("court3",EXIT_DIR);
   set_short("In an empty building in a quaint village");
   set_long("This is one of the quaint little buildings of the village, "+
            "neat as a pen and looking almost brand new on the inside. "+
            "It is empty except for a long bar along the north wall and "+
            "a small clay bricked hearth along the "+hdir+". It looks "+
            "like it used to be some kind of shop that went out of "+
            "business.\n");
   add_item("bar",
      "It is a long bar along the north wall made of polished wood.\n");
}
