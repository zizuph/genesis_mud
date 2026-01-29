// Rat tail
// Made by Boriska@Genesis, Nov 1994

inherit "/std/object";

#include <stdproperties.h>
#include "/d/Avenir/common/dark/dark.h"

create_object()
{
  if (!IS_CLONE)
    return;
  
  set_name ("tail");
  set_short ("rat tail");
  add_adj ("rat");
  set_long ("Blooded rat tail. How disgusting!\n");
  add_prop (OBJ_I_WEIGHT, 30);
  add_prop (OBJ_I_VOLUME, 30);
  add_prop (OBJ_I_VALUE, 5);

  set_alarm (300.0, 0.0, "decay");
}

void
decay ()
{
  object env = environment();

  seteuid(getuid());
  if (env)
    {
      tell_room (env, "The rat tail decays, leaving some pitiful remains.\n");
      clone_object (OBJ + "r_meat")->move(env);
    }
  remove_object(); // in any case
}
