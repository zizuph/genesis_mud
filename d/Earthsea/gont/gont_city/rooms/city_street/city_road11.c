#pragma strict_types
#pragma no_clone

inherit "/std/room";

#include <stdproperties.h>

public void
create_room()
{
    add_prop(ROOM_S_MAP_FILE, "earthsea_map.txt");
    set_short("Between wooden buildings");
    set_long("The narrow street is lined on both sides"+
        " with two-story wooden buildings, built closely"+
        " together to provide living quarters for as many"+
        " as possible. This seems to be a part of the city"+
        " where the common people live, but you can also"+
        " see a few shops serving the neighborhood. Looking"+
        " southeast you can catch a glimpse of the harbour"+
        " and the many masts of the ships anchored there"+
        " while to the north the road continues towards"+
        " larger stone houses.\n");
    add_item("buildings","The wooden houses are built by"+
        " boards and are closely packed together, providing"+
        " living space for many citizens of the Port of Gont.\n");
    add_item("street","The street is fairly dirty, littered"+
        " with refuse. You can see animals poking around in the"+
        " dirt in the small side alleys.\n");
    add_item("animals","You see pigs and hens poking around"+
        " on the small alleys.\n");
    add_item("shops","These shops are small grocery stores,"+
        " serving the people with common goods. They don't seem"+
        " very interesting at all.\n");
    add_item("masts","To the southeast you can see many"+
        " tall masts rise up above the wooden buildings"+
        " blocking the way.\n");
    add_item("harbour","Between the houses you can catch"+
        " a glimpse of the busy harbour.\n");
    add_item("houses","Northwards are finer quarters, where"+
        " noblemen and merchants live in large stone buildings.\n");
    add_exit("city_road5", "north");
    add_exit("city_road10", "southeast");
}
