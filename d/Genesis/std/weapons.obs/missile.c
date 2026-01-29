/*
 *  ~Genesis/std/weapons/missile.c
 *
 * So far, just your basic missile. (Broken at that)
 *
 * Objects inheriting this file may be fired from missile casters 
 * of the correct type.
 *
 * What ought to be done:
 *    1) set up ways to specify quality of missile.
 *    2) Make it act like a missile 8)
 *    3) Treat missile casting as spell casting.
 *    4) Make wielder more vulnerable while preparing to cast.
 *    5) Some reasonable concept of range would be nice, but is beyond scope
 *       of this object -- mudlib changes are needed.
 *    6) you shouldn't be able to use missiles while meleeing.
 *    7) shooting missiles into melee could hit either opponent.
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
 * Function name: create_missile
 * Description: Default for clones, sets up so we know we ARE a clone.
 */
void
create_missile()
{
    ::create_stdweapon();
    set_long("This weapon should be described by a wizard.\n");
}

/*
 * Function name: create_stdweapon
 * Description: Set up a generic missile.
 */
nomask void
create_stdweapon() 
{
    set_material("oak");
    set_hit(10);
    set_pen(10);
    add_prop(OBJ_I_VOLUME, 75); 
    set_dt(W_SLASH);
    set_hands(W_ANYH);

    create_missile();

    set_name("missile");
    set_wt(W_MISSILE);
}