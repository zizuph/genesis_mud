/*
 * /d/Genesis/std/weapons/polearm.c
 *
 * Very Generic polearm of Genesis.  Provides common functions of all swords.
 *
 * WISHLIST:
 *
 */
#pragma save_binary

inherit "/d/Genesis/std/weapons/stdweapon.c";

#include "wa_types.h"
#include "stdproperties.h"

/*
 * Function name: create_polearm
 * Description: Go ahead and make the weapon, but ensure the values are
 * reasonable when we're done.
 */
void
create_polearm()
{
    ::create_stdweapon();
    set_long("This polearm is unconfigured.\n");
}

/*
 * Function name: create_stdweapon
 * Description: Go ahead and make the weapon, but ensure the values are
 * reasonable when we're done.
 */
void
create_stdweapon()
{
    set_material("steel");
    create_polearm();
    add_name("polearm");
    set_wt(W_POLEARM);
    set_hands(W_BOTH);
}

/*
 * Function name: enter_env
 * Description: Called every time the object changes environments.
 *    Used here to prevent putting the polearm in a bag.
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
       !to->query_prop(CONT_I_RIGID)&&
       !to->query_prop(CORPSE_S_RACE)&&
       (member_array("scabbard", to->query_names()) < 0))
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
        write("The polearm s much too long for the " + descr + "!\n");
        write("You remove it from the " + descr +".\n");
}