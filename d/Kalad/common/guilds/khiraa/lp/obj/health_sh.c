/* 
 * /d/Kalad/common/guilds/khiraa/lp/obj/health_sh.c
 * Purpose    : This is added to 'fake' the health of a person when they 
 *              look at it.
 * Located    : Conjured from the spell 'lhealth'.
 * Created By : Sarr 16.Jun.97
 * Modified By: Sarr 29.Jun.98
 */ 

#pragma save_binary
#pragma strict_types

#include "/d/Kalad/common/guilds/khiraa/khiraa.h"
#include "/d/Kalad/common/guilds/khiraa/default.h"
#include "/d/Kalad/common/guilds/khiraa/magic.h"


inherit "/std/shadow";
inherit SPELL_EFFECT_OBJECT;

int type;

int
query_hp()
{
    /* trick ourself into thinking we are almost dead */
    if(file_name(previous_object()) == "/cmd/live/state")
    {
        if(type == 1)
            return 1;
        else
            return shadow_who->query_max_hp();
    }
    return shadow_who->query_hp();
}

void
remove_health_shadow()
{
    tell_object(shadow_who,"You feel very weird for a moment.\n");
    shadow_who->remove_spell_effect(TO);
    remove_shadow();
}

void
set_remove_time(int i, int a)
{
    type = a;
    set_alarm(itof(i),0.0,&remove_health_shadow());
}

void
start()
{
    ::start();
    shadow_me(spell_target);
}

int
query_health_shadow()
{
    return 1;
}

public int
dispel_spell_effect(object ob)
{
    tell_object(shadow_who,"The illusion around you is dispelled!\n");
    tell_object(ob,"You dispel the illusion around "+
    shadow_who->query_the_name(ob)+"!\n");
    tell_room(ENV(shadow_who),"The illusion around "+QTNAME(shadow_who)+
    " is dispelled by "+QTNAME(ob)+"!\n",({shadow_who,ob}));
    remove_health_shadow();
    return 1;
}
