#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/nordmaar/jennison/local.h"

inherit JENNISON_OUT;

void
reset_jennison_room()
{
    return;
}

void
create_jennison_room()
{
    set_short("East end of southern pier in Jennison");
    set_long("@@long_descr");

    /* from /d/Ansalon/nordmaar/jennison/std/o_room_base.c */
    add_pier_descriptions();
    add_bay_descriptions();

    add_item(({"sign", "large sign"}), "The sign has been nailed to "
        + "one of the massive wooden pillars here. The sign is much "
        + "taller than it is wide. Written vertically, from the top "
        + "and down, in large bold letters, you read: 'Flotsam.'\n");

    add_cmd_item(({"sign", "large sign"}), "read", "@@read_sign");

    add_exit(JENNISON_CITY + "pier06", "west", 0);

    reset_jennison_room();
}

string
read_sign()
{
    string str;

    str = "Written vertically, from the top and down, in large bold "
        + "letters, you read: 'Flotsam.'\n";

    return str;
}

string
long_descr()
{
    string str;    

    str = tod_descr1() + tod_descr2();
    str = str + "The wooden pier extending from the harbour ends "
        + "abruptly here, giving you a nice view of the small bay "
        + "that nestles the port city of Jennison. A ship could "
        + "easily land here. A large sign has been nailed to one "
        + "of the massive wooden pillars supporting the pier.\n";

    return str;
}
