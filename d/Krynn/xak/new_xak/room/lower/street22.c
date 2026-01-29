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
    set_long("On the street.\n");

    add_exit(LOWER + "street16", "north");
    add_exit(LOWER + "street23", "south");
}



