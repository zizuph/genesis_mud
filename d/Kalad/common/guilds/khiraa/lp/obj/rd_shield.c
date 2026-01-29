/*
 * Sarr 1.Jul.98
 * Resist death magic shield
 */

#include "/d/Kalad/common/guilds/khiraa/khiraa.h"
#include "/d/Kalad/common/guilds/khiraa/default.h"
#include "/d/Kalad/common/guilds/khiraa/magic.h"

inherit "/std/shadow";
inherit SPELL_EFFECT_OBJECT;

int power = 1;
int power2 = 1;

public void
set_remove_time(int time)
{
    power = 30 + random(21);
    power2 = 10 + random(21);
    tell_object(shadow_who,"A faint purple-tinted mist suddenly "+
    "appears around you.\n");
    tell_room(ENV(shadow_who),"A faint purple-tinted mist suddenly "+
    "appears around "+QTNAME(shadow_who)+"!\n",shadow_who);
    set_alarm(itof(time),0.0,&remove_shadow());
}

public void
remove_shadow()
{
    tell_object(shadow_who,"You feel the death magic shield around you fade.\n");
    tell_room(ENV(shadow_who),"The faint purple-tinted mist around "+
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
    if(what == shadow_who && prop == MAGIC_I_RES_DEATH)
        return ({power,0});
    if(what == shadow_who && prop == MAGIC_I_RES_MAGIC)
        return ({power2,0});
}

public int
dispel_spell_effect(object ob)
{
    tell_object(shadow_who,"The death magic shield around you is dispelled "+
    "by "+ob->query_the_name(shadow_who)+"!\n");
    tell_object(ob,"You dispel the death magic shield around "+
    shadow_who->query_the_name(ob)+"!\n");
    remove_shadow();
    return 1;
}

int
query_resdeath_shadow()
{
    return 1;
}

