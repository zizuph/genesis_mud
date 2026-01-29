/********************** module: Steam engine ******************************
 *                        flag: 3                                         *
 **************************************************************************/

int
check(string str)

{
    int res;

    if(str == "distillationapparatus" || str == "Distillationapparatus" ||
      str == "DistillationApparatus")
    {
        if (!darkcheck(TP))
            return 1;
        NF("You forgot to attach that module.\n");;
        if(!(flag(12,0)))
            return 0;
        write("The CentralCavityContainingLiquidsToBeDistilled is ");
        res = QUERY_LIQUID(TP);
        if(res == 3000) write("full.\n");
        if(res > 2300 && res != 3000) write("well filled.\n"); 
        if(res > 1500 && res <= 2300) write("about half full.\n"); 
        if(res > 700 && res <= 1500) write("not yet half full.\n"); 
        if(res > 10 && res <= 700) write("quite empty.\n"); 
        if(res <= 10) write("empty.\n"); 
        return 1;
    }

    if(str == "water" || str == "flour")
    {

        if (!darkcheck(TP))
            return 1;
        NF("You forgot to attach that module.\n");;
        if(str == "water")
        {
            if(!(flag(2,0)))
                return 0;
            write("The tank inside the dispenser is ");
            res = (find_gizmo(TP)->check_water());
        }
        else
        {
            if(!(flag(10,0)))
                return 0;
            write("The storage room for flour is ");
            res = (find_gizmo(TP)->check_flour());
        }
        allbb(" checks something in " + POSSESSIVE(TP)
          + " gizmo.");
        if(res == 40) write("full.\n");
        if(res > 31 && res != 40)write("nearly full.\n");
        if(res > 23 && res < 32) write("well filled.\n");
        if(res > 15 && res < 24) write("about half full.\n");
        if(res > 7  && res < 16) write("quite empty.\n");

        if(res < 8  && res) write("nearly empty.\n");
        if(!res) write ("empty.\n");
        return 1;
    }
    NF("Check what?\n");
    if(str != "engine" && str != "steamengine" && str != "wood")
        return 0;

    NF("You forgot to attach that module.\n");;
    if(!(flag(3,0)))
        return 0;
    if (!darkcheck(TP))
        return 1;

    if(str == "wood")
    {
        write("The storage chamber for wood inside the engine is ");
        allbb(" checks something in " + POSSESSIVE(TP)
          + " gizmo.");
        res = (find_gizmo(TP)->check_wood());
        if(res ==14) write("full.\n");
        if(res > 9 && res != 14)write("nearly full.\n");
        if(res > 3 && res <  10) write("about half full.\n");
        if(res < 4 && res) write("nearly empty.\n");
        if(!res) write ("empty.\n");
        return 1;
    }
    write("You check the steamengine:\n");
    allbb(" checks something in " + POSSESSIVE(TP)
      + " gizmo.");
    if(find_gizmo(TP)->check_fire())
        write("The fire is burning.\n");
    else
    {
        write("The engine is switched off.\n");
        return 1;
    }
    if(find_gizmo(TP)->check_steam())
        write("Pressure of the steam is ok.\n");
    else write("There is not enough pressure yet.\n");
    return 1;
}

int
engulf(string str)
{
 [32m    object target, *oblist; [0m
    string result;


    if (!darkcheck(TP))
        return 1;
    result = steamengine_check(TP);
    if(result != "ok")
    {
        write(result);
        return 1;
    }

 [32m    write("You open a valve at the engine and release a cloud of steam"); [0m
 [33m    say(QCTNAME(TP) + " does something to " + POSSESSIVE(TP) + " gizmo " [0m
      + "and releases a cloud of steam");
    find_gizmo(TP)->reduce_water();

    if((random (10) < 2) || (str == "me") || (str == "myself") || (C(str) ==
TP->query_name()))
    {
        write(" completely engulfing yourself.\n");
 [33m        say(" which engulfs " + OBJECTIVE(TP) + " completely. " [0m
          + C(PRONOUN(TP)) + " is invisible for a second.\n");
        TP->command("$cough");
        return 1;
    }

 [32m    if (!(target = P(str, E(TP)))) [0m
    {
 [32m        write(" but cannot find your target.\n"); [0m
 [33m        say(".\n"); [0m
        return 1;
    }    

 [32m    if (!living(target)) [0m
    {
 [32m        tell_room(E(TP)," engulfing the " + target->query_adj() + " " [0m
 [32m          + target->query_name() + ".\n"); [0m
        return 1;
    }

 [32m    oblist = ({target, TP}); [0m
 [32m    if ((target->query_stat(1)) >= (random(80) - 20)) [0m
    {
 [32m        TP->catch_msg(" but miss " + QTNAME(target) + ".\n"); [0m
 [32m        tell_room(E(TP), " which closely misses " + QTNAME(target) [0m
          + ".\n", oblist);
 [32m        target->catch_msg(" in your direction which you easily evade.\n"); [0m
        return 1;
    }
 [32m    TP->catch_msg(" engulfing " + QTNAME(target) + ". " [0m

      + C(PRONOUN(TP)) + " is invisible for a second.\n");
 [32m    tell_room(E(TP), " engulfing " + QTNAME(target) + ". "  [0m
 [32m      + C(PRONOUN(target)) + " is invisible for a second.\n" [0m
      , oblist);
 [32m    target->catch_msg(" engulfing you.\n"); [0m
 [32m    target->command("$cough"); [0m
    return 1;
}


int
toot()
{
    string *exits;
    int i;
    string result;

    result = steamengine_check(TP);
    if(result != "ok")
    {
        write(result);
        return 1;
    }


    find_gizmo(TP)->reduce_water();
 [32m    write("You open a valve of the steam engine.\n"); [0m
    allbb(" does something to " + POSSESSIVE(TP) + " gizmo.");
    tell_room(E(TP), "Toooooot!!!\n");

    exits = (E(TP)->query_exit());
    for(i=0; i < sizeof(exits); i+=3)
        tell_room(exits[i], "Tooooot!\n");
    return 1;
}

int
ignite(string str)
{
    NF("You forgot to attach that module.\n");
    if(!flag(3,0))
        return 0;

    if (!darkcheck(TP))
        return 1;

    NF("Ignite what?\n");
    if(str != "engine" && str != "steamengine")
        return 0;


    NF("The engine has already been ignited.\n");
    if(find_gizmo(TP)->check_fire())
        return 0;

    NF("There isn't any wood left.\n");
    if(!(find_gizmo(TP)->check_wood()))
        return 0;

    if(flag(3,1) == -1)
        return 1;

    find_gizmo(TP)->burn_wood();
    write("Ok.\n");
    allbb(" does something to " + POSSESSIVE(TP) + " gizmo.");
    return 1;
}

int
ext_engine(string str)
{
    NF("You forgot to attach that module.\n");
    if(!flag(3,0))
        return 0;

    NF("It is too dark to do that!\n");
    if (!darkcheck(TP))
        return 0;

    NF("Switch what off?\n");
    if(str != "engine off")
        return 0;

    NF("The engine is already switched off.\n");
    if(!(find_gizmo(TP)->check_fire()))
        return 0;

    write("You extinguish the fire and lower the pressure.\n");
 [33m    say(QCTNAME(TP) + " does something to " + POSSESSIVE(TP) + " gizmo.\n"); [0m
    find_gizmo(TP)->ext_fire();
    return 1;
}


