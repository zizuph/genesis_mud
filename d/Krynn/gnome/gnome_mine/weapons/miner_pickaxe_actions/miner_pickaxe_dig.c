void
make_entrance()
{
    object instances_room = 0;

    int selType;

    object tp = this_player();

    instances_room = clone_object(ROOMS_DIR + "mine_instance");

    instances_room->set_short("A mineshaft.");

    instances_room->set_long("This is the entrance to a mineshaft. " +
                    "There's a hole in the roof and a rope dangling from above\n");

    environment(tp)->add_exit(file_name(instances_room),
    "down");

    instances_room->add_exit(environment(tp), "up");

    instances_room->set_boundaries(3 + random(8));
    instances_room->set_master_instance_pointer(instances_room);

    instances_room->set_x(0);
    instances_room->set_y(0);
    instances_room->set_z(0);

    instances_room->set_room_loc(0, 0, 0, instances_room);

    instances_room->set_master_mine_ore(ore_in_room());
    instances_room->set_room_ore("none");

    remove_flag();

    tp->add_fatigue(mining_fatigue);

    object * ob = FIND_STR_IN_OBJECT("rope", this_player());
    ob[0]->remove_object();    

    tp->catch_msg("You finish making a new entrance. " +
                "You tie a rope to a big nearby rock and throw it down the tunnel.\n");
    tell_room(environment(tp), QCTNAME(tp) + " finishes " +
                    "making a new entrance.\n" +
                    QCTNAME(tp) + " ties a rope to a big nearby rock and throws it down the tunnel.\n", tp);
    paralyze->stop_paralyze();

    //TODO check if its not better to have a chance of the appearence of cave/dungeon
    //TODO finish caves/dungeons in make_random_rooms
/*
    selType = random(2);

    switch (selType)
    {
        case 0:
            make_random_rooms(instances_room, random(3) + 2, "cave");
            break;
        case 1:
            make_random_rooms(instances_room, random(3) + 2, "dungeon");
            break;
    }
*/
}


mapping DIGING_EVENT_ROCK=   ([
                            "msg"   : "You mine a few rocks off.\n",
                            "env"   : " mines a few rocks off.\n",
                            "timer"  : -2,
                            "fatigue" : -1,
                            "percent" : 0
                        ]);

mapping DIGING_EVENT_BIG_ROCK=   ([
                            "msg"   : "You crack a big rock in half, opening up a big space.\n",
                            "env"   : " cracks a big rock in half, opening up a big space.\n",
                            "timer"  : -3,
                            "fatigue" : -2,
                            "percent" : 0
                        ]);

mapping DIGING_EVENT_UNBREAK_ROCK=   ([
                            "msg"   : "You cannot break this rock, " +
                                        "you decide to move to the side and try again.\n",
                            "env"   : " cannot break this rock, " +
                                        "then decides to move to the side and tries again.\n",
                            "timer"  : 0,
                            "fatigue" : -3,
                            "percent" : 0
                        ]);

mapping DIGING_EVENT_SAND=   ([
                            "msg"   : "You hit a patch of sand after breaking a rock, " +
                                        "the sand makes it harder to keep digging.\n",
                            "env"   : " hits a patch of sand after breaking a rock, " +
                                        "the sand makes it harder to keep digging.\n",
                            "timer"  : 1,
                            "fatigue" : -2,
                            "percent" : 0
                        ]);

mapping DIGING_EVENT_ROOF=   ([
                            "msg"   : "You hit the wrong rock, since some of the floor " +
                                        "slides and blocks part of what you were mining.\n",
                            "env"   : " hits the wrong rock, since some of the floor " +
                                        "slides and blocks part of the mining site.\n",
                            "timer"  : 1,
                            "fatigue" : -2,
                            "percent" : 0
                        ]);

mapping DIGING_EVENTS=    ([
                            "rock"       : DIGING_EVENT_ROCK,
                            "bigrock"    : DIGING_EVENT_BIG_ROCK,
                            "unrock"     : DIGING_EVENT_UNBREAK_ROCK,
                            "sand"       : DIGING_EVENT_SAND,
                            "roof"       : DIGING_EVENT_ROOF
                        ]);


void
dig_entrance(int mining_timer)
{
    object tp = this_player();

    if (mining_timer < 0)
    {
        make_entrance();
    }
    else if (mining_timer > 25)
    {
        tp->catch_msg("You don't seem to be going nowhere, you stop mining to " +
                    "contemplate what you are doing wrong, perhaps you " +
                    "could use a bit more awareness.\n");
        tell_room(environment(tp), QCTNAME(tp) + " doesn't seem to be going nowhere, then stops mining to " +
                    "contemplate what's wrong.\n", tp);
        
        remove_flag();
        paralyze->stop_paralyze();
    }
    else
    {

        if (tp->query_fatigue() < 1)
        {
            if (this_player()->query_wiz_level())
            {
                write("Since you are a wizard, you can keep mining without worring about fatigue.\n");
            }
            else
            {
                remove_flag();
                paralyze->stop_paralyze();
                tp->catch_msg("You fall to the ground trying to catch your breath. You are too tired to keep mining.\n");
                tell_room(environment(tp), QCTNAME(tp) + " falls to the ground exhausted of mining.\n", tp);                
                return;
            }
        }

        //TODO tweak values, change awareness for mining.
        DIGING_EVENT_ROCK["percent"]            = random(tp->query_skill(SS_AWARENESS) - 10);
        DIGING_EVENT_BIG_ROCK["percent"]        = random(tp->query_skill(SS_AWARENESS) - 50);
        DIGING_EVENT_UNBREAK_ROCK["percent"]    = random(70 - tp->query_skill(SS_AWARENESS));
        DIGING_EVENT_SAND["percent"]            = random(80 - tp->query_skill(SS_AWARENESS));
        DIGING_EVENT_ROOF["percent"]            = random(50 - tp->query_skill(SS_AWARENESS));

        string selected = random_by_percent(0, DIGING_EVENTS, "percent");

        tp->catch_msg(DIGING_EVENTS[selected]["msg"]);
        tell_room(environment(tp), QCTNAME(tp) + DIGING_EVENTS[selected]["env"], tp);
        mining_timer = mining_timer + DIGING_EVENTS[selected]["timer"];
        tp->add_fatigue(DIGING_EVENTS[selected]["fatigue"]);


        mining_alarm = set_alarm(5.0, 0.0, &dig_entrance(mining_timer));
    }
}

int
do_dig(string str)
{
    object tp = this_player();
    int time_to_mine = 0;

    if (!str)
    {
        notify_fail("You mean make entrance?\n");
        return 0;
    }

    object * ob = FIND_STR_IN_OBJECT("miner_pickaxe", this_player());
    if (ob[0]->query_wielded() == 0)
    {
        notify_fail("You must wield a miner pickaxe first.\n");
        return 0;
    }

    ob = FIND_STR_IN_OBJECT("rope", this_player());
    if (sizeof(ob) == 0)
    {
        notify_fail("You must have a rope to climb down before starting to mine.\n");
        return 0;
    }

    if (str == "entrance")
    {
        if (is_terrain_minable())
        {
            if (!environment(tp)->query_prop(ROOM_I_INSIDE))
            {
                if (!check_flag())
                {
                    if (member_array("down",environment(tp)->query_exit()) < 0)
                    {
                        if (use_pickaxe() >= 0 || this_player()->query_wiz_level())
                        {
                            if (use_pickaxe() < 0 && this_player()->query_wiz_level())
                            {
                                write("Since you are a wizard, you can keep mining without recharging.\n");
                            }                            

                            tp->catch_msg("You start mining an entrance.\n");
                            tell_room(environment(tp), QCTNAME(tp) + " starts " +
                                    "mining an entrance.\n", tp);
                            
                            time_to_mine = 0 + random(check_delay_in_mining());

                            seteuid(getuid());
                            paralyze = clone_object("/std/paralyze");
                            paralyze->set_stop_fun("stop_mining");
                            paralyze->set_stop_verb("stop");
                            paralyze->set_combat_stop(1);
                            paralyze->set_stop_message("You stop mining.\n");
                            paralyze->set_remove_time(300);
                            paralyze->set_fail_message("You are busy mining. You must " +
                                "'stop' to do something else.\n");
                            paralyze->move(this_player(),1);

                            add_flag();

                            mining_alarm = set_alarm(5.0, 0.0, &dig_entrance(time_to_mine));
                        }
                        else
                        {
                            tp->catch_msg("The pickaxe seems to have run out of juice, it's no longer humming. " +
                                "Try as you might, it's impossible to mine anything; you should <refill> the <lava tank> " +
                                "with a lava source.\n");
                        }
                    }
                    else
                    {
                        tp->catch_msg("There is already an entrance here.\n");
                    }
                }
                else
                {
                    tp->catch_msg("Someone is already making an entrance here, wait till they finish or find another place.\n");
                }
            }
            else
            {
                tp->catch_msg("Cannot make entrance indoors.\n");
            }
        }
        else
        {
            tp->catch_msg("This terrain is no good, nothing to be found here.\n");
        }            
    }
    else
    {
        notify_fail("You mean make entrance?\n");
        return 0;
    }
    return 1;
}

varargs int
stop_mining(mixed arg)
{

    remove_alarm(mining_alarm);

    tell_room(environment(this_player()), QCTNAME(this_player())
      + " stops mining.\n",this_player());

    remove_flag();

    return 0;
}

