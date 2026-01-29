/*
 * /d/Gondor/common/dwarf_guild/store.c
 *
 * Copyright (C) Stas van der Schaaf - Januari 7 1994
 *               Mercade @ Genesis
 *
 * This is the store-room of the shop of the dwarven race guild. The nice
 * feature about this store room is that the shop always keeps a certain
 * basic stock.
 *
 * Revision history:
 */

#pragma save_binary

inherit "/d/Gondor/common/room";
inherit "/lib/store_support";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"
#include "dwarf.h"

#define SHOP            (DWARF_DIR + "shop")

#define OIL_LAMP        (OBJ_DIR + "oil_lamp")
#define LAMP_OIL        (OBJ_DIR + "oilflask")
#define RUGSACK         (DWARVEN_RACE_GUILD_OBJECTS + "rugsack")
#define TORCH           (DWARVEN_RACE_GUILD_OBJECTS + "torch")
#define WALLET          (DWARVEN_RACE_GUILD_OBJECTS + "wallet")

void
create_room() 
{
    set_short("the store-cabinet of shop in the " + DWARVEN_RACE_GUILD_NAME);
    set_long(BSN("This cabinet is used as to store all items that are for " +
        "sale in the shop of the " + DWARVEN_RACE_GUILD_NAME + "."));

    add_exit(SHOP, "out");

    add_prop(ROOM_I_INSIDE, 1);

    set_default_stock( ({ OIL_LAMP, 2, LAMP_OIL, 4, RUGSACK, 2, TORCH, 4,
        WALLET, 2 }) );
    reset_store();
}

void
reset_room()
{
    reset_store();
}

void
enter_inv(object obj, object from)
{
    ::enter_inv(obj, from);

    if (interactive(obj))
    {
        if (obj->query_wiz_level())
        {
            return;
        }

	/* We must use move() here rather than move_living() since this
	 * call is being made from within a move_living() and that call
	 * cannot be made recursively.
	 */
        if (!(obj->move(SHOP, 1)))
        {
            tell_room(SHOP, QCTNAME(obj) + " falls out of the cabinet.\n",
                ({ obj }) );
            tell_room(TO, QCTNAME(obj) + " falls out of the cabinet.\n");
            tell_object(obj, BSN("You fall out of the cabinet."));

            return;
        }

        /* should never happen. */
        tell_room(TO, "You hear the shopkeeper shout: COME OUT!\n");
        return;
    }

    store_update(obj);
}
