
/******************** gbored **********************************************/

int
gbored()
{
    write("YAWN... Again, there is nothing to do for your superior "
      + "intellect.\n");
 [35m    all(" yawns. There is no real challenge for " [0m
      + OBJECTIVE(TP) + " in this world today.");
    return 1;
}

/******************** build **********************************************/

int
build(string str)
{
    int alarm;
    object kit;


    if(!GMEMBER(TP))
        return 0;
    if(!P("kit", TP))
        return 0;
    NF("You don't have that kit.\n");
    if(!(kit = P("kit_for_" + str, TP)))
        return 0;
    NF("You don't know how to do that.\n");
    if((TP->query_skill(SS_BUILD)) < 1)
        return 0;
    if(!darkcheck(TP))
        return 1;
    write("You start assembling the parts.\n");
 [33m    say(QCTNAME(TP) + " sits down and starts working on something.\n" [0m
      + C(PRONOUN(TP)) + " seems to be completely absorbed.\n");
    paralyze_player(TP, "You are completely absorbed by building " 
      + "the " + str + ".\n", "", 30);
    alarm = set_alarm(6.0, 6.0, "build_msg", TP);
    set_alarm(38.0, -1.0, "build_ready", TP, kit, alarm);
    return 1;
}

void

build_msg(object player)
{
    int a;
    string *msg;
 [32m    msg = ({"put together some parts","add some springs","add some wheels", [0m
      "happily add a whistle", "add a nicely shaped bell", 
 [32m      "frown at your progress then continue working", [0m
 [32m      "inspect the internals then give a satisfied nod", [0m
      "rotate a piece so it fits better",
      "wriggle a recently-attached part and look thoughtful"
    });
    a = random(sizeof(msg));
    player->catch_msg("You " + msg[a] + ".\n");
    tell_room(E(player), QCTNAME(player) + " works hard at something"
      + ".\n", player); 
}

void
build_ready(object player, object kit, int alarm)
{
    int skill, min_skill, i;
    string type;

    remove_alarm(alarm);

    tell_room(E(player), QCTNAME(player) + " finished " +
      POSSESSIVE(player) + " work.\n", player);
    player->catch_msg("You finished your new module!\n");
    skill = (TP->query_skill(SS_BUILD));
 [32m    type = (kit->get_type()); [0m
    for(i=0;i<sizeof(TYPES);i++)
    {
        if(type == TYPES[i])
            min_skill = MIN_SKILLS[i];
    }

    if(skill < min_skill)
    {
        kit->is_bomb();
        if(skill > (min_skill - 10))
            player->catch_msg("But somehow, what you built "
              + "doesn't look right.\n");
    }
    kit->set_short("readyToAttach" + capitalize(type));
    kit->set_long("This " + capitalize(type) + "-module is ready "
      + "to attach to the gizmo.\n"); 
    kit->set_built();
    kit->set_break_chance(2*skill - min_skill);
    kit->add_name("module");
}


/********************* concentrate **************************************/

int
concentrate(string str)
{
    if(!str)
    {
        allbb(" concentrates deeply.");
        write("You concentrate deeply.\n");
        return 1;
    }
    allbb(" concentrates hard on " + str + ".");
    write("You concentrate hard on " + str + ".\n");
    return 1;
}



