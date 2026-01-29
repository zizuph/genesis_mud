inherit "/d/Kalad/std/monster";
#include "/d/Kalad/defs.h"
#include "/d/Kalad/common/guilds/khiraa/khiraa_defs.h"
#include <tasks.h>

string npc_short;
string npc_long;
string npc_met_long;
object *illshads = ({});
object gMaster;

void
create_monster()
{
    ::create_monster();
    add_name("clone");
    set_long("A wierdo man.\n");
    set_stats(({60,60,60,50,50,100}));
    set_skill(SS_UNARM_COMBAT,100);
    set_skill(SS_DEFENSE,100);
    add_prop(NPC_I_NO_FEAR,1);
    add_prop(LIVE_I_SEE_DARK,5);
}

string
query_combat_file()
{
    return "/d/Kalad/common/raum/std/chumanoid.c";
}

void
heal_hp(int hp)
{
    ::heal_hp(query_max_hp());
}


void
attack_object(object ob)
{
    object sh;
    int res;
    ::attack_object(ob);
    seteuid(getuid());
    if(ob->illmon_check(TO))
    {
        if(ob->illmon_check(TO) == 2)
            ob->attack_object(gMaster); // Attack creator
        return;
    }
    if(ob->resolve_task(TASK_DIFFICULT, ({SKILL_WEIGHT,80, TS_WIS,    
    SKILL_AVG, SS_FORM_ILLUSION, SS_FORM_ABJURATION, SKILL_END})) > 0)
    {
        tell_object(ob,"You are cleaver enough to see that the "+        
        "creature attacking you is a mere illusion, and are not affected "+
        "by its power! You instead attack the creater of this thing!\n");
        tell_object(gMaster,ob->query_The_name(gMaster)+" is not fooled "+
        "by "+query_the_name(gMaster)+", and attacks you instead!\n");
        ob->attack_object(gMaster);
        res = 1;
    }
    if(ob->query_illmon_shadow())    
    {
        ob->add_to_cobj(TO,res);
        return;
    }
    sh = clone_object("/d/Kalad/common/guilds/khiraa/lp/obj/illmon_shadow");
    sh->shadow_me(ob);
    sh->set_cobj(TO,res);
    illshads += ({ sh });
}

void
attacked_by(object ob)
{
    object sh;
    int res;
    ::attacked_by(ob);
    seteuid(getuid());
    if(ob->illmon_check(TO))   
    {
        if(ob->illmon_check(TO) == 2)
            ob->attack_object(gMaster); // Attack creator
        return;
    }
    if(ob->resolve_task(TASK_DIFFICULT, ({SKILL_WEIGHT,80, TS_WIS,    
    SKILL_AVG, SS_FORM_ILLUSION, SS_FORM_ABJURATION,SKILL_END})) > 0)
    {
        tell_object(ob,"You are cleaver enough to see that the "+        
        "creature attacking you is a mere illusion, and are not affected "+
        "by its power! You instead attack the creater of this thing!\n");
        tell_object(gMaster,ob->query_The_name(gMaster)+" is not fooled "+     
        "by "+query_the_name(gMaster)+", and attacks you instead!\n");
        ob->attack_object(gMaster);
        res = 1;
    }
    if(ob->query_illmon_shadow())    
    {
        ob->add_to_cobj(TO,res);
        return;
    }
    sh = clone_object("/d/Kalad/common/guilds/khiraa/lp/obj/illmon_shadow");
    sh->shadow_me(ob);
    sh->set_cobj(TO,res);
    illshads += ({ sh });
}    

void
destruct_shadows()
{
    int i;
    for(i = 0; i < sizeof(illshads); i++)
    {
        if(objectp(illshads[i]))
            illshads[i]->remove_ill_shadow();
    }
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
set_gmaster(object ob)
{
    gMaster = ob;
}
 
int
check(string slive, string str)
{
    object ob;
    string fix;
    int i;
    i = strlen(str);
    ob = find_player(lower_case(slive));
    fix = extract(str,-i,-3);
    if(ob == gMaster)
        set_alarm(0.1,0.0,&command(fix));
}
string
query_m_out()
{
    return "shambles";
}

