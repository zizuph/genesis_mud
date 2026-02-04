/*
 * /d/Terel/mountains/ghastly_keep/obj/g_throw_stun.c
 *
 * The stun object for the Brew stun.
 *
 * Znafsnuf
 *
 * - Language tweak complete (Gorboth)
 *
 */

inherit "/std/paralyze";

#include "defs.h"

string freezing_stun_start();
string freezing_stun_stop();

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
    set_name("_g_stun_object");
    set_long("A freezing stun.\n");
    add_prop(OBJ_I_WEIGHT,  1);
    add_prop(OBJ_I_VOLUME,  1);
    add_prop(OBJ_M_NO_SELL, 1);
    add_prop(OBJ_I_NO_DROP, 1);

    set_no_show();
    set_stop_verb("");

    set_fail_message("You are frozen solid to the ground, hindering your "
                    + "movements!\n");
    set_stop_message("The icy liquid metal is melting, and you can finally "
                    + "move again.\n");
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
    freezing_stun_start();

}

string
freezing_stun_start()
{

    ENV(TO)->add_prop(LIVE_S_EXTRA_SHORT, ", who is frozen solid to the ground");
    ENV(TO)->catch_msg("You are frozen to the ground.\n");
    tell_room(ENV(ENV(TO)), QCTNAME(ENV(TO)) + " is frozen solid to the "
              + "ground.\n", ENV(TO));

    return "";
}

string
freezing_stun_stop()
{

    ENV(TO)->remove_prop(LIVE_S_EXTRA_SHORT);
    tell_room(ENV(ENV(TO)), QCTNAME(ENV(TO)) + " is slowly melting from the "
              + "ground.\n", ENV(TO));
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
     freezing_stun_stop();
    ::leave_env(old, dest);
}