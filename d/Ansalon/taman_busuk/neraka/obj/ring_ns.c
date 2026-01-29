#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/taman_busuk/neraka/local.h"
#include "/d/Ansalon/taman_busuk/neraka/std/jewelry.h"
#include <macros.h>

inherit NSTD+"jewelry.c";

/* Sarr */



string
my_long()
{
    string gem,metal;
    int i;
    gem = query_jewelry_gem();
    metal = query_jewelry_metal();
    if(!gem)
        return "This beautifully crafted ring is made out of "+
        "gleaming "+metal+". There are many beautiful, "+
        "intricate designs carved in it as well, proving this "+
        "piece of jewelry is of fine quality.\n";
    return "This beautifully crafted ring is made out of "+
    "gleaming "+metal+". The sparkling "+gem+" in the center "+
    "catches your eye, and you marvel at its perfection. The "+
    "fine quality of this ring is proven by all the intricate "+
    "and detailed designs carved in it.\n";
    add_item("designs","The are spirals, runes, and intricate "+
    "patterns all engraved upon this wonderful ring.\n");
}


void
create_jewelry()
{
    ::create_jewelry();
    remove_name("bracelet");
    set_name("ring");
    set_ok_jewelry_slots(({ANSALON_JEWELRY_RHAND,ANSALON_JEWELRY_LHAND}));
    set_long("@@my_long@@");
    set_short("@@my_short@@");
}

string
my_short()
{
    string gem,metal;
    gem = query_jewelry_gem();
    metal = query_jewelry_metal();
    if(gem) 
        return gem+" ring of "+metal;
    return metal+" ring";
}

