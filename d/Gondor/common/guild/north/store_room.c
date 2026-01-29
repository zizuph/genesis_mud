#pragma save_binary

inherit "/d/Gondor/common/room";
inherit "/lib/store_support";

#include <stdproperties.h>
#include "/d/Gondor/defs.h"

#define OIL_LAMP "/d/Gondor/common/obj/oil_lamp"
#define OILFLASK "/d/Gondor/common/obj/oilflask"
#define BACKPACK "/d/Gondor/common/guild/obj/backpack"

object *oil;
int nr;

create_room() 
{
    set_short("The store room of the rangers of the North shop");
    set_long(BS("The store room of the rangers of the North shop.\n"));

    add_prop(ROOM_I_INSIDE,1);
    add_exit(RANGER_NORTH_DIR+"shop","north",0,0);

    nr = 2 + random(2);
    oil = allocate(nr);

    reset_room();
}

reset_room()
{
    int i;
    object  sword;

    seteuid(getuid(TO));
    if (!present("boots",TO))
        clone_object(RANGER_NORTH_DIR+"obj/travel_boots")->move(TO);
    if (!present("shortsword",TO))
    {
        (sword = clone_object(WEP_DIR + "r_lsword"))->move(TO);
        sword->remove_prop("_Gondor_m_rangers_no_sell");
    }

}

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    store_update(ob);
}

