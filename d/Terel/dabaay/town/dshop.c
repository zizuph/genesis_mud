#include "/d/Terel/include/Terel.h"
inherit STDSHOP;

#pragma strict_types

#define DAB_TOWN DABAAY_DIR + "town/"
#define STORE_ROOM DAB_TOWN + "dstore"
#define DOBJ DABAAY_DIR + "obj/"

void
create_shop() 
{
    set_store_room(STORE_ROOM);
    set_keeper_file(DABAAY_DIR + "npc/beeman");
    set_shop_name("Beeman's General Store");
    set_short("Inside a run-down old shop");
    set_long(
        "You are inside a dilapidated little shop. It looks as though "+
        "no one has bothered to repair anything for years. Various "+
        "items are on display on several shelves behind a row of "+
        "crates that are serving as a counter. There is a sign hanging "+
        "from the back wall.\n");

    add_item("sign", "Beeman's General Store.\n");
    add_item(({"crates","crate","counter"}),
        "Several old crates are lined up in a row, serving as a makeshift "+
        "counter.\n");

    add_item(({"shelf","shelves","item","items"}),
        "Rough planks of wood, supported by triangular wood bracers, are "+
        "attached to the walls all around you. You may see a <list> of "+
        "the items for sale.\n");

    INSIDE;

    hated_race = ({"goblin"});
    favoured_race = ({"human","elf","dwarf","hobbit","gnome"});
    suspected_race = ({"half-elf","kender"});

    add_exit(STORE_ROOM, "south", "@@wiz_check");
    add_exit(DAB_TOWN + "square2_4", "east", 0);
}
