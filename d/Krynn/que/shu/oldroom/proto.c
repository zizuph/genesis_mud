
#include "../local.h"
inherit ATTACKROOM;
#include "/d/Krynn/common/random_meet.h"
#define TABLE "/d/Krynn/common/rndtables/tblwar"

object monster;

void
create_attack_room()
{
    set_short("On a grass path in Que Kiri");
    set_long(BS("You are standing in the middle of a grass path"
      + " within the Que Kiri village. The sights and sounds of"
      + " the village overwhelm your senses. Never have you seen"
      + " such a close, interworking group of people. To the northeast"
      + " you spot the beginnings of some tents, which seem to be the"
      + " the main living quarters to these people. To the west you"
      + " spot the entrance of the village.", 70));
    set_change_msg(0,ATTACK);
    set_change_short(1,SMOKPATH);
    set_change_long(1,FIGHTING);
    set_change_msg(1,SMOLDER);
    set_change_short(2,CHARPATH);
    set_change_long(2,REMAINS);
    set_change_msg(2,ARRIVAL);
    set_change_short(3,DESERTED);
    set_change_long(3,PEOPLE);
    set_change_msg(3,REBUILD);
    set_change_short(4,CONSTRUCT);
    set_change_long(4,CZONE);
    set_change_msg(4,FINISH);
    
    OUTSIDE;

    add_exit(ROOM + "kiri_c9","northeast");
    add_exit(ROOM + "kiri_d7","west");

    add_item(({"tents","tent","remains"}),"@@tent_desc");
    add_item(({"entrance","wall",}),"@@wall_desc");
    add_item(({"smoke",}),"@@smoke_desc");
}

string
tent_desc()
{
    switch (state_of_room)
      {
	case 0: return "You can reach the tents by going northeast. A lot " +
	  "of laughter and noise is coming from that direction.\n";
	case 1: return "You can reach the tents by going northeast. Strange " +
	  "gurring voices can be heard from there and also human screams.\n";
	case 2: return "These can hardly be called tents anymore. A few metal " +
	  "pieces is all that is left.\n";
	case 3: return "You think you can hear someone there.\n";
	case 4: return "You can see some people rebuilding the tents.\n";
	default: return 0;
      }
}

string
wall_desc()
{
    switch(state_of_room)
      {
	case 0: return CWALL;
	case 1: return FWALL;
	case 2: return OLDWALL;
	case 3: return FOUNDWALL; 
	case 4: return REWALL;
	default: return 0;
      }
}

string
smoke_desc()
{
    switch(state_of_room)
      {
	case 1: return "There is smoke all around you! Even the grass " +
	  "under your feet is smoking.\n";
	default: return 0;
      }
}

int
hook_change_room(int which)
{
    if (which == 0)
      {
	  if (monster)
	    return 0;
	  monster = RANDOM_MEET(TABLE);
	  monster->move_living("xx",TO);
	  return 1;
      }
    if (which == 1)
      if (monster)
	return 0;
    return 1;
}

