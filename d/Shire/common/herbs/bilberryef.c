/*
  Effect for bilberry herb
  Thanks to palmer for doing it.
  Finwe, March 2003
 
  ChangeLog:
  April 1, 2004 - Palmer
  Upped light level to 10 to offset dark root
 
  April 29, 2004 - Palmer
  Capped effect at 10, cut effect time in half,
  cut effect from 10 to 5

  October 8, 2004 - Finwe
  Set effect to 2 per Gorboth's request since Darkroot does the same,
  and set time to 30 seconds, too.

  April 19, 2008
  Updated by Mercade. Remember the effect you set and unset the same.
  Otherwise it's not compatible with other effects that work in parallel.
 */

#include <ss_types.h>
 
inherit "/d/Shire/common/lib/effect";

#include <stdproperties.h>

/* Global variable. */
static int extra_vision = 0;

void
create_effect()
{
    set_name("_bilberry_effect_");
    set_time((30 + ( ( random(3) ) * 60 ) ));
}

void
do_start_effect(object who)
{
/*    
    c = query_vision();
    
    if (c <= 10)
        c += 5;
*/
    extra_vision = 2;

    who->catch_tell("Your eyes begin to tingle.\nThings suddenly shift into sharper view.\n");
    /* Must apply effect as delta, (duh) for otherwise it won't be
     * compatible with other similar effects. /Mercade, 19 April 2008. */
    who->add_prop(LIVE_I_SEE_DARK, who->query_prop(LIVE_I_SEE_DARK) + extra_vision);
}
 
void
do_stop_effect(object who)
{
    who->catch_tell("You blink your eyes rapidly.\nYour vision returns to normal.\n");
    /* Must apply effect as delta, (duh) for otherwise it won't be
     * compatible with other similar effects. /Mercade, 19 April 2008. */
    who->add_prop(LIVE_I_SEE_DARK, who->query_prop(LIVE_I_SEE_DARK) - extra_vision);
}
