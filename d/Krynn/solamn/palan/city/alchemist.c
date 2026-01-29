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

//inherit "/d/Avenir/common/lib/shop";
inherit "/d/Gondor/common/lib/potion_shop";
inherit "/d/Krynn/std/room";

#include "../local.h"
#include <cmdparse.h>
#include <ss_types.h>
#include <macros.h>

#define STRM   "/d/Krynn/solamn/palan/city/alchemiststore"

object keeper;

void
reset_krynn_room()
{
    if (!objectp(keeper))
    {
        keeper = clone_object("/d/Krynn/solamn/palan/living/alchemist");
        keeper->move(TO, "arrives");

    }

}


void
create_krynn_room()
{
    seteuid(getuid(TO));
    config_default_trade();
    set_store_room(STRM);
    (STRM)->load_me();

    set_short("Alchemist Shop in Palanthas");
    set_long("This is the alchemist shop, where mages sometimes passes " +
                "to sell off their spare magical items, lately the shop" +
                "keeper have started adding his own potions to the " +
                "sales.\n");
    add_item(({"sign"}), "@@exa_sign");
    add_cmd_item(({"sign"}), "read",
        "@@exa_sign");
    add_item(({"case", "display case", "displays", "glass case", "display" }),
        "@@do_case");

    add_prop(MAGIC_AM_MAGIC,({40,"enchantment"}));
    add_exit(ROOM + "street4","west",0,1);
    enable_reset(100);
    reset_krynn_room();

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

