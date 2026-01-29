inherit "/std/room";
inherit "/lib/shop";

#include "/d/Roke/common/defs.h"
#include "/d/Roke/Cirath/defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <language.h>
#include <cmdparse.h>
#include <composite.h>
#include <filter_funs.h>

#define STORE_ROOM CIUBORI+"market/store1"

void
create_room()
{
    config_default_trade();
    set_money_greed_sell(95);
    set_money_greed_buy(95);
    set_money_give_out(({10000, 500, 10, 2}));
    set_money_give_reduce(({0, 4, 20, 15}));
    set_store_room(STORE_ROOM);
    set_short("The Ciubori Merchants Trade-Post");
    set_long(BS(
      "You are standin inside the Ciubori Merchants Trade-Post. "+
      "It's a quite large shop with highly decorated walls. The "+
      "owner is propably making a lot of money here."+
      "", 60));

    add_item("sign", "A nice looking sign, perhaps you should read it.\n");

    add_exit(CIUBORI+ "market/store1", "up", "@@wiz_check");
    add_exit(CIUBORI+"topaz/street2", "west");

    INSIDE;
}

void
init()
{
    ::init();
    init_shop();
}

