/* This is a magic lighter, that lights up the room. It's cloned by the
* light spell, and should never be seen by players.
*/

inherit "/std/monster";
#include <stdproperties.h>

query_mm_in(){ return "lands on your nose"; }
void
create_monster()
{
   set_living_name("Fatty");
   set_name("Fatty");
   add_name("fatty");
   set_short("Fatty");
   set_chat_time(1);
   add_chat("Hi!");
   add_chat("Have anything to eat?");
   add_chat("Where did all the donuts go?");
   enable_commands();
}

void set_duration(int dur) { call_out("remove_object", dur); }

void
enter_env(object dest, object old)
{
   if (dest && dest->query_prop(ROOM_I_IS))
      tell_room(dest, "Fatty lands on your nose.\n");
}

void
leave_env(object old, object dest)
{
   if (old && old->query_prop(ROOM_I_IS))
      tell_room(old, "Fatty folds himself in half till he is gone.\n");
}

