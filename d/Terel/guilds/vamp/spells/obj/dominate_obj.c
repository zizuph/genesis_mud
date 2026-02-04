
#include "../../guild.h"

inherit "/std/shadow";
inherit SPELLOBJ_DIR+"spell_obj";

#include <stdproperties.h>
#include <macros.h>
#include <language.h>

#define DOMINATE_SUBLOC   "dominuate_subloc"

int Dlevel;

varargs public int
dispel_spell_effect(object dispeller)
{

    if (effect_caster)
    {
        effect_caster->catch_msg("Your mental link to "+
            QTNAME(effect_target) + " is severed.\n");
        effect_caster->remove_dominated(TO);
    }
    
    QSW->remove_subloc(DOMINATE_SUBLOC);
    remove_shadow();
    remove_spell_effect_object();
    
    return 1;
}


public string show_subloc(string subloc,  object on, object for_obj)
{
    if (subloc==DOMINATE_SUBLOC && 
        !QSW->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS) &&
        IS_VAMP(for_obj))
    {
        return
        ( for_obj==QSW ? "You are " : capitalize(PRO(QSW)) + " is " ) +
        "being mentally dominated by " + 
        (effect_caster==for_obj ? "you" : 
                effect_caster->query_the_name(for_obj))+ 
        ".\n";
    }

    return QSW->show_subloc(subloc,on,for_obj);
}


public object query_dominated()
{
    return effect_caster;
}

public int
start()
{
    set_spell_effect_desc("dominate");
    set_spell_effect_name("dominate");

    if (!::start() || !shadow_me(effect_target))
    {
        remove_spell_effect_object();
        return 0;
    }

    int delay=max(240,effect_caster->query_vamp_stat()*40);

    delay=min(10800,delay);

    effect_caster->catch_msg(
    "Your press your thoughts into the mind of " + QTNAME(effect_target) +
    ", pushing back " + POSS(effect_target) + " instincts and rational "+
    "thought and allowing you to compel " + OBJ(effect_target) + " to do "+
    "your bidding.\n");
    
    effect_target->catch_msg("You feel compelled to obey the commands "+
    "of "+QTNAME(effect_caster)+".\n");

    set_dispel_time(delay);

    QSW->add_subloc(DOMINATE_SUBLOC,TO);
    
    effect_caster->add_dominated(TO);

    return 1;
}

public void notify_seen(object player)
{
    if (objectp(effect_caster) && 
        environment(effect_caster)!=environment(QSW))
    {
        string desc=player->query_race_name();
        if (QSW->query_humanoid())
        {
            desc=one_of_list(player->query_adj(1)[..1])+" "+desc;
        }
        desc=LANG_ADDART(desc);
        effect_caster->catch_msg("Through your link with " +
        QTNAME(QSW) + " you can sense the presence of " + desc +
        ".\n");
    }
}

public void do_die(object killer)
{
    if (effect_caster)
    {
        if (environment(QSW)!=environment(effect_caster))
        {
            effect_caster->catch_msg("As "+QTNAME(QSW)+" dies, the "+
            "intensity of "+POSS(QSW)+" fear causes you mental "+
            "strain.\n");
            effect_caster->add_mana(-10);
        }
        else
        {
            effect_caster->catch_msg("As "+QTNAME(QSW)+" dies, you press "+
                "peaceful thoughts into "+POSS(QSW)+" mind, leaving "+ 
                OBJ(QSW) + " calm in death.\n");
        }
        effect_caster->remove_dominated(TO);
    }    
    QSW->do_die(killer);
}

public void init_living()
{
    QSW->init_living();
    if (TP!=effect_caster && objectp(effect_caster) && 
        TP->check_seen(QSW) && interactive(TP))
    {
        set_alarm(3.0,0.0,&notify_seen(TP));
    }
}

