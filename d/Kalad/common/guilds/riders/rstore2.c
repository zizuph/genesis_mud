inherit "/d/Kalad/room_std";
inherit "/lib/store_support";
#include "/d/Kalad/defs.h"
/* 
 * /d/Kalad/common/guilds/riders/rstore.c
 * Purpose    : store room for rshop.c(used store room exapmles)
 * Located    : riders guild hall
 * Created By : mhyrkhaan 2-20-97
 * Modified By: 
 */

#define MAX_ITEMS 50

void
create_room()
{
   ::create_room();
   add_prop(ROOM_I_INSIDE,1);
   set_short("Store room");
   set_long("You are in the store room of the Riders guild.\n");
   add_exit("/d/Kalad/common/guilds/riders/rshop2", "east",0,-1,-1);
   reset_room();
}

public void
enter_inv(object ob, object from)
{
   ::enter_inv(ob, from);
   store_update(ob);
}
#define SWORD "/d/Kalad/common/caravan/wep/lksword"
#define ARMOR "/d/Kalad/common/caravan/arm/cmscale"
#define SHIELD "/d/Kalad/common/caravan/obj/backpack"
#define HELM "/d/Kalad/common/caravan/arm/ghelm"
#define CLOAK "/d/Kalad/common/guilds/riders/da_cloak"
#define ARMOR2 "/d/Kalad/common/caravan/arm/gchain"
#define OIL "/d/Kalad/common/caravan/obj/oilflask"

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
mixed to_check = ({ ({ "create_sword", SWORD, 2 }),
({ "create_armor", ARMOR, 2 }),
({ "create_helm", HELM, 2 }),
({ "create_cloak", CLOAK, 5 }),
({ "create_armor2", ARMOR2, 2 }),
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
