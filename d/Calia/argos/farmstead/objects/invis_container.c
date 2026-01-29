/* /d/Calia/argos/farmstead/objects/invis_container.c
**   An invisible container, used to store a quest item while it
**   appears to be standing on a table
**
**   History:
**   Date       Coder      Action
**   --------   ---------- ---------------------------------
**   3/22/20    Brine      Created
**
*/

#pragma strict_types

inherit "/std/container";

#include <stdproperties.h>
#include <macros.h>
#include "defs.h"

void
create_container()
{
    seteuid(getuid());

    set_name("container");

    set_short("table");
    set_long("An invisible container. How are you even reading this?!\n");

    add_prop("OBJ_M_NO_GET", 1);
    add_prop("CONT_I_WEIGHT", 1);
    add_prop("CONT_I_MAX_WEIGHT", 10000);
    add_prop("CONT_I_VOLUME", 1);
    add_prop("CONT_I_MAX_VOLUME", 10000);

    set_no_show();
}
