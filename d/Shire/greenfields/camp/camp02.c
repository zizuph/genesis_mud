inherit "/d/Shire/greenfields/camp/enter_tent";
#include "/d/Shire/common/defs.h"
#include "/d/Shire/orcmaker/orcmaker.h"
#include "camp.h"

object scout, fighter;
object warrior,leader;
int alarmed;

void add_stuff() 
{
  if(!scout)
  {
    scout=clone_object(ORCMAKER_DIR+"orcmaker");
    scout->set_power(45+random(11));
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
  if(!fighter)
  {
    fighter=clone_object(ORCMAKER_DIR+"orcmaker");
    fighter->set_power(200+random(26));
    fighter->set_type(WARRIOR);
    fighter->set_random_move(15);
    fighter->set_aggressive(1);
    fighter->set_attack_chance(50);
    fighter->set_restrain_path(({GREEN_DIR + "camp"}));
    fighter->move(TO);
  }
}


void reset_room()
{
   if(!present("_orcmaker_orc"))
  {
   alarmed = 0;
  }
  add_stuff();
}


create_room()
{
  create_camproom();
  set_short("Within the camp");
  set_long("Tents surround you to the north "+
    "and west, providing shelter for the inhabitants of this camp "+
    "and ready hiding places for them also.  A campfire flickers "+
    "in front of a large tent nearby that has a standard planted right "+
    "outside the flap. The entrance to the camp sits to the "+
    "southwest.\n");

  add_exit(GREEN_DIR + "camp/camp06","northwest","@@check_me");
  add_exit(GREEN_DIR + "camp/camp07","northeast","@@check_me");
  add_exit(GREEN_DIR + "camp/entrance","southwest",0);
  set_tent_name("tent02");
  enable_reset();

  STANDARDS;
}


int check_me()
{
  if(TP->query_race_name() != "orc" && alarmed && present("_orcmaker_orc")
    && (CAN_SEE(warrior,TP) || CAN_SEE(leader,TP)))
  {
    write("An orc blocks the way, preventing you from getting "+
      "further into their camp.\n");
    say(QCTNAME(TP)+" is stopped by an orc.\n");
    return 1;
  }
  return 0;
}


void alarm_me()
{
   if(!alarmed)
  {
  alarmed = 1;
  set_alarm(0.5,0.0,"get_troops");
  }
}


get_troops()
{
  int i;

  leader=clone_object(ORCMAKER_DIR+"orcmaker");
  leader->set_power(150+random(51));
  leader->set_type(WARRIOR);
  leader->set_aggressive(1);
  leader->set_attack_chance(0);
  leader->move(TO);
  for(i=0;i<3;i++)
  {
    warrior=clone_object(ORCMAKER_DIR+"orcmaker");
    warrior->set_power(100+random(51));
    warrior->set_type(WARRIOR);
    warrior->set_aggressive(1);
    warrior->set_attack_chance(0);
    warrior->move(TO);
    leader->team_join(warrior);
  }
  tell_room(TO,"A squad of warriors rushes up to defend the camp.\n");
}
