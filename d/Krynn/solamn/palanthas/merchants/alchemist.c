/* created by Aridor 06/21/93 */
// March 30, 2000 Commented out cloning the jeweler, as there is
// no jeweler, the store is supposed to be closed, but something
// was loading up this room and spamming the error logs.
// Gwyneth
//
// Added gem store features from /d/Avenir/common/bazaar/intr/lapidary.c
// Arman 9/11/2003


#pragma save_binary
#pragma strict_types

#include "../local.h"
#include <cmdparse.h>
#include <ss_types.h>
#include <macros.h>

inherit MERCH_ROOMBASE;
inherit "/d/Gondor/common/lib/potion_shop";
//inherit "/d/Krynn/std/room";

#define STRM   "/d/Krynn/solamn/palanthas/merchants/alchemiststore"

object keeper;

void
reset_palan_room()
{
    if (!objectp(keeper))
    {
        keeper = clone_object("/d/Krynn/solamn/palanthas/merchants/living/alchemist");
        keeper->move(TO, "arrives");

    }

}


void
create_palan_room()
{
    seteuid(getuid(TO));
    config_default_trade();
    set_store_room(STRM);
    (STRM)->load_me();

    set_short("Alchemist Shop in Palanthas");
    set_long("This is the alchemist shop, where mages sometimes come " +
                "to sell off their spare magical items.  Lately the shop" +
                "keeper has started adding his own potions to the " +
                "shelves.\n");
    add_item(({"sign"}), "@@exa_sign");
    add_cmd_item(({"sign"}), "read",
        "@@exa_sign");
    add_item(({"case", "display case", "displays", "glass case", "display" }),
        "@@do_case");

    add_prop(MAGIC_AM_MAGIC,({40,"enchantment"}));
    add_exit(MERCH + "w26","northwest",0,1);
    enable_reset(100);
    reset_palan_room();

}

/*
 * Function name:   init
 * Description:     Is called for each living that enters this room
 * Returns:
 */
void
init()
{
    ::init();
    init_potion_shop();
}

public string
exa_sign()
{
   return "\nThe Palanthian Alchemy!\n"+
          "          WeirdestItems        \n"+
          "            Guarenteed         \n"+
          "        BoughtAndSoldHere.    \n\n"+
          "       FeelFreeToExamineThe     \n"+
          "       DisplaysForAnything      \n"+
          "       ThatCatchesYourEye!!   \n\n"+
          "     KenderMustStandTwoFeet  \n" +
          "           FromDisplays!\n\n";
}

public int
do_read(string str)
{
    return 0;
}

string
do_case()
{
    do_list("all");
    return "You stare through the thick glass.\n";
}

