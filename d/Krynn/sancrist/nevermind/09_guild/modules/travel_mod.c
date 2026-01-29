/********************** module: advanced traveller ************************
 *                        flag: 4                                         *
 **************************************************************************/

int

travel(string str)
{
    NF("You forgot to attach that module.\n");
    if(!(flag(4,0)))
        return 0;

    if (!darkcheck(TP))
        return 1;

    if(str == "n") str = "north";
    if(str == "ne") str = "northeast";
    if(str == "e") str = "east";
    if(str == "se") str = "southeast";
    if(str == "s") str = "south";
    if(str == "sw") str = "southwest";
    if(str == "w") str = "west";
    if(str == "nw") str = "northwest";

    NF("You cannot travel into that direction.\n");
    if(str!="north"&&str!="northeast"&&str!="east"&&str!="southeast"&&
      str!="south"&&str!="southwest"&&str!="west"&&str!="northwest")
        return 0;       

    if(flag(4,1) == -1)
        return 1;

    TP->catch_msg("You take aim carefully and open the valve...\n");
    allbb(" does something to " + PRONOUN(TP) + " gizmo.");
    if(random(100) < 6) 
    {
        set_alarm(4.0, -1.0, "do_whirl", TP, str);
        return 1;
    }
    set_alarm(4.0, -1.0, "do_travel", TP, str, 0);
    return 1;
}

string
check_exit(string direction, object player, int flag)
{
    int i;
    mixed *exits;
    string result;

    result = steamengine_check(player);
    if(flag > 0)
        result = "ok";  /* We are already moving */
    if(result != "ok")

    {
        player->catch_msg("Why...? Nothing happened.\n");
        if(result == "What?\n")
            player->catch_msg("You don't have a steamengine.\n");
        else
            player->catch_msg(result);
        return "fault";
    }
    result = "no_exit";
    exits = (E(player)->query_exit());
    for(i=0;i<sizeof(exits)/3;i++)
    {
        if(exits[3*i+1] == direction)
        {
            result = exits[3*i];
            if(exits[3*i+2] != 0)
                result = "no_exit";
        }
    }
    return result;
}

void
do_travel(object player, string direction, int flag)
{
    string exit;

    exit = check_exit(direction, player, flag);
    if(exit == "fault")
        return;
    if(exit == "no_exit" && flag)
    {
        set_alarm(2.0, -1.0, "bonk", player, direction, flag);
        return;
    }
    if(exit == "no_exit")
    {
        player->catch_msg("There is no exit to the " + direction + ".\n");
        return;
    }

    if(!CAN_SEE_IN_ROOM(player))
    {
        player->catch_msg("Oh no! It's dark in here!\nYou loose control.\n");
set_alarm(2.0, -1.0, "bonk", player, direction, flag);
    }



    if((find_gizmo(player)->check_water()) > 0)
    {
        if(flag == 0)
        {
            player->catch_msg("Wwwuussshhh.... Off we go!\n");
            tell_room(E(player), "Leaving a lot of steam behind, "
              + QTNAME(player) + " is  flung " + direction + "wards.\n"
              , player);
        }
        else
        {
            player->catch_msg("You rush " + direction + "wards.\n");
            tell_room(E(player), "Leaving a lot of steam behind, a gnome "
              + "rushes past you to the " + direction + ".\n"
              + "What an incredible speed!\n", player);
        }
        flag++;
        player->move(exit);
        find_gizmo(player)->reduce_water();
        set_alarm(1.5, -1.0, "do_travel", player, direction, flag);
    }
    else
    {
        player->catch_msg("You suddenly lose control of direction.\n");

        set_alarm(2.0, -1.0, "bonk", player, direction, flag);
    }
}

void
bonk(object player, string direction, int flag)
{
    player->catch_msg("OUCH... you hit something!! Everything goes black"
      + "...\n");
    tell_room(E(player), "A gnome flies past you.\nThe next second you "
      + "hear a terrible crashing sound and see, as you turn, " + QNAME(player)
      + " lying flat on " + POSSESSIVE(player) + " back.\n", player);
    player->heal_hp(-((player->query_max_hp()) / 20) - flag*5);
    if((player->query_hp()) < 0)
    {
        player->do_die();
        return;
    }
    paralyze_player(player, "Your head is too dizzy for that.\n",
      "You can see again.\n", (10+3*flag));
}

string
find_exit(object player)

{
    int a;
    string *exits;

    exits = (E(player)->query_exit());
    a = random((sizeof(exits)/3));
    return exits[a*3+1];
}

void
do_whirl(object player, string str)
{
    string exit = str;
    int tries = 0;

    player->catch_msg("... and release too much steam!\nOops! "
      + "Something went wrong!\nYou are flung about the "
      + "room like balloon with a hole in it.\n");
    tell_room(E(player), QCTNAME(player) + " creates a huge cloud "
      + "of steam and is flung about the room like a balloon "
      + "with a hole in it!\n", player);
    while(exit == str && tries < 3)
    {
        exit = find_exit(player);
        tries++;
    }
    set_alarm(7.0, -1.0, "flung_msg", player);
    set_alarm(8.0, -1.0, "do_travel", player, exit, 1);
}

void
flung_msg(object player)
{
    player->catch_msg("Then your Traveller determines a direction for you!\n");
}

