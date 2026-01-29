#include "/d/Krynn/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <stdproperties.h>
#include <cmdparse.h>
#include "/d/Krynn/guilds/sohm/defs.h"

inherit POOLBOTTOM_IN;
inherit "/d/Gondor/common/lib/potion_storage";

#define POTIONSTORE "/d/Krynn/solace/poolbottom/room/store_log"

void
reset_poolbottom_room()
{
}

create_poolbottom_room()
{
    set_short("alchemy lab potion storeroom");
    set_long("alchemy lab potion storeroom.\n");

    set_save_file(POTIONSTORE);
    create_potion_storage();

    reset_poolbottom_room();
}

public void
enter_inv(object ob, object from)
{
   ::enter_inv(ob, from);
   enter_storage_inv(ob, from);
}