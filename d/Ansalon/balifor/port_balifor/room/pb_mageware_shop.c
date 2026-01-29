#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/port_balifor/local.h"
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <composite.h>
#include <cmdparse.h>
#include <const.h>

#include "/d/Krynn/common/clock/clock.h"
#include "/d/Krynn/guilds/sohm/defs.h"

inherit BALIFOR_IN;

#include "/d/Krynn/haven/town/room/mageware_shop_items.c"

#define HERB_GLOVES     "/d/Shire/frogmorton/obj/herb_gloves"
#define HERB_JAR        "/d/Gondor/guilds/rangers/obj/herbjar"
#define MORTAR          "/d/Gondor/common/potions/mortar"
#define VIAL            "/obj/potion_vial"
#define SATCHEL         "/d/Gondor/common/potions/satchel"
#define SCROLL          "/d/Krynn/common/scrolls/light_spell_scroll"

#define MAGEWARE_EQUIP  ({ HERB_GLOVES, HERB_JAR, HERB_POUCH, MORTAR, VIAL, SATCHEL, SCROLL })

object herbalist;

void
reset_balifor_room()
{
  reset_euid();

  if(!herbalist)
    (herbalist = clone_object(BNPC+"herbalist"))->move(TO);

}

void
create_balifor_room()
{
    seteuid(getuid(TO));
    config_default_trade();

    set_money_greed_buy(80);
    set_money_greed_sell(100);

    set_store_room(BROOM + "pb_mageware_store");
    (BROOM + "pb_mageware_store")->load_me();
    set_standard_equip(MAGEWARE_EQUIP);

    set_short("mageware shop, Port Balifor");
    set_long("You stand inside the Mageware shop located in Port Balifor. " +
       "The salty smell of the sea wafting in from outside mixed with " +
       "the drying herbs hanging from hooks throughout the store provide " +
       "an unusual yet pleasant and exotic fragrance throughout the room.\n");

    add_item(({"drying herbs","herbs","hooks"}),
       "Strings of herbs hang drying from hooks throughout the store.\n");

    add_exit(BROOM+"city18","west");
    reset_balifor_room();

}

public void
init()
{
    ::init(); 
    init_shop(); 
}
