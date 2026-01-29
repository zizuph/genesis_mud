/* 
* This is the Telberin shop. They don't get a better deal here, though,
* otherwise we would get a nasty tax bill. Many thanks to Nick & Tricky
* for coding such nice shops for us to steal. #:-)
 * Thanks go to Tulix for letting me use this shop...I altered it a little.
 */
/*
 * Modified this shop to use in the Keepers of Telberin
 */

inherit "/std/room";
inherit "/d/Emerald/lib/shop_list";
#include <stdproperties.h>
#include <language.h>
#include "../guild.h"

/*
 * Function name:   create_room
 * Description:     Initialize this room
 */
void
create_room()
{
    config_default_trade();
    set_short("Keepers of Telberin shop");
    set_long("   This small, wooden-walled room is the shop for the "+
	     "Keepers of Telberin. A few merchants from the city proper "+
	     "agree to take turns manning and stocking this shop. They make "+
	     "quite a big profit here, so it is in their best interest "+
	     "to keep it running. You can use value or list commands "+
	     "here, 'list armours', 'list weapons', 'list <name>' and 'list' "+
	     "works too. There is also a small sign here to read containing "+
	     "more instructions.\n\n");

    add_exit("store", "north", "@@wiz_check");
    add_exit("post", "east");
    add_exit("kot_hq1", "west");    

    add_item("sign", "The sign is written in the old tongue.\n");

    add_prop(ROOM_I_INSIDE, 1);  /* This is a real room */

    set_store_room(KOT_ROOM_DIR + "store");

    add_item(({"walls", "wall"}),
	     "The walls are covered with wooden tiles, providing a nice, "+
	     "warm, comforting atmosphere.\n");

    add_item(({"floor","ground"}), "The floor is solid stone.\n");
}

/*
 * Function name:   init
 * Description:     Is called for each living that enters this room
 */
void
init()
{
    ::init();   /* You MUST do this in a room-init */
    init_shop(); /* Get the commands from the shop */
}

int do_list(string str)
{
    int res = ::do_list(str);

    write("Ri crystals may also be purchased here for twenty copper coins.\n" +
       "Simply \"buy <number> ri crystals\".\n");

    return res;
}

int
do_buy(string str)
{
    int num;
    object c;
    string s;

    if (sscanf(str, "%s ri crystals", s) || 
        sscanf(str, "%s ri crystal", s))
    {
        if (((num = atoi(s)) < 1) && ((num = LANG_NUMW(s)) < 1))
	{
            notify_fail("Buy how many ri crystals?\n");
            return 0;
	}

        c = clone_object(KOT_OBJ_DIR + "crystal");
        c->set_heap_size(num);
        if (sizeof(buy_it(({ c }), "", "")))
	{
  	    return shop_hook_bought_items(({ c }));
	}

        return 0;
    }

    return ::do_buy(str);
}

int
query_buy_price(object ob)
{
    if (ob->id(CRYSTAL_OBJECT))
    {
        return ob->query_prop(OBJ_I_VALUE);
    }

    return ::query_buy_price(ob);
}
