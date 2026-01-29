/* 
 * /d/Kalad/common/guilds/khiraa/lp/obj/prism_sh.c
 * Purpose    : Create a shield to reduce pen hits by %100, and magic by %50.
 * Located    : Conjured from the spell 'lprism'.
 * Created By : Sarr 19.Jun.97
 * Modified By: Sarr 12.Jun.98
 */ 

#pragma save_binary
#pragma strict_types

#include "/d/Kalad/common/guilds/khiraa/khiraa.h"
#include "/d/Kalad/common/guilds/khiraa/default.h"
#include "/d/Kalad/common/guilds/khiraa/magic.h"
#include <wa_types.h>

inherit "/std/shadow";
inherit SPELL_EFFECT_OBJECT;

void
set_remove_time(int i)
{
    tell_object(shadow_who,"A multi-colored prism forms around you.\n");
    tell_room(E(shadow_who),"A multi-colored prism forms around "+
    QTNAME(shadow_who)+".\n",shadow_who);

    set_alarm(itof(i),0.0,&remove_shadow());
}


void
remove_shadow()
{
    tell_object(shadow_who,"The multi-colored prism around you fades.\n");
    tell_room(E(shadow_who),"The multi-colored prism around "+QTNAME(shadow_who)+
    " fades away.\n",shadow_who);
    shadow_who->remove_magic_effect(TO);
    ::remove_shadow();
}

varargs public mixed
hit_me(int wcpen, int dt, object attacker, int attack_id, int hitloc)
{
    object weapon;
    int amt = 100;
    if(dt != MAGIC_DT )
    {
        weapon = attacker->query_weapon(attack_id);
        if(objectp(weapon) && sizeof(weapon->query_prop(MAGIC_AM_MAGIC)))
            amt -= (amt * weapon->query_prop(MAGIC_AM_MAGIC)[0]) / 100;
        wcpen -= ( wcpen * amt ) / 100;
    }
    return shadow_who->hit_me(wcpen,dt,attacker,attack_id,hitloc);
}

int
query_prism_shield()
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
    tell_object(shadow_who,"Your prism shield is dispeled by "+
    ob->query_the_name(shadow_who)+"!\n");
    tell_object(ob,"You dispel the prism shield around "+
    shadow_who->query_the_name(ob)+"!\n");
    tell_room(ENV(shadow_who),QCTNAME(ob)+" dispels the prism shield "+
    "around "+QTNAME(shadow_who)+"!\n",({ob,shadow_who}));

    remove_shadow();
    return 1;
}
