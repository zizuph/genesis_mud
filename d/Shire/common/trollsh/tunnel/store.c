#pragma strict_types
 
#include "local.h"
 
//inherit HOUSE_IN_BASE;
inherit "/std/room";
inherit "/lib/store_support";
void reset_shire_room();


void
create_room()
{
    set_short("Stuffy store room");
    set_long("Storage room of Trollshaw shop.\n");
 
    set_max_values(35, 7);
 
 
    add_exit(TUN_DIR + "shop", "north", 0);
    reset_shire_room();
}
 
void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    store_update(ob);
}

void
reset_shire_room()
{
}
