/* 
 * /d/Kalad/common/guilds/khiraa/lp/obj/revenant_sh.c
 * Purpose    : Add speed.
 * Located    : Conjured from the spell 'lspeed'.
 * Created By : Sarr 18.Jun.97
 * Modified By: Sarr 9.Jun.98 (recode)
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

    shadow_who->add_prop(LIVE_I_QUICKNESS, 
     shadow_who->query_prop(LIVE_I_QUICKNESS) + 200);

    tell_object(shadow_who,"You suddenly feel the unholy spirits of "+
    "the blade revenant in you, and you go berzerk with crazed power!\n");
    tell_object(shadow_who,"You scream with unholy rage!\n");

    tell_room(E(shadow_who),QCTNAME(shadow_who)+" suddenly screams "+
    "with unholy rage, and goes berzerk!\n",shadow_who);

    set_alarm(itof(i),0.0,&remove_shadow());
    shadow_who->query_combat_object()->cb_calc_speed();
}


void
remove_shadow()
{
    shadow_who->add_prop(LIVE_I_QUICKNESS, 
     shadow_who->query_prop(LIVE_I_QUICKNESS) - 200);
    
    tell_object(shadow_who,"You feel the powers of rage diminish within "+
    "you, and you return to normal.\n");
    tell_room(E(shadow_who),QCTNAME(shadow_who)+" calms down.\n",shadow_who);
    shadow_who->query_combat_object()->cb_calc_speed();
    shadow_who->remove_magic_effect(TO);
    ::remove_shadow();
}

int
query_revenant_shadow()
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
    tell_object(shadow_who,"Your unholy speed is dispeled by "+
    ob->query_the_name(shadow_who)+"!\n");
    tell_object(ob,"You dispel the unholy speed on "+
    shadow_who->query_the_name(ob)+"!\n");
    remove_shadow();    
    return 1;
}

