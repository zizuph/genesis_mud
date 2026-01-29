/*
 *   The storage room of the Solace drugstore
 */

#include "/d/Krynn/common/defs.h"
#include "local.h"
#include "/sys/stdproperties.h"

inherit SOLINROOM;
inherit "/lib/store_support";

#define TORCH 	"solace_shop_torch"

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    store_update(ob);
}

create_solace_room()
{
    set_short("The shop's store room");
    set_long("This is the store room for the shop.\n");

    add_exit(TDIR + "shop", "south");

    add_prop(ROOM_I_INSIDE, 1);  /* This is an inside room */
    reset_solace_room();
}

reset_solace_room()
{
    object ob;

    if (P(TORCH, TO))
	return;
    seteuid(getuid(TO));
    ob = clone_object(OBJ + "torch");
    ob->add_name(TORCH);
    ob->move(TO);
}


