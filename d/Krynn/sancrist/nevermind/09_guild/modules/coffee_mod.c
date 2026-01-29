/********************* module: coffeemaker ********************************
 *                     flag:   5                                          *
 **************************************************************************/

int
makecoffee(string str)
{
    int coffee_alarm;
    string result;

    NF("You forgot to attach that module.\n");;
    if(!flag(6,0))
        return 0;
    if(!darkcheck(TP))
        return 1;

    result = steamengine_check(TP);
    if(result == "What?\n")
        result = "You'll need a steamengine first.\n";
    if(result != "ok")
    {

        write(result);
        return 1;
    }
    if(flag(6,1) == -1)
        return 1;

    write("You press the button requesting a CupOfHotCappuccino "
      + "and wait ...\n");
    tell_room(E(TP), QCTNAME(TP) + " does something to " + POSSESSIVE(TP) 
      + " gizmo but nothing seems to happen ... yet.\n", TP);
    coffee_alarm = set_alarm(5.0, 5.0, "coffee_msg", TP);
    set_alarm(26.0, -1.0, "coffee_2", TP, coffee_alarm);
    return 1;
}

void
coffee_msg(object player)
{
    int a;
    string *msg = ({"You hear nothing ..", "The coffeemaker rumbles "
      + "dangerously", "The whole gizmo shakes fiercely", "A valve opens "
      + "and releases a cloud of steam", "Something rattles noisily inside "
      + "the gizmo", "A smelly brownish liquid drips from your gizmo",
      "The coffeemaker creates a buzzing sound"}) 

    , *telr = ({"", "Something rumbles dangerously.\n", 
      QCTNAME(player) + "'s gizmo shakes fiercely.\n"
      , QCTNAME(player) + " releases a cloud of steam.\n"
      , QCTNAME(player) + "'s gizmo rattles noisily.\n", QCTNAME(player) 
      + " produces a smelly brownish liquid which drops to the floor.\n"
      , "You hear a buzzing sound.\n"});

    a = random(sizeof(msg));
    player->catch_msg(msg[a] + ".\n");
    tell_room(E(player), telr[a] , player);
}

void
coffee_2(object player, int coffee_alarm)
{
    remove_alarm(coffee_alarm);
    find_gizmo(player)->reduce_water();
    if (!random(5))
    {     
        player->catch_msg("A stream of hot cappuccino splashes into the "
          + "dispensing chamber. Then a cup arrives. Frustrated you "
          + "recycle the cup.\n");
        if(!random(5))
            player->catch_msg("You make a note you want to hand to "

              + "the responsible committee on next occasion.\n");
        tell_room(E(player), QCTNAME(player) + " receives some hot cappuccino,
"
          + "then a cup.\n", player);
        return;
    }
    player->catch_msg("A cup appears in the dispensing slot which is "
      + "rapidly filling with delicious hot cappuccino.\nYou eagerly "
      + "take the cup.\n"); 
    tell_room(E(player), QCTNAME(player) + " receives a cup of hot
cappuccino.\n", player);
 [32m    setuid();seteuid(getuid()); [0m
    clone_object(FOOD + "coffee.c")->move(player);
}

