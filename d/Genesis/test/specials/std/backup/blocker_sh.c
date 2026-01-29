
#include "defs.h"
inherit "/std/shadow";
inherit ABILITY_DIR+"effect_object";

#include <stdproperties.h>
#include <macros.h>

#define TP            this_player()
#define TO            this_object()
#define QSW           query_shadow_who()
#define POSS(obj)     obj->query_possessive()
#define PRO(obj)      obj->query_pronoun()
#define OBJ(obj)      obj->query_objective()
#define SHORT(obj)    obj->short()

#define BLOCKED_SHADOW (ABILITY_DIR+"std/block_sh")

int Attempt_move=0;

object Blocked;

string Exit;

varargs public int
dispel_ability_effect(object dispeller)
{
    if (objectp(Blocked))
    {
        Blocked->remove_blocker(TO);
    }
    return 1;
}


public object query_blocking()
{
    return Blocked;
    
}

public int query_blocker_moving()
{
    return Attempt_move;
}

public string query_blocker_exit()
{
    return Exit;
}

public varargs int
move_living(string how, mixed to_dest, int dont_follow, int no_glance)
{
    object room=environment(TP);
    
    Attempt_move=1;

    int result=QSW->move_living(how, to_dest, dont_follow, no_glance);

    Attempt_move=0;
    
    if (!result && objectp(Blocked))
    {
        Blocked->remove_blocker(QSW);
    }
    if (!result)
    {
        set_alarm(0.1,0.0,remove_shadow);
    }

    return result;    
}

public int
start()
{

    if (!::start())
    {
        remove_effect_object();
        return 0;
    }
    
    if (!QSW->query_blocking())
    {
        shadow_me(effect_caster);
    }
    else
    {
        QSW->query_blocking()->remove_blocker(QSW);
    }
    
    Exit = effect_target[1];
    
    object target=effect_target[0];
    
    if (!target->query_blocked())
    {
        object shadow=clone_object(BLOCKED_SHADOW);
        shadow->shadow_me(target);
        target=shadow;
    }

    Blocked=target;

    effect_caster->catch_msg("You move to block " + QTNAME(target) + 
    " from the "+Exit+" exit.\n");

    target->catch_msg(QCTNAME(effect_caster)+ " moves to block your "+
    Exit+" escape.\n");

    target->add_blocker(effect_caster);        
        
    return 1;
}
