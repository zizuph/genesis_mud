/* 
 * /d/Kalad/common/guilds/khiraa/lp/obj/infra_sh.c
 * Purpose    : This is the shadow that allows to see in the dark
 * Located    : Conjured from the spell 'kinfra'.
 * Created By : Sarr 26.May.98
 * Modified By: 
 */ 

#pragma save_binary
#pragma strict_types

#include "/d/Kalad/common/guilds/khiraa/khiraa.h"
#include "/d/Kalad/common/guilds/khiraa/default.h"
#include "/d/Kalad/common/guilds/khiraa/magic.h"

inherit "/std/shadow";
inherit SPELL_EFFECT_OBJECT;

int see_lvl;

void
set_remove_time(int i, int lv)
{
    see_lvl = lv;

    tell_object(shadow_who,"Your eyes glow with a fierce red light, and you "+
    "begin to see things in a blood-red haze.\n");

    shadow_who->add_prop(LIVE_I_SEE_DARK,shadow_who->query_prop(LIVE_I_SEE_DARK) +
        see_lvl);

    set_alarm(itof(i),0.0,&remove_shadow());
}


void
remove_shadow()
{
    shadow_who->add_prop(LIVE_I_SEE_DARK,shadow_who->query_prop(LIVE_I_SEE_DARK) -
        see_lvl);
    tell_object(shadow_who,"Your vision loses its night-seeing capability.\n");
    shadow_who->remove_magic_effect(TO);
    ::remove_shadow();
}

public void
start()
{
    ::start();
    shadow_me(spell_target);
}

int
query_infra_shadow()
{
    return 1;
}

public int
dispel_spell_effect(object ob)
{
    tell_object(shadow_who,"Your night vision is dispeled by "+
    ob->query_the_name(shadow_who)+"!\n");
    tell_object(ob,"You dispel the night vision on "+
    shadow_who->query_the_name(ob)+"!\n");
    remove_shadow();
    return 1;
}
