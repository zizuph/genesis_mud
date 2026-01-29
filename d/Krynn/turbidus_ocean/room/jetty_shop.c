#include "/d/Krynn/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <composite.h>
#include <cmdparse.h>
#include <const.h>

inherit SAIL_ROOM_BASE;

#include "jetty_shop_items.c"

#define CHALK     "/d/Krynn/solamn/palanthas/aesthetics/obj/mchalk"
#define ROPE      "/d/Krynn/solamn/palanthas/aesthetics/obj/mhemp_rope"
#define LANTERN   "/d/Krynn/solamn/palanthas/aesthetics/obj/mlantern_hooded"
#define OIL       "/d/Krynn/solamn/palanthas/aesthetics/obj/moil_flask"
#define SPYGLASS  "/d/Ansalon/goodlund/bloodsea/obj/spyglass"
#define NET       "/d/Calia/sea/objects/fish_net"
#define BOTTLE    "/d/Calia/gelan/objects/bottle"

#define JETTY_EQUIP  ({ CHALK, ROPE, LANTERN, OIL, SPYGLASS, NET, BOTTLE })


void
reset_sea_room()
{
  return;
}

/* This next function is essential when it comes to removing the drown 
   object. Imagine if one leaves a standard water room into an area with
   non-standard underwater rooms.. the drown object will stay, but it will
   not get removed if they then go to an ordinary room. */
int
query_standard_water_room()
{
    return 0; 
}

public void
sink(object ob)
{
    return;
}

void
create_sea_room()
{
    seteuid(getuid(TO));
    config_default_trade();

    set_money_greed_buy(80);
    set_money_greed_sell(100);

    set_store_room(ROOM + "jetty_store");
    (ROOM + "jetty_store")->load_me();
    set_standard_equip(JETTY_EQUIP);

    set_short("pirate fence in Reefcutter's Jetty");
    set_long("You stand within a ramshackled building that is the " +
        "resident store for pirates where they can fence their " +
        "ill-gotten goods. You can 'sell' plundered goods here, " +
        "'list' standard sailor equipment, and 'buy' goods in stock if " +
        "you so wish.\n");

    add_exit(ROOM + "jetty", "out");

    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
    add_prop(ROOM_I_INSIDE, 1);

    reset_sea_room();

}

public void
init()
{
    ::init(); 
    init_shop(); 
}
