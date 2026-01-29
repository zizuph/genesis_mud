/* -*-C++-*-
 * file name:     /d/Avenir/common/obj/lib/double_punch
 * creator(s):    Lilith    9/17/97
 * purpose:       To provide combat abilities common to all humanoid 
 *                Sybarite NPCS.
 * note:          This file is included by /d/Avenir/common/obj/npc_soul.c
 *
 */
void
do_punch(object me, object victim)
{
    object gloves, wep;
    int success, g, pen, dam, how;
    mixed *hitres, where;
    string str;
    string *randhit = ({"face", "head", "nose", "eye", "chest", "kidney",
                         "abdomen", "chin"});
    if (!objectp(me))
        return;

    if ((!objectp(victim)) || (environment(me) != environment(victim)))
        return;

    wep = check_weapon(me);
    if (wep)
    {
        write("Can't punch wielding weapons!\n");
        return;
    }

    // The enemy has evaded, no attack this round.
    if (victim->query_not_attack_me(me, -1))
      return;

    gloves = check_gloves(me);
    if (gloves)
        str = "fists clad in "+ gloves->query_short();
    else
        str = "bare fists";

    // 66% chance of hit from cb_tohit table.
    if (me->query_combat_object()->cb_tohit(-1, 70, victim) > 0)
    {
        pen = (400 + random(400));

        if (gloves)
        {
    	    g = gloves->query_ac();
            if (g <= 0)
                g = 1 + random(5);
			pen += g * 10;
        }

        pen = pen * F_STR_FACTOR(me->query_average_stat()) / 100;
        hitres = victim->hit_me(pen, W_BLUDGEON, me, -1);
        dam = (sizeof(hitres) ? hitres[0] : -1);
    }

    if (dam <= 0)
    {
        victim->catch_msg("You see "+ QTPNAME(me) +" fists flying toward "+
            "you just in time to evade them.\n");
        me->tell_watcher(QCTNAME(victim) +" evades "+ QTPNAME(me) +" "+
            "flying fists.\n", victim, me);
        return;
    }

    how = random(sizeof(randhit));    
    where = randhit[how];

    victim->catch_msg(QCTNAME(me)+" dodges under your guard "+
        "and gives you a quick double-punch in the " + where +
        " with "+ POSSESS(me) +" "+ str +".\n");
    me->tell_watcher(QCTNAME(me)+" dodges under "+ QTPNAME(victim) + 
        " guard and gives "+ victim->query_objective() +
        " a quick double-punch to the "+ where +"!\n", victim);
    return;       
}

int
double_punch(string str)
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

    do_punch(me, victim);
    return 1;
}

