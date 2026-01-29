/* 
 * /d/Kalad/common/guilds/khiraa/lp/obj/shadow_sh.c
 * Purpose    : This is the shadow that is added to the caster from the lich spell 'lshadow'. It improves the defense of the caster, and makes a fake shadow around the caster, making it seem like it is deflecting blows.
 * Located    : Conjured from the spell 'lshadow'.
 * Created By : Sarr 10.Apr.97
 * Modified By: Sarr 18.Jun.98 (rebalance)
 */ 

#pragma save_binary
#pragma strict_types

#include "/d/Kalad/common/guilds/khiraa/khiraa.h"
#include "/d/Kalad/common/guilds/khiraa/default.h"
#include "/d/Kalad/common/guilds/khiraa/magic.h"
#include <ss_types.h>

inherit "/std/shadow";
inherit SPELL_EFFECT_OBJECT;

int skill_lv;

void
set_remove_time(int i)
{
    skill_lv = 30 + random(20);

    if(skill_lv + shadow_who->query_skill(SS_DEFENSE) > 100)
        skill_lv -= (shadow_who->query_skill(SS_DEFENSE) + skill_lv) - 100;

    shadow_who->set_skill_extra(SS_DEFENSE,
        shadow_who->query_skill_extra(SS_DEFENSE) + skill_lv);

    tell_object(shadow_who,"A shadow rises out of the ground and "+
    "surrounds you!\n");

    tell_room(E(shadow_who),"A shadow rises out of the ground and "+
    "surrounds "+QTNAME(shadow_who)+"!\n",shadow_who);

    set_alarm(itof(i),0.0,&remove_shadow());
}


void
remove_shadow()
{

    shadow_who->set_skill_extra(SS_DEFENSE,
        shadow_who->query_skill_extra(SS_DEFENSE) - skill_lv);

    shadow_who->catch_msg("The shadow around you fades away.\n");
    tell_room(E(shadow_who),"The shadow around "+QTNAME(shadow_who)+
    " seems to fade away.\n",shadow_who);
    shadow_who->remove_magic_effect(TO);
    ::remove_shadow();
}

varargs public mixed
hit_me(int wcpen, int dt, object attacker, int attack_id, int hitloc)
{
    if(wcpen < 0)
    {
        tell_object(shadow_who,"The shadow around you seems to deflect the "+
        "blow!\n");
        tell_room(E(shadow_who),"The shadow around "+QTNAME(shadow_who)+
        " seems to deflect the blow!\n",shadow_who);
    }
    return shadow_who->hit_me(wcpen,dt,attacker,attack_id,hitloc);
}

void
start()
{
    ::start();
    shadow_me(spell_target);
}

int
query_shadow_shadow()
{
    return 1;
}

public int
dispel_spell_effect(object ob)
{
    tell_object(shadow_who,"Your shadow defense is dispeled by "+
    ob->query_the_name(shadow_who)+"!\n");
    tell_object(ob,"You dispel the shadow defense around "+
    shadow_who->query_the_name(ob)+"!\n");
    remove_shadow();
    return 1;
}
