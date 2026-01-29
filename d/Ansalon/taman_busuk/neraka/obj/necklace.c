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

