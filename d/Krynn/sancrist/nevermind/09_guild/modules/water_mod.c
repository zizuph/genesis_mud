/******************************* module: water dispenser ******************
 *                                 flag: 2
 **************************************************************************/

void
do_refresh(object player, int amount)
{
    if ((player->query_fatigue()) > ((player->query_max_fatigue()) - amount))
        player->set_fatigue(player->query_max_fatigue());
    else
        player->add_fatigue(amount);

}

int
refresh(string str)
{
    int number;
 [32m    object target, *oblist; [0m

    NF("You forgot to attach that module.\n");;
    if (!flag(2,0))
        return 0;

    if(!darkcheck(TP))
        return 1;

    NF("You don't have much water left.\n");
    if(!find_gizmo(TP)->check_water())
        return 0;

    NF("Refresh whom?\n");
    if (!str)
        return 0;
    if(flag(2,1) == -1)
        return 1;


    write("You release a splash of water ");
    tell_room(E(TP), "A splash of water spurts forth out of " + QTNAME(TP)
      + "'s gizmo", TP);
    find_gizmo(TP)->reduce_water();

    str = lower_case(str);
    number = random(5);
    if (str == "me" || str == "myself" || str == lower_case(TP->query_name()))
    {
        if ((TP->query_stat(1)) >= (random(40) + 10) && number)
        {
            write("and skillfully catch it with your mouth.\n");
 [33m            say(", which " + PRONOUN(TP) + " skillfully directs into " [0m
              + POSSESSIVE(TP) + " mouth.\n");
            do_refresh(TP, 20);
        }
        else
        {
 [32m            write("which misses your mouth but hits your nose!\nYou feel [0m
refreshed "
              + "though.\n");
 [33m            say(" and hits " + OBJECTIVE(TP) + "self in the face.\n"); [0m
            do_refresh(TP, 40);
        }

        return 1;
    }

    if(!number)
    {     
        write("but somehow manage to miss your mouth and hit your nose!\n"
 [32m          + "You feel quite refreshed.\n"); [0m
 [33m        say(" aims carefully at " + POSSESSIVE(TP) + " mouth but hits "  [0m
          + "the nose.\n");
        TP->command("$oops");
        do_refresh(TP, 40);       
        return 1;              
    }

 [32m    target = present(str, E(TP)); [0m
 [32m    if (!target) [0m
    {
 [32m        write("but cannot find your target.\n"); [0m
 [33m        say(".\n"); [0m
        return 1;
    }

 [32m    if (!living(target)) [0m
    {

 [32m        write("and soak the " + target->short() + ".\n"); [0m
 [32m        say(" soaking the " + target->short() + ".\n"); [0m
        return 1;
    }

 [32m    oblist = ({target, TP}); [0m
 [32m    if ((target->query_stat(1)) >= (random(140) + 20)) [0m
    {
 [32m        TP->catch_msg("and refresh " + QTNAME(target) + ".\n"); [0m
 [32m        tell_room(E(target), " which " + target->query_the_name(target) + " [0m
skillfully "
 [32m          + "catches with " + POSSESSIVE(target) + " mouth.\n" [0m
          ,oblist);
 [32m        target->catch_msg(" which you skillfully catch with your mouth.\n" [0m
 [32m          + "You feel refreshed.\n"); [0m
 [32m        do_refresh(target, 20); [0m
        return 1;
    }
 [32m    TP->catch_msg("and shower " + QTNAME(target) + ".\n"); [0m
 [32m    tell_room(E(TP), " hitting " + QTNAME(target) + " between the eyes.\n" [0m
      ,oblist);
 [32m    target->catch_msg(" hitting you between the eyes!\nYou feel very [0m
refreshed.\n");
 [32m    do_refresh(target, 40); [0m
    return 1;
}

