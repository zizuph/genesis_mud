/*
*  Balrog's whip stun
*
*  This object is used for the whip stun
*
*
*  Created by Znagsnuf.
*
*
*  Date:                      What is done:                            By whom:            
*  ----------------------------------------------------------------------------
*  01/05-17                   Started remaking it                      Znagsnuf
*
*/

inherit "/std/paralyze";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Gondor/defs.h"

string whip_stun_start();
string whip_stun_stop();

/*
 * Function name: set_remove_time
 * Description  : Set how long time player should be paralyzed (in seconds).
 * Arguments    : int time - the time to set.
 */
void
set_remove_time(int time)
{
    remove_time = time;
}

/*
 * Function name: query_remove_time
 * Description  : Returns the paralyze time (in seconds).
 * Returns      : int - the time.
 */
int
query_remove_time()
{
    return remove_time;
}

void
create_paralyze()
{
    set_name("_balrig_whip_object");
    set_long("A whip stun.\n");
    add_prop(OBJ_I_WEIGHT,  1);
    add_prop(OBJ_I_VOLUME,  1);
    add_prop(OBJ_M_NO_SELL, 1);
    add_prop(OBJ_I_NO_DROP, 1);

    set_no_show();
    set_stop_verb("");

    set_fail_message("You are hold back by the flames, hindering your "
                    + "movements!\n");
    set_stop_message("The burning flames around your leg finally let go"
                   + ".\n");
}

/*
 * Function name: enter_env
 * Description  : When we enter an interactive environment, add a subloc to
 *                indicate that the person is writing something.
 * Arguments    : object to - the object we are entering.
 *                object from - the object we come from.
 */
void
enter_env(object to, object from)
{
    ::enter_env(to, from);

    if (!objectp(to) || !living(to))
    {
      remove_object();
      return;
    }

    //Send emotes.
    whip_stun_start();

}

string
whip_stun_start()
{

    ENV(TO)->add_prop(LIVE_S_EXTRA_SHORT, ", who is hindered by flames");
    ENV(TO)->catch_msg("Flames around your legs, hinders your movement.\n");
    tell_room(ENV(ENV(TO)), QCTNAME(ENV(TO)) + " is hindered by the burning "
        +"flames around " + HIS_HER(ENV(TO)) + " leg.\n", ENV(TO));

    return "";
}

string
whip_stun_stop()
{

    //ENV(TO)->remove_prop(LIVE_S_EXTRA_SHORT);
    ENV(TO)->remove_prop(LIVE_S_EXTRA_SHORT, ", who is hindered by flames");
    tell_room(ENV(ENV(TO)), QCTNAME(ENV(TO)) + " is able to move again as "
                           + "the flames let go of " + HIS_HER(ENV(TO)) 
                           + " leg.\n", ENV(TO));
    return "";
}

/*
 * Function name: leave_env
 * Description  : When you inherit /lib/holdable_item.c you MUST also define
 *                the function leave_env() as copy of this function. It MUST
 *                make the call to holdable_item_leave_env(from, to) as well.
 *                If you omit this, then the item will not be automatically
 *                released when the player drops it, for instance.
 *                PS: This is just a dummy function. It does not exist. You
 *                    must write your own as copy of this one.
 * Arguments    : object from - the environment we are leaving.
 *                object to   - the environment we are entering.
 */
void
leave_env(object old, object dest)
{
     // Stop emotes.
      whip_stun_stop();
    ::leave_env(old, dest);
}