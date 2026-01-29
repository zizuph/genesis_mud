/*
 * Function name: drain
 * Description  : Two effects. It hits a specific hitloc of a specific target,
 *                if the hitloc is armoured, it corrodes the armour and breaks
 *                it. If the hitloc is unarmoured, it drains the target's
 *                stats.
 * Arguments    : object who - Object pointer to the player to hit.
 * Returns      : N/A
 */
public void
drain(object who)
{
    object armour,
           cob;
    int hloc,
        *hlocarr;
    string desc;

  /* Get the target's hitlocs */
    cob = who->query_combat_object();
    hlocarr = cob->query_hitloc_id();

  /* Pick one of the hitlocs to hit. */
    hloc = hlocarr[random(sizeof(hlocarr))];
    desc = cob->query_hitloc(hloc)[2];

  /* Get the armour worn on selected hitloc, if any. */
    armour = who->query_armour(hloc);

    who->catch_msg(TO->query_The_name(who) + " extends a bony hand towards your " +
        desc + "!\n");
    tell_room(environment(TO), QCTNAME(TO) + " extends a bony hand towards " +
        QTNAME(who) + "'s " + desc + "!\n", ({who, TO}));

  /* If the target wasn't wearing armour, drain some stats. */
    if (!armour)
    {
        who->catch_msg("As " + TO->query_The_name(who) + "'s hand brushes "+
            "against your " + desc + ", you feel a numb chill spread " +
            "outwards from it, as if draining your very soul away!\n");
        tell_room(environment(TO), "As " + QTNAME(TO) + "'s hand brushes " +
            "against " + QTNAME(who) + "'s " + desc + ", " +
            HE_SHE(who) + " shivers visibly, " + HIS_HER(who) + 
            " shoulders slumping as if weakened.\n",({who,TO}));
        who->add_tmp_stat(SS_STR, -20, 30);
	who->add_tmp_stat(SS_DEX, -20, 30);
	who->add_tmp_stat(SS_CON, -20, 30);
	who->add_tmp_stat(SS_INT, -20, 30);
        who->add_tmp_stat(SS_WIS, -20, 30);
	who->add_tmp_stat(SS_DIS, -20, 30);
        return;
    }

  /* If the target was wearing armour, kiss it goodbye! */
    who->catch_msg("As " + TO->query_the_name(who) + "'s hand brushes against " +
        "the " + armour->short() + " covering your " + desc + ", it begins " +
        "to corrode rapidly, as if whatever held it together was being " +
        "sucked out of it by her touch!\n");
    tell_room(environment(TO), "As " + QTNAME(TO) + "'s hand brushes " +
        "against the " + armour->short() + " covering " + QTNAME(who) +
        "'s " + desc + ", it begins to corrode rapidly, as if " +
        "whatever held it together was being sucked out of it " +
        "by her touch!\n", ({who, TO}));
    armour->remove_broken();
    who->update_armour(armour);
}