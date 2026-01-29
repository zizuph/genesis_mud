inherit "/std/armour";
#include "/d/Kalad/defs.h"

int
query_recover()
{
    return 0;
}

void
create_armour()
{
    set_name("cat-claws");
    add_adj("cat");
    add_name("claws");
    set_adj("steel");
    set_short("pair of steel cat-claws");
    set_pshort("pairs of steel cat-claws");
    set_long("You see a pair of steel spiked arm length gloves that "+
    "attach via strong leather straps. The spikes jut out from around "+
    "your hand. They are slightly curved, making climbing surfaces "+
    "a bit easier.\n");
    set_at(A_HANDS);
    set_ac(1);
    set_af(TO);
    add_prop(OBJ_I_WEIGHT,55);
    add_prop(OBJ_I_VOLUME,43);
    add_prop(OBJ_I_VALUE,800);
}

mixed
wear(object what)
{
    set_this_player(E(what));
    TP->set_skill_extra(SS_CLIMB,TP->query_skill_extra(SS_CLIMB)+2);
    return 0;
}

mixed
remove(object what)
{
    set_this_player(E(what));
    TP->set_skill_extra(SS_CLIMB,TP->query_skill_extra(SS_CLIMB)-2);
    return 0;
}

