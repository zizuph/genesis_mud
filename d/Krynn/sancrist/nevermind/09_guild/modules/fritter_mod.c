
/****************** Module: MasterBakerFritter ****************************
 *                           flag:   10                                   *
 **************************************************************************/
int
gbake(string str)
{
    string result, name;
    object gizmo, fruit, fritter;
    int alarm, amount;

    NF("You forgot to attach the MasterBakerFritter.\n");
    if(!(flag(10,0)))
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
    NF("You're still baking something.\n");
 [32m    if(GET_BAKE_ALARM(TP)) [0m
        return 0;
    NF("Gbake what?\n");
    if (!str)
        return 0;
    NF("You don't have the necessary ingredients for a " + str + "-
fritter.\n");
    gizmo = find_gizmo(TP);
    if((gizmo->check_flour() < 1) || (!(fruit = P(str, TP))))
        return 0;
    NF("You cannot gbake a " + str + ".\n");
    if (member_array("/std/food.c", inherit_list(fruit)) == -1)
        return 0;
    NF("You'll need more water first.\n");
    if(gizmo->check_water() < 1)
        return 0;

    if(flag(10,1) == -1)
        return 1;
 [32m    write ("Ok.\nYou put a " + str + " into the opening of the funnel and " [0m
      + "activate the MasterBakerFritter.\n");
 [33m    say(QCTNAME(TP) + " puts a " + str + " into " + POSSESSIVE(TP) + " [0m
gizmo.\n");

 [32m    setuid();seteuid(getuid()); [0m
    fritter = clone_object(GOBJ + "fritter");
    fritter->set_fruit(fruit->query_name());
    fritter->set_amount(fruit->query_amount() * 2);
    name = fruit->query_name();

    if ((amount = fruit->num_heap()) > 1)
        fruit->set_heap_size(amount-1);
    else
        fruit->remove_object();
    alarm = set_alarm(5.0, -1.0, "gbake_msg", name, fritter, TP, 0);
 [32m    STORE_BAKE_ALARM(TP,alarm); [0m
    TP->add_prop("_gnome_s_fruit_", str);
    return 1;
}

void
gbake_msg(string fruit, object fritter, object player, int call)

{
    int alarm, i;

    if(call == 0)
    {
        player->catch_msg("The opening begins to close.\nYour gizmo "
          + "vibrates.\n");
        tell_room(E(player), QCTNAME(player) + "'s gizmo starts to vibrate.\n"
          ,player);
        if(random(5) == 0)
            alarm = set_alarm(5.0, -1.0, "end_it", fruit, fritter, player, 0);
        else
            alarm = set_alarm(5.0, -1.0, "gbake_msg", fruit, fritter, player,
1);
 [32m        STORE_BAKE_ALARM(player,alarm); [0m
        return;
    }
    if(call == 1)
    {
        find_gizmo(player)->reduce_flour();
        player->catch_msg("As soon as the opening has closed, flour is blown "
          + "at the " + fruit + ".\n");
        tell_room(E(player), "A small white cloud gathers.\n");
        alarm = set_alarm(5.0, -1.0, "gbake_msg", fruit, fritter, player, 2);
 [32m        STORE_BAKE_ALARM(player,alarm); [0m
        return; 
    }
    if(call == 2)
    {
        player->catch_msg("The grinder activates and a series of gears and "
          + "mechanisms begin to rotate noisily.\n");
        tell_room(E(player), QCTNAME(player) + "'s gizmo creates some noises "
          + "making you believe that something is grinded.\n", player);
        player->remove_prop("_gnome_s_fruit_");
        alarm = set_alarm(5.0, -1.0, "gbake_msg", fruit, fritter, player, 3);
 [32m        STORE_BAKE_ALARM(player,alarm); [0m
        return;
    }
    if(call == 3)
    {
        tell_room(E(player), "A whistle blows.\n", player);
        player->catch_msg("A whistle blows indicating the beginning of the "
          + "mixing process.\n");
        alarm = set_alarm(3.0, -1.0, "gbake_msg", fruit, fritter, player, 4);
 [32m        STORE_BAKE_ALARM(player,alarm); [0m
        return;
    }
    if(call == 4)
    {
        tell_room(E(player), QCTNAME(player) + "'s gizmo makes WHOOSH. Then "
          + "clanking and banging noises can be heard.\n", player);
        player->catch_msg("The fine powdery substance sifts through a "
          + "hose with a WHOOSH while at the same time water "
          + "drips in.\nClanking and banging noises can be heard as "
 [32m          + "the two are mixed together.\n"); [0m
        find_gizmo(player)->reduce_water();
        alarm = set_alarm(4.0 + itof(random(5)), -1.0, 
          "gbake_msg", fruit, fritter, player, 5);
 [32m        STORE_BAKE_ALARM(player,alarm); [0m
        return;   
    }
    if(call == 5)
    {
        tell_room(E(player), "A whistle blows.\n", player);
        player->catch_msg("A second whistle blows indicating that the "
 [32m          + "GnomishAutomaticBatterCreamySmoothnessSensor initiates " [0m
          + "the final phase.\n");
        alarm = set_alarm(5.0, -1.0, "gbake_msg", fruit, fritter, player, 6);
 [32m        STORE_BAKE_ALARM(player,alarm); [0m
        return;
    }
    if(call == 6)
    {
        tell_room(E(player), QCTNAME(player) + "'s gizmo makes GlubGlub.\n"
          , player);
 [35m        player->catch_msg("GlubGlub.\nThe batter pours out of the bowl into " [0m
          + "the CentralCavitiy of the oven.\n");
        alarm = set_alarm(5.0, -1.0, "gbake_msg", fruit, fritter, player, 7);
 [32m        STORE_BAKE_ALARM(player,alarm); [0m
        return;
    }
    if(call == 7)
    {
        player->catch_msg("A red light indicates commencing of the baking "
          + "process.\n");
        i = random(7) + 3;
        alarm = set_alarm(50.0, -1.0, "smell_fritter", fritter, player, i, 0);
 [32m        STORE_BAKE_ALARM(player,alarm); [0m
        return;
    }
}  


void
smell_fritter(object fritter, object player, int i, int call)
{
    int alarm;


    if(call < 7)
        tell_room(E(player), "You smell a delicious aroma.\n");
    else if(call == 7)
        tell_room(E(player), "Something smells burned.\n");
    else
    {
        tell_room(E(player), "Black clouds gather around " + QTNAME(player)
          + ".\nIt smells burned.\n", player);
        player->catch_msg("Black clouds gather around you. Is there "
          + "something burning?\n");             
    }
    call++;
    if(call < i)
    {
        alarm = set_alarm(20.0, -1.0, "smell_fritter", fritter, player, i,
call);
 [32m        STORE_BAKE_ALARM(player,alarm); [0m
    }
    else
    {           
 [32m        alarm = set_alarm(20.0, -1.0, "give_fritter", fritter, player, i); [0m
 [32m        STORE_BAKE_ALARM(player,alarm); [0m
    }
}


void
 [32mgive_fritter(object fritter, object player, int baking_time) [0m
{
    tell_room(E(player), "A bell rings.\n");
    player->catch_msg("You receive your hot fritter.\n");

    fritter->set_durch(baking_time);
    fritter->move(player);

    REMOVE_BAKE_ALARM(player);
}   


void
end_it(string fruit, object fritter, object player, int call)
{
    int alarm;

    if(call == 0)
    {   
        player->command("$oops");
        player->catch_msg("The closing mechanism jammed! "
          + "Most of the flour aimed at the " + fruit
          + " blasts at you and leaves you being a white gnome.\n");       
tell_room(E(player), "Suddenly a white cloud emanates from "
          + QTNAME(player) + "'s gizmo and engulfs " + OBJECTIVE(player)
          + " completely.\n", player);
        find_gizmo(player)->reduce_flour();
        alarm = set_alarm(5.0, -1.0, "end_it", fruit, fritter, player, 1);
 [32m        STORE_BAKE_ALARM(player,alarm); [0m
        return; 
    }
    if(call == 1)
    {
        player->catch_msg("The grinder starts working and showeres you "
          + " in a sticky substance.\nIt then grinds to a halt.\n");
        tell_room(E(player), "Then, " + QTNAME(player) + "'s gizmo starts "
          + "working again and showers " + OBJECTIVE(player) + " in "
          + "a sticky substance.\n", player);
        alarm = set_alarm(10.0, -1.0, "end_it", fruit, fritter, player, 2);
 [32m        STORE_BAKE_ALARM(player,alarm); [0m
        player->remove_prop("_gnome_s_fruit_");
        return;
    }
    if(call == 2)
    {
        player->catch_msg("Small trickles of water drip from your gizmo.\n");

        find_gizmo(player)->reduce_water();             
        fritter->remove_object();
        REMOVE_BAKE_ALARM(player);
        return;
    }
}

int
end_gbake(string str)
{
    string fruit;
    object fruit_obj;
    int amount;

    NF("What?\n");
    if(!(flag(10,0)))
        return 0;
    NF("End what?\n");
    if(str != "baking")
        return 0;
    NF("You aren't baking anything.\n");
 [32m    if(!GET_BAKE_ALARM(TP)) [0m
        return 0;
 [32m    remove_alarm(GET_BAKE_ALARM(TP)); [0m
 [35m    write("You shut down the MasterBakerFritter and "); [0m
    if(fruit = TP->query_prop("_gnome_s_fruit_"))
    {
        if(fruit_obj = P(fruit, TP))
        {
            amount = fruit_obj->num_heap();
            amount ++;
            fruit_obj->set_heap_size(amount);
            write("retrieve your " + fruit + ".\n");
            tell_room(E(TP), QCTNAME(TP) + " retrieves something from "
              + POSSESSIVE(TP) + " gizmo.\n", TP);
            TP->remove_prop("_gnome_s_fruit_");
            REMOVE_BAKE_ALARM(TP);
            return 1;
        }
    }
    write("clean it thouroughly throwing away the sad remains of your "
      + TP->query_prop("_gnome_s_fruit_") + ".\n");
 [33m    say(QCTNAME(TP) + " does something to " + POSSESSIVE(TP) [0m
      + " gizmo and then cleans it thouroughly.\n");
    TP->remove_prop("_gnome_s_fruit_");
    REMOVE_BAKE_ALARM(TP);
    return 1;
}

