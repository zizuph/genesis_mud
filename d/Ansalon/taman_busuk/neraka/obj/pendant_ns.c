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
    return "This is a beautiful pendant that has "+
    "a sparkling "+gem+" hanging from a "+metal+" chain.\n";
}


void
create_jewelry()
{
    ::create_jewelry();
    remove_name("bracelet");
    set_name("pendant");
    set_gem_name("quartz");
    set_ok_jewelry_slots(({ANSALON_JEWELRY_NECK}));
    set_long("@@my_long@@");
    set_short("@@my_short@@");
}

string
my_short()
{
    string gem,metal;
    gem = query_jewelry_gem();
    metal = query_jewelry_metal();
    return gem+" pendant";
}

