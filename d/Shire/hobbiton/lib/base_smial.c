/*
 * Base file for smials
 * Finwe, March 2020
 */

#include "/d/Shire/sys/defs.h"
#include "../defs.h"
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>

inherit AREA_ROOM;
inherit "/d/Shire/std/room/room_tell";
inherit "/lib/commands.c";

void create_smial() {}

public void create_room()
{
    set_room_tell_time(60+random(120));

    create_smial();

}

void add_floor(string str)
{
    add_item(({"floor", "down", "ground"}),
        "The floor is covered in a pattern of stone blocks in a " +
        "criss-cross pattern. They are smooth and look clean. " + str + "\n");
}

void add_walls(string str)
{
    add_item("walls", 
        "The walls are round and tunnel shaped. They are covered with plaster " +
        "and painted a pale yellow color." + str + "\n");
}

void add_ceiling(string str)
{
    add_item(({"up", "ceiling"}), 
        "The ceiling is round and covered with plaster. It is painted " +
        "a pale yellow color. " + str + "\n");
}

/*
void XXX(string str)
{
    add_item(({"XXX"}),
        "XXX" + str + "\n");
}

void XXX(string str)
{
    add_item(({"XXX"}),
        "XXX" + str + "\n");
}

void XXX(string str)
{
    add_item(({"XXX"}),
        "XXX" + str + "\n");
}

void XXX(string str)
{
    add_item(({"XXX"}),
        "XXX" + str + "\n");
}


*/



