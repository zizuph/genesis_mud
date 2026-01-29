/* Peddler.c coded by Amelia for Ten Alders 4/13/97
 * Use for the new Re Albi by Marisol 2/3/98
 * Modified by Marisol (07/14/98) to be used as
 * the duffer in the village of Ovejuno in Emerald
 */

inherit "/d/Emerald/std/room";
inherit "/d/Emerald/lib/shop_list";
#pragma no_clone
#pragma strict_types

#include "/d/Emerald/sys/macros.h"
#include <stdproperties.h>
#include <defs.h>
#include <cmdparse.h>
#include <macros.h>
#define STORE VILLAGE+ "duffer_store_ov.c"


#define DOOR DOORS+ "duffer_in.c"

object door;



void
reset_room()                    
{
}

void
create_emerald_room()
{
    config_default_trade();
    set_money_greed_sell(80);
    set_money_greed_buy(80);

    set_store_room(STORE);
    set_short("Duffer shop");
    set_long("The duffer's shop in Ovejuno. You see piles "+
        "of cheap, flashy articles all around the floor. You can barely "+
        "walk to the counter. You can <buy> or <sell> loot from your "+
        "journeys here. Also, you can <list> equipment, armours, or "+
        "weapons to see what the duffer has in stock.\n");

    add_item((({"articles", "piles of articles"})),
      "All sorts of used junk that the duffer buys and "+
      "resells.\n");



    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 1);
    add_prop(ROOM_I_IS, 1);
    reset_room();

    door = clone_object(DOOR);
    door->move(TO);  
}

void
init()
{
    ::init();
    init_shop();
}                     
