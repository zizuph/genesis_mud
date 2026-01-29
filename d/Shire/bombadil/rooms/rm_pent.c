/*
 * guest/pentroom  of Tom's House
 * By Finwe, January 2001
 */
 
#pragma strict_types

#include "/d/Shire/sys/defs.h" 
#include "../local.h"
 
inherit HOUSE_BASE;

void
create_house_room()
{
    set_short("A guest room");
    set_long("This is a low lean-to room with a sloping roof. It " +
        "has been added to the north end of the house. There are " +
        "windows in the east and west walls overlooking the flower " +
        "garden and the kitchen garden. Some beds are lined up " +
        "against the west wall, beneath a window looking out onto " +
        "the flower garden. A bench is set against the east wall, " +
        "under the window overlooking the kitchen garden.\n");

    add_item("furniture",
        "There are four beds lined against the west wall with a " +
        "bench against the west wall. They are both carved of oak " +
        "wood and look beautiful.\n"); 
    add_item(({"bench"}),
        "The bench is carved from oak. It is polished to a dark " +
        "color and serves more as a table than something to sit " +
        "on. A porcelain pitcher and a wash basin sit on the bench.\n");
    add_item(({"pitcher", "porcelain pitcher"}),
        "The pitcher is stout looking with a bulging base with " +
        "a wide lip. A large handle is attached opposite the lip " +
        "permitting the user to lift it and pour water into the " +
        "basin. The pitcher is white glazed and decorated with " +
        "small flowers both inside and outside the pitcher.\n");
    add_item(({"basin", "wash basin"}),
        "The basin is large bowl shaped. It is glazed white and " +
        "decorated with small flowers on the inside and out. The " +
        "basin is used to hold water poured from the pitcher for " +
        "cleaning oneself.\n");
    add_item(({"small flowers"}),
        "The small flowers are painted onto the porcelain pitcher " +
        "and wash basin. They twin about the objects and are very " +
        "delicate looking.\n");

    add_item(({"wood", "oak"}),
        "The wood is very beautiful and expertly carved. The " +
        "grain is rich and a dark color.\n");

    add_item(({"large bed", "bed"}),
		"The beds are made of wood. Each bed has a soft mattress, " +
        "a large bedcover, and some pillows at the head of the bed.\n");
    add_item(({"mattress", "mattresses"}),
        "The mattresses are thick and comfortable looking. They " +
        "are full of feathers and covered with a white cotton " +
        "linen cloth.\n");
    add_item(({"bedcover", "large bedcover", "bedcovers", "large bedcovers"}),
        "The bedcovers are a beige color. They are thick, luxurious, " +
        "and stuffed with down feathers. The bedcovers are spread " +
        "across the bed.\n");
    add_item(({"pillows", "pillow"}),
        "There pillows are soft and fluffy and sit at the head of " +
        "the bed.\n");
    add_item("windows",
        "The windows are large. During the day they fill the " +
        "room with bright sunlight and at night fill the room " +
        "with star and moonlight,\n");
    add_item(({"flowers"}),
        "The flowers are beautiful, growing outside the window in " +
        "gardens that surround the house.\n");
    add_item(({"flower gardens", "flower garden"}),
        "The flower gardens can be seen outside the western window. " +
        "They are full of healthy plants and bright flowers.\n");
    add_item(({"kitchen garden", "kitchen gardens"}),
        "The kitchen gardens grow outside the east window. They " +
        "are full of healthy green plants.");
    add_item(({"gardens", "garden"}),
        "The gardens grow outside the east and west windows. " +
        "They are flower gardens and kitchen gardens. The gardens " +
        "look healthy and well tended and cared for.\n");

    add_item(({"west window", "western window"}), 
        "@@west_down@@\n");
    add_item(({"east window", "eastern window"}), 
        "@@east_down@@\n");

    set_extra_window("@@window_position@@ set into the " +
        "east and west walls.");
    add_cmd_item(({"curtains", "drapes"}), "close",
        "@@close_curtains@@");
    add_cmd_item(({"curtains", "drapes"}), "open",
            "@@open_curtains@@");

    num_of_windows=2;
    reset_shire_room();

    add_exit(ROOMS_DIR + "rm_hall02", "south");
}


void
reset_shire_room()
{
}
