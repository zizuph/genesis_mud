inherit "/d/Shire/greenfields/camp/enter_tent";
#include "/d/Shire/common/defs.h"
#include "/d/Shire/orcmaker/orcmaker.h"
#include "camp.h"

object warrior;

void add_stuff() 
{
  if(!warrior)
  {
    warrior=clone_object(ORCMAKER_DIR+"orcmaker");
    warrior->set_power(110);
    warrior->set_type(WARRIOR);
    warrior->set_random_move(10);
    warrior->set_restrain_path(({MOUNT_DIR+"camp"}));
    warrior->move(TO);
  }
}


void reset_room()
{
  add_stuff();
}


create_room()
{
  create_camproom();
  set_short("Within the camp");
  set_long("Tents surround you to the north "+
    "and east, providing shelter for the inhabitants of this camp "+
    "and ready hiding places for them also.  A large tent is nearby "+
    "with a standard set up right outside the flap.\n");

  add_exit(GREEN_DIR + "camp/camp08","northwest",0);
  add_exit(GREEN_DIR + "camp/camp03","west",0);
  add_exit(GREEN_DIR + "camp/camp01","southwest",0);
  set_tent_name("tent04");
  enable_reset();
  add_stuff();

  STANDARDS;
}
