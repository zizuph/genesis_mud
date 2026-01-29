#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/tharkadan/local.h"
#include "/sys/stdproperties.h"

inherit THARK_IN;
inherit "/lib/store_support";

#define TORCH 	"solace_shop_torch"
#define TOBACCO TOBJ + "tobacco"

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    store_update(ob);
}

void
create_tharkadan_room()
{
    set_short("The shop's store room");
    set_long("This is the store room for the shop.\n");

    add_exit(ROOM + "dwarf/shop", "south");

    add_object("/d/Krynn/solace/new_village/obj/torch");
    add_object(TOBACCO, 4);
}

