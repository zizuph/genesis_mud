inherit "/std/door";
inherit "/d/Gondor/morgul/feeling.c";

#include <macros.h>
#include "/d/Gondor/defs.h"

create_door()
{
  ::create_door();
  set_door_id("morgulgate");
  set_pass_command(({"s","south"}));
  set_door_name(({"dark gate","gate","morgul gate"}));
  set_other_room(MORGUL_DIR + "city/i_ngate");
  set_door_desc(VBFC_ME("long_desc"));
  set_open(0);
  set_locked(1);
  set_key("Morgul_Key");
   set_knock_command(0);
}

string long_desc()
{
  if(open_status)
  {
    return BSN("The open gate is shaped like a gaping mouth. Inside " +
      "the gate everything is dark, and you cannot make out anything. " +
      "Thick steel spikes are looming down from the wall above the gate, " +
      "looking like gleaming teeth.");
  }
  else
  {
    return BSN("The dark gate is closed. It is made of two large " +
      "black wings covered with thick black metal plates. From the " +
      "wall above the gate thick steel spikes are looming down. ");
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
        if (query_feeling(TP) > -1)
            ENV(TO)->close_gate_to_stop_invaders(TP);
        else
	    TP->move_living(query_verb(), other_room);
    }
    else
	write(check_call(fail_pass));

    return 1;
}

