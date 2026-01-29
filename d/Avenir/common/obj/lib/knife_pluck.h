/* -*-C++-*-
 * file name:     /d/Avenir/common/obj/lib/knife_pluck
 * creator(s):    Lilith    9/17/97
 * purpose:       To provide combat abilities common to all humanoid 
 *                Sybarite NPCS.
 * note:          This file is included by /d/Avenir/common/obj/npc_soul.c
 *
 */

void
do_pluck(object me, object victim)
{
    object wep;
    int success, c, w, pen, dam, how;
    mixed *hitres, where;
    string str1, str2;
    string *randhit = ({"face", "head", "nose", "eye", "chin", "cheek", 
                        "abdomen", "ribs" });

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

    victim->catch_msg(QCTNAME(me)+" tosses "+ POSSESS(me) +" "+  
        "knife into the air!\n");
    me->tell_watcher(QCTNAME(me) +" tosses "+ POSSESS(me) +" "+
        "knife into the air!\n", victim, me);

    // 66% chance of hit from cb_tohit table.
    if (me->query_combat_object()->cb_tohit(-1, 70, victim) > 0)
    {
        pen = F_PENMOD(wep->query_pen(), me->query_skill(wep->query_wt()));
        pen = pen * F_STR_FACTOR(me->query_average_stat()) / 100;
        hitres = victim->hit_me(pen, W_SLASH, me, -1);
        dam = (sizeof(hitres) ? hitres[0] : -1);
    }
	
    switch(dam)
    {
		case 0:
            str1 = "You manage to leap far enough out of the way "+
              "so that the blade just misses";
            str2 = "barely misses";
		    break;
        case 1..15:
        {
            str1 = "You manage to leap far enough out of the way "+
              "so that the blade just grazes";
            str2 = "grazes";
            break;
        }
        case 16..30:  
        {
            str1 = "You leap to the side, but "+ PRONOUN(me) +
                " still manages to slash";
            str2 = "slash";   
            break;
        }
        case 31..45:
        {
            str1 = "You are unable to evade the blade and it badly "+
               "cuts";
            str2 = "badly cuts";
            break;
        }
        default:
        {
	      str1 = "Despite your best efforts, the full length of "+
                "the blade impales";
            str2 = "impales"; 
            break;        
        }
    } 

    /* I can't see, so my attack is less effective */
    if (!CAN_SEE(me, victim))
    {
        victim->catch_msg(QCTNAME(me) +" manages to pluck the knife from the air " +
            "and lunges wildly in your direction. " + str1 + " you!\n");
        me->tell_watcher(QCTNAME(me) + " " + str2 + " " + QTNAME(victim) +
            " with the knife "+ PRONOUN(me) +" plucked from the air!\n", victim);

    }       

    victim->catch_msg(QCTNAME(me) +" plucks the knife from the air " +
        "and lunges toward you. " + str1 + " you!\n");
    me->tell_watcher(QCTNAME(me) + " " + str2 + " " + QTNAME(victim) +
        " with the knife "+ PRONOUN(me) +" plucked from the air!\n", victim);

    if (victim->query_hp() <= 0)
        victim->do_die(me);
    return;       
}
int
knife_pluck(string str)
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

    do_pluck(me, victim);
    return 1;
}
