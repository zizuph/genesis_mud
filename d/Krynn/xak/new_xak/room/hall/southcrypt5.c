/* 
 * Xak Tsaroth - Hall of the Ancestors
 * Originaly coded by Percy
 * Revamped by Rastlin
 */
#pragma strict_types

#include "../../local.h"
#include <macros.h>

inherit INROOM;

object gDrac1, gDrac2, gDrac3;

public void
reset_xak_room()
{
    MOVE(gDrac1, GET_NPC_HA)
    MOVE(gDrac2, GET_NPC_HA)
    MOVE(gDrac3, GET_NPC_HA)
}

public void
create_xak_room()
{    
    set_short("Southern crypts");
    set_long("You are standing in a long, narrow corridor that " +
	     "extends to the east and west. Coffins " +
	     "line the walls here and the stench of death assails " +
	     "your nostrils. The corridor is lit by " +
	     "torches that flickers and smokes in the stifling air. " +
	     "The light reflects off the walls wet with condensed " +
	     "moisture. To the east darkness marks the end of the " +
	     "corridor. A strange sound is coming from there.\n");

    LIGHT;

    add_exit(HALL + "southcrypt6", "east");
    add_exit(HALL + "southcrypt4", "west");

    add_item(({"torch", "torches"}), "The torches flickers and smokes. " +
	     "They are attached to the walls, you wonder what they do " +
	     "with them when they are burnt down.\n");
    add_cmd_parse("[the] 'torch' / 'torches'", ({"take", "get"}),
		  "The torches can't be taken.\n");

    add_item(({"coffin", "normal coffin", "normal coffins", "coffins"}), 
	     "The coffins are made of stone and they all " +
	     "looks very heavy to lift.\n");

    seteuid(getuid());

    reset_xak_room();
}







