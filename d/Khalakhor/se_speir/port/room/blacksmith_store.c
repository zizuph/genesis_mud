/*
 * blacksmith_store
 *
 * The store room for the blacksmith forge.
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
 *                        0 - Clone mace.
 *                        1 - Clone morning star.
 *                        2 - Clone smiths hammer.
 *                number - How many of 'item' do we want to
 *                         add to storage.
 * Returns      : n/a
 */
public void
add_equip(int item, int number)
{
    string *weps = ({"/d/Khalakhor/common/wep/mace",
                     "/d/Khalakhor/common/wep/morning_star",
                     "/d/Khalakhor/common/wep/smiths_hammer"});
    int i;

    if (item > -1)
        weps = ({weps[item]});

    if (!sizeof(weps))
        return;

    for (i = 0; i < number; i++)   
        map(weps, clone_object)->move(this_object());
}

public void
create_khalakhor_room()
{
    set_short("blacksmith storage");
    set_long("   This is the storage room for the " +
        "blacksmith.\n");
    add_exit(ROOM + "blacksmith_forge", "forge");
    set_alarm(0.5, 0.0, &add_equip(-1, 2));
}

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    store_update(ob);
}
