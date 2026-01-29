#include "../default.h"

inherit CVAN_ROOM;
inherit "/lib/store_support"; /* the default store-room support */

#include <stdproperties.h>    /* the properties                 */

void
create_cvan_room()
{
    set_short("The store room of the map shop");
    set_long("This is the store room of the mapmaker's shop, better get "+
      "out now or Ystof will get very irate with you!\n");

    add_exit(CVAN + "shop/mmshop", "east");

    add_prop(ROOM_I_INSIDE, 1);

    set_hear_bell(1);

    this_object()->reset_room();
}

/*
 * You should always call store_update() if an object enters the store-
 * room to update it and let it be added to the stock.
 */
void
enter_inv(object obj, object from)
{
    ::enter_inv(obj, from);
    store_update(obj);
}

/*
 * Here ends the necessary store-room code. If you want to have a nifty
 * feature, you might consider the code below. Every time the function
 * reset_room() is called, the store of the shop is checked to see if
 * a certain "default" stock is in stock and if not, if will be supplied.
 */

#define KMAP		(OBJ + "kmap")
#define CARMAP		(OBJ + "carmap")
#define KAMAP		(OBJ + "kamap")
#define WKALMAP		(OBJ + "wkalmap")
#define PORTMAP		(OBJ + "portmap")
#define CENTMAP		(OBJ + "centmap")
#define NOBLEMAP	(OBJ + "noblemap")

/*
 * This global variable defines the standard inventory that should be
 * cloned every reset if the shop is not in full stock. The first entry is
 * the function that is used to create the object, the second its filename
 * and the third is the number of objects that should be in stock.
 *
 * In this particular shop, two bags and four torches will be in the shop
 * each time reset_room is called to update the shop. This may of course
 * mean that the shop can be sold out in the meantime. If there are more
 * than four torches when reset_room is called, the surplus is not removed.
 */
mixed to_check = ({ ({ "create_book", KMAP, 3 }),
  ({ "create_book", NOBLEMAP, 3 }),
  ({ "create_book", CARMAP, 3 }),
  ({ "create_book", CENTMAP, 3 }),
  ({ "create_book", KAMAP, 3 }),
  ({ "create_book", WKALMAP, 3 }), ({ "create_book", PORTMAP, 3 }),
});

void
reset_room()
{
    object *all_inv = all_inventory();
    int     i, j;
    int     num_found;

    for (i = 0; i < sizeof(to_check); i++)
    {
	num_found = sizeof(filter(all_inv, "object_filter", this_object(),
	    ({ to_check[i][0], to_check[i][1] }) ));

	if (num_found < to_check[i][2])
	{
	    for (j = num_found; j < to_check[i][2]; j++)
	    {
		clone_object(to_check[i][1])->move(this_object(), 1);
	    }
	}
    }
}

/*
 * This function is a support function that helps keeping the stock
 * full every time reset_room() is called.
 *
 * extra = ({ function_name, filename }) ... given from reset_room()
 */
int
object_filter(object obj, mixed extra)
{
    return (function_exists(extra[0], obj) == extra[1]);
}
