/* 
 * /d/Kalad/common/guilds/khiraa/lp/obj/shadow_sh.c
 * Purpose    : This is the shadow that is added to the caster from the lich spell 'lshadow'. It improves the defense of the caster, and makes a fake shadow around the caster, making it seem like it is deflecting blows.
 * Located    : Conjured from the spell 'lshadow'.
 * Created By : Sarr 10.Apr.97
 * Modified By: 
 */ 

#pragma save_binary
#pragma strict_types

#include "/d/Kalad/common/guilds/khiraa/khiraa.h"
#include "/d/Kalad/common/guilds/khiraa/default.h"
#include "/d/Kalad/common/guilds/khiraa/magic.h"

inherit "/std/shadow";
inherit SPELL_EFFECT_OBJECT;

void
set_remove_time(int i)
{

    tell_object(shadow_who,"You feel a deep weakness within your body, "+
    "and your eyes begin to water.\n");

    tell_room(E(shadow_who),QCTNAME(shadow_who)+" winces lightly and "+
    "looks weaker.\n",shadow_who);

    set_alarm(itof(i),0.0,&remove_shadow());
}


void
remove_shadow()
{
    shadow_who->catch_msg("The terrible sickness in your body seems "+
    "to have left you.\n");
    tell_room(E(shadow_who),QTNAME(shadow_who)+" looks less "+
    "pained.\n",shadow_who);
    shadow_who->remove_magic_effect(TO);
    ::remove_shadow();
}

varargs mixed
hit_me(int wc, int dt, object att, int att_id, int hl = -1)
{
    int temp_dam,dam,x;
    mixed *hr;
    object cll;
    hr = shadow_who->hit_me(wc,dt,att,att_id,hl);
    dam = hr[3];

    if(dam > 0)
    {
        tell_object(shadow_who,"You feel a sharp pain from your "+hr[1]+
        ", and the hit hurt more than normal.\n");
        temp_dam = dam / 2;
        temp_dam -=
        (temp_dam * shadow_who->query_magic_res(MAGIC_I_RES_DEATH)) / 100;
        shadow_who->heal_hp(-temp_dam);
    }
    return hr;
}

int
query_pain_shadow()
{
    return 1;
}

void
start()
{
    ::start();
    shadow_me(spell_target);
}

public int
dispel_spell_effect(object ob)
{
    tell_object(shadow_who,"The pain curse around you is dispelled by "+
    ob->query_the_name(shadow_who)+"!\n");
    tell_object(ob,"You dispel the pain curse around "+
    shadow_who->query_the_name(ob)+"!\n");

    remove_shadow();
    return 1;
}
