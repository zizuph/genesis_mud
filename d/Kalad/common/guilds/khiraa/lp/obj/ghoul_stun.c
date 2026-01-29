/* 
 * /d/Kalad/common/guilds/khiraa/lp/ghoul_stun.c
 * Purpose    : Stun spell effect for ltouch
 * Located    : Lich spells
 * Created By : Sarr 12.Apr.97
 * Modified By: Fysix, Feb 1998, recoded and balanced
 */ 

#include "../../default.h"
#include "../../magic.h"

inherit "/std/shadow";
inherit SPELL_EFFECT_OBJECT;

void
start()
{
    ::start();
    shadow_me(spell_target);
}

public void
set_remove_time(int time)
{
    shadow_who->add_attack_delay(time, 0);
    set_alarm(itof(time),0.0,&remove_shadow());

    tell_object(shadow_who,"You feel your limbs go numb, and you feel "+
    "yourself stunned!\n");
    tell_room(ENV(shadow_who),QCTNAME(shadow_who)+" suddenly stiffens and "+
    "looks very pale!\n",shadow_who);
}

public int
query_ghoul_stun()
{
    return 1;
}

public void
remove_shadow()
{
    tell_object(shadow_who,"You feel your limbs become lose again, and "+
    "you are able to fight again.\n");
    tell_room(ENV(shadow_who),QCTNAME(shadow_who)+" looks less pale and "+
    "stiff.\n",shadow_who);
    shadow_who->remove_spell_effect(TO);
    ::remove_shadow();
}

public int
dispel_spell_effect(object ob)
{
    tell_object(shadow_who,ob->query_The_name(shadow_who)+
    " dispels the stun curse on you!\n");
    tell_object(ob,"You dispel the stun curse on "+
    shadow_who->query_the_name(ob)+"!\n");

    remove_shadow();
    return 1;
}
