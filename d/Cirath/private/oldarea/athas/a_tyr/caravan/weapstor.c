/* weapstor.c: The storeroom of the Tyr weapon merchant */
inherit "/std/room";
inherit "/lib/store_support";
#include "defs.h"

#define STNEDGGR "/d/Cirath/athas/o_weapons/knife_sd.c"
#define QUABONE  "/d/Cirath/athas/o_weapons/quabone.c"
#define STONEAXE "/d/Cirath/athas/o_weapons/axe_ston.c"

void create_room()
{
    set_short("the storeroom of the weapon merchant");
    set_long("Various weapons are stored on shelves to be sold later in "+
             "Grik's shop.\n");
    INSIDE
    add_exit(TZ_CARAVAN+"weapmrch.c", "north", 0, 1);
    clone_object(STNEDGGR)->move(TO, 1);
    clone_object(QUABONE)->move(TO, 1);
    clone_object(STONEAXE)->move(TO, 1);
}

void enter_inv(object obj, object from)
{
    ::enter_inv(obj, from);
    store_update(obj);
}
