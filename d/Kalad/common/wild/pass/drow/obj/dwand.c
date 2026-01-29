/*
 * A very basic wand, which will be the "common loot"
 * from the drow instead of the dhwand.c ( healing wand).
 *
 * Created Sep 2017, by Andreas Bergstrom ( Zignur )
 *
 */
inherit "/std/object";
inherit "/lib/holdable_item";
inherit "/lib/keep";

#include "/d/Kalad/defs.h"


/* Prototypes */

public void
create_wand()
{
    // Mask this function to customize the wand.
}

void
create_object()
{
    set_name("wand");
    set_adj("long");
    add_adj("ceremonial");
    add_adj("onyx");
    set_long("This is a long ceremonial onyx wand, commonly"
      + " used by the drow priestesses in various rituals."
      + " It does not seem to hold any magical properties"
      + " though.\n" );
    
    add_prop(OBJ_I_VALUE,1728);
    add_prop(OBJ_I_WEIGHT,250);
    add_prop(OBJ_I_VOLUME,250);

    set_slots(W_ANYH);

    // Call the create_wand function for customization purposes
    create_wand();
}

void
leave_env(object env, object to)
{
    ::leave_env(env, to);
    holdable_item_leave_env(env, to);
}

