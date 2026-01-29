
/*
    Diamond. Collection Store

   collect.c
   --------
   Coded .........: October 1997
   By ............: Kentari

   Latest Update .: January 1998
   By ............: Kentari

*/


#pragma save_binary

#include <stdproperties.h>
#include <macros.h>
#include "../local.h"
#include "/d/Krynn/common/defs.h"

inherit "/lib/shop";
inherit IN_BASE;

object keeper;


void
reset_dim_room()
{
    if (!keeper)
	if (!P(keeper, TO))
	{
	    keeper = clone_object(DINPC + "kilnmaster");
	    keeper->move(TO);
	}
}

void
create_dim_room()
{
    config_default_trade();
    set_money_give_max(1000);
    set_store_room(DIROOM + "collect_store");
    setuid();
    seteuid(getuid());
    (DIROOM + "collect_store")->teleledningsanka();
    set_money_greed_sell(125);
    set_short("Collection Store of Diamond City");
    set_long("This is the Collection Store of Diamond City. " +
      	"A diamond shaped hole is set in the back wall in which you " +
	"see a magical fire burning, yet feel no noticeable heat " +
	"emanating from it. A sign is posted on a large counter which " +
	"separates the room so customers cannot get near the fire. " +
	"Behind the counter stands the Kilnmaster who takes weapons " +
	"and armours and melts them down.\n");
    AI(({"diamond shaped hole","hole","diamond hole","back wall","wall"}),
	"Through this hole is the magical fire that melts down the various " +
	"armours and weapons that are bought. You notice a twinkling, " +
	"almost like diamond dust, lining the hole.\n");
    AI(({"magical fire","fire","flame"}),
	"This fire burns like nothing you've ever seen before. Its " +
	"colours are ever changing and no heat seems to be " +
	"radiating from it. To melt so many weapons and armours, of " + 
	"both normal make and enchanted, it would take something " +
	"above the average kiln fire, and this seems to be just that.\n");
    AI(({"twinkling","twinkle","diamond dust","lining","dust"}),
	"This twinkling dust probably helps contain the fire, as anything " +
	"that could melt what this kiln does would most likely burn " +
	"down the whole building if not contained correctly.\n");
    AI(({"counter","large counter"}),
	"This counter both separates the room so no one can get near " +
	"the kiln, and is a great place for the Kilnmaster to conduct " +
	"business upon.\n");
    AI("sign", "Try reading it instead, no?\n");

    AE(DIROOM + "sw2", "northeast", 0);
    INSIDE;
    reset_dim_room();
}

/*
* Function name:   init
* Description:     Is called for each living that enters this room
* Returns:
*/
void
init()
{
    ::init();   /* You MUST do this in a room-init */
    init_shop();
}

int
do_read(string str)
{
    if (str == "sign")
    {
	write("The sign reads:\nYou may sell weapons and armours " +
	"here, though we do not sell them as this is a peaceful city.\n");
	return 1;
    }
    else
    {
	NF("Read what? The sign?\n");
	return 0;
    }
}

mixed
do_sell(string str)
{
    if (!P(keeper, TO))
	{
	NF("The shopkeeper is not here to buy your items.\n");
	return 0;
	}
    return ::do_sell(str);
}

mixed
do_buy(string str)
{
    NF("There is nothing to buy here!\n");
    return 0;
}

mixed
do_list(string str)
{
    NF("There is nothing to list!\n");
    return 0;
}
