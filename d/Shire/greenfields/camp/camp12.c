inherit "/d/Shire/greenfields/camp/enter_tent";
#include "/d/Shire/common/defs.h"
#include "camp.h"

create_room()
{
  create_camproom();
  set_short("Within the camp");
  set_long("Tents surround you to the south "+
   "but to the north and west they seem to diminish. The "+
   "tents here are set up in orderly fashion, as if someone "+
   "stood around and orchestrated the layout. This is the warrior's "+
   "section of the camp, and you shouldn't stick around too long.\n");

  add_exit(GREEN_DIR + "camp/camp08","southwest",0);
  add_exit(GREEN_DIR + "camp/camp09","southeast",0);
  add_exit(GREEN_DIR + "camp/camp13","east",0);
  set_tent_name("tent12");
}
