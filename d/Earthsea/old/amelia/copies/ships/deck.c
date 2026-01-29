#pragma save_binary

inherit "/d/Genesis/ship/deck";

#include <stdproperties.h>
#include "/d/Roke/common/defs.h"
#include <macros.h>
#include <ss_types.h>

hopp(object tp);

void
create_deck()
{
    set_short("On the large warship");
    set_name("water");
    set_long(BS("You are standing on the deck of a huge warship sailing "+
		"between Gont and Sparkle. Some sailors are working high up "+
		"in the masts, and beside you stands the admiral, giving "+
		"orders to the crew. Around you are various items: long "+
		"ropes, buckets of water, and not to forget, the impressive "+
		"catapults of the ship. There is also a staircase leading down "+
		"towards the admiral's cabin.\n",76));

    add_item(({"mast", "masts"}), break_string("There are three great masts "+
	     "supporting the enormous sails, and you can see people high up "+
	     "climbing about.\n",76));
    add_item(({"sail", "sails"}), break_string("The sails are made out of "+
	     "thick, incredibly strong canvas, but you can't see that from "+
	     "down here really. What you see is that the sails are set and "+
	     "when a gust of wind fills one or several, you feel a rift going "+
	     "through all of the ship and notice the masts swaying slightly "+
	     "to the enormous pressure.\n",76));
    add_item(({"catapult", "catapults"}),
             break_string("The catapults are brand new "+
	     "and you realize this is probably the best weaponry that "+
	     "money can buy. The craftsmanship is excellent.\n",76));
    add_exit(SHIPS+"gontsparkle/cabin", "down", 0);

    add_prop("_room_i_no_dig",1);
}
jump(string s)
{
  if(s!="overboard")
    {
      TP->catch_msg("Jump where? Overboard?\n");
      return 1;
    }
  
  say(QCTNAME(TP)+" jumps overboard.\n");
 
  TP->move_living("M",E(ship));

  set_alarm(1.0, 0.0, &hopp(TP));

  return 1;
}
hopp(object tp)
{
  if(E(tp)->query_prop(ROOM_I_TYPE)!=1)
    {
      tp->catch_msg("You hit the ground with your head first! It hurts terribly!\n");
      tell_room(TO,QCTNAME(tp)+" hits the ground with "+tp->query_possessive()+
		" head first. It sounds awful.\n");
      tp->heal_hp(-tp->query_max_hp()/3);
      if(tp->query_hp()==0)
	tp->do_die(TO);
      return;
    }
  tp->catch_msg("You jump into the fresh, cold water.\n");
  
  if(!tp->query_skill(SS_SWIM))
    {
      tp->catch_msg("Unfortunately you never learned to swim. You panic, and\n"+
		    "are unable to avoid drowning.\n");
      tell_room(TO,QCTNAME(tp)+" seems to be unable to swim and drowns.\n");
      tp->heal_hp(-300784);
      tp->do_die(TO);
      ROKE_LOG("drowned",capitalize(TP->query_real_name())+" (From the ship) "+ctime(time())+"\n");
    }
}

init()
{
  ::init();

    add_action("jump","jump");
  }


