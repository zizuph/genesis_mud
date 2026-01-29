inherit "/d/Gondor/common/lib/town";

#include "/d/Gondor/defs.h"

string  read_sign();

void
create_room()
{
    set_hillside("west");
    set_height(3);
    set_road(1);
    set_density(3);
    set_extraline("A sign is hanging over the door to a house to " +
        "the west. Kingsroad continues upwards to the southeast " +
        "and downwards to the northeast.");
    add_exit(EDORAS_DIR + "shop","west","@@check_open");
    add_exit(EDORAS_DIR + "square1","northeast",0);
    add_exit(EDORAS_DIR + "path6","southeast",0);

    make_the_room();
    add_item("sign", read_sign());
    add_cmd_item("sign", "read", read_sign());

    (EDORAS_DIR + "shop")->load_me();
}

string
read_sign()
{
    return BSN(
        "The sign is two by three feet, and made of wood. "+
        "It is hanging in forged iron bars. The sign states: 'Bendars "+
        "General Shop' in golden letters. Under it is written: "+
        " 'Open from dawn to dusk'.");
}

int
check_open()
{
    object clock = find_object(CLOCK);
    string time = clock->query_time_of_day();
    if (time == "night" && (!TP->id("shopkeeper")))
    {
        write("The shop is closed at night. Please come back in the morning.\n");
        return 1;
    }
    return 0;
}
