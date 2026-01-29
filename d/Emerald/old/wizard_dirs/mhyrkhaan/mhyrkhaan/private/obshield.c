inherit "/d/Kalad/std/armour.c";
#include "/d/Kalad/defs.h"


void
create_armour()
{
    ::create_armour();
    set_name("kite-shield");
    set_short("shining obsidian kite-shield");
    add_name("shield");
    set_adj("obsidian");
    add_adj("shining");
    set_long("this sheild must be very powerful indeed, for it seems it should "+
    "weigh a ton, yet is virtually weightless. It is made of solid jet-black "+
    "obsidian. There are runes etched all along the shields outer edge.The "+
    "runes are glowing with a pale green light.\n");
    add_prop(OBJ_I_IS_MAGIC_ARMOUR,1);
    add_prop(MAGIC_AM_ID_INFO,({"You sense that this shield, is forged with and "+
    "ancient power,a power of darkness and despair. Pwer radiated from this shield "+
    "obviously one a true warrior of darkness could benefit from.\n",35}));
    add_prop(OBJ_S_WIZINFO,"This is a magic shield that gives the "+
    "wearer a +25 additive resistance againts magic. It also gives "+
    "extra light.\n");
    add_prop(OBJ_I_RES_FIRE,100);
    add_prop(OBJ_I_RES_ACID,100);
    add_prop(OBJ_I_RES_COLD,100);   
    set_ac(40);
    set_at(A_SHIELD);
    add_prop(OBJ_I_VALUE, 850);
    add_prop(OBJ_I_VOLUME, 1500);
    add_prop(OBJ_I_WEIGHT, 2000);
    set_af(TO);
}

int
wear()
{
    tell_object(TP,"The runes around the shield flare momentarily.\n");
    TP->add_magic_effect(TO);
    return 0;
}

int
remove()
{
    tell_object(query_worn(),"The runes on the shield dim.\n");
    query_worn()->remove_magic_effect(TO);
    return 0;
}

mixed*
query_magic_protection(string prop, object what)
{
    if(prop == MAGIC_I_RES_MAGIC && what == query_worn())
    {
        return ({25,1});
    }
    return ::query_magic_protection(prop,what);
}

