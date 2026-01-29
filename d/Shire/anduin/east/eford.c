/*
 * East ford in vales of Anduin.
 * By Finwe, June 2001
 * Swim routine borrowed from Gondor.
 */
 
#pragma strict_types
 
#include "local.h"
#include "/d/Shire/sys/defs.h"

inherit VALE_BASE;

void
create_vale_room()
{
    set_area("on the east side of");
    set_areaname("the Old Ford");
    set_land("the Vales of the Anduin");
    add_my_desc(" West is the Anduin river. There is a ford here " +
        "permitting travellers to cross the river. It is " +
        "dangerous, but if you are strong enough, you should be able " +
        "to swim across it. The Old Ford, as it is known, has " +
        "fallen into disrepair. The marshy land is evidence " +
        "that the river often crests its bank.\n");

    add_item(({"ford", "old ford"}),
        "The ford is a wide, shallow area in the Anduin that " +
        "allows travellers to cross it. It's rather difficult " +
        "as the river is swift and has been known to wash " +
        "unfortunate victims down river.\n");
    
    set_add_river_far();
    set_add_misty_far();

    add_exit(WEST_DIR + "wford", "west");
    add_exit(EAST_DIR + "rd01", "east");
    reset_shire_room();
 
}

void
reset_shire_room()
{
/*
    object whistle;

        if (!present("whistle",TO))
    {
        whistle = clone_object("/d/Shire/scav_hunt/whistle");
        whistle->add_prop(OBJ_I_HIDE, 10 + random(10));
        whistle->move(TO);
    }
*/
}
