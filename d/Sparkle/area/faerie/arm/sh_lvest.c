/*
 * Leather for Faerie Leather Shop
 * Finwe, April 2005
 */

inherit "/std/object";
inherit "/lib/wearable_item";

#include "defs.h"
#include <wa_types.h>
#include <stdproperties.h>

public nomask void
create_object()
{
    setuid(); seteuid(getuid());

    set_name("vest");
    add_name("cowhide vest");
    set_short("cowhide vest");
    set_long("This "+short()+" is elegant but simple sleeveless garment. " +
        "It is worn over the shoulders and chest. The cowhide is supple " +
        "and soft.\n");

    set_slots(A_TORSO);

    set_layers(0);
    set_looseness(0);

    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME,   50);
    add_prop(OBJ_I_VALUE,  50);
}

public void
leave_env(object env, object to)
{
    ::leave_env(env, to);

    wearable_item_leave_env(env, to);
}

void
appraise_object(int num)
{
    ::appraise_object(num);

    appraise_wearable_item();
}
