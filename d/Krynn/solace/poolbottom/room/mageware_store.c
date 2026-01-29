#include "/d/Krynn/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <stdproperties.h>
#include <cmdparse.h>
#include "/d/Krynn/guilds/sohm/defs.h"

inherit POOLBOTTOM_IN;
inherit "/d/Gondor/common/lib/herb_storage";

#define MAGESTORE "/d/Krynn/solace/poolbottom/room/mware_log"

void
reset_poolbottom_room()
{
}

create_poolbottom_room()
{
    set_short("mageware storeroom");
    set_long("mageware storeroom.\n");

    set_save_file(MAGESTORE);

    reset_poolbottom_room();
}

public void
enter_inv(object ob, object from)
{
   ::enter_inv(ob, from);
   enter_storage_inv(ob, from);
}