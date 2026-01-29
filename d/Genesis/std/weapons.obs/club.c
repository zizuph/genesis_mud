/*
 *  ~Genesis/std/weapons/club.c
 *
 * So far, just your basic club.
 * What ought to be done:
 *    1) set up way to specify construction and quality of weapon.
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
 * Function name: create_club
 * Description: Default for clones, sets up so we know we ARE a clone.
 */
void
create_club()
{
    ::create_stdweapon();
    set_long("This weapon should be described by a wizard.\n");
}

/*
 * Function name: create_stdweapon
 * Description: Set up a generic club.
 */
nomask void
create_stdweapon() 
{
    set_material("oak");
    set_hit(15);
    set_pen(15);

    add_prop(OBJ_I_VOLUME,2500); 

    create_club();

    set_name("club");

    set_wt(W_CLUB);
    set_dt(W_BLUDGEON);
    set_hands(W_ANYH);
}