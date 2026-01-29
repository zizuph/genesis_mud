
string
check_lava_tank()
{
    string msg = "You check the lava tank, the meter reads: ";

    if (lava == 100)
    {
        msg += "full.";
    }
    else if (lava > 90)
    {
        msg += "almost full.";
    }
    else if (lava > 50)
    {
        msg += "over half way full.";
    }
    else if (lava > 20)
    {
        msg += "half way empty.";
    }
    else if (lava > 0)
    {
        msg += "almost empty.";
    }
    else
    {
        msg += "empty.";
    }

    return msg;
}

int
do_check(string str)
{

    object tp = this_player();

    if (str == "dial")
    {
        tp->catch_msg("You check the dial on the pickaxe, there's a small arrow pointing at the number " + check_mining_speed() + ".\n");
        tell_room(environment(tp), QCTNAME(tp) + " checks the dial in "+tp->query_possessive()+" pickaxe.\n", tp);

        return 1;
    }
    else if (str == "tank" || str == "lava tank" || str == "meter")
    {
        
        tp->catch_msg(check_lava_tank() + "\n");
        tell_room(environment(tp), QCTNAME(tp) + " checks the lava meter in "+tp->query_possessive()+" pickaxe.\n", tp);

        return 1;        
    }

    notify_fail("Check what? dial? meter?\n");
    return 0;       
}