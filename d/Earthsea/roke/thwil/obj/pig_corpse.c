#include <stdproperties.h>
inherit "/std/corpse";

object tied_to;

void create_corpse()
{
  add_name("corpse");
  add_name("corpse of a pig");
  add_name("remains");
  add_name("remains of of a pig");
  set_short("bloodied corpse of a pig");
  set_pshort("bloodied corpses of pigs");
  set_long("This is the bloodied corpse of a pig.\n");
  change_prop(CONT_I_WEIGHT, 50000);
  change_prop(CONT_I_VOLUME, 50000);
  decay_id = set_alarm(60.0, 60.0, decay_fun);
}

int tie_object(object rope, string str)
{
  tied_to = rope;
  return 1;
}

int untie_object(object rope)
{
  if (rope == tied_to)
    {
      tied_to = 0;
      return 1;
    }
  return 0;
}
