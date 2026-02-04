#include "/d/Terel/include/Terel.h"
#include "../bhunters.h"
#include <tasks.h>

inherit "/std/shadow";

string ball_kind;
object snare_object;


public void trap_me(object ppl, object ball)
{
	ball_kind = ball->query_component_info();
	ppl->catch_msg("\nSuddenly you hear a loud clang, and notice steel jaws of a foothold " +
		"trap tearing your leg. Before you're able to react you find yourself traped and chained to "+
		ball_kind + " iron ball.\n\n");
	tell_room(E(ppl), QCTNAME(ppl) + " makes a careless step and triggers a foothold trap.\n", ppl);
	shadow_me(ppl);
	snare_object = clone_object(BHTRAPS + "snare_object");
	snare_object->move(ppl);
	snare_object->set_size(ball, TO);
}

public int query_relaxed_from_combat()
{
	return 0;
}

public void attacked_by(object ob)
{
	shadow_who->attacked_by(ob);
	snare_object->disturb_open();
}

query_m_in()
{ 
   return "arrives dragging " + ball_kind + " iron ball with " + shadow_who->query_pronoun(); 
}

query_m_out()
{
   return "drags " + ball_kind + " iron ball with " + shadow_who->query_pronoun(); 
}


public varargs int move_living(string how, mixed to_dest, int dont_follow, int no_glance)
{
	mixed res = shadow_who->move_living(how, to_dest, dont_follow, no_glance);
	if(res == 0)
	{
		int damage = -20;
		if(ball_kind == "medium")
			damage -= 20;
		if(ball_kind == "heavy")
			damage -= 40;
		write("You pull the iron ball with you, steel teeth of the trap tears deep wound in " +
			"your leg.\n");
		shadow_who->heal_hp(damage);
	}
	return res;	
}
