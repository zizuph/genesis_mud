/*
 *   The storage room of the Pelargir Arms shop
 */

inherit "/d/Gondor/common/room";
inherit "/lib/store_support";
#include <stdproperties.h>
#include "/d/Gondor/defs.h"

/* prototype */
void reset_room();

int nr;

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    store_update(ob);
}
void
create_room() 
{
set_short("The store room of the Arms Shop of Pelargir");
set_long("This is the store room for the Arms Shop of Pelargir.\n");
add_exit("/d/Gondor/pelargir/misc/pelarms", "east",0);
add_prop(ROOM_I_INSIDE, 1);  /* This is an inside room */
reset_room();
}

void
reset_room()
{
    FIX_EUID
    if (!present("sword",TO))
    {
        clone_object(WEP_DIR+"lsword")->move(TO);
        clone_object(WEP_DIR+"ssword")->move(TO);
    }
    if (!present("armour",TO))
    {
        clone_object(ARM_DIR+"studl")->move(TO);
        clone_object(ARM_DIR+"fsshield")->move(TO);
    }
    if (!present("saw", TO))
    {
        clone_object("/d/Gondor/pelargir/obj/saw")->move(TO);
    }
}


