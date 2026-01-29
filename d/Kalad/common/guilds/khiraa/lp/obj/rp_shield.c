/*
 * Sarr 1.Jul.98
 * Resist poison shield
 */

#include "/d/Kalad/common/guilds/khiraa/khiraa.h"
#include "/d/Kalad/common/guilds/khiraa/default.h"
#include "/d/Kalad/common/guilds/khiraa/magic.h"

inherit "/std/shadow";
inherit SPELL_EFFECT_OBJECT;

int power = 1;

public void
set_remove_time(int time)
{
    power = 50 + random(21);
    tell_object(shadow_who,"A faint green-tinted mist suddenly "+
    "appears around you.\n");
    tell_room(ENV(shadow_who),"A faint green-tinted mist suddenly "+
    "appears around "+QTNAME(shadow_who)+"!\n",shadow_who);
    set_alarm(itof(time),0.0,&remove_shadow());
}

public void
remove_shadow()
{
    tell_object(shadow_who,"You feel the poison shield around you fade.\n");
    tell_room(ENV(shadow_who),"The faint green-tinted mist around "+
    QTNAME(shadow_who)+" fades away.\n",shadow_who);

    shadow_who->remove_magic_effect(TO);
    ::remove_shadow();
}

public void
start()
{
    ::start();
    shadow_me(spell_target);
}

mixed
query_magic_protection(string prop, object what)
{
    if(what == shadow_who && prop == MAGIC_I_RES_POISON)
        return ({power,0});
}

public int
dispel_spell_effect(object ob)
{
    tell_object(shadow_who,"The poison shield around you is dispelled "+
    "by "+ob->query_the_name(shadow_who)+"!\n");
    tell_object(ob,"You dispel the poison shield around "+
    shadow_who->query_the_name(ob)+"!\n");
    remove_shadow();
    return 1;
}

int
query_respoi_shadow()
{
    return 1;
}

