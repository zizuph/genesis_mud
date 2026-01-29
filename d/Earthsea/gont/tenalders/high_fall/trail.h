public int
test_loc()
{
    object tp = this_player();

    if ((tp->query_skill(SS_LOC_SENSE) < 15) &&
      (tp->query_skill(SS_TRACKING) < 15))
    {
        write("You cannot go further without getting lost.\n");
        return 1;
    }

    return 0;
}
