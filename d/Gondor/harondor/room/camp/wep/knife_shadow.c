/* Name      : /w/toby/obj/knife_shadow.c
 * Purpose   : The shadow to the knife of parry.
 *             Using this shadow to mask the skillbonus
 *             from players wielding the knife.
 * Created by: Toby Windahl (Toby), 20:th of June 2001
 * 
 *   Modified: 2005-11-23, Sir Toby
 *                         Modified to work with the
 *                         Genesis mudlib.
 */

#include <stdproperties.h>
#include <macros.h>
#include <filter_funs.h>
#include <ss_types.h>
#include "/w/toby/path.h"

inherit "/std/shadow";

/* KNIFE_RANDOM = random(2) from the cloned knife */
int KNIFE_RANDOM = (PATH + "obj/knife")->query_knife_random();

#define KNIFE_BONUS_PARRY     KNIFE_RANDOM+3
#define KNIFE_BONUS_DEFENCE   KNIFE_RANDOM+2

void
remove_knife_effect()
{
  set_alarm(2.0, 0.0, &remove_shadow());
}


int
query_skill(int snum)
{
    if ( (snum == SS_PARRY || snum == SS_DEFENCE) && 
		calling_program() == "cmd/live/state.c")
        return query_shadow_who()->query_skill(snum);


    switch (snum)
    {
        case SS_PARRY:
            return query_shadow_who()->query_skill(SS_PARRY) + KNIFE_BONUS_PARRY;
        case SS_DEFENCE:
            return query_shadow_who()->query_skill(SS_DEFENCE) + KNIFE_BONUS_DEFENCE;
        default:
            return query_shadow_who()->query_skill(snum);
    }
}



