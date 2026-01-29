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
    set_short("Southern pier in Jennison");
    set_long("@@long_descr");

    /* from /d/Ansalon/nordmaar/jennison/std/o_room_base.c */
    add_pier_descriptions(); 

    add_item(({"gate", "large gate"}), "A tall, wide, and very "
        + "open, gate leads south and into a large warehouse.\n");

    add_item(({"warehouse", "old warehouse"}), "Built of heavy "
        + "timber the old warehouse looks very sturdy. It has "
        + "been painted rust-red, like most of the buildings in "
        + "the harbour area. A large open gate leads south into "
        + "the warehouse.\n");

    add_exit(JENNISON_CITY + "pier05", "west", 0);
    add_exit(JENNISON_CITY + "pier07", "east", 0);
    

    reset_jennison_room();
}

string
long_descr()
{
    string str;    

    str = tod_descr1() + tod_descr2();
    str = str + "The wooden pier leads west towards the city "
        + "itself, and from here further east where it seems to "
        + "come to an end. A large ship could comfortably land "
        + "here. South, a large open gate leads into an old "
        + "warehouse.\n";

    return str;
}
