/*
 *   The storage room of the example shop
 */

inherit "/std/room";
inherit "/lib/store_support";

#include <stdproperties.h>
#include "/d/Terel/common/terel_defs.h"

object boot1,boot2;

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    store_update(ob);
}

reset_room()
{
    if (!boot1 || !present(boot1,this_object()))
    {
	boot1 = clone_object(MANSION + "obj/mining_boots");
	boot1->move(this_object());
    }
    if (!boot2 || !present(boot2,this_object()))
    {
	boot2 = clone_object(MANSION + "obj/mining_boots");
	boot2->move(this_object());
    }
}


create_room() 
{
    set_short("storage room");
   set_long("Storage room.\n"
     + "Do you think you should really be in here?\n");

    add_exit("/d/Terel/n_port/shop", "down");

   add_prop(ROOM_I_INSIDE, 1);  /* This is an inside room */
    reset_room();
}
