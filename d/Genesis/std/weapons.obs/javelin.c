/*
 * /d/Genesis/std/weapons/javelin.c
 *
 * Very Generic javelin of Genesis.  Provides common functions of all javelins.
 *
 * WISHLIST:
 *    1. Be nice if you could throw it.
 *    2. Be even better if you could hit anything when thrown.
 *
 */
#pragma save_binary

inherit "/d/Genesis/std/weapons/stdweapon.c";

#include "wa_types.h"
#include "stdproperties.h"

/*
 * Function name: create_javelin
 * Description: Go ahead and make the weapon, but ensure the values are
 * reasonable when we're done.
 */
void
create_javelin()
{
    ::create_stdweapon();
    set_long("This javelin is unconfigured.\n");
}

/*
 * Function name: create_stdweapon
 * Description: Go ahead and make the weapon, but ensure the values are
 * reasonable when we're done.
 */
void
create_stdweapon()
{
    set_material("oak");
    create_javelin();

    add_name("javelin");
    set_wt(W_POLEARM);
    set_hands(W_BOTH);
}

/*
 * Function name: enter_env
 * Description: Called every time the object changes environments.
 *    Used here to prevent putting the javelin in a bag.
 * Arguments: 'to'   - the destination
 *            'from' - the source
 */
void
enter_env(object to, object from)
{
    /* 
     * Allow us to move into a living, a room, 
     * a rigid container, or a scabbard. 
     */
    if (!to->query_prop(ROOM_I_IS)&&
       !to->query_prop(LIVE_I_IS)&&
       !to->query_prop(CORPSE_S_RACE)&&
       !to->query_prop(CONT_I_RIGID))
    {
        call_out("do_reject_message", 1, to->short());
        this_object()->move(from);
    }
}

/* 
 * Function name: do_reject_message
 * Description: Called in case of failure to print a correct message
 */ 
void
do_reject_message(string descr)
{
        write("The javelin is much too long for the " + descr + "!\n");
        write("You remove it from the " + descr +".\n");
}