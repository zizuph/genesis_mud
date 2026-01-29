/*********************************************************************
 * - wstore.c                                                      - *
 * - Created by Damaris 7/2005                                     - *
 *********************************************************************/
#pragma strict_types
#include <macros.h>
#include <stdproperties.h>
#include "../defs.h"
inherit "/d/Khalakhor/std/room";
inherit "/lib/store_support"; /* the default store-room support */


void
create_khalakhor_room() 
{
	set_short("Weaponry storeroom");
	set_long("   This is the store room for weapons.\n");
	
	add_exit("wshop", "north");
	this_object()->reset_room();
}

/*********************************************************************
 * - You should always call store_update() if an object enters the - *
 * - storeroom to update it and let it be added to the stock.      - *
 *********************************************************************/
void
enter_inv(object obj, object from)
{
	::enter_inv(obj, from);
	store_update(obj);
}

/*********************************************************************
 * - Here ends the necessary store-room code. If you want to have a- *
 * - nifty feature, you might consider the code below. Every time  - *
 * - the function reset_room() is called, the store of the shop is - *
 * - checked to see if a certain "default" stock is in stock and if- *
 * - not, if will be supplied.                                     - *
 *********************************************************************/
#define WEP1        (WEP + "dagger")
#define WEP2        (WEP + "rapier")
#define WEP3        (WEP +   "pole")
#define WEP4        (WEP +    "axe")
#define WEP5        (WEP +   "axe2")
#define WEP6        (WEP +  "pole2")

/*********************************************************************
 * - This global variable defines the standard inventory that      - *
 * - should be cloned every reset if the shop is not in full stock.- *
 * - The first entry is the function that is used to create the    - *
 * - object, the second its filename and the third is the number of- *
 * - objects that should be in stock.                              - *
 *********************************************************************/
 
mixed to_check = ({ ({"create_weapon", WEP1, 3}),
                    ({"create_weapon", WEP2, 3}),
                    ({"create_weapon", WEP3, 3}),
                    ({"create_weapon", WEP4, 3}),
                    ({"create_weapon", WEP5, 3}),
                    ({"create_weapon", WEP6, 3}), 
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

/*********************************************************************
 * - This function is a support function that helps keeping the    - *
 * - stock full every time reset_room() is called.                 - *
 * -                                                               - *
 * - extra = ({ function_name, filename }) ...                     - *
 * - given from reset_room()                                       - *
 *********************************************************************/
int
object_filter(object obj, mixed extra)
{
	return (function_exists(extra[0], obj) == extra[1]);
}
