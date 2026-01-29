
/* -*-C++-*-
 * file name:     /d/Avenir/common/obj/lib/dej_smash
 * creator(s):    Lilith    9/17/97
 * purpose:       To provide combat abilities common to all humanoid 
 *                Sybarite NPCS.
 * note:          This file is included by /d/Avenir/common/obj/npc_soul.c
 *                This attack causes some mana loss on the player:
 *                -50 + random(40)
 *
 */

void
do_smash(object me, object victim)
{
    object wep;
    int success, c, w, pen, dam, rhit;
    mixed *hitres, where;
    string how;
    string *randhit = ({"face", "nose", "chin", "cheek", "shoulder",
                        "upper arm", "forearm", "abdomen", "stomach", 
                        "chest", "back", "rib" });

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
        // Increased from random(1500) due to 30% chance of miss.
        pen = (700 + random(700))*F_STR_FACTOR(me->query_average_stat()) / 100;
        hitres = victim->hit_me(pen, W_BLUDGEON, me, -1);
        dam = (sizeof(hitres) ? hitres[0] : -1);
    }

    victim->catch_msg(QCTNAME(me)+" stomps on your foot and swings "+ 
        POSSESS(me) +" arm around with great force!\n");
    me->tell_watcher(QCTNAME(me) +" swings "+ POSSESS(me) +" "+  
        "arm around with great force!\n", victim, me);

    rhit = random(sizeof(randhit));    
    where = randhit[rhit];

    if (dam <= 0)
	{
      victim->catch_msg(QCTPNAME(me)+" elbow barely missing your " + where +
        ".\n");
      me->tell_watcher(QCTPNAME(me)+" elbow barely missing "+ QTPNAME(victim) + 
        " " + where + ".\n", victim);
	  return;
	}

    switch(dam)
    {
        case 1..7:
        {
            how = "bumping";
            break;
        }
        case 8..12:  
        {
            how = "grazing";   
            break;
        }
        case 13..25:
        {
            how = "hurting";
            break;
        }
        case 26..40:
        {
            how = "bashing";
            break;
        }
        case 41..60:
        {
            how = "smashing";
            break;
        }
        case 61..1600:
        {
            how = "crushing";
            break;
        }  
        default:
        {
            how = "bumping"; 
            break;        
        }
    } 

    victim->catch_msg(QCTPNAME(me)+" elbow connects with your " + where +
        ", "+ how +" it.\n");
    victim->add_mana(-50 +random(40));
    me->tell_watcher(QCTPNAME(me)+" elbow connects with "+ QTPNAME(victim) + 
        " "+ where +", "+ how +" it!\n", victim);

    return;       
}

int
dej_smash(string str)
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

    do_smash(me, victim);
    return 1;
}


