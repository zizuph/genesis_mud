inherit "/std/shadow";
#include "/d/Kalad/common/guilds/khiraa/default.h"
#include "/d/Kalad/common/guilds/khiraa/khiraa.h"
#include "/d/Kalad/common/guilds/khiraa/magic.h"

inherit SPELL_EFFECT_OBJECT;
/* Invisible */

int power;

void
remove_invis_shadow()
{
    shadow_who->add_prop(OBJ_I_INVIS,
        shadow_who->query_prop(OBJ_I_INVIS) - power);

    tell_object(shadow_who,"You fade into view.\n");
    tell_room(E(shadow_who),QCTNAME(TP)+" suddenly fades into view.\n",
    shadow_who);
    shadow_who->remove_magic_effect(TO);
    remove_shadow();
}

int
query_invis_shadow()
{
    return 1;
}

void
set_remove_time(int i)
{
    power = MAX(1,shadow_who->query_guild_order()/6);

    tell_room(E(shadow_who),QCTNAME(shadow_who)+" slowly fades from view.\n",
    shadow_who);
    tell_object(shadow_who,"You slowly fade from view.\n");
    shadow_who->add_prop(OBJ_I_INVIS,
        shadow_who->query_prop(OBJ_I_INVIS) + power);
    set_alarm(itof(i),0.0,&remove_invis_shadow());
}

void
attack_object(object ob)
{
    tell_object(shadow_who,"Your invisibility is disrupted.\n");
    shadow_who->attack_object(ob);
    remove_invis_shadow();
}

void
attacked_by(object ob)
{
    tell_object(shadow_who,"Your invisibility is disrupted.\n");
    shadow_who->attacked_by(ob);
    remove_invis_shadow();
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
    tell_object(shadow_who,"Your invisibility is dispelled by "+
    ob->query_the_name(shadow_who)+"!\n");
    tell_object(ob,"You dispel the invisibility around "+
    shadow_who->query_the_name(ob)+"!\n");
    tell_room(ENV(shadow_who),QCTNAME(ob)+" dispels the invisibility around "+
    QTNAME(shadow_who)+"!\n",({ob,shadow_who}));
    remove_invis_shadow();
    return 1;
}
