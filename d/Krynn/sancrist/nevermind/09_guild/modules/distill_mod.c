/**************** Module: DistillationApparatus****************************
 *                           flag:   12                                   *
 **************************************************************************/
int

open_funnel(string str)
{
    int alarm;

    if(!(flag(12,0)))
        return 0;
    NF("Open what?\n");
    if(str != "funnel")
        return 0;
    if(!darkcheck(TP))
        return 1;
    NF("The funnel is already open.\n");
    if(QUERY_FUNNEL_OPEN(TP))
        return 0;
 [32m    write("You open the funnel of the DistillationApparatus.\n"); [0m
 [33m    say(QCTNAME(TP) + " opens a funnel on " + POSSESSIVE(TP) [0m
      + " gizmo.\n");
    alarm = set_alarm(100.0, -1.0, "spill_water",TP,1);
 [32m    STORE_SPILL_ALARM(TP,alarm); [0m
    FUNNEL_OPEN(TP);
    return 1;
}

int
pour_drink(string str)
{
    int i, many, inherit_flag = 0;
    string arg, *inherits;
    object drink;

    if(!flag(12,0))
        return 0;
    NF("The funnel of the Distillationapparatus is still closed.\n");
    if(!QUERY_FUNNEL_OPEN(TP))
        return 0;
    NF("Pour how many what into the funnel?\n");
    if(!parse_command(str, environment(TP), "[the] / [a] %d %w 'into' [the]
'funnel' [.]",  many ,arg))
        return 0;
    if(!darkcheck(TP))
        return 1;
    NF("You don't have a " + arg + ".\n");
    if(!(drink = P(arg, TP)))
        return 0;
    inherits = inherit_list(drink);
    for(i=0;i<sizeof(inherits);i++)
        if(inherits[i] == "/std/drink.c")
            inherit_flag = 1;
    NF("You cannot pour the " + drink->short() + " down the funnel.\n");

    if(!inherit_flag)
        return 0;
    if(many >= drink->num_heap())
    {
        many = drink->num_heap(); 
        write("You take carful aim and pour " + drink->short() + " down the
funnel.\n");
 [33m        say(QCTNAME(TP) + " fills " + drink->short()  + " into " + [0m
POSSESSIVE(TP)
          + " gizmo.\n"); 
    }
    else
    {
        write("You take carful aim and pour " + many + " " + drink->query_adj()
+ " " 
          + drink->query_name() + " down the funnel.\n");
 [33m        say(QCTNAME(TP) + " fills " + drink->short()  + " into " + [0m
POSSESSIVE(TP)
          + " gizmo.\n"); 
    }
    NF("A bell rings.\nA valve opens and your precious drink spills out.\n"
      + "The CentralCavityContainingLiquidsToBeDistilled seems to be already
full.\n");
    if(QUERY_LIQUID(TP) >= 3000)
    {
 [33m        say("But somehow spilled it to the floor.\n"); [0m
        drink->remove_object();
        return 0;
    }
    i = drink->query_soft_amount() * many;
    if(i + QUERY_LIQUID(TP) >= 3000)
    {
 [35m        write("A valve opens and spits out some of the liquid you just " [0m
          + "filled in.\n");    
 [33m        say(QCTNAME(TP) + "'s gizmo spits out again some of the liquids.\n"); [0m
        i = 3000 - QUERY_LIQUID(TP);
    }
    ADD_VALUE(TP, i * drink->query_alco_amount() / drink->query_soft_amount());
    ADD_LIQUID(TP, i);
    drink->set_heap_size(drink->num_heap() - many);
    return 1;
}

int
close_funnel(string str)
{
    if(!(flag(12,0)))
        return 0;
    if(!darkcheck(TP))
        return 1;
    NF("Close what?\n");
    if(str != "funnel")
        return 0;
    NF("The funnel is already closed.\n");
    if(!QUERY_FUNNEL_OPEN(TP))
        return 0;
 [32m    write("You close the funnel.\n"); [0m
 [33m    say(QCTNAME(TP) + " closes a funnel on " + POSSESSIVE(TP) [0m
      + " gizmo.\n");
    remove_alarm(QUERY_SPILL_ALARM(TP));
    REMOVE_SPILL_ALARM(TP);
    FUNNEL_CLOSED(TP);
    return 1;
}


void
spill_water(object player, int flag)
{
    int alarm;

    if(QUERY_LIQUID(player) < 1)
        return;
    if(player->query_skill(SS_AWARENESS)/3+random(60) > 50)
    {
        if(flag == 1)
            player->catch_msg("Some water drips from the open funnel "

              +"of your DistillationApparatus.\n");
        else
            player->catch_msg("Some liquid sips from your gizmo.\n");
    }
    if(QUERY_LIQUID(player) < 100)
    {
        REMOVE_LIQUID(player);
        REMOVE_VALUE(player);
    }
    else
    {
        ADD_LIQUID(player, -100);
        ADD_VALUE(player, -100 * QUERY_VALUE(player) / QUERY_LIQUID(player));
    }
    alarm = set_alarm(100.0, -1.0, "spill_water",player,1);
 [32m    STORE_SPILL_ALARM(player,alarm); [0m
}

// Called from burn_wood() in the gizmo:

void
distill_contents(string str)
{
    int i, j, boom;

    float water, alk;
    object gizmo, *inv, player;
    string *inherits;

    player = TP;
    if(!(flag(12,0)))
        return;
    if(!QUERY_LIQUID(player))
        return;
    gizmo = find_gizmo(player);
    inv = all_inventory(player);
    for(j=0;j<sizeof(inv);j++)
    {
        inherits = inherit_list(inv[j]);
        for(i=0;i<sizeof(inherits);i++)
            if(inherits[i] == "/std/torch.c")
                if(inv[j]->query_lit())
                    boom = 1;
    }
    if(boom == 1)
    {
        tell_room(E(player), "BOOOOM!!! " + QCTNAME(player) 
          + " is the center of an explosion.\n", player);
        player->catch_msg("BOOOOM!!! Your gizmo exploded!\n");
        tell_room(E(player), "Shards of glass are flying everywhere.\n");
        player->heal_hp(-(player->query_max_hp()/10));
        if(player->query_hp < 0)
            player->do_die();
        REMOVE_LIQUID(player);
        REMOVE_VALUE(player);
        REMOVE_SPILL_ALARM(player);
        gizmo->do_break(12);
        if(flag(3,0))
            gizmo->do_break(3);
        if(!random(2) && flag(2,0))
            gizmo->do_break(2);
        if(!random(2) && flag(2,0))
            gizmo->do_break(2);
        if(!random(4) && flag(4,0))
            gizmo->do_break(2);
        if(!random(4) && flag(6,0))
            gizmo->do_break(2);
        if(!random(5) && flag(8,0))
            gizmo->do_break(2);
        if(!random(3) && flag(10,0))
            gizmo->do_break(2);
        if(!random(3) && flag(11,0))
            gizmo->do_break(2);
        return;
    }
    water = itof(QUERY_LIQUID(player)) *0.2;
    alk = itof(QUERY_VALUE(player))*0.2;
    ADD_LIQUID(player, ftoi(-water));
    ADD_VALUE(player, ftoi(-alk));
    tell_room(E(player), "A bell rings.\nA bubbling noise emanates from "
      + QTNAME(player) + ".\n", player);
    player->catch_msg("A bell rings.\nA bubbling noise emanates from "
      + "your gizmo.\n");
    water = water / 10.0;
    if(gizmo->check_water() + ftoi(water) >= 40)
    {
        gizmo->refill_water(40);
        player->catch_msg("A gush of water streams from your gizmo.\n");
        tell_room(E(player), "A stream of water gushes from " + QTNAME(player) 
          + "'s gizmo.\n", player);
    }   
    else
        gizmo->refill_water(gizmo->check_water() + ftoi(water));
    alk = alk / 10.0;
    if(gizmo->check_wood() + ftoi(alk) >= 14)
    {
        gizmo->set_wood(14);

 [35m        player->catch_msg("Your gizmo spits out some pure alcohol.\n"); [0m
 [35m        tell_room(E(player), QCTNAME(player) + "'s gizmo spits out some " [0m
          + "transparent liquid.\n", player);
    }
    else
        gizmo->set_wood(gizmo->check_wood() + ftoi(alk));
}

