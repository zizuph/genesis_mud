/* 
 * Xak Tsaroth - Lower level
 * Originally coded by Percy
 * Revamped by Rastlin
 */
#pragma strict_types

#include "../../local.h"

inherit INROOM;

public void
create_xak_room()
{
    set_short("An old deserted street");
    set_long("On Plaza.\n");

    add_exit(LOWER + "street5", "east");
    add_exit(LOWER + "street7", "west");
}



