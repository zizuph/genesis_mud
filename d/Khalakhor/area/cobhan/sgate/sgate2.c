/* File:          /d/Khalakhor/cobhan/sgate/sgate2.c
 * Creator:       Teth
 * Date:          Dec 26 2001
 * Modifications:
 * Purpose:       This is a gate room in the area.
 * Related Files: /d/Khalakhor/cobhan/
 * Comments:
 */

#pragma save_binary
#pragma strict_types

#include "../local.h"

inherit CSTD + "sgate_base";

public void
reset_sgate_room()
{
}

public void
create_sgate_room()
{
    set_up_sgate();
    set_long("@@my_long");
    add_my_desc("A guard room. \n");

    add_exit(SGATE + "sgate5", "northwest");
    add_exit(SGATE + "sgate1", "east");
    add_exit(SGATE + "sgate4", "southwest");
}

