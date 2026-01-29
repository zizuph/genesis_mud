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
    set_long("On a street.\n");

    add_exit(LOWER + "street8", "north");
    add_exit(LOWER + "street6", "east");
}



