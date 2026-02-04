#pragma save_binary

inherit "/std/room";
inherit "/lib/store_support";
#include "/d/Terel/cedric/guild/guild_defs.h"
#include <macros.h>
#include "/d/Terel/common/terel_defs.h"
#include <stdproperties.h>

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    store_update(ob);
}

void
create_room()
{
    set_short("Workshop storeroom");
}