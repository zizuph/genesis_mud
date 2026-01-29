/* This file is for switching medallions from the tmp copy to the permanent
 * copy.
 */

inherit "/std/object";
#include "defs.h"

void
switch_medallions()
{
    seteuid(getuid());
    clone_object("/d/Calia/glykron/palace/objects/calian_medallion")->
	move(environment());
    remove_object();
}

void
create_object()
{
    set_alarm(1.0, 0.0, "switch_medallions");
}
