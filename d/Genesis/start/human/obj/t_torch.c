// A torch carried by dark/mon/t_goblin
// Made by Boriska, Feb 28 1995

inherit "/std/torch";

#include <stdproperties.h>

void
create_torch()
{
  set_name("torch");
  add_name("_medium_torch");
  set_short("medium torch");
  add_adj("medium");
  set_long("Is is a wooden stick with some oiled rugs rolled around it.\n" +
	   "Hopefully it provides more light than smoke.\n");
  set_time(800);
}

int
light_me_after_delay()
{
    tell_room(environment(this_player()),
	   "The torch fills the air with black smoke. Thankfully, " +
	      "it emits some light as well.\n");
    return ::light_me_after_delay();
}
