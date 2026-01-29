inherit "/d/Shire/greenfields/camp/enter_tent";
#include "/d/Shire/common/defs.h"
#include "/d/Shire/orcmaker/orcmaker.h"
#include "camp.h"

object scout, guard;

void add_stuff() 
{
  if(!scout)
  {
    scout=clone_object(ORCMAKER_DIR+"orcmaker");
    scout->set_power(50+random(6));
    scout->set_type(SCOUT);
    scout->add_act("sneak north");
    scout->add_act("sneak south");
    scout->add_act("sneak west");
    scout->add_act("sneak east");
    scout->add_act("sneak northwest");
    scout->add_act("sneak northeast");
    scout->add_act("sneak southwest");
    scout->add_act("sneak southeast");
    scout->move(TO);
  }
  if(!guard)
  {
    guard=clone_object(ORCMAKER_DIR+"orcmaker");
    guard->set_power(90+random(26));
    guard->set_type(GUARD);
    guard->set_random_move(35);
    guard->set_restrain_path(({MOUNT_DIR + "camp"}));
    guard->move(TO);
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
  set_long("Tents surround you to the north, and to the south they "+
   "seem to thin out somewhat. This section of the camp is guarded and "+
   "inhabited by normal members of the army, but there are "+
   "a great many of them.\n");

  add_exit(GREEN_DIR + "camp/camp13","northwest",0);
  add_exit(GREEN_DIR + "camp/camp14","northeast",0);
  add_exit(GREEN_DIR + "camp/camp09","west",0);
  add_exit(GREEN_DIR + "camp/camp11","east",0);
  add_exit(GREEN_DIR + "camp/camp05","southwest",0);
  set_tent_name("tent10");
  enable_reset();
  add_stuff();

  STANDARDS;
}
