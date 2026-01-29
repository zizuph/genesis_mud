/*
 * Filters and other miscellaneous functions for use in the Union soul.
 * Cirion, May 1996
 */
private object
has_knife(object who)
{
    object *what = who->query_weapon(-1);
    what = filter(what, &operator(==)(W_KNIFE) @ &->query_wt());

    if (sizeof(what))
	return one_of_list(what);

    return 0;
}

private object
has_sword(object who)
{
    object *what = who->query_weapon(-1);
    what = filter(what, &operator(==)(W_SWORD) @ &->query_wt());

    if (sizeof(what))
	return one_of_list(what);

    return 0;
}

/* Is it a weapon? Is it a knife? */
private int
is_knife(object ob)
{
//    if (!IS_WEAPON_OBJECT(ob)) return 0;
    return (ob->query_wt() == W_KNIFE);
}

/* Is it ok to throw? (needs to be impaling knife) */
private int
valid_knife(object ob, object who)
{
    if (!is_knife(ob))			return 0;
/*
 * Do we really want this?
    if (ob->query_dt() != W_IMPALE)	return 0;
 */
    if (ob->query_wielded())		return 0;
    if (ob->query_prop(OBJ_I_BROKEN))	return 0;
    if (ob->query_prop(OBJ_M_NO_DROP))	return 0;

    return ob->check_seen(who);
}

/* Gets one knife in the players inventory, selecting first
 * from unwielded objects, then from knives in the
 * bandeleria.
 */
private object
get_knife(object who)
{
    object *oblist, band;

    foreach(object item: filter(all_inventory(who), &->id(BAND_ID)))
    {
	if (!item->check_seen(who))
	    continue;

	if (sizeof(oblist = filter(all_inventory(item), &valid_knife(,who))))
	{
	    band = item;
	    break;
	}
    }

    if (!sizeof(oblist) &&
	!sizeof(oblist = filter(all_inventory(TP), &valid_knife(,who))))
    {
	return 0;
    }

    if (!objectp(band))
	return one_of_list(oblist);

    foreach(object ob: oblist)
    {
	if (ob->move(who))
	    continue;

	who->catch_tell("You draw "+ LANG_ASHORT(ob) +" out of your "+
	    band->short() +".\n");
	tell_room(environment(who), QCTNAME(who) +" draws "+
	    LANG_ASHORT(ob) +" out of "+ HIS(who) +" "+
	    band->short( )+".\n", ({ who }), who);

	return ob;
    }
    return 0;
}

/*
 * php returns % of hp left for who
 */
private nomask int
php(object who)
{
    int max = who->query_max_hp();

    if (!max)	return 0;
    return min((who->query_hp() * 100) / max, 100);
}

/*
 * pfat returns % of fatigue who is at
 */
private nomask int
pfat(object who)
{
    int max = who->query_max_fatigue();

    if (!max)	return 0;
    return min(((max - who->query_fatigue()) * 100) / max, 100);
}

/*
 * ppanic returns % of max panic enemy is at. Max panic is assumed to
 * be SS_DIS * 3, since there is no max_panic formula.
 */
private nomask int
ppanic(object who)
{
    int max = who->query_stat(SS_DIS) * 3;

    if (!max)	return 0;
    return min((who->query_panic() * 100) / max, 100);
}
