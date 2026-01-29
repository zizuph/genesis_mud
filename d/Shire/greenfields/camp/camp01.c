inherit "/d/Shire/greenfields/camp/enter_tent";
#include "/d/Shire/common/defs.h"
#include "camp.h"
#include "/d/Shire/orcmaker/orcmaker.h"
#include <macros.h>

int alarmed;
object warrior,leader;

void reset_room()
{
    if(!present("_orcmaker_orc"))
    {
	alarmed = 0;
    }
}


create_room()
{
    create_camproom();
    set_short("Within the camp");
    set_long("Tents surround you to the north "+
      "and east, providing both shelter for the inhabitants of this "+
      "camp and handy hiding places for them.  A large tent is nearby "+
      "with a standard planted in the debris outside the flap. "+
      "Other tents stand nearby to the northwest and northeast. "+
      "The entrance to the camp lies to the southeast.\n");

    add_exit(GREEN_DIR + "camp/camp03","northwest","@@check_me");
    add_exit(GREEN_DIR + "camp/camp04","northeast","@@check_me");
    add_exit(GREEN_DIR + "camp/entrance","southeast",0);
    set_tent_name("tent01");
    enable_reset();

}


int check_me()
{
    if(TP->query_race_name() != "orc" && present("_orcmaker_orc") &&
      (CAN_SEE(warrior,TP) || CAN_SEE(leader,TP)) && alarmed)
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
    tell_room(TO,"A squad of warriors rush up to defend the camp.\n");
}
