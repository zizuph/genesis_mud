/*
 *  /d/Gondor/clubs/nisse/room/store.c
 *
 *  The storage room of the shop in the Nisse Ohtar camp.
 *
 *  Deagol, April 2003
 */

#pragma save_binary
#pragma strict_types

inherit "/std/room";
inherit "/lib/store_support";

#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "../nisse_defs.h"

#define TORCH_OBJ	(OBJ_DIR + "torch")
#define PACK_OBJ	(NISSE_OBJ_DIR + "basketpack")
#define SKIN_OBJ	(NISSE_OBJ_DIR + "waterskin")
#define GLOVE_OBJ	(NISSE_OBJ_DIR + "glove")
#define HOOD_OBJ	(NISSE_OBJ_DIR + "hood")
#define POUCH_OBJ	(NISSE_OBJ_DIR + "pouch")
#define JESSES_OBJ	(NISSE_OBJ_DIR + "jesses")
#define WOAD_OBJ	(NISSE_OBJ_DIR + "woad")

void
create_room() 
{
    set_short("The store-room of the Nisse Ohtar Store");
    set_long("This is the store-room for the Nisse Ohtar Store.\n");

    add_exit(NISSE_ROOM_DIR + "shop", "east", 0, 0, 0);

    add_prop(ROOM_I_INSIDE, 1);

    set_default_stock( ({ TORCH_OBJ, 1, PACK_OBJ, 1, SKIN_OBJ, 1,
        GLOVE_OBJ, 1, HOOD_OBJ, 1, POUCH_OBJ, 1, JESSES_OBJ, 1,
        WOAD_OBJ, 1 }) );

    reset_store();
}

/*
 *  Function name: leave_inv
 *  Description  : This routine makes this store room always full, when an
 *                 object leaves the room, the room is updated.
 *  Arguments    : object ob - the object that just leaved this inventory
 *                 object to - where it went
 */
void
leave_inv(object obj, object to)
{
    ::enter_inv(obj, to);

    store_update(obj);

    reset_store();
}
