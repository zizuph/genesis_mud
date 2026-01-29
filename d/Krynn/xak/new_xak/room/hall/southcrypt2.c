/* 
 * Xak Tsaroth - Hall of the Ancestors
 * Originaly coded by Percy
 * Revamped by Rastlin
 */
#pragma strict_types

#include "../../local.h"
#include <macros.h>

inherit INROOM;

int gCount;
object gDrac1, gDrac2;

public void
reset_xak_room()
{
    MOVE(gDrac1, GET_NPC_HA)
    MOVE(gDrac2, GET_NPC_HA)
    gCount = 2;
}

public void
create_xak_room()
{    
    set_short("Southern crypts");
    set_long("You are standing in a long, narrow corridor that " +
             "extends to the east and west. An arched doorway " +
             "reveals a large coffin to the south. Other coffins " +
             "line the walls here and the stench of death assails " +
             "your nostrils. A strange screeching sound can be heard, " +
	     "comming from east end of the corridor. The corridor is lit by " +
             "torches that flickers and smokes in the stifling air. " +
             "The light reflects off the walls wet with condensed " +
             "moisture.\n");
    LIGHT;

    add_exit(HALL + "southcrypt3", "east");
    add_exit(HALL + "southcrypt1", "west");

    add_item(({"torch", "torches"}), "The torches flickers and smokes. " +
	     "They are attached to the walls, you wonder what they do " +
	     "with them when they are burnt down.\n");
    add_cmd_parse("[the] 'torch' / 'torches'", ({"take", "get"}),
		  "The torches can't be taken.\n");

    add_item(({"normal coffin", "normal coffins", "coffins"}), 
	     "The coffins are made of stone and they all " +
	     "looks very heavy to lift.\n");

    add_item("coffin", "Which coffin should that be?\n");
    add_item("large coffin", "@@exa_coffin");

    seteuid(getuid());

    reset_xak_room();
}

public string
exa_coffin()
{
    if (BUPU_PACK(TO))
    {
        tell_room(TO, QCTNAME(TP) + " starts to examine the large " +
		  "coffine, and the suddenly discovers something.\n", TP);

	return "You discover a small leather backpack beside the coffin.\n";
    }

    if (!gCount)
        return "You examine the large coffin and everything seems normal. " +
               "Well,  as normal as can be expected for such a gloomy " +
	       "place as this.\n";
    else 
    {
        tell_room(TO, QCTNAME(TP) + " is examining the large coffin when " +
		  "suddenly a ghostly figure emerges from it.\n", TP);

        clone_object(NPC + "wraith")->move(TO);

	gCount--;

        return "You examine the large coffin when suddenly a ghostly " +
               "form emerges from it.\n";
    }
}




