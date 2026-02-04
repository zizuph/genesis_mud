
/*
 * Function name: panic
 * Description  : adds panic the target.
 * Arguments    : object who - Object pointer to the player to hit.
 * Returns      : N/A
 */
public void
panic(object who)
{
    object cob;
    int hloc,
        *hlocarr;
    string desc;

  /* Get the target's hitlocs */
    cob = who->query_combat_object();
    hlocarr = cob->query_hitloc_id();

  /* Pick one of the hitlocs to hit. */
    hloc = hlocarr[random(sizeof(hlocarr))];
    desc = cob->query_hitloc(hloc)[2];

    who->catch_msg(TO->query_The_name(who) + " reaches for your " +
        desc + "!\n");
    tell_room(environment(TO), QCTNAME(TO) + " reaches out attempting to touch " +
        QTNAME(who) + "'s " + desc + "!\n", ({who, TO}));

        who->catch_msg("As " +TO->query_the_name(who) + "'s hand passes "+
            "through your " + desc + ", you feel as if a fist of ice clenches " +
            "at your heart in a merciless grip. You fight the urge to flee " +
            "for your life!\n");
        tell_room(environment(TO), "As the " + QTNAME(TO) + " touches " +
            QTNAME(who) + "'s " + desc + ", " +
            HE_SHE + " appears visibly upset, as if attempting " + 
            "to maintain " + HIS_HER + " composure.\n",({who,TO}));
        who->add_panic(40 + random(20));
        return;
}
