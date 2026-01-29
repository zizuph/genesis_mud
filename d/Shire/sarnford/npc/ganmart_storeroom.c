#include <stdproperties.h>
#include <macros.h>
#include "/d/Shire/sys/defs.h"
#include "/d/Shire/sys/shop_items.h"

inherit "/std/room";
inherit "/lib/store_support";

void
create_room()
{
	add_prop(ROOM_I_INSIDE, 1);

	set_default_stock( ({ SWORD, 2, 
						  TORCH, 4,
						  BACKPACK, 2, 
						  SACK, 1,
						  SBAG, 2,
						  HERB_POUCH, 3,
						  HERB_GLOVES, 3 }) );
    reset_store();
}

void
enter_inv(object obj, object from)
{
    ::enter_inv(obj, from);
    store_update(obj);
}

void
reset_room()
{
	reset_store();
}