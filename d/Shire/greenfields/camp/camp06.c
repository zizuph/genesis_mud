inherit "/d/Shire/greenfields/camp/enter_tent";
#include "/d/Shire/common/defs.h"
#include "camp.h"
#include "/d/Shire/orcmaker/orcmaker.h" 

object slave, slave1;

void add_stuff()
{
  if(!slave)
  {
    slave=clone_object(ORCMAKER_DIR+"orcmaker");
    slave->set_power(30);
    slave->set_type(SLAVE);
    slave->move(TO);
  }
  if(!slave1)
  {
    slave1=clone_object(ORCMAKER_DIR+"orcmaker");
    slave1->set_power(35+random(6));
    slave1->set_type(SLAVE);
    slave1->set_random_move(15);
    slave1->set_restrain_path(({MOUNT_DIR+"camp"}));
    slave1->move(TO);
    slave1->team_join(slave);
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

  add_exit(GREEN_DIR + "camp/camp11","northeast",0);
  add_exit(GREEN_DIR + "camp/camp07","east",0);
  add_exit(GREEN_DIR + "camp/camp02","southeast",0);
  set_tent_name("tent06");

  enable_reset();
  reset_room();
}
