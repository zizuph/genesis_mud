/*
 *   The storage room of the Edoras armoury
 */

inherit "/std/room";
inherit "/lib/store_support";

#include <stdproperties.h>
#include "/d/Gondor/defs.h"

void reset_room();

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    store_update(ob);
}

void
create_room()
{
   set_short("The shop's store room");
   set_long("This is the store room for the shop.\n");

   add_exit(EDORAS_DIR + "armoury", "west",0);

   add_prop(ROOM_I_INSIDE, 1);  /* This is an inside room */

    reset_room();
}

void
reset_room()
{
    FIX_EUID
    if (!present("helmet",TO))
        clone_object(ARM_DIR + "fhelmet")->move(TO);
    if (!present("hatchet",TO))
        clone_object(WEP_DIR + "hatchet")->move(TO);
    if (!present("knife",TO))
        clone_object(EDORAS_DIR + "obj/fknife")->move(TO);
    if (!present("shovel",TO))
        clone_object(OBJ_DIR + "shovel")->move(TO);
}
