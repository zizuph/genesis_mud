/* Approx 7.2% of time when mods match and no supermods */
/* Just under 50% of time when mods match and victim cannot see thief */
/* Around 30% of time when thief's mods are 25% better */
 
public int
bonus_thief(object me, object vic, object ob)
{
    int bonus = 0;
    bonus += 200 * vic->query_intoxicated() /
        vic->query_prop(LIVE_I_MAX_INTOX);
    bonus += 15 * vic->query_weight_encumberance() / 10;
    bonus += 3 * me->query_skill(SS_PICK_POCKET);
    bonus += 15 * me->query_stat(SS_DEX) / 10;
    return bonus;
}
 
public int
bonus_victim(object me, object thief, object ob)
{
    bonus += 200 * thief->query_intoxicated() /
        thief->query_prop(LIVE_I_MAX_INTOX);
    bonus += 15 * thief->query_weight_encumberance() / 10;
    bonus += 3 * me->query_skill(SS_AWARENESS);
    bonus += me->query_stat(SS_INT) / 2;
    bonus += 50 * ob->query_prop(OBJ_I_WEIGHT) /
        (me->query_prop(OBJ_I_WEIGHT) - me->query_prop(CONT_I_WEIGHT)) +
        50 * ob->query_prop(OBJ_I_VOLUME) /
        (me->query_prop(OBJ_I_VOLUME) - (me->query_prop(CONT_I_VOLUME));
    return bonus;
}
 
/*
 * The following things are factored with the following weights:
 * Helps the thief:
 *    Victim is drunk, % max drunk * 2
 *    Victim is encumbered, %
 *    Pick Pocket Skill * 3
 *    Dexterity Stat * 1.5
 *
 * Hinders the thief:
 *    Thief is drunk, % max drunk * 2
 *    Thief is encumbered, %
 *    Victim's Awareness * 3
 *    Victim's Int Stat / 2
 *    Percent Weight desired object is of total weight carried / 2
 *    Percent Volume desired object is of total volume carried / 2
 *
 * Total weight of modifiers for each is 8
 *
 * These are major factors, shifting difficulty rather than success %:
 *    Victim cannot see thief   -- 60 % shift down.
 *    Victim is wearing object  -- 100 % shift up.
 *    Victim is wielding object -- 100 % shift up.
 *    Victim is brighter than room - 60 % shift up * levels above
 */
public int
resolve_steal(object vic, object thief, object ob)
{
    int difficulty, tmp;
 
    difficulty = TASK_DIFFICULT;
    if (!CAN_SEE(thief, vic))
        difficulty -= 300;
    tmp = thief->query_prop(OBJ_I_LIGHT) - environment(thief)->query_prop(
        ROOM_I_LIGHT);
    if (tmp > 0)
        difficulty += (tmp * 200);
 
    if (ob->query_wielded())
        difficulty += 400;
    if (ob->query_worn())
        difficulty += 400;
    if (thief->query_attack())
        difficulty += 500;
    if (vic->query_attack())
        difficulty += 500;
 
    return resolve_task(difficulty,
        ({ &bonus_thief(thief, vic, ob) }), vic,
        ({ &bonus_victim(vic, thief, ob) }));
}
