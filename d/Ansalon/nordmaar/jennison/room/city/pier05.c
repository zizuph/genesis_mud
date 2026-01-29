#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/nordmaar/jennison/local.h"

inherit JENNISON_OUT;

void
reset_jennison_room()
{
    return;
}

create_jennison_room()
{
    set_short("West end of southern pier in Jennison");
    set_long("@@long_descr");

    /* from /d/Ansalon/nordmaar/jennison/std/o_room_base.c */
    add_pier_descriptions(); 

    add_item(({"road", "dirt road", "wide road", "wide dirt road"}),
          "This is the main road leading into Jennsion from the "
        + "south. It is little more than a wide dirt road running "
        + "almost parallel to the piers' north-south direction.\n");

    add_exit(JENNISON_CITY + "pier06", "east", 0);

    reset_jennison_room();
}

string
long_descr()
{
    string str;    

    str = tod_descr1() + tod_descr2();
    str = str + "The wooden pier runs north and east from here. "
        + "The sharp turn of the pier only allow smaller ships "
        + "access to these parts of the harbour area. A little "
        + "distance to the west, a wide dirt road runs north-south "
        + "almost parallel to the pier.\n";


    return str;
}
