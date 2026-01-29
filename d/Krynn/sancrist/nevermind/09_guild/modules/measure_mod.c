/********************* module: measure ************************************
 *                     flag:   5                                          *
 **************************************************************************/

string
 [32mmeasure_2(object target, string str) [0m
{
    string sht;
 [32m    if(living(target)) [0m
 [32m        return QTNAME(target) + ".\n"; [0m
 [32m    if(strlen(sht = (target->query_short())) == 0) [0m

        sht = str;
    return "the " + sht + ".\n";
}

int
measure(string str)
{
 [32m    object target, *oblist; [0m
    int toflag = 0;

    NF("You forgot to attach that module.\n");;
    if (!flag(5,0))
        return 0;
    if(!darkcheck(TP))
        return 1;

    NF("Measure what?\n");
    if (!str)
        return 0;
    if (str[0..2] == "to ")
    {
        toflag = 1;
        str = str[3..];
        NF("Measure to what?\n");

    }

    oblist = FIND_STR_IN_OBJECT(str,E(TP));
    if (!oblist || !sizeof(oblist))
        return 0;

    if(flag(5,1) == -1) /* Break test */
        return 1;

 [32m    target = oblist[0]; [0m
    if (!toflag)
    {
        NF("You don't bother with the tape. You know your size.\n");
 [32m        if(target == TP) [0m
            return 0;
 [32m        TP->catch_msg("You get out your convenient measure tape and " [0m
 [32m          + "measure the size of " + measure_2(target, str) [0m
          + "You calculate the volume to be about " +
 [32m          (target->appraise_volume(50 + TP->query_skill(SS_BUILD) / 2)) + [0m
          ".\n");
 [32m        tell_room(E(TP), QCTNAME(TP) + " gets out a " [0m
          + "measure tape and quickly measures the size "
 [32m          + "of " + measure_2(target, str), ({TP,target})); [0m
 [32m        if(living(target)) [0m

 [32m            target->catch_msg(QCTNAME(TP) + " gets out a " [0m
              + "measure tape and quickly measures your size.\n");
        return 1;
    }
    else
    {
        NF("The distance between you and you is zero.\n");
 [32m        if(target == TP) [0m
            return 0;
 [32m        TP->catch_msg("You get out your convenient measure tape and " [0m
 [32m          + "measure the distance to " + measure_2(target, str)); [0m
 [32m        tell_room(E(TP), QCTNAME(TP) + " gets out a " [0m
          + "measure tape and quickly measures the distance between "
 [32m          + OBJECTIVE(TP) + " and " + measure_2(target, str), ({TP, target})); [0m
 [32m        if(living(target)) [0m
 [32m            target->catch_msg(QCTNAME(TP) + " gets out a measure " [0m
              + "tape and quickly measures the distance between you "
              + "and " + OBJECTIVE(TP) + ".\n");
        return 1;
    }
    NF("Measure what?\n");
    return 0;
}


