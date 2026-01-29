/*
 * Storage room for Rivendell shop
 * Will clone a rabbit skin herb sack every xx hours
 * Based on the Bree bank
 * -- Finwe, June 2007
 */

#pragma strict_types

#include "local.h"

inherit HOUSE_IN_BASE;
inherit "/lib/store_support";
void reset_shire_room();
#define MAX_POUCHES 10

static object *pouches = allocate(MAX_POUCHES);
object sack;
int day_count = 0,
    day_max = 30;



void
create_room()
{
    object sack;

    set_short("Stuffy store room");
    set_long("You are in the stuffy store room of the general store.\n");

    set_max_values(27, 7);

    add_exit(VALLEY_DIR + "shop", "up", 0);

    sack = clone_object("/d/Shire/common/obj/herb_sack");
    sack -> move(TO);
//    find_player("finwe")->catch_tell("\nRivendell herb sack cloned, - Reboot, /d/Shire/rivendell/room/valley/store \n\n");


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
int index;

 for(index = 0; index < MAX_POUCHES; index++)
    {
        if (!objectp(pouches[index]))
        {
            pouches[index] = clone_object("/d/Shire/common/obj/herb_pouch");
            pouches[index]->move(TO);

        }
    }

// clone the sack
    if(day_count<day_max)
    {
        day_count = day_count +1;
    }

    else if(day_count>=day_max)
    {
        sack = clone_object("/d/Shire/common/obj/herb_sack");
        sack -> move(TO);

        day_count = 0;
    }

}
