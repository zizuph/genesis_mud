inherit "/d/Shire/greenfields/camp/camp.c";
#include "/d/Shire/common/defs.h"
#include "/d/Shire/orcmaker/orcmaker.h"
#include <stdproperties.h>
#include <language.h>
#include <macros.h>

object guard1,guard2;

void add_stuff()
{
    if(!guard1)
    {  
	guard1=clone_object(ORCMAKER_DIR + "oma");
	guard1->set_power(59+random(22));
	guard1->set_type(GUARD);
	guard1->add_prop(OBJ_I_HIDE,50+random(26));
	guard1->disable_noise();
	guard1->set_aggressive(0);
	guard1->move(TO);
    }
    if(!guard2)
    {  
	guard2=clone_object(ORCMAKER_DIR + "oma");
	guard2->set_power(65+random(16));
	guard2->set_type(GUARD);
	guard2->disable_noise();
	guard2->add_prop(OBJ_I_HIDE,50+random(26));
	guard2->set_chat_time(21);
	guard2->set_act_time(21);
	guard2->set_aggressive(0);
	guard2->move(TO);
	guard1->team_join(guard2);
    }
}


void
create_room()
{
    create_camproom();
    set_short("Camp entrance");
    set_long("Two sturdy poles supporting a crosspiece mark the entrance "+
      "to this rather large camp.  Vaguely humanlike shapes move about "+
      "the camp area occasionally.  Tents sprawl around campfires "+
      "like hounds around the hearth.  The whole camp is shrouded in "+
      "mist that no light source seems to penetrate or burn off.  A "+
      "vague feeling of unease creeps over you as you observe the camp.\n");
/*
    add_exit(GREEN_DIR + "camp/camp01","northwest","@@check_me");
    add_exit(GREEN_DIR + "camp/camp02","northeast","@@check_me");
    add_exit(GREEN_DIR + "path5","south",0,1);
*/
    add_item(({"pole","poles","standard","standards","crosspiece"}),
      "Thick poles that still have their bark support a similar "+
      "crosspiece.  Attached to the crosspiece are various trophies, "+
      "including some weapons, armours, and skulls.  These trophies "+
      "were undoubtedly taken by the inhabitants of this camp from their "+
      "previous owners by force.\n");
    add_item(({"trophy","trophies"}),"These are a variety of skulls, "+
      "weapons, and armours.\n");
    add_item(({"weapons","weapon"}),
      "These weapons, amoung which are a few swords, a great spiked club, "+
      "a rusty iron mace, and a broken-off spear head are all dented, bent "+
      "and rusted so badly they are barely recognizable, let alone "+
      "useable.\n");
    add_item(({"armour","armours"}),
      "These armours are not even identifiable, they have so many "+
      "missing or rusted out pieces, holes, dents, and dings.  Suffice to "+
      "say that whoever has been collecting them seems to have had "+
      "a rather long winning streak.\n");
    add_item(({"skull","skulls"}),"@@skull_me");

    enable_reset();
    add_stuff();
    (GREEN_DIR + "camp/warg_room")->load_me();
}


int check_me()
{
    if((guard1 || guard2) && (CAN_SEE(guard1,TP) || CAN_SEE(guard2,TP)))
    {
	write("You hear a loud voice bellow from behind you: 'Intruders "+
	  "in the camp! Intruders in the camp!'\n");
	tell_room(TO,"A hidden orc shouts: Intruders in the camp! "+
	  "Intruders in the camp!\n",TP);
	(GREEN_DIR+"camp/camp01")->alarm_me();
	(GREEN_DIR+"camp/camp02")->alarm_me();
	return 0;
    }
    return 0;
}


string skull_me()
{
    return "Most of these skulls are bare, bleached bone that has "+
    "been cracked and chipped by the weather and scavengers over "+
    "some unknown period of time.  There is one fresh skull from "+
    LANG_ADDART(TP->query_race_name())+
    " however. "+CAP(HE_SHE(TP))+
    " looked a lot like you, in fact.\n";
}

void reset_room()
{
    add_stuff();
}
