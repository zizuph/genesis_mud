inherit "/std/door";
inherit "/d/Gondor/minas/lib/minas_fof.c";

#include <macros.h>
#include "/d/Gondor/defs.h"

#define	LIVE_I_KNOCKED	"_live_i_knocked"

create_door()
{
  ::create_door();
  set_door_id("greatgate");
  set_pass_command(({"w","west"}));
  set_door_name(({"great gate","gate","citygate"}));
  set_other_room(MINAS_DIR + "ingate1");
  set_door_desc(VBFC_ME("long_desc"));
  set_open(0);
  set_locked(1);
  set_knock_command(0);
  set_key("Minas_Tirith_Key");
}

string long_desc()
{
  if(open_status)
  {
    return BSN("The Great Gate of Minas Tirith is open, its large "+
	       "iron doors swung back on steel posts, allowing entrance "+
	       "to the capital of Gondor. The strong gatehouse of stone "+
	       "has battlements and crenelations on top, and you glimpse "+
	       "people moving around up there.");
  }
  else
  {
    return BSN("The Great Gate is closed. It is made of two large " +
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
        if (TP->query_prop(LIVE_I_KNOCKED))
	{
	    TP->remove_prop(LIVE_I_KNOCKED);
	    TP->move_living(query_verb(), other_room);
	}
        else if (query_friend_or_foe(TP) < 0)
	{
	    ENV(TO)->close_gate_to_stop_invaders(TP);
	}
	else if (query_friend_or_foe(TP) == 0 && 
		  find_object(CLOCK)->query_war())
	{
	    ENV(TO)->close_gate();
	    ENV(TO)->suspicious_to_entry(TP);
	}
        else
	{
	    TP->move_living(query_verb(), other_room);
	}
    }
    else
	write(check_call(fail_pass));

    return 1;
}
