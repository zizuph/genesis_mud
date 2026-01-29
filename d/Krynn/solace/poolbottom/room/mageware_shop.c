#include "/d/Krynn/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <composite.h>
#include <cmdparse.h>
#include <const.h>

#include "/d/Krynn/common/clock/clock.h"
#include "/d/Krynn/guilds/sohm/defs.h"

inherit POOLBOTTOM_IN;

#include "mageware_shop_items.c"

#define HERB_GLOVES     "/d/Shire/frogmorton/obj/herb_gloves"
#define HERB_JAR        "/d/Gondor/guilds/rangers/obj/herbjar"
#define HERB_POUCH      "/d/Shire/common/obj/pouch"

#define MAGEWARE_EQUIP      ({ HERB_GLOVES, HERB_JAR, HERB_POUCH})



void
reset_poolbottom_room()
{

}

create_poolbottom_room()
{
    seteuid(getuid(TO));
    config_default_trade();

    set_money_greed_buy(80);
    set_money_greed_sell(100);

    set_store_room(ROOM + "mageware_store");
    (ROOM + "mageware_store")->load_me();
    set_standard_equip(MAGEWARE_EQUIP);

    set_short("mageware shop");
    set_long("Mageware shop.\n");

    reset_poolbottom_room();
}

public void
init()
{
    ::init(); 
    init_shop(); 
}
