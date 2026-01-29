#pragma save_binary
#pragma strict_types

#include "../defs.h"
inherit "/d/Cirath/std/room.c";
inherit "/lib/shop";

#include <wa_types.h>
#include "/d/Cirath/common/mobber.h"

#define STORE_ROOM ALT_HOU + "boot_store"

void
reset_room()
{
   bring_room_mob("lorian",ALT_NPC+"lorian.c",1,0);
}

void
create_room()
{
    config_default_trade();
    set_money_greed_sell(95);
    set_money_greed_buy(95);
    set_money_give_out(({10000, 500, 10, 2}));
    set_money_give_reduce(({0, 4, 20, 15}));
    set_store_room(STORE_ROOM);
    set_short("The Boot Makers Shop");
    set_long("You are in the shop of Lorian the Bootmaker. The shop smells" +
        " of shoeleather and tanning liquids. Lorian is hard at work on a" +
        " pair of black boots." +
        " There is a small sign with instructions here.\n");

    add_item("sign", "A nice looking sign, perhaps you should read it.\n");
    
    add_exit(ALT_STR + "07",  "south");
    add_exit(STORE_ROOM, "east", "@@wiz_check");

    add_prop(ROOM_I_INSIDE,1);
    reset_room();
}

void
init()
{
    ::init();
    init_shop();
}

int
shop_hook_allow_sell(object ob)
{
    if(ob->query_at() != A_FEET)
    {
    write("Sorry but Lorian only deals in footwear!\n");
    return 0;
    }
return 1;
}