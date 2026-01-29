inherit "/d/Shire/greenfields/camp/enter_tent";
#include "/d/Shire/common/defs.h"
#include "camp.h"

create_room()
{
  create_camproom();
  set_short("Within the camp");
  set_long("Tents surround you to the north "+
    "and west, providing shelter for the inhabitants of this camp "+
    "and ready hiding places for them also.  A large tent is nearby "+
    "with a standard set up right outside the flap.\n");

  add_exit(GREEN_DIR + "camp/camp11","north",0);
  add_exit(GREEN_DIR + "camp/camp06","west",0);
  add_exit(GREEN_DIR + "camp/camp02","southwest",0);
  set_tent_name("tent07");
  STANDARDS;
}
