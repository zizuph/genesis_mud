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

