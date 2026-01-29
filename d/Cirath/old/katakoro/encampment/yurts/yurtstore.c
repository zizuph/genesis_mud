/*
* Created by: Chaos
* Date: 5 April 1995
*
* File: /d/Cirath/katakoro/encampment/yurts/yurtstore.c
* Comments: Metalworker's Yurt	,edited by Luther Oct. 2001
*/

inherit "/std/room";          
inherit "/lib/store_support"; 

#include <stdproperties.h>   
#include "defs.h"
#define SABER KAT_WEP + "saber.c"
#define KALAT KAT_ARM + "kalat2.c"


void
create_room() 
{
    	set_short("The merchants storeroom");
    	set_long("This room is used as to store all items avaliable for " +
        	"purchase in the merchants shop.\n");

   add_exit(KAT_YURTS + "yurt3","out", 0, 1);

    	INSIDE;

    	this_object()->reset_room();
}

void
enter_inv(object obj, object from)
{
    	::enter_inv(obj, from);
    	store_update(obj);
}

mixed to_check = ({ ({ "create_weapon",SABER,2 }),
                    ({ "create_armour",KALAT,4 }),
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

int
object_filter(object obj, mixed extra)
{
    return (function_exists(extra[0], obj) == extra[1]);
}
	
