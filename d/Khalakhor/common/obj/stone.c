/* File:          /d/Khalakhor/common/obj/stone.c
 * Creator:       Teth
 * Date:          December 7, 1997
 * Modifications:
 * Purpose:       This object can be found in many areas.
 * Related Files: /d/Khalakhor/ship/macdunn/under_pier.c
 * Comments:      TODO: Make it inherit a standard file.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/object";

#include <stdproperties.h>

public void
create_object()
{
    set_name("stone");
    add_name(({"rock","mineral"}));
    set_pname("stones");
    add_pname(({"rocks","minerals"}));
    set_adj("grey");
    add_adj(({"hard","gray","solid","small"}));
    set_short("grey stone");
    set_pshort("grey stones");
    set_long("This small stone is ordinary rock, the type seen on " +
        "roadsides and in townships. Young children can be found " +
        "inventing games to play with them.\n");

    add_prop(OBJ_I_VALUE, 1);
    add_prop(OBJ_I_WEIGHT, 227);
    add_prop(OBJ_I_VOLUME, 112);
}

