#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/haven/local.h"
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <composite.h>
#include <cmdparse.h>
#include <const.h>

#include "/d/Krynn/common/clock/clock.h"
#include "/d/Krynn/guilds/sohm/defs.h"

inherit HAVENINBASE;

#include "mageware_shop_items.c"

#define HERB_GLOVES     "/d/Shire/frogmorton/obj/herb_gloves"
#define HERB_JAR        "/d/Gondor/guilds/rangers/obj/herbjar"
#define HERB_POUCH      "/d/Gondor/common/obj/herbpouch"
#define MORTAR          "/d/Gondor/common/potions/mortar"
#define VIAL            "/obj/potion_vial"
#define SATCHEL         "/d/Gondor/common/potions/satchel"
#define CHARM           "/d/Krynn/common/warfare/obj/warfare_scry_amulet"

#define MAGEWARE_EQUIP  ({ HERB_GLOVES, HERB_JAR, HERB_POUCH, MORTAR, VIAL, SATCHEL, CHARM})

object herbalist;

void
reset_haven()
{
  reset_euid();

  if(!herbalist)
    (herbalist = clone_object(HNPC+"herbalist"))->move(TO);

}

void
create_haven()
{
    seteuid(getuid(TO));
    config_default_trade();

    set_money_greed_buy(80);
    set_money_greed_sell(100);

    set_store_room(HROOM + "mageware_store");
    (HROOM + "mageware_store")->load_me();
    set_standard_equip(MAGEWARE_EQUIP);

    set_short("Lemuel's Mageware shop, Haven");
    set_long("You stand inside the Mageware shop of Lemuel, a " +
       "Hedge Wizard and herbalist based in Haven. The interior " +
       "of the mage's shop is dark - the shutters over the windows " +
       "closed and keeping out all the daylight - with the only " +
       "illumination being from a handful of candles and a low burning " +
       "fire. Shelves line the walls, however it is difficult to make " +
       "out what is on them in the gloom of the room.\n");

    add_item(({"shop","mageware shop","shop of lemuel","interior"}),
       "This is a mageware shop, identified as such from the subtle " +
       "sign out the front of the establishment, the Night of the Eye - " +
       "a symbol of that singular event where the three moons of magic " +
       "align, resembling a huge white eye with a black pupil and red " +
       "iris. Here practitioners of magic can purchase equipment to " +
       "assist them in their endeavours.\n");

    add_item(({"windows","shutters","daylight"}),
       "The shutters are closed over the windows here, blocking all " +
       "light from entering from the outside.\n");

    add_item(({"light","candles","candle","fire","low burning fire"}),
       "The room is dark, with the only light coming from a handful of " +
       "candles and a low burning fire.\n");

    add_item(({"shelves","walls","wall","shelf"}),
       "It is difficult to make out what is on the shelves lining the " +
       "walls.\n");

    add_exit(HROOM+"st5","out");

}

public void
init()
{
    ::init(); 
    init_shop(); 
}
