/*  Updated the shop to have a preset list of items
 *  that are always on sale.
 *
 *  Arman October 2017
 */ 


#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <composite.h>
#include <cmdparse.h>
#include <const.h>

inherit DWARF_IN;

#include "dwarf_shop_items.c"

#define STORE_ROOM   IRON + "shop_sr"

#define WHISTLE     "/d/Ansalon/estwilde/steed/pig_whistle"
#define BOARBAG     "/d/Ansalon/estwilde/steed/boarbag"
#define LAMP        EOBJ + "oil_lamp"
#define OIL         EOBJ + "oilflask"
#define BACKPACK    EOBJ + "dwarf_backpack"
#define HELM        ARMOUR + "horned_helmet"
#define SHIELD      ARMOUR + "shield"
#define CHAIN       ARMOUR + "chainmail"
#define AXE         WEP + "iron_axe"
#define HAMMER      WEP + "warhammer"

#define STANDARD_EQUIP      ({ HAMMER, AXE, CHAIN, SHIELD, HELM, BACKPACK, OIL, LAMP, WHISTLE, BOARBAG })

void
reset_dwarf_room()
{
    return;
}

void
create_dwarf_room()
{
    config_default_trade();
/* the numbers here are mixed up therefore I will change it and add some
   penalty for time being
     15.06.2002 Torqual
    set_money_greed_buy(80);
    set_money_greed_sell(75);
 */
    set_money_greed_buy(110);
    set_money_greed_sell(110);

    set_store_room(STORE_ROOM);
    (STORE_ROOM)->load_me();
    set_standard_equip(STANDARD_EQUIP);

    set_short("Local store in Iron Delving");
    set_long("You stand in a long stone " +
      "building used " +
      "as the local store. A wooden counter stands against " +
      "the southern wall.\n" +
      "You can also use value or list commands, 'list armours',\n" +
      "'list weapons', 'list <name>' and 'list' works too.\n" +
      "There is also a small sign to read with more instructions.\n" +
      "");

    add_item(({"counter","wooden counter","southern wall"}),
      "Against the southern wall is a counter where the shops " +
      "attendant serves his customers from. \n");

    add_exit(IRON + "r14","north",0);
    add_invis_exit(STORE_ROOM,"south","@@wiz_check");

    add_item("sign", "A nice looking sign for you to read.\n");
    add_cmd_item("sign", "read", "@@do_read");

    reset_dwarf_room();
}

void
init()
{
    ::init();   /* You MUST do this in a room-init */
    init_shop(); /* Get the commands from the shop */
}


/*
* Function name:   wiz_check
* Description:     Check if a player is a wizard
   * Returns:         0 if the player is a wizard
   *                  1 otherwise
*/
int
wiz_check()
{
    if(this_player()->query_wiz_level() || this_player()->query_npc())
	return 0;
    write("Some magic force keeps you from going south.\n");
    say(QCTNAME(this_player()) + " tries to go south but fails.\n");
    return 1;
}

