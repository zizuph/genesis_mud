/*
* Created by: 
* Date: 
*
* File: /d/Cirath/chukel/ciubori/houses/shop.c
* Comments: edited by Luther Oct. 2001
*/

inherit "/std/room";
inherit "/lib/shop";

#include "defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <language.h>
#include <cmdparse.h>
#include <composite.h>
#include <filter_funs.h>

#define STORE_ROOM CIU_HOU + "store1"

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
    	set_long("You are standing inside the Ciubori Merchants Trade-Post. "+
      		"It's a quite large shop with highly decorated walls. The "+
      		"owner is propably making a lot of money here.\n");

    	add_item("sign", "A nice looking sign, perhaps you should read it.\n");

    	INSIDE;
    	
    	add_exit(CIU_HOU + "store1", "up", "@@wiz_check", 1);
    	add_exit(CIU_STR + "tstreet2", "west", 0, 1);
	reset_room();
}

void
init()
{
    	::init();
    	init_shop();
}

