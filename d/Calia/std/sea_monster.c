
/* 
   Sea creatures can be netted when they are killed so that they 
   don't sink. 

   Maniac
*/ 

#pragma save_binary

inherit "/std/monster"; 

#include "/d/Calia/sys/water.h"
#include "/d/Calia/sea/sea_defs.h"

#include <std.h>
#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>
#include <filter_funs.h>


#define CEX if (!combat_extern) combat_reload()


/*
 * Function name:   do_die
 * Description:     Called from enemy combat object when it thinks we died.
 * Arguments:       killer: The enemy that caused our death.
 */
public void
do_die(object killer)
{
    object * players = FILTER_PLAYER_OBJECTS(all_inventory(environment(killer)));
    players -= ({ killer });
    players = ({ killer }) + players; // ensure killer is first
    foreach (object player : players)
    {
        object net = present(SEA_NET_ID, killer);
        if (!objectp(net))
        {
            continue;
        }
        net->sea_creature_do_die_post_actions(killer);
        break;
    }
    
    ::do_die(killer);
}
