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
    set_short("An old deserted shop");
    set_long("You find yourself in a ruined shop. Looking around you'd " +
	     "guess that this used to be an alchemists of some sort. " +
	     "Glass apparatus and bottles line the walls but all are " +
	     "long since broken or smashed beyond use. A small doorway " +
	     "leads into a storeroom to the south.\n");

    add_exit(MIDDLE + "sidestreet2", "west");
    add_exit(MIDDLE + "sage2", "south");
}

