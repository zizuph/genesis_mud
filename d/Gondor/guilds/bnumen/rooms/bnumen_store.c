/*
 *   The storage room of the armoury in the House of the Black Numenoreans.
 *
 *	Coded by Olorin, November 1994.
 */
#pragma save_binary
#pragma strict_types

inherit "/std/room";
inherit "/lib/store_support";

#include <stdproperties.h>
#include "/d/Gondor/defs.h"

#define MAX_ITEMS	20
#define ITEMS		({ (BNUMEN_DIR + "obj/bnumen_hauberk"), \
			   (BNUMEN_DIR + "obj/bnumen_helm"),    \
			   (BNUMEN_DIR + "obj/bnumen_surcoat"), \
			   (BNUMEN_DIR + "obj/backpack"), \
			   (BNUMEN_DIR + "obj/horn"),    \
			   (MINAS_DIR + "obj/mt_weapon"),  \
			})

void
reset_room();

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    store_update(ob);
}

void
create_room()
{
   set_short("The shop's store room");
   set_long("This is the store room for the shop.\n");

   add_exit(BNUMEN_DIR + "rooms/bnumen_shop", "out",0);

   add_prop(ROOM_I_INSIDE, 1);  /* This is an inside room */

   enable_reset(200);
   reset_room();
}

void
add_one_item()
{
    int     i, j;
    object  wep;

    for (j = 0; j < 5; j++)
    {
	if (sizeof(all_inventory(TO)) >= MAX_ITEMS)
	    return;

	switch (i = random(sizeof(ITEMS)))
	{
        case 0..4:
            wep = clone_object(ITEMS[i]);
            break;
        case 5:
            wep = clone_object(ITEMS[i]);
            wep->set_weapon_type(
		 ONE_OF_LIST(wep->query_weapon_types()));
            break;
        default:
            break;
	}
	wep->move(TO);
    }

    set_alarm(2.0, 0.0, add_one_item);
}

void
reset_room() 
{
    int i;

    add_one_item();
}
