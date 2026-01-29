/*
 * int query_friend_or_foe(object pl)
 * returns: -1 = goblins, morgul mages, angmarim, vampires, align < -250
 *           0 = others
 *           1 = elves, rangers, paladines, align > 750
 */
varargs int
query_friend_or_foe(mixed pl)
{
    if (stringp(pl))
        pl = find_living(LOW(pl));
    else if (!objectp(pl))
        pl = TP;

    if (!objectp(pl))
        return 0;

    if (M_TIRITH_MASTER->query_enemy(pl->query_real_name(),
        pl->query_race()))
        return -1;
  
    return ::query_friend_or_foe(pl);
}
