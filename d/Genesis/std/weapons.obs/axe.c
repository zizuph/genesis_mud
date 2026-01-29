/*
 *  ~Genesis/std/weapons/axe.c
 *
 * So far, just your basic axe.
 * Wishlist:
 *    1) set up ways to specify quality of blade.
 *    2) Seperate haft from blade in the volume/price/weight computations.
 *
 * If other things should be added, please feel free to modify
 * this file and then contact an Arch to have it installed.
 *
 */
 
#pragma save_binary

inherit "/d/Genesis/std/weapons/stdweapon";

#include "wa_types.h"
#include "/sys/stdproperties.h"

/*
 * Function name: create_axe
 * Description: Default for clones, sets up so we know we ARE a clone.
 */
void
create_axe()
{
    ::create_stdweapon();
    set_long("This weapon should be described by a wizard.\n");
}

/*
 * Function name: create_stdweapon
 * Description: Set defaults for an axe.
 */
nomask void
create_stdweapon() 
{
    set_material("steel");
    set_hit(10);
    set_pen(10);
    add_prop(OBJ_I_VOLUME, 75); 
    set_hands(W_ANYH);

    create_axe();

    set_name("axe");

    set_wt(W_AXE);
    set_dt(W_IMPALE|W_BLUDGEON);
}

/*
 * Function name: enter_env
 * Description: Called every time the object changes environments.
 *    Used here to prevent putting the axe in a bag.
 * Arguments: 'to'   - the destination
 *            'from' - the source
 */
void
enter_env(object to, object from)
{
    /* 
     * Allow us to move into a living, a room, 
     * a rigid container, or a sheath. 
     */
    if (!to->query_prop(ROOM_I_IS)&&
       !to->query_prop(LIVE_I_IS)&&
       !to->query_prop(CONT_I_RIGID)&&
       (member_array("corpse", to->query_names()) < 0)&&
       (member_array("sheath", to->query_names()) < 0))
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
        write("The axe would damage the " + descr + "!\n");
        write("You remove it from the " + descr +".\n");
}