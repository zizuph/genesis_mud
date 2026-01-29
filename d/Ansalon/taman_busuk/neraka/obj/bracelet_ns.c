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
        return "This fine piece of jewelry is made out of pure "+metal+
    ". It looks like very good worksmanship, as you can see "+
    "the flawless surface gleaming in the light.\n";
    else
        return "This fine piece of jewelry is made out of pure "+
    metal+". Gleaming "+gem+" gems adorn its surface, making this "+
    "even more vaulable. The fine workmanship is aparent in its "+
    "overall shine.\n";
}


void
create_jewelry()
{
    ::create_jewelry();
    set_name("bracelet");
    set_ok_jewelry_slots(({ANSALON_JEWELRY_RARM,ANSALON_JEWELRY_LARM}));
    set_long("@@my_long@@");
}

