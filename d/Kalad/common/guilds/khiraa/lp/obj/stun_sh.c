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
    shadow_who->add_attack_delay(i,0);
    set_alarm(itof(i),0.0,"remove_shadow");
}


void
remove_shadow()
{
    tell_room(E(shadow_who),QCTNAME(shadow_who)+" suddenly looks less "+
    "pale.\n",shadow_who);

    tell_object(shadow_who,"You feel the coldness leave your body.\n");

    ::remove_shadow();
}

int
query_stun_shadow()
{
    return 1;
}

void
start()
{
    shadow_me(spell_target);
}

