#include "/d/Krynn/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <composite.h>
#include <cmdparse.h>
#include <const.h>

inherit R_FILE

#include "keep_shop_items.c"

#define CHALK     "/d/Krynn/solamn/palanthas/aesthetics/obj/mchalk"
#define ROPE      "/d/Krynn/solamn/palanthas/aesthetics/obj/mhemp_rope"
#define LANTERN   "/d/Krynn/solamn/palanthas/aesthetics/obj/mlantern_hooded"
#define OIL       "/d/Krynn/solamn/palanthas/aesthetics/obj/moil_flask"
#define WHISTLE   "/d/Krynn/throtyl/obj/bone_whistle"
#define BAG       "/d/Krynn/throtyl/obj/lootbag"

#define FENCE_EQUIP  ({ CHALK, ROPE, LANTERN, OIL, WHISTLE, BAG })


void
reset_krynn_room()
{
  return;
}

void
create_krynn_room()
{
    seteuid(getuid(TO));
    config_default_trade();

    set_money_greed_buy(80);
    set_money_greed_sell(100);

    set_store_room(ROOMS + "keep_store");
    (ROOMS + "keep_store")->load_me();
    set_standard_equip(FENCE_EQUIP);

    set_short("fence in the ruined tower of East Keep");
    set_long("You stand on the upper floor of a ruined tower of " +
        "East Keep, currently being used by raiders to fence their " +
        "ill-gotten loot. You can 'sell' plundered goods here, " +
        "'list' raider equipment, and 'buy' goods in stock if " +
        "you so wish.\n");

    add_exit("/d/Krynn/guilds/hobgob/joinroom", "down");

    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
    add_prop(ROOM_I_INSIDE, 1);

    reset_krynn_room();

}

public void
init()
{
    ::init(); 
    init_shop(); 
}
