inherit "/d/Shire/greenfields/camp/enter_tent";
#include "/d/Shire/common/defs.h"
#include "camp.h"

create_room()
{
  create_camproom();
  set_short("Within the camp");
  set_long("Tents surround you to the west "+
   "and this part of the camp seems devoted to the middle rank of orc "+
   "soldier. The tents are less shabby and worn than in the southern "+
   "parts of the camp. Orcs mill about now and then, you'd better "+
   "hope that they don't catch you!\n");

  add_exit(GREEN_DIR + "camp/camp14","northwest",0);
  add_exit(GREEN_DIR + "camp/camp10","west",0);
  add_exit(GREEN_DIR + "camp/camp06","southwest",0);
  add_exit(GREEN_DIR + "camp/camp07","south",0);
  set_tent_name("tent11");
}
