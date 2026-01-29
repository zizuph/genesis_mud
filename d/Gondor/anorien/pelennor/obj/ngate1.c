inherit "/std/door";
inherit "/d/Gondor/common/lib/friend_or_foe";

#include <macros.h>
#include "/d/Gondor/defs.h"
#include "../ngatedefs.h"
#define DID_ATTACK_MT_GATES  "_attacked_mt_gate"

create_door()
{
  ::create_door();
  set_door_id("anoriengate");
  set_pass_command(({"s","south"}));
  set_door_name(({"great gate","gate","citygate"}));
  set_other_room(INGATE);
  set_door_desc(VBFC_ME("long_desc"));
  set_open(0);
  set_knock_command(0);
  set_locked(1);
  set_key("Rammas_Echor_Key");
}

string long_desc()
{
  if(open_status)
  {
    return BSN("The great gate of the Anorien Fort is open, its large "+
	       "iron doors swung back on steel posts, allowing entrance "+
	       "to the Pelennor Fields. The strong gatehouse of stone "+
	       "has battlements and crenelations on top, and you glimpse "+
	       "people moving around up there.");
  }
  else
  {
    return BSN("The great gate is closed. It is made of two large " +
      "iron doors, held up by strong steel posts. A strong stone "+
      "gatehouse surrounds it all, with battlements on top. There are "+
      "probably guards up there, watching you as well. ");
  }
}

/*
 * Function name: pass_door
 * Description:   Pass the door.
 * Arguments:	  arg - arguments given
 */
int
pass_door(string arg)
{
    int dexh;

    if (!other_door)
	load_other_door();

    if (open_status)
    {
        if (query_friend_or_foe(TP) < 0)
            ENV(TO)->close_gate_to_stop_invaders(TP);
        else
	    TP->move_living(query_verb(), other_room);
    }
    else
	write(check_call(fail_pass));

    return 1;
}

varargs int
query_friend_or_foe(mixed pl)
{
    if (stringp(pl))
        pl = find_living(LOW(pl));
    else if (!objectp(pl))
        pl = TP;

    if (!objectp(pl))
        return 0;

    if (M_TIRITH_MASTER->query_enemy(pl->query_real_name(),
        pl->query_race()))
        return -1;

    if (pl->query_prop(DID_ATTACK_MT_GATES))
        return -1;

    return ::query_friend_or_foe(pl);
}



