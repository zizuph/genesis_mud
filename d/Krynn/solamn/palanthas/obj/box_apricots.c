/* 
 * Palanthas food by Mortis 09.2005
 * If someone can tell me how to use query_guild_name_race
 * in a food, change the special_effect to uncomment.
 */

#pragma save_binary
//#pragma strict_types

inherit "/std/food.c";
#include <macros.h>
#include <composite.h>
#include "/d/Krynn/common/defs.h"
#include "../local.h";

public void
create_food()
{
    set_amount(40);
    set_name("box");
    set_pname("boxes");
	add_pname(({"apricots", "boxes of apricots"}));
	add_name(({"apricot", "box of apricots"}));
	set_adj("dried");
    set_short("box of dried apricots");
    set_pshort("boxes of dried apricots");
    set_long("A small, brown paper box of apricots from Sancrist.  They "
	+ "have been halved then dried under the sun.  The rinds are wrinkly and "
	+ "dry but the centers are moist and sticky sweet.\n");
}

void
init()
{
    ::init();
    ADA("smell");
}

int
smell(string str)
{
    NF("Smell what?\n");

    if (!str)
	return 0;

    if (str != "box" && str != "box of apricots" && str != "apricots"
	    && str != "dried apricots")
	return 0;

    TP->catch_msg("You hold the box of apricots up to your nose to "
	+ "catch its fragrance.  Though not strong, they do smell sunny "
	+ "and sweet in a citrus-like way.\n");
    tell_room(E(TP), QCTNAME(TP)+ " holds a box of apricots up to " + HIS(TP)
	+ " nose closing " + HIS(TP) + " eyes "
	+ "for a moment as " + PRONOUN(TP) + " inhales its fragrance.\n",
		({TO, TP}));

    return 1;
}

special_effect(string str)
{
	string swrace, swrace1;
	swrace = QRACE(TP);
	swrace1 = TP->query_guild_name_race();

	if (swrace == "elf" || swrace1 == "Noldor of Imladris")
	{
		TP->catch_msg("Your eyelids drift heavily shut as the sticky "
		+ "sweet citrus sugar of the dried apricots touches your elven "
		+ "tongue and a tingle slides down your throat.  You feel warm "
		+ "and flushed and a golden light floods your senses as you "
		+ "contemplate its tangy aftertaste.\n");
		tell_room(E(TP), QCTNAME(TP)+ "'s eyes close as " + PRONOUN(TP)
    	+ " places a dried apricot in " + HIS(TP) + " mouth and "
	    + HIS(TP) + " face flushes deeply.\n", ({TO, TP}));
		return 1;
	}
    TP->catch_msg("The sweet citrus sugar of the dried apricots is "
	+ "tangy and sunny.\n");
	
}


		



/*
void
special_effect(int n)
{
    TP->catch_msg("@@race_taste@@");
}
*/