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
    slave->set_power(40);
    slave->set_type(SLAVE);
    slave->move(TO);
  }
  if(!slave1)
  {
    slave1=clone_object(ORCMAKER_DIR+"orcmaker");
    slave1->set_power(35+random(6));
    slave1->set_type(SLAVE);
    slave1->set_random_move(23);
    slave1->set_restrain_path(({GREEN_DIR+"camp"}));
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
  set_long("Tents surround you on all sides "+
    "and your feeling of being watched has never been more "+
    "intense. There are many tents around, but one tent towers over all- it is "+
    "the residence of the leader of these goblins, and "+
    "it seems a measure of some social status for orcs to camp near "+
    "their leaders. Or perhaps it gives them easy access for "+
     "assassination attempts?\n");

  add_exit(GREEN_DIR + "camp/camp15","north",0);
  add_exit(GREEN_DIR + "camp/camp12","west",0);
  add_exit(GREEN_DIR + "camp/camp09","southwest",0);
  add_exit(GREEN_DIR + "camp/camp10","southeast",0);
  add_exit(GREEN_DIR + "camp/camp14","east",0);
  set_tent_name("tent13");
  enable_reset();
  add_stuff();
  
  STANDARDS;
}
