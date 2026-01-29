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
    set_long("At the liftbottom.\n");

    add_exit(LOWER + "larder", "north");
    add_exit(LOWER + "street21", "south");
    add_exit(LOWER + "street20", "west");
}



