#pragma strict_types

inherit "/d/Gondor/common/lib/town.c";

#include "/d/Gondor/defs.h"

public int check_open();
string sign();

void
create_room()
{
    hillside = "east";
    height = 2;
    road = 1;
    density = 3;
    extraline = "You stand almost halfway up towards Meduseld, " +
        "which golden walls can be seen up the hill to the west. " +
        "There is a big solid stone building to the east. " +
        "Over the door of the building is hanging a sign. " +
        "Kingsroad continues towards a little square to the " +
        "northwest and downwards to the southwest."; 
    add_cmd_item("sign", "read", sign());
    add_item(({"sign", }), sign());

    make_the_room();

    add_exit(EDORAS_DIR + "armoury", "east",      check_open);
    add_exit(EDORAS_DIR + "path3",   "southwest", 0);
    add_exit(EDORAS_DIR + "square1", "northwest", 0);

    (EDORAS_DIR + "armoury")->load_me();
}

public int
check_open()
{
    object  clock = find_object(CLOCK);
    string  time = clock->query_time_of_day();
    if (time == "night" && (!TP->id("shopkeeper")))
    {
        write("The shop is closed at night. Please come back in the morning.\n");
        return 1;
    }
    return 0;
}

string
sign()
{
    return BSN(
        "The sign is two by three feet, and made of wood. "+
        "It is hanging in forged iron bars. The sign states: " +
        "'Alwine's Armoury' in golden letters. Under it is written: "+
        " 'Open from dawn to dusk'.");
}

