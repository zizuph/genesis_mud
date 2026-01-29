#include "defs.h"
#include <ss_types.h>
#include <filter_funs.h>

inherit "/std/shadow";

object jealousy;
object lochaber;

/*
 * Function name: set_jealousy
 * Description  : Simply sets the 'jealousy' var.
 *                This variable is used to tell the 
 *                shadow to remember to give the axe's
 *                wielder a spanking.
 * Arguments    : object ob - Object pointer to the player that
 *               made the axe jealous.
 * Returns      : n/a
 */
public void
set_jealousy(object ob)
{
    jealousy = ob;
}

/*
 * Function name: remove_jealousy
 * Description  : Simply removes the 'jealousy' var.
 * Arguments    : n/a
 * Returns      : n/a
 */
public void
remove_jealousy()
{
    jealousy = 0;
}

/*
 * Function name: query_jealousy
 * Description  : Queries the jealousy var.
 * Arguments    : n/a
 * Returns       : Object pointer to the player who made the
 *                axe jealous.
 */
public object
query_jealousy()
{
    return jealousy;
}

/*
 * Function name: move_living (MASK)
 * Description  : Called when a living is moved between
 *                environments. Masked here to prevent
 *                players from changing environments when
 *                locked into a fight started by a jealous
 *                axe by means other than teleportation.
 * Arguments    : see 'sman move_living'
 * Returns      : see 'sman move_living'
 */
public varargs int
move_living(string how, mixed to_dest, int dont_follow, int no_glance)
{
  /* If the axe is jealous... */
    if (jealousy && jealousy == shadow_who)
    {
      /* And the player's in a fight... */
        if (shadow_who->query_attack())
        {
          /* And the move isn't a teleport... */
            if (how != "X")
            {
              /* Have a good fight, you've got no choice. */
                tell_object(shadow_who, "You feel the lochaber " +
                    "axe resist your attempt to leave, kill or " +
                    "be killed!\n");
                return 7;
            }
        }
    }
    return shadow_who->move_living(how, to_dest, dont_follow, no_glance);
}

/*
 * Function name: set_caller
 * Description  : Sets the 'lochaber' variable as an
 *                object pointer to shadow_who's lochaber
 *                axe, so it can interract with the shadow.
 * Arguments    : object ob - Object pointer to lochaber
 *                            axe responsible for this 
 *                            shadow.
 * Returns      : n/a
 */
public void
set_caller(object ob)
{
    lochaber = ob;
}

/*
 * Function name: execute_jealousy
 * Description  : Exacts revenge from the axe if the player
 *                made the mistake of picking up another 
 *                magic weapon while wielding the lochaber
 *                axe.
 * Arguments    : object who - Object pointer to the living
 *                             to force the wielder to attack.
 * Returns      : n/a
 */
public void
execute_jealousy(object who)
{
  /* Make sure the person this shadow is shadowing */
  /* is the person wielding the lochaber axe. */
    if (shadow_who != lochaber->query_wielded())
        return;

    lochaber->jealous_revenge(jealousy);
    shadow_who->set_stat_extra(SS_DIS, 200);
    shadow_who->command("$kill " + OB_NAME(who));
    shadow_who->set_stat_extra(SS_DIS, 0);
}

/*
 * Function name: try_jealous_attack
 * Description  : While the axe is jealous, this function is
 *                called every now and then to see if the player
 *                should attack anyone available.
 * Arguments    : n/a
 * Returns      : n/a
 */
public void
try_jealous_attack()
{
    object target, 
           *arr;
    int i;

  /* Don't do anything if the axe isn't jealous. */
    if (!jealousy || jealousy != shadow_who)
        return;

  /* Axe is jealous, look for a victim. */
  /* If no victim, nothing happens. */
    arr = FILTER_OTHER_LIVE(all_inventory(environment(shadow_who)));
    if (!sizeof(arr))
        return;

  /* Go through all possible victims in the room and */
  /* look for the biggest target. */
    for (i = 0; i < sizeof(arr); i++)
    {
        if (!target)
        {
            target = arr[i];
        }
        else if (target->query_average_stat() <
            arr[i]->query_average_stat())
        {
            target = arr[i];
        }
    }

    execute_jealousy(target);
}      

public void
init_living()
{
    shadow_who->init_living();
    if (jealousy)
        try_jealous_attack();
    lochaber->check_other_magic();
}
