/*
 * /d/Genesis/std/wearable_pack.c
 *
 *  Standard pack code to be inherited for creating receptacles
 *  which may be worn and filled/emptied in bulk. If neither of these
 *  things are required just use a standard receptacle. 
 *
 *  Creation function: 
 *  ------------------
 *  create_wearable_pack()
 *
 *  See /d/Genesis/std/pack.c for more information.
 */

#pragma save_binary
#pragma strict_types

#include <wa_types.h>

inherit "/d/Genesis/std/pack";
inherit "/lib/wearable_item";

/* Ensure here that the player removes the pack first if 
 * it leaves his/her inventory.
 */
void
leave_env(object old, object dest)
{
    ::leave_env(old, dest);

    wearable_item_leave_env(old, dest);
}

/* Ensure that the player can properly appraise this item. 
 */
void
appraise_object(int num)
{
    ::appraise_object(num);

    appraise_wearable_item();
}

/******** Creation and Initialisation Functions ********/

public void
create_wearable_pack()
{
}

nomask void
create_pack()
{
    set_slots(A_BACK);
    set_layers(15);
    set_looseness(8);    
    create_wearable_pack();
}

