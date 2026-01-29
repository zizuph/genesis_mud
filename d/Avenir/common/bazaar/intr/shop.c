/*  Shop based on Gondor's /lib/shop.c
 *   by Iliyian
 */


inherit "/d/Avenir/common/lib/shop";
#include "../bazaar.h"
#include "/d/Avenir/include/relation.h"

#define STORE_ROOM (INTR + "store") /* Where the items are stored*/

void
create_shop()
{
    object bin;

    set_store_room(STORE_ROOM);
    set_short("A small store");
    set_long("A small, rectangular shop with flagstone floors and "+
       "rows of wooden shelves along the walls.  Spiralling stairs "+
       "lead up to the second floor balcony, where you can just "+
       "glimpse the extra stores neatly arranged in shelves that "+
       "reach the ceiling high above.  A wooden sign hangs "+
       "over the counter.  "+
       "The noises from the bazaar can be heard through open doorways "+
       "to the north and east.\n");

    AI(({"sign"}), "It has writing on it.\n");
    AI(({"counter","countertop"}),"It is of solid oak, well-worn and "+
       "whethered over the years.\n");
    AI(({"wall","walls"}),"The walls of ancient pale stone.\n");
    AI(({"floor","ground"}),"The flagstones are fairly clean, "+
       "considering all the traffic that comes through here.\n");
    AI(({"stair","stairs","staircase"}),"The stairs look very unstable. "+
        "Dosen't really matter, because you know you won't be getting "+
        "up there, don't you?\n");

    add_exit(EXTR+"str18.c", "north", 0);
    add_exit(EXTR+"str22.c", "east", 0);
    add_exit(STORE_ROOM, "up", "@@wiz_check");
			
	IN;       // Avenir is an undergound domain.
	IN_IN;    // Interior room, no flux msgs, steeds etc.


    set_shop_name("Sybarus Bazaar Goods and Services");
    set_keeper_file(NPC+"shopkeeper");
    set_suspected_race(({"hobbit"}));    // 'cause there aren't any in Avenir
    set_favoured_race(({"elf","dwarf"}));
    add_item("poster","It has readable words on it.\n");
    
    bin = clone_object("/d/Avenir/common/obj/trash_can");
    bin->move(this_object());

}



int
do_buy(string args)
{
    if (IS_INFIDEL(this_player()))
    {
        tell_object(this_player(), "The shopkeeper does not conduct "+
            "business with criminals.\n");
        return 1;
    }
    if (check_keeper()) return ::do_buy(args);
        return 0;
}

int
do_value(string args)
{
    if (check_keeper()) return ::do_value(args);
        return 0;
}

int
do_sell(string args)
{
    if (IS_INFIDEL(this_player()))
    {
        tell_object(this_player(), "The shopkeeper does not conduct "+
            "business with criminals.\n");
        return 1;
    }

  if (check_keeper()) return ::do_sell(args);
  return 0;
}

int
do_list(string args)
{
  if (check_keeper()) return ::do_list(args);
  return 0;
}


mixed
shop_hook_filter_sell(object ob)
{
   return 0;
  // cause we want it to buy everything...
}
