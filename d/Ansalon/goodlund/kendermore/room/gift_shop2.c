/* Storeroom for gift shop */

inherit "/std/room";
inherit "/lib/store_support";

#include "../local.h"
#include <stdproperties.h>
#include "/d/Ansalon/common/defs.h"

#define CARVING KOBJ + "carving"

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    store_update(ob);
}

create_room()
{
    set_short("The shop's store room");
    set_long("This is the store room for the shop.\n");

    add_exit(KROOM + "gift_shop", "west");

    INSIDE;
    reset_room();
}

reset_room()
{
/*    object ob;
    seteuid(getuid(TO));
    if (!P(CARVING, TO))
        {
        ob = clone_object(CARVING);
        ob->add_name(CARVING);
        ob->move(TO);
        }
*/
return;
}
