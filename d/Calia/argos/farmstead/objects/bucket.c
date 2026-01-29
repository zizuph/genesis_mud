/* /d/Calia/argos/farmstead/objects/bucket.c
**   A battered bucket, it can be used to fetch water from the
**   farmyard well
**
**   History:
**   Date       Coder      Action
**   --------   ---------- ---------------------------------
**   2/23/20    Brine      Created
**
*/

#pragma strict_types

inherit "/std/container";

#include <stdproperties.h>
#include <macros.h>
#include "defs.h"

int has_water = 0;

void
create_container()
{
    seteuid(getuid());

    set_name(({ "bucket", "battered bucket" }));

    set_adj("rusty");
    set_adj("battered");
    set_adj("old");
    set_adj("metal");
    set_adj("corroded");

    set_short("battered bucket");

    set_long(
        "An old metal bucket. It is corroded and battered, but seems "
        + "to still be able to hold water.\n"
    );

    add_prop(CONT_I_RIGID, 1); // Metal buckets don't expand
    add_prop(CONT_M_NO_REM, "You can't pick up water with your hands.\n");
    add_prop(CONT_I_WEIGHT, 500);
    add_prop(CONT_I_VOLUME, 250);
    add_prop(CONT_I_MAX_WEIGHT, 5500);
    add_prop(CONT_I_MAX_VOLUME, 5250);
    add_prop(OBJ_I_VALUE, 10);
}

int
query_has_water()
{
    return has_water;
}

void
set_has_water()
{
    has_water = 1;
}

/*
 * Function name: prevent_enter
 * Description  : Shadowed inherited function, makes sure this bucket
 *                 will only accept the quest item it is designed to carry
 */
int
prevent_enter(object ob)
{
    if (MASTER_OB(ob) != OBJ_DIR + "water")
    {
        write("The " + short() + " is really only suitable to hold water.\n");
        return 1;
    }
    return 0;
}

/*
 * Function name: describe_contents
 * Description  : The function inherited from /std/container doesn't play
 *                nicely with the object this bucket is designed to hold,
 *                so we shadow it
 */
void
describe_contents(object for_obj, object *obarr)
{
    if (sizeof(obarr) > 0)
    {
        for_obj->catch_tell("The " + short() + " is full of water.\n");
        return;
    }

    for_obj->catch_tell("  " + "The " + short() + " is empty.\n");
}
