/*    history:
*    coder(s):    Amelia
*    
*
*/

inherit "/std/room";
inherit "/d/Calia/sea/specials/room_tell";
#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
#define SWALLOWED "_i_swallowed_by_clam"


void
create_room()
{
   
   set_short("Inside a giant clam");
   set_long("You are inside a giant clam. It is very dark and "+
      "wet here. You are engulfed in some soft, fleshy "+
      "substance. There appears to be no way out!\n");
   
   add_prop(ROOM_I_LIGHT, 0);
   add_prop(ROOM_I_IS, 1);
   add_prop(ROOM_I_INSIDE, 1);
   
   set_tell_time(15);
   add_tell("The clam tries to digest you.\n");
   add_tell("The clam burps loudly, emitting a jet of water.\n");
}

void
init()
{
   object tp = this_player();
   int id;
   ::init();
   id = set_alarm(45.0, 0.0, "spit_out", tp);
}

void
enter_inv(object ob, object from)
{
   
   
   ::enter_inv(ob, from);
   if (interactive(ob))
      {
      start_room_tells();
   }
}

int
spit_out(object tp)
{
    int old, new;
    old = tp->query_prop(SWALLOWED);
    if (old == 2)
    {
        tp->catch_msg("The clam digests you totally.\n");
        tell_room(environment(tp), "The clam totally digests "+
            QTNAME(tp)+".\n",tp);
            reset_euid();
        tp->add_prop(LIVE_I_NO_CORPSE,1);
        tp->heal_hp(-tp->query_max_hp());
        tp->do_die(this_object());
        return 1;
    }
    new = old + 1;
    tp->add_prop(SWALLOWED, new);
   tp->catch_msg("The clam spits you out!\n");
    tell_room(E(tp), "The clam spits out "+QTNAME(tp)+".\n",tp);
   tp->move_living("M", CLAM_ROOM, 1);
   tell_room(environment(tp), QCTNAME(tp)+ " flies out of the clam's mouth and lands in the water hard.\n", tp);
   tp->catch_msg("Splash! you land in the sea.\n");
   return 1;
}
