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
    return "This is one fine piece of jewelry. Upon a "+
    "pure "+metal+" chain, hangs a beautiful "+gem+" encrused "+
    "idol shaped like an dragon. You marvel at the superb "+
    "workmanship.\n";
}


void
create_jewelry()
{
    ::create_jewelry();
    remove_name("bracelet");
    set_name("medallion");
    add_adj("dragon");
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
    return gem+" dragon medallion";
}

