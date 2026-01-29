/* created by Zizuph 09/2021 */

inherit "/std/container";
#include "../local.h"

#include <stdproperties.h>

#define FLYER_PATH  OBJ + "thau_flyer"

create_container()
{
    setuid();
    seteuid(getuid());
    set_short("grand wooden desk");
    set_name("desk");
    add_adj(({ "grand", "wooden" }));
    set_long("This is a grand wooden desk.  On top of it are several " +
       "parchments.\n");

    add_prop(CONT_I_WEIGHT, 10000);
    add_prop(CONT_I_VOLUME, 10000);

    add_prop(CONT_I_MAX_VOLUME, 12000);
    add_prop(CONT_I_MAX_WEIGHT, 12000);
    add_prop(OBJ_M_NO_GET, "You do not want to disturb the desk.\n");

    reset_container();
    enable_reset();
}

void reset_container()
{
    int count = 0;
    foreach (object obj : all_inventory(this_object()))
    {
        if (obj->query_name(0) == "_transform_parchment")
            count++;
    }
    for (int i = count ; i < 10; i++)
    {
        object flyer = clone_object(FLYER_PATH);
        flyer->move(this_object(), 1);
    }
}
