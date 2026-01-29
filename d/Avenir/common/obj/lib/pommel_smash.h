/* -*-C++-*-
 * file name:     /d/Avenir/common/obj/lib/pommel_smash.h
 * creator(s):    Lilith    9/17/97
 * purpose:       To provide combat abilities common to all humanoid 
 *                Sybarite NPCS.
 * note:          This file is included by /d/Avenir/common/obj/npc_soul.c
 *
 * Last update:	  Lucius, Jan 2009: Runtime fix on non-pointer hitres result.
 *
 */
 
#include <formulas.h>

void
do_pommel(object me, object victim)
{
    object wep;
    int success, c, w, pen, dam, how;
    mixed *hitres, where;
    string str;
    string *randhit = ({"face", "head", "nose", "eye", "chin", "cheek"});

    if (!objectp(me))
        return;

    if ((!objectp(victim)) || (environment(me) != environment(victim)))
        return;


    wep = check_weapon(me);
    /* Must have a weapon in-hand */
    if (!wep)
    {
        write("No weapon, must wield.\n");
        me->command("wield all");
        return;
    }


    // The enemy has evaded, no attack this round.
    if (victim->query_not_attack_me(me, -1))
      return;

    // 66% chance of hit from cb_tohit table.
    if (me->query_combat_object()->cb_tohit(-1, 70, victim) > 0)
    {
        pen = F_PENMOD(wep->query_pen(), me->query_skill(wep->query_wt()));
		pen += (check_weight(wep) / 100);
        pen = pen * F_STR_FACTOR(me->query_average_stat()) / 100;
        hitres = victim->hit_me(pen, W_BLUDGEON, me, -1, A_HEAD);
        dam = (sizeof(hitres) ? hitres[0] : -1);
    }

    if (dam <= 0 )
    {
        victim->catch_msg("You notice "+ QTPNAME(me) +" attempt to step inside "+
            "your guard and prevent "+ OBJECTIVE(me) +" from doing so.\n");
        me->tell_watcher(QCTNAME(victim) +" blocks "+ QTPNAME(me) +" attempt "+
            "to step inside "+ POSSESS(victim) +" guard.\n", victim, me);
        return;
    }

    switch(dam)
    {
        case 1..10:   str = "hits";    break;
        case 11..20:  str = "bangs";   break;
        case 21..30:  str = "slams";   break;
        case 31..40:  str = "bashes";  break;
        default:      str = "smashes"; break;
    } 
    how = random(sizeof(randhit));    
    where = randhit[how];
    victim->catch_msg(QCTNAME(me)+" ducks down and dodges inside your guard, "+
        "then rising and turning swiftly, "+ str +" you in the "+ where +
        " with the pommel of "+ POSSESS(me) +" "+ wep->query_short() +"!\n");
    me->tell_watcher(QCTNAME(me) +" ducks down and dodges inside "+
        QTPNAME(victim) + " guard, then rising and turning swiftly, "+ 
        str +" "+ OBJECTIVE(victim) +" in the "+ where +" with "+
        POSSESS(me) +" "+ wep->query_short() +"!\n", victim, me);
    return;       
}


int
pommel_smash(string str)
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

    do_pommel(me, victim);
    return 1;
}
