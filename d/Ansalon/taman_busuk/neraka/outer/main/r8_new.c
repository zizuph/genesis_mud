/* Ashlar, 25 Jul 97 */

#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/taman_busuk/neraka/local.h"
#include "/d/Ansalon/taman_busuk/mountains/local.h"
#include <macros.h>

inherit OUTER_OUT;

void
create_neraka_room()
{
	set_short("a dirt road in the vincinity of Neraka");
    set_extra_long("You are standing on a dirt road not far from " +
        "the city of Neraka. The road leads north towards the distant " +
        "mountains, and south to the city. There is a raised wooden " +
        "platform here, which leads into a large warehouse to the west.");
    add_item_dirtroad();
    add_item(({"city","neraka"}),"The city sprawls out to the south, " +
        "across the plains.\n");
    add_item(({"platform","wooden platform"}),
        "The raised platform is made of wooden planks. From the look of " +
        "it, you guess it is there to facilitate loading and unloading " +
        "cargo from wagons coming in to Neraka.\n");
    add_item(({"planks","wooden planks"}),
        "The planks that make up the platform are old but still sturdy.\n");
    add_item("warehouse","It is large and seems able to hold quite a lot " +
        "of goods. There are people going to and from it, carrying various " +
        "sacks and crates to and from the city to the south.\n");

    add_exit(NOUTER+"main/r7","south");
    add_exit(NOUTER+"main/ware","west");

    if (LOAD_ERR(MOUNTAINS_OBJECT))
    {
        write("\nBug! Cannot link to the mountains! Please report immediately!\n\n");
        return;
    }   

    add_exit("","north","@@enter_map:" + MOUNTAINS_OBJECT + "|N@@");

}

int
no_go()
{
    write("The mountains are so far, and the road is so dusty.. You would " +
        "rather try to catch a transport out of here.\n");
    return 1;
}
