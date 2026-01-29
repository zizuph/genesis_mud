/* -*-C++-*-
 * file name:     /d/Avenir/common/obj/lib/stun_kick.h
 * creator(s):    Lilith    9/17/97
 * purpose:       To provide combat abilities common to all humanoid 
 *                Sybarite NPCS.
 * note:          This file is included by /d/Avenir/common/obj/npc_soul.c
 *
 */

#include <formulas.h>

void
do_stun_kick(object me, object victim)
{
    object boots;
    int success, b, c, pen, dam;
    mixed *hitres;

    if (!objectp(me))
        return;

    if ((!objectp(victim)) || (environment(me) != environment(victim)))
        return;

    // The enemy has evaded, no attack this round.
    if (victim->query_not_attack_me(me, -1))
      return;

    // 66% chance of hit from cb_tohit table.
    if (me->query_combat_object()->cb_tohit(-1, 70, victim) > 0)
    {
		// Roughly F_PENMOD(40,100) on average.
        pen = random(500);
        boots = check_boots(me);
        if (boots)
            b = boots->query_ac();
        if (b <= 0)
            b = 1 + random(5);

		pen += b * 5;
        pen = pen * F_STR_FACTOR(me->query_average_stat()) / 100;
        hitres = victim->hit_me(pen, W_BLUDGEON, me, -1, A_HEAD);
        dam = (sizeof(hitres) ? hitres[0] : -1);
    }

    /* Darn! He caught on to me! */
    if (dam <= 0)
    {
        victim->catch_msg("You notice a shift in "+ QTPNAME(me) +" "+
            "center of gravity just in time to dodge "+ POSSESS(me) +
            " attempt to kick your legs out from under you!\n");
        me->tell_watcher(QCTNAME(victim) +" dodges "+ QTPNAME(me) +" "+
            "attempt to kick "+ POSSESS(victim) +" legs out from under "+ 
            OBJECTIVE(victim) +".\n", victim, me);
        return;
    }

    victim->catch_msg(QCTPNAME(me)+" leg moves so quickly it is a "+
       "blur. "+ capitalize(PRONOUN(me)) +" kicks your legs out from "+
       "under you so that you are thrown to the ground!\n");
     me->tell_watcher(QCTNAME(me) +" moves with lightning speed and " + 
       "kicks "+ QTNAME(victim) + " to the ground!\n", victim, me);

    switch(dam)
    {
        case 0..10:
            victim->catch_msg("You roll quickly back to your feet in "+
                "time to meet your opponents next attack.\n");
            me->tell_watcher(QCTNAME(victim)+" rolls quickly back to " + 
                POSSESS(victim) +" feet, apparently unharmed.\n", victim, me);
            break;
        case 11..24:
            victim->catch_msg("You are only slightly injured in the "+
                "fall, but you do feel a bit winded.\n");
            me->tell_watcher(QCTNAME(victim)+" looks a bit winded as "+ 
                PRONOUN(victim) +" staggers back to "+ POSSESS(victim) +
                " feet.\n", victim, me);
            break;
        default:
            if (!victim->query_prop("_live_i_attack_delay"))
                victim->add_attack_delay(dam / 5, 0);
            victim->catch_msg("You land hard on your back, knocking the "+
                "wind from your lungs. Unable to breathe, you cannot fight!\n");
            me->tell_watcher(QCTPNAME(victim)+" face changes colour and "+ 
                PRONOUN(victim) +" gasps futilely for breath as "+ 
                PRONOUN(victim) +" struggles to "+ POSSESS(victim) +
                " knees.\n", victim, me);
            break;
    } 
    return;       
}


int
stun_kick(string str)
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

    do_stun_kick(me, victim);
    return 1;
}

