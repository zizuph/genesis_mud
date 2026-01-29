inherit "/d/Kalad/room_std";
inherit "/lib/store_support"; /* the default store-room support */

#include "/d/Kalad/defs.h"
#include <stdproperties.h>    /* the properties                 */

void
create_room()
{
set_short("Storeroom");
set_long("This is a big room with alcohol in it.\n");
add_exit(TRADE(tsquare/liquor_shop),"north",0,-1,-1);

    add_prop(ROOM_I_INSIDE, 1);
hear_bell = 1;

    this_object()->reset_room();
}

void
enter_inv(object obj, object from)
{
    ::enter_inv(obj, from);

    store_update(obj);
}

#define VODKA "/d/Kalad/common/trade/tsquare/obj/vomit_vodka.c"
#define WHISKEY "/d/Kalad/common/trade/tsquare/obj/whiskey.c"
#define TEQUILA "/d/Kalad/common/trade/tsquare/obj/tequila.c"
#define STOUT "/d/Kalad/common/trade/tsquare/obj/triple_stout.c"

mixed to_check = ({ ({ "create_drink", VODKA, 6}),
({ "create_drink", WHISKEY, 6}),
({ "create_drink", STOUT, 6}),
({ "create_drink", TEQUILA, 6}),
                 });

void
reset_room()
{
    object *all_inv = all_inventory();
    int     i, j;
    int     num_found;

    for (i = 0; i < sizeof(to_check); i++)
    {
        num_found = sizeof(filter(all_inv, "object_filter",
this_object(),
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
