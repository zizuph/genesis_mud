inherit "/std/object";
#include "/d/Kalad/defs.h"
#include "/d/Kalad/common/guilds/khiraa/khiraa_defs.h"
#include <cmdparse.h>

void
create_object()
{
    ::create_object();
    set_name("candle");
    set_adj(({"eerie","white"}));
    set_short("eerie white candle");
    
    set_long("This is a strange candle formed in the shape of a "+
    "pyramid. On each side of it, there is a grim skull carved. You "+
    "could add it to a jack-o-lantern.\n");
    add_prop(OBJ_I_WEIGHT,10);
    add_prop(OBJ_I_VOLUME,4);
    add_prop(OBJ_I_VALUE,30);
}

int
do_light(string str)
{
    if(str == "candle")
    {
        write("The wick doesn't seem to want to light.\n");
        return 1;
    }
    return 0;
}

int
do_add(string str)
{
    object *obs;
    string st2,st3;
    NF("Add candle to what?\n");
    if(!str)
        return 0;
    if(sscanf(str,"%s to %s",st2,st3) != 2)
        return 0;
    if(st2 != "candle")
        return 0;
    obs = FIND_STR_IN_OBJECT(st3,TP);
    if(!sizeof(obs))
        return 0;
    NF("You can't add the candle to that.\n");
    if(MASTER_OB(obs[0]) != KHIRAA_DIR(temple/obj/jack_lamp))
        return 0;
    NF("The "+obs[0]->short()+" already has a candle in it.\n");
    if(obs[0]->query_time())
        return 0;
    write("You add the candle to the "+obs[0]->short()+".\n");
    say(QCTNAME(TP)+" puts a new candle into the "+obs[0]->short()+
    ".\n");
    obs[0]->set_time(1200);
    remove_object();
    return 1;
}

void
init()
{
    ::init();
    add_action(do_light,"light");
    add_action(do_add,"add");
}
