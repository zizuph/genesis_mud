#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/wayreth/local.h"
#include <macros.h>
#include <stdproperties.h>
#include <cmdparse.h>
#include "/d/Krynn/guilds/wohs/defs.h"

inherit TOWERROOM;
inherit "/d/Gondor/common/lib/potion_storage";

#define POTIONSTORE "/d/Krynn/wayreth/tower/store_log"

void
reset_tower_room()
{
}

create_tower_room()
{
    set_short("alchemy lab potion storeroom");
    set_long("alchemy lab potion storeroom.\n");

    set_save_file(POTIONSTORE);
    create_potion_storage();

    reset_tower_room();
}

public void
enter_inv(object ob, object from)
{
   ::enter_inv(ob, from);
   enter_storage_inv(ob, from);
}