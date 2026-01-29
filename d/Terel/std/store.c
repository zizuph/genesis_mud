/*
 *   The storage room of the example shop
 */
#include "/d/Terel/include/Terel.h"
inherit STDROOM;
inherit "/lib/store_support";

#include <stdproperties.h>


object boot1,boot2;

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    store_update(ob);
}

reset_room()
{
    if (!boot1 || !present(boot1,TO))
    {
     boot1 = clone_object(MANSION + "obj/mining_boots");
     boot1->move(TO);
    }
    if (!boot2 || !present(boot2,TO))
    {
     boot2 = clone_object(MANSION + "obj/mining_boots");
     boot2->move(TO);
    }
}


create_room() 
{
    set_short("The SILVER FOREST TRADING POST Storage room");
    set_long("You are in the SILVER FOREST TRADING POST's Storage room.\n"
     + "Do you think you should really be in here?\n");

    add_exit(CALATHIN_DIR + "shop", "down");

   add_prop(ROOM_I_INSIDE, 1);  /* This is an inside room */
    reset_room();
}
