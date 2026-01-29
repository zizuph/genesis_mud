inherit "/std/room.c";

#include "/sys/stdproperties.h"
#include "/d/Roke/common/defs.h"
#include <macros.h>

string long;
object marshal, sergeant;

create_room()
{
   set_short("Marshal's office");
   set_long(
      "This is the Marshal's office.\n"
      + "In this room many people have been interrogated. All important\n"
      + "decisions concerning Cove are made here. There is a large desk\n"
      + "in the corner as well as a window on the east wall. The people\n"
      + "of Cove come here to file complaints against others. You see a\n"
      + "weapon rack against one of the walls. The town Marshal can be\n"
      + "found here most of the time, day or night. He is the one that\n"
      + "keeps Cove free of scum and the like. There is a painting on\n"
      + "one of the walls.\n");
   
   add_item(({"desk", "large desk"}), "This is a large oak desk with many "+
      "important papers on top.\n");
   add_item(({"papers"}), "Strangely enough you cannot seem to read what is "+
      "written on them. It seems to be some sort of secret code.\n");
   add_item(({"stone", "large stone"}), "It is quite heavy.\n");
   add_item(({"window", "east window"}), "The view from here shows that of "+
      "gently rolling foothills in the fore ground, while mountains "+
      "protrude from the background.\n");
   add_item(({"rack", "weapons rack"}), "Unfortunately it seems to be empty "+
      "at the moment.\n");
   
   add_item(({"picture", "painting"}), "It is a painting of a strapping "+
"young man who is depicted as killing hordes of criminals alone.\n");
   
   
   add_exit("/d/Roke/vladimir/lawo", "south");
   
   reset_room();
}

reset_room()
{
   if(!marshal)
      {
   marshal = clone_object("/d/Roke/vladimir/monsters/marshal");
      marshal-> move_living("xxx", TO);
   }
   if(!sergeant)
      {
      sergeant = clone_object("/d/Roke/vladimir/monsters/sergeant");
      sergeant-> move_living("xxx", TO);
   }
}

