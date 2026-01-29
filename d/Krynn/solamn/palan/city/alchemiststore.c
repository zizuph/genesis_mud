// Gem storeroom borrowed from Avenir
// Arman 9/11/2003

#define POTIONSTORE "/d/Krynn/solamn/palan/city/pstore"

#include "../local.h"
#include <stdproperties.h>

inherit ROOM_BASE
inherit "/d/Gondor/common/lib/potion_storage";

#define AWARE_POT "/d/Krynn/common/potions/awareness_potion"
#define STONE_POT "/d/Krynn/common/potions/stone_potion"
#define STEEL_POT "/d/Krynn/common/potions/steel_potion"
#define SPEED_POT "/d/Krynn/common/potions/speed_potion"

void
reset_palan_room()
{
    object items;
    mixed pots = query_potions();

    //index 0 is the number of potions
    if (!pots[AWARE_POT] || !pots[AWARE_POT][0]) {
        items = clone_object(AWARE_POT);
        items->move(this_object());
        enter_inv(items,TP);
    }
    
    if (!pots[STONE_POT] || !pots[STONE_POT][0]) {
        items = clone_object(STONE_POT);
        items->move(this_object());
        enter_inv(items,TP);
    }

    if (!pots[STEEL_POT] || !pots[STEEL_POT][0]) {
        items = clone_object(STEEL_POT);
        items->move(this_object());
        enter_inv(items,TP);
    }

    if (!pots[SPEED_POT] ||!pots[SPEED_POT][0]) {
        items = clone_object(SPEED_POT);
        items->move(this_object());
        enter_inv(items,TP);
    }
}

void
create_palan_room()
{

    set_short("The Palanthas alchemist shop");
    set_long("This is the alchemist shop in Palanthas, where mages " +
             "sometimes comes to sell off their speciality items " +
             "or others visit to see the most weird items in the " +
             "realm.\n");

    add_exit("/d/Krynn/solamn/palan/city/alchemist", "up");
    set_save_file(POTIONSTORE);
    create_potion_storage();
    enable_reset(10);
    reset_palan_room();
}


public void
enter_inv(object ob, object from)
{
   ::enter_inv(ob, from);

   enter_storage_inv(ob, from);
}


