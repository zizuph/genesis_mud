
/*
 * Function name: panic
 * Description  : It hits a specific hitloc of a specific target,
 *                If the hitloc is unarmoured, it adds panic the target.
 * Arguments    : object who - Object pointer to the player to hit.
 * Returns      : N/A
 */
public void
panic(object who)
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


    who->catch_msg(TO->query_The_name(who) + " reaches for your " +
        desc + "!\n");
    tell_room(environment(TO), QCTNAME(TO) + " reaches out attempting to touch " +
        QTNAME(who) + "'s " + desc + "!\n", ({who, TO}));

  /* If the target wasn't wearing armour, drain some stats. */
    if (!armour)
    {
        who->catch_msg("As the " +TO->query_The_name(who) + "'s hand passes "+
            "through your " + desc + ", you feel as if a fist of ice clenches " +
            "at your heart in a merciless grip. You fight the urge to flee " +
            "for your life!\n");
        tell_room(environment(TO), "As the " + QTNAME(TO) + " touches " +
            QTNAME(who) + "'s " + desc + ", " +
            HE_SHE + " appears visibly upset, as if attempting " + 
            "to maintain " + HIS_HER + " composure.\n",({who,TO}));
        who->add_panic(random(20));
        return;
    }
}