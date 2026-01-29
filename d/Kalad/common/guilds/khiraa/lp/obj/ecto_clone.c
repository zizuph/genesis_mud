inherit "/d/Kalad/std/monster";
#include "/d/Kalad/defs.h"


string npc_short;
string npc_long;
string npc_met_long;

void
create_monster()
{
    ::create_monster();
    add_name("clone");
    set_long("A wierdo man.\n");
    set_stats(({100,100,100,100,100,100}));
    set_random_move(5);
}

void
set_up_clone(object caster, object original)
{
    int i;
    object *adjs;
    adjs = original->query_adj(1);
    for(i=0;i<sizeof(adjs);i++)
        add_adj(adjs[i]);
    set_name(lower_case(original->query_name()));
    set_race_name(original->query_race_name());
    set_gender(original->query_gender());
    if(interactive(original))
    {
        npc_met_long = original->long(TO);
        original->add_prop(LIVE_I_NEVERKNOWN,1);
        npc_long = original->long(users()[0]);
        original->remove_prop(LIVE_I_NEVERKNOWN);
    }
    else
    {
        npc_met_long = original->query_long();
    }
    set_long("@@mylong@@");
    npc_short = original->query_nonmet_name();
    if(original->query_prop(LIVE_I_NEVERKNOWN))
        add_prop(LIVE_I_NEVERKNOWN,1);
}

string
mylong()
{

    if(stringp(npc_long))
    {
        if(TP->query_met(lower_case( query_name() )) )
            return npc_met_long;
        else
            return npc_long;
    }
    return npc_met_long;
}

varargs string 
short(object ob)
{
    if(!ob)
        ob = this_player();
    if(ob->query_met(lower_case(query_name())))
        return C(query_name());
    return npc_short;
}

string
query_nonmet_name()
{
    return npc_short;
}

void
remove_object()
{
    tell_room(E(TO),"The "+short()+" shatters into a million shards!\n");
    ::remove_object();
}

void
attacked_by(object ob)
{
    remove_object();
}

void
attack_object(object ob)
{
    remove_object();
}

