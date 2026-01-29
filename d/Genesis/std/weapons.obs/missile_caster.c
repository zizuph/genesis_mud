/*
 *  ~Genesis/std/weapons/missile_caster.c
 *
 * So far, just your basic missile caster. (Broken at that)
 * What ought to be done:
 *    1) set up ways to specify quality of missile.
 *    2) Make it act like a missile caster 8)
 *    3) Using a missile caster should make you more vulnerable.
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
 * Function name: create_missile_caster
 * Description: Default for clones, sets up so we know we ARE a clone.
 */
void
create_missile_caster()
{
    ::create_stdweapon();
    set_long("This weapon should be described by a wizard.\n");
}

/*
 * Function name: create_stdweapon
 * Description: Set up a generic missile caster.
 */
nomask void
create_stdweapon() 
{
    set_material("oak");

    set_hit(0);
    set_pen(0);

    add_prop(OBJ_I_VOLUME, 75); 
    set_hands(W_BOTH);

    create_missile_caster();

    set_dt(0);
    set_wt(W_MISSILE);
}