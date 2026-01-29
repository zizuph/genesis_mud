/*
 * bladesmith_store
 *
 * The store room for the bladesmith forge.
 * 
 * Khail - August 15, 1997
 */
#pragma strict_types

#include "room.h"

inherit "/d/Khalakhor/std/room";
inherit "/lib/store_support";

/*
 * Function name: add_equip
 * Description  : Called to add equip to the store room.
 * Arguments    : item - Specify which item to clone into
 *                       the store room.
 *                       -1 - Clone all items.
 *                        0 - Clone claymore.
 *                        1 - Clone dirk.
 *                        2 - Clone axe.
 *                number - How many of 'item' do we want to
 *                         add to storage.
 * Returns      : n/a
 */
public void
add_equip(int item, int number)
{
    string *weps = ({"/d/Khalakhor/common/wep/claymore",
                      "/d/Khalakhor/common/wep/dirk",
                      "/d/Khalakhor/common/wep/axe"});
    int i;

    if (item > -1)
        weps = ({weps[item]});

    for (i = 0; i < number; i++)   
        map(weps, clone_object)->move(this_object());
}

public void
create_khalakhor_room()
{
    set_short("bladesmith storage");
    set_long("   This is the storage room for the " +
        "bladesmith.\n");
    add_exit(ROOM + "bladesmith_forge", "forge"); 

    set_alarm(0.5, 0.0, &add_equip(-1, 2));
}

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    store_update(ob);
}

