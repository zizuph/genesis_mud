/* -*-C++-*-
 * file name:     /d/Avenir/common/obj/lib/cloak_disarm
 * creator(s):    Lilith    9/17/97
 * purpose:       To provide combat abilities common to all humanoid 
 *                Sybarite NPCS.
 * note:          This file is included by /d/Avenir/common/obj/npc_soul.c
 *
 *          01-15-2002  Goldberry: Added check for seeing in room.
 *          14-Jan-2006 Mercade: Calling unwield() must have an argument.
 */

/* cloak-disarm */
void
do_disarm(object me, object victim)
{   
    object wep, cloak;
    int success;

    if (!objectp(me))
        return;

    if ((!objectp(victim)) || (environment(me) != environment(victim)))
        return;

    /* I can't do this w/o a cloak */
    cloak = check_cloak(me);
    if (!cloak)
    {
        me->command("wear all");
        return;
    }

    /* Enemy doesn't have weapons, don't bother */
    wep = check_weapon(victim);
    if (!wep)
    {
        write("Victim has no weapon wielded.\n");
        return;
    }
    success = me->resolve_task(TASK_SIMPLE, ({TS_DEX, SS_ACROBAT, SS_DEFENCE }),
              victim, ({SS_AWARENESS, SS_ACROBAT}) );
    if (success <= 0 )
    {
        victim->catch_msg(QCTNAME(me) +" tries to snare your "+ wep->short() +
            " in "+ POSSESS(me) +" "+ cloak->short() +", but you succeed "+
            "in evading "+ OBJECTIVE(me) +"\n");
        me->tell_watcher(QCTNAME(victim) +" evades "+ QTPNAME(me) +" attempt "+
            "to ensnare "+ POSSESS(victim) +" "+ wep->short() +
            ".\n", victim, me);
        return;
    }
    if (success < 20 || (check_weight(victim) > (check_weight(me) * 2)))
    {
        victim->catch_msg(QCTNAME(me) +" snares your "+ wep->short() +
            " in "+ POSSESS(me) +" "+ cloak->short() +", but you throw "+
            "yourself backwards, using your weight to pull the "+ 
            wep->short() +" free.\n");
        /* do some damage to the cloak object */
        cloak->set_condition(cloak->query_condition() - 1);
        me->tell_watcher(QCTNAME(victim) +" evades "+ QTPNAME(me) +" attempt "+
            "to ensnare "+ POSSESS(victim) +" "+ wep->short() +".\n", 
            victim, me);
        return;
    }
    
    mixed result = wep->unwield_me();
    if ( (stringp(result)) || (result < 1) )
    { 
        victim->catch_msg(QCTNAME(me) +" tries to snare " +
            "your "+ wep->short() +
            " in "+ POSSESS(me) +" cape, but you manage to keep hold of your "+
            "weapon and yank it free.\n");
        return;
    }

    victim->catch_msg(QCTNAME(me) +" snares your "+ wep->short() +
        " in "+ POSSESS(me) +" "+ cloak->short() +" and gives a "+
        "powerful tug, pulling the "+ wep->short() +" free of "+
        "your grasp.\n");
    me->tell_watcher(QCTNAME(me) +" snares "+ QTPNAME(victim) +" "+ 
        wep->short() +" within the folds of "+ POSSESS(me) +" "+ 
        cloak->short() +" and tugs it free of "+ POSSESS(victim) +
        " grasp.\n", victim, me);
 
    /* Temp prop so you can filter disarm events. */
    me->add_prop("__avenir_cloak_disarm", 1);

    int b = (wep->move(me));
    switch(b)
    {
        case 0:
            break;
 
        case 1:
            /* FALLTHROUGH */
        case 8:
        {
            wep->move(ENV(me));
            victim->catch_msg(QCTNAME(me) +" fumbles and drops your "+ 
                wep->short() +".\n");
            me->tell_watcher(QCTNAME(me) +" fumbles and drops a "+ 
                wep->short() +".\n", victim, me);
        }      
            break;
 
        default:
            break;
    }

    /* Remove temp prop. */
    me->remove_prop("__avenir_cloak_disarm");
}   

int
cloak_disarm(string str)
{
    object me = this_player();
    object *oblist, victim;

    if (!str)
        victim = me->query_attack();
    else
    {
        oblist = parse_this(str, "[the] %l");
        if (sizeof(oblist) >= 1)
            victim = oblist[0];
    }
    
    if (!objectp(victim))
        return 0;

    /* Failed attack checks */
    if (!can_attack(me, victim))
        return 1;

    /* Can we see? */
    if (!(me->can_see_in_room()))
        return 1;

    do_disarm(me, victim);
    return 1;
}

  
