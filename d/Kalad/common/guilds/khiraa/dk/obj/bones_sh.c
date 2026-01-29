/* 
 * /d/Kalad/common/guilds/khiraa/lp/obj/shadow_sh.c
 * Purpose    : This is the shadow that is added to the caster of 'kbones'
 * to fake a defense.
 * Located    : Conjured from the spell 'kbones'.
 * Created By : Sarr 27.Mar.97
 * Modified By: 
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
    skill_lv = 15;
    shadow_who->set_skill_extra(SS_DEFENSE,
        shadow_who->query_skill_extra(SS_DEFENSE) + skill_lv);
    tell_object(shadow_who,"You toss the pile of bones into the air "+
    "and they begin to grow and spin, making a protective barrier around "+
    "you.\n");
    tell_room(E(TO),QCTNAME(shadow_who)+" tosses the pile of bones into "+
    "the air and they begin to grow and spin, making a protective barrier "+
    "around "+HIM(shadow_who)+".\n",shadow_who);
    set_alarm(itof(i),0.0,&remove_shadow());
}


void
remove_shadow()
{

    shadow_who->set_skill_extra(SS_DEFENSE,
        shadow_who->query_skill_extra(SS_DEFENSE) - skill_lv);

    shadow_who->catch_msg("The bones around you vanish!\n");
    tell_room(E(shadow_who),"The bones around "+QTNAME(shadow_who)+
    " vanish!\n",shadow_who);
    ::remove_shadow();
}

public void
start()
{
    shadow_me(spell_target);
}


varargs public mixed
hit_me(int wcpen, int dt, object attacker, int attack_id, int hitloc)
{
    if(wcpen < 0 && random(10) < 8)
    {
        tell_object(shadow_who,"One of the bones around you seems to "+
        "deflect the blow!\n");
        tell_room(E(shadow_who),"One of the bones around "+QTNAME(shadow_who)+
        " seems to deflect the blow!\n",shadow_who);
    }
    return shadow_who->hit_me(wcpen,dt,attacker,attack_id,hitloc);
}

int
query_bones_shadow()
{
    return 1;
}

public int
dispel_spell_effect(object dispeler)
{
    tell_object(dispeler,"You dispel the cage of bones around "+
    shadow_who->query_tha_name(dispeler)+"!\n");
    tell_room(E(dispeler),QCTNAME(dispeler)+" dispels the cage of bones "+
    "around "+QTNAME(shadow_who)+"!\n",({dispeler,shadow_who}));
    remove_shadow();
    return 1;
}
