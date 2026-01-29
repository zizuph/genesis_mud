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
    return "This is beautiful "+metal+" chain sparkles "+
    "brightly. Its intricate woven pattern makes you "+
    "marvel at its masterful workmanship. Its long enough "+
    "to probably fit around your waist as well as your neck.\n";
}


void
create_jewelry()
{
    ::create_jewelry();
    remove_name("bracelet");
    set_name("chain");
    set_ok_jewelry_slots(({ANSALON_JEWELRY_NECK,ANSALON_JEWELRY_WAIST}));
    set_long("@@my_long@@");
    set_short("@@my_short@@");
}

string
my_short()
{
    string gem,metal;
    gem = query_jewelry_gem();
    metal = query_jewelry_metal();
    return metal+" chain";
}

