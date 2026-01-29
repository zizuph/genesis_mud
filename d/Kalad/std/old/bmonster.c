/*
   /d/Kalad/std/bmonster.c
   
   Kalad standard base monster.
   
   Fysix@Genesis, Oct 1997
 */
#pragma strict_types
#pragma save_binary

inherit "/std/monster";
inherit "/d/Kalad/lib/prestige";

#include <stdproperties.h>
#include <filter_funs.h>

/* Function name: attacked_by
 * Description:   Masked this function to let everybody in
 *                the environment know that I am attacked.
 *                Is used for letting guards assist me.
 * Arguments:     object attacker
 */
public void
attacked_by(object attacker)
{
   ::attacked_by(attacker);

   // If I attacked myself, don't call notify_ob_attacked_me
   if (calling_function() != "combat_init")
      FILTER_LIVE(all_inventory(environment()) - ({this_object()}))->
         notify_ob_attacked_me(this_object(), attacker);
}

/* Function name: create_kalad_monster
 * Description:   Creation function of the standard Kalad monster.
 */
public void
create_kalad_monster()
{
}

// Not nomask for backwards compatibility
public void
create_monster()
{
    add_prop(NPC_M_NO_ACCEPT_GIVE, "@@mobile_deny_objects");

    create_kalad_monster();
}
