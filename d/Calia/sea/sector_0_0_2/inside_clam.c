
/*   
 *   The inside of a clam in the water area, a less pleasant part of the 
 *   mermaid quest that happens if a player attacks the clam. Players are 
 *   moved here when swallowed. 
 *   If they have been swallowed before, they've already had their 
 *   warning, so they are digested this time after a while. Otherwise, 
 *   they're spat out. 
 * 
 *    coder(s):    Amelia  1995
 *    Modifications by Maniac 9/9/96
 *    Added log file for deaths July 8/2003
 *
 */

inherit "/d/Calia/std/water_room";

#include <stdproperties.h>
#include <macros.h>
#include "defs.h"

#include SEA_QUESTS


void
create_water_room()
{
   set_short("Inside a giant clam");
   set_long("You are inside a giant clam. It is very dark and "+
      "wet here. You are engulfed in some soft, fleshy "+
      "substance. There appears to be no way out!\n");

   add_prop(ROOM_I_LIGHT, 0);
   add_prop(ROOM_I_INSIDE, 1);

   set_tell_time(25);
   add_tell("The clam tries to digest you.\n");
   add_tell("The clam burps loudly, emitting a jet of water.\n");
}


int
spit_out(object tp)
{
    if (!objectp(tp) || !objectp(present(tp, this_object())))
        return 0;

    if (tp->query_prop(PLAYER_I_MERMQ_CLAMMED_UP))
    {
        tp->catch_msg("The clam digests you totally.\n");
        tell_room(environment(tp), "The clam totally digests "+
            QTNAME(tp)+".\n",tp); 

        reset_euid();

        if (tp->query_wiz_level()) {
            tp->catch_msg("You would have died now wiz!\n"); 
            return 1;
        }

        tp->add_prop(LIVE_I_NO_CORPSE, 1);
        tp->heal_hp(-tp->query_max_hp());
        tp->do_die(this_object());
        log_file("clam_death_log",capitalize(tp->query_real_name()) + 
            " was eaten by the clam, " + ctime(time()) + ".\n");
        return 1;
    }

   tp->add_prop(PLAYER_I_MERMQ_CLAMMED_UP, 1);
   tp->catch_msg("The clam spits you out!\n");
   tell_room(environment(tp), "The clam spits out "+QTNAME(tp)+".\n",tp);
   tp->move_living("M", CLAM_ROOM, 1);
   tell_room(environment(tp), QCTNAME(tp)+ " flies out of the " +
                       "clam's mouth and into the water!\n", tp);
   tp->catch_msg("Splash! You land in the sea.\n");
   return 1;
}


void
enter_inv(object ob, object from)
{
   ::enter_inv(ob, from);
   if (interactive(ob))
       set_alarm(35.0, 0.0, &spit_out(ob));
}

