inherit "/d/Kalad/common/raum/std/undead_std";
inherit "/std/combat/unarmed.c";

#include <tasks.h>
#include "/d/Kalad/common/guilds/khiraa/khiraa.h"
#include "/d/Kalad/common/guilds/khiraa/default.h"
#include <ss_types.h>
#include <wa_types.h>
#include <formulas.h>

string npc_short;
string npc_long;
string npc_met_long;
object *illshads = ({});
object gMaster;

public void
setup_illusion(object caster)
{
    int i;
    object *adjs;
    adjs = caster->query_adj(1);

    set_skill(SS_UNARM_COMBAT,caster->query_skill(SS_ELEMENT_DEATH));
    set_skill(SS_DEFENSE,caster->query_skill(SS_FORM_CONJURATION));
    gMaster = caster;            

    for(i=0;i<sizeof(adjs);i++)
        add_adj(adjs[i]);
    set_name(lower_case(caster->query_name()));
    set_race_name(caster->query_race_name());
    set_gender(caster->query_gender());
    if(interactive(caster))
    {
        npc_met_long = caster->long(TO);
        caster->add_prop(LIVE_I_NEVERKNOWN,1);
        npc_long = caster->long(users()[0]);
        caster->remove_prop(LIVE_I_NEVERKNOWN);
    }
    else
    {
        npc_met_long = caster->query_long();
    }
    set_long("@@mylong@@");
    npc_short = caster->query_nonmet_name();
    if(caster->query_prop(LIVE_I_NEVERKNOWN))
        add_prop(LIVE_I_NEVERKNOWN,1);

}

void
create_monster()
{
    ::create_monster();

    set_stats(({125,125,140,150,120,100}));
    add_prop(LIVE_I_NO_CORPSE,1);
    set_alignment(-1200);
    set_knight_prestige(900);
    add_prop(LIVE_I_NEVERKNOWN,1);
    add_prop(LIVE_I_SEE_DARK,5);
    set_cact_time(5);
    add_cact("emote laughs eerily.");

    set_all_hitloc_unarmed(60);
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
            if(present(ob,ENV(gMaster)))
                ob->attack_object(gMaster); // Attack creator
        return;
    }
    if( (LP_DIR+"obj/lp_med")->spell_resist_illusion(gMaster,ob,
          SS_ELEMENT_DEATH, TASK_DIFFICULT) > 0)
    {
        tell_object(ob,"You are cleaver enough to see that the "+        
        "creature attacking you is a mere illusion, and are not affected "+
        "by its power!\n");

        if(present(ob,ENV(gMaster)))
        {
            tell_object(gMaster,ob->query_The_name(gMaster)+" is not fooled "+
            "by "+query_the_name(gMaster)+", and attacks you instead!\n");
            ob->attack_object(gMaster);
            res = 1;
        }
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
            if(present(ob,ENV(gMaster)))
                ob->attack_object(gMaster); // Attack creator
        return;
    }
    if( (LP_DIR+"obj/lp_med")->spell_resist_illusion(gMaster,ob,
          SS_ELEMENT_DEATH, TASK_DIFFICULT) > 0)
    {
        tell_object(ob,"You are cleaver enough to see that the "+        
        "creature attacking you is a mere illusion, and are not affected "+
        "by its power!\n");
        if(present(ob,ENV(gMaster)))
        {
            tell_object(gMaster,ob->query_The_name(gMaster)+" is not fooled "+
            "by "+query_the_name(gMaster)+", and attacks you instead!\n");
            ob->attack_object(gMaster);
            res = 1;
        }
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
remove_object()
{
    destruct_shadows();
    ::remove_object();
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

int
cr_try_hit(int aid)
{
    object enemy;
    int power, phurt, *locs, where;
    string desc;

    if(enemy->illmon_check(TO) == 2)
        return 0;

    if(random(100) > 80)
        return 0;

    enemy = query_attack();
    power = F_PENMOD(gMaster->query_stat(SS_INT) / 2, 
             gMaster->query_skill(SS_FORM_ILLUSION) );
    power = random(power);
    if(power <= 0)
        power = -1;
    enemy->heal_vhp(-power);

    if(enemy->query_vhp() > 0)
        phurt = (power * 100) / enemy->query_vhp();
    else
        phurt = 1;

    locs = enemy->query_combat_object()->query_hitloc_id();
    where = locs[random(sizeof(locs))];

    desc = enemy->query_combat_object()->query_hitloc(where)[2];
    query_combat_object()->cb_did_hit(aid, desc, phurt,
        enemy, power, power);

    return 0;    
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
        return CAP(query_name());
    return npc_short;
}
