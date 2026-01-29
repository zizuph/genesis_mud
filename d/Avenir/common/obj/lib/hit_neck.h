/* -*-C++-*-
 * file name:     /d/Avenir/common/obj/lib/hit_neck
 * creator(s):    Lilith    9/17/97
 * purpose:       To provide combat abilities common to all humanoid 
 *                Sybarite NPCS.
 * note:          This file is included by /d/Avenir/common/obj/npc_soul.c
 *
 */
void
do_hit_neck(object me, object victim)
{
    object wep;
    int success, w, pen, dam;
    mixed *hitres;
    string str;

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

    victim->catch_msg(QCTNAME(me)+" raises "+ POSSESS(me) +" "+  
        wep->query_short() +" high and swings it toward your head!\n");
    me->tell_watcher(QCTNAME(me) +" raises "+ POSSESS(me) +" "+
        wep->query_short() +" high and swings it toward "+ QTPNAME(victim)+
        " head!\n", victim, me);

    // 66% chance of hit from cb_tohit table.
    if (me->query_combat_object()->cb_tohit(-1, 70, victim) > 0)
    {
        pen = F_PENMOD(wep->query_pen(), me->query_skill(wep->query_wt()));
		pen += (check_weight(wep) / 100);
        pen = pen * F_STR_FACTOR(me->query_average_stat()) / 100;
        hitres = victim->hit_me(pen, W_BLUDGEON, me, -1, A_HEAD);
        dam = (sizeof(hitres) ? hitres[0] : -1);
    }

    if (dam < 1)
    {     
        victim->catch_msg(QCTPNAME(me)+" "+ wep->query_short() +" whistles "+
            "past your neck with a scant hairsbreadth to spare!\n");               
        me->tell_watcher(QCTPNAME(me) +" "+ wep->query_short() +" whistles "+
            "past "+ QTPNAME(victim) +" neck with a scant hairs breadth "+
            "to spare!\n", victim, me);
        return;
    }
    switch(dam)
    {
        case 1..10: 
        {   
            if (wep->query_dt() == W_BLUDGEON)
                str = "just scrapes"; 
            else        
                str = "just grazes";  
            break;
        }
        case 11..20:
        {
            if (wep->query_dt() == W_BLUDGEON)
                str = "thumps into";
            else
                str = "slices into";  
            break;
        }
        case 21..30:
        {
            if (wep->query_dt() == W_BLUDGEON)
                str = "bangs into";
            else
                str = "slices deeply into";  
            break;
        }
        case 31..40:
        {
            if (wep->query_dt() == W_BLUDGEON)
                str = "bashes into";
            else
                str = "cuts deeply into";  
            break;
        }
        default:
        {
            if (wep->query_dt() == W_BLUDGEON)
                str = "smashes into";
            else
                str = "cleaves deeply into";  
        }
        break;
    } 
    victim->catch_msg(QCTPNAME(me)+" "+ wep->query_short() +" "+ str +
        " your neck!\n");               
    me->tell_watcher(QCTPNAME(me) +" "+ wep->query_short() +" "+ str +
        " "+ QTPNAME(victim) +" neck!\n", victim, me);
}


int
hit_neck(string str)
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

    do_hit_neck(me, victim);
    return 1;
}

