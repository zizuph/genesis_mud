/*
 *  /d/Gondor/clubs/nisse/obj/glove.c
 *
 *  The glove for the Nisse Ohtar. They need it for carrying their hawks
 *  on a wrist.
 *
 *  Deagol, April 2003
 */

#pragma save_binary
#pragma strict_types

inherit "/std/object";
inherit "/lib/wearable_item";
inherit "/lib/keep";

#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>

#include "/d/Gondor/defs.h"
#include "../nisse_defs.h"

void
create_object()
{
    ::create_object();
    
    set_name("glove");
    add_name(NISSE_GLOVE_ID);
    set_adj("leather");
    add_adj("cowhide");
    set_short("leather glove");
    set_long("This soft leather glove is tough and durable. It appears to " +
        "be made from cowhide which will protect your hand and arm from " +
        "even the sharpest talons. This glove seems to be crafted " +
        "especially for falconry. The glove fits snuggly and seem to be " +
        "made for smaller hands.\n");

    add_prop(OBJ_I_VALUE, 110);

    config_wearable_item(A_L_HAND, 1, 0);
    set_wf(this_object());
    set_keep(1);
    
}

/*
 *  Function name: enter_env
 *  Description  : When we enter an interactive environment, add a subloc to
 *                 indicate that the person is writing something.
 *  Arguments    : object to - the object we are entering.
 *                 object from - the object we come from.
 */
void
enter_env(object dest, object from)
{
    ::enter_env(dest, from);
}

/*
 *  Function name: leave_env
 *  Description  : When you inherit /lib/holdable_item.c you MUST also define
 *                 the function leave_env() as copy of this function. It MUST
 *                 make the call to holdable_item_leave_env(from, to) as well.
 *                 If you omit this, then the item will not be automatically
 *                 released when the player drops it, for instance.
 *  Arguments    : object from - the environment we are leaving.
 *                 object to   - the environment we are entering.
 */
void
leave_env(object dest, object from)
{
    ::leave_env(dest, from);

    wearable_item_leave_env(from, dest);
}

/*
 *  Function name: wear
 *  Description  : Only the Nisse members can wear the glove.
 *  Returns      : failure msg or 0 (can be worn normally)
 */
mixed
wear()
{
    if (!TP->query_nisse_level())
    {
        return "The " + short() + " does not fit on your hand.\n";
    }

    return 0;
}

/*
 *  Function name: remove
 *  Description  : Tests if a player can remove the glove.
 *  Returns      : failure msg or 0 (can be removed normally)
 */
mixed
remove()
{
    if (present(NISSE_HAWK_ID, TP))
    {
        return "You cannot remove the " + short() + ". " + "A " +
            CAP(present(NISSE_HAWK_ID, TP)->short()) + " is sitting on your " +
            "left wrist.\n";
    }
    
    return 0;
}

string
query_recover()
{
    return MASTER + ":" + query_keep_recover();
}

void
init_recover(string arg)
{
    ::init_keep_recover(arg);
}