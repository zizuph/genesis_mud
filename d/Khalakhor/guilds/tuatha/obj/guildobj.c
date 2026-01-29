/* File         : /d/Khalakhor/guilds/tuatha/obj/guildobj.c
 * Creator      : Teth@Genesis
 * Copyright:   : Daniel Mosquin
 * Date         : August 12, 1998
 * Purpose      : This is the Tuatha De Danaan guild object.
 * Related Files: 
 * Comments     : TODO: add a desc, make it vbfc
 *                      add in appraisal via lore skill
 *                      add in func comments
 *                      security issues with entering/leaving inv
 *                      redefine wear() and remove() messages
 *                      ensure presence for spells to be cast?
 * Modifications:
 */

#pragma no_inherit
#pragma save_binary
#pragma strict_types

inherit "/d/Khalakhor/std/object";
inherit "/lib/wearable_item";

#include <stdproperties.h>
#include <wa_types.h>

#include "../guild.h"

/*
 * Function name : create_khalakhor_object
 * Purpose       : The constructor function.
 */
public void
create_khalakhor_object()
{
    set_name("torc");
    add_name("torque"); // Alternate spelling.
    add_name("band");
    set_adj("gold");
    add_adj("twisted");
    add_adj("metal");
    set_short("gold torc");    
    set_long("This is a gold torc.\n");

    config_wearable_item(A_NECK, 2, 1, this_object());

    add_prop(OBJ_I_VALUE, 2339);
    add_prop(OBJ_I_VOLUME, 101);
    add_prop(OBJ_I_WEIGHT, 1919);
}

void
leave_env(object from, object to)
{
     ::leave_env(from, to);

     wearable_item_leave_env(from, to);
}

void
appraise_object(int num)
{
    ::appraise_object(num);

    appraise_wearable_item();
}
