inherit "/d/Shire/room";
#include "/secure/std.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/d/Gondor/defs.h"

create_room()
{
   ::create_room();
   set_long(break_string(
         "This is Dunstable's Lord Room, where he administers the Shire."+
         " Many are the exits leading forth from here to important places"+
         " that he must travel to. There are no comforts here, it is"+
         " all work and little play.\n",70));
}

nomask void
enter_inv(object obj, object from)
{
   if(living(obj))
      { 
      tell_object(obj, "You slide down a greased chute, ");
     tell_object(obj, "and end up in a new place.\n");
      say(
        capitalize(QCTNAME(obj))+ "comes sliding down the chute.\n");


   obj->move("/d/Shire/common/hollin/crevice");

    }
}
