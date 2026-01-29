/* File:          /d/Khalakhor/cobhan/humancamp/camp6.c
 * Creator:       Teth
 * Date:          Dec 26 2001
 * Modifications:
 * Purpose:       This is a human camp room in the area.
 * Related Files: /d/Khalakhor/cobhan/
 * Comments:
 */

#pragma save_binary
#pragma strict_types

#include "../local.h"

inherit CSTD + "humancamp_base";

public void
reset_humancamp_room()
{
}

public void
create_humancamp_room()
{
    set_up_humancamp();
    set_long("@@my_long");
    add_my_desc("Human camp. \n");

    add_exit(HUMANCAMP + "camp5", "west", 0, 2);
}

