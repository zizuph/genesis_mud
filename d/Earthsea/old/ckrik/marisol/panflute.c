inherit "/d/Earthsea/std/object.c";

#include "/sys/stdproperties.h"
#include "/sys/formulas.h"
#include "/sys/macros.h"

void
create_earthsea_object()
{
  set_name("flute");
  set_pname("flutes");

  set_adj("pan");

  set_short("pan flute");
  set_pshort("pan flutes");
  
  set_long("A goat herder's pan flute. This flute does not really " +
	   "bear much resemblence to a normal flute. It is made of " +
	   "many tubes attached together, each " +
	   "successive tube shorter than its predecesor.\n");

  add_prop(OBJ_I_VALUE, 250 + random(20));
  add_prop(OBJ_I_WEIGHT, 200);
  
  add_prop(OBJ_I_VOLUME, 350);
}

void
init()
{
  ::init();
  add_action("play", "play");
  add_action("play", "blow");
}

int
play(string str)
{
  if (str == "pan flute" || str == "flute")
    {
      this_player()->catch_msg("You blow into the pan flute and " +
			       "beautiful music flows out from the " +
			       "flute.\n");
      tell_room(environment(this_player()), QCTNAME(this_player()) + 
		" blows into the pan flute and beautiful music " +
		"flows out from the flute.\n", this_player());
      return 1;
    }

  return 0;
}
