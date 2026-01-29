/*
 */

#pragma save_binary
#pragma strict_types

inherit "/std/room";
inherit "/lib/store_support";

#include "/sys/stdproperties.h"
#include "defs.h"
#include GARDEN_HERB_FILE



void
create_room()
{
    int i;

    set_short("The shop's store room");
    set_long("This is the store room for the herb "+
      "store.\n");
    set_max_values(270, 25);
    for (i = 0; i < (sizeof(GARDEN_HERBS) / 4); i++)
	(clone_object(GARDEN_HERBS[random(sizeof(GARDEN_HERBS))]))->move(TO);

}


void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    store_update(ob);
}

void
leave_inv(object ob, object to)
{
    ::leave_inv(ob, to);
    // restart decay in herbs when they leave here
    ob->restart_decay();
}
