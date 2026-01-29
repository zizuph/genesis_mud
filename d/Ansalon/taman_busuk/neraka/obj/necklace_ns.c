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
        return "This is a beautiful necklace made of brilliant "+
    metal+". The interlaced bands of "+metal+" sparkle with "+
    "a keen shine.\n";
    return "This is a beautiful necklace made of brilliant "+
    metal+". The whole necklace is studded with sparkling "+
    gem+" gems.  The interlaced bands of "+metal+" sparkle with "+
    "a keen shine.\n";
}


void
create_jewelry()
{
    ::create_jewelry();
    remove_name("bracelet");
    set_name("necklace");
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
    if(gem) 
        return gem+" necklace";
    return metal+" necklace";
}

