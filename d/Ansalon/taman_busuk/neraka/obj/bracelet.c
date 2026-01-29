#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/taman_busuk/neraka/local.h"
#include "/d/Ansalon/taman_busuk/neraka/std/jewelry.h"
#include <macros.h>

inherit NSTD+"jewelry.c";

/* Sarr */


string
query_auto_load()
{
    return MASTER+":"+jewelry_gem+"|"+jewelry_metal+"|"+query_prop(OBJ_I_VALUE)+"|";
}

void
init_arg(string arg)
{
    int value;
    string str1,str2;
    sscanf(arg,"%s|%s|%d|",str1,str2,value);
    if(str1 != "0")
        set_gem_name(str1);
    else
        jewelry_gem = 0;
    if(str2 != "0")
        set_metal_name(str2);
    else
        jewelry_metal = 0;
    add_prop(OBJ_I_VALUE,value);
}

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

