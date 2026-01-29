
int mining_alarm;
int someoneIsMining = 0;

object paralyze_mining;

/*
 * Function name: add_instance_room
 * Description  : Builds the next room in the instance and adds proper
 *              exits. If the exit is an already excavated room, simply connects them.
 *				Also makes an awarness check. if the room has a preset ore (can only be 
 				the same type as the mine type EG: copper mine), there's a rarity% chance 
 				(+ up to 30% more from awareness) that you will find another room with
 				the mines ore, thus making this the continuation of an ore "vein".
				Otherwise, there's a very small chance (-10%, but +15% from maxed awareness) 
				that you will find a random gem (sorted by rarity, thus a high rarity gem has 
				less chance of appearing), -5% (but +15% from maxed awareness) that you will
				find a random ore sorted by rarity, and finally rarity% (+10% with awareness maxed) 
				that you will find the mines ore, thus starting another "vein".
				"veins" can only go in one direction, once the direction is found, the room_ore
				is set to "none" to avoid having it go in 2 directions.
 */
void
add_instance_room(string str)
{
	object tp = this_player();
    object instances_room = 0;

	int delta_x = 0;
	int delta_y = 0;
	int delta_z = 0;

    object gem;


	if (dirLocsLetters[str] == "x")
	{
		delta_x = delta_x + dirLocs[str];
	}
	else if (dirLocsLetters[str] == "y")
	{
		delta_y = delta_y + dirLocs[str];
	}
	else if (dirLocsLetters[str] == "z")
	{
		delta_z = delta_z + dirLocs[str];
	}

	object roomExists = query_master_instance_pointer()->query_rooms(x + delta_x, y + delta_y, z + delta_z);

	if (roomExists == 0)
	{
	    instances_room = clone_object(ROOMS_DIR + "mine_instance");

	    instances_room->query_descr(instances_room, -1);

	    if (str == "down")
	    {
            this_object()->add_exit(file_name(instances_room),
                str, block_player_down);

            this_object()->add_item(({ "rock" }),
                "A big rock.\n");

            instances_room->add_item(({ "roof" }),
                    "There's a hole in the roof.\n");
	    }
	    else
		{
            this_object()->add_exit(file_name(instances_room),
                str, block_player);

            instances_room->add_exit(file_name(this_object()), opositeDirs[str]);
	    }

	    instances_room->set_master_instance_pointer(query_master_instance_pointer());

		instances_room->set_x(x + delta_x);
	    instances_room->set_y(y + delta_y);
	    instances_room->set_z(z + delta_z);

	    query_master_instance_pointer()->set_room_loc(x + delta_x, y + delta_y, z + delta_z, instances_room);

		if (room_ore != "none" && random(100) < (ORES[query_master_instance_pointer()->query_master_mine_ore()]["rarity"] + (tp->query_skill(SS_AWARENESS)/5))) //this is a vein (find it with rarity+(skill/5))
		{
	    	//and find (?) (the same ore again, it's a vein)
		}
		else
		{
			if (random(100) < -5 + (tp->query_skill(SS_AWARENESS)/10)) //this is a random find (find it with -5+(skill/10)) (max 5%)
			{
				room_ore = "none";
				tp->catch_msg("You catch a glimpse of a sparkling gem in the rubble.\n");
				gem = RANDOM_GEM_BY_RARITY(GEM_ALL);
                gem->move(environment(tp));
			}
			else if (random(100) < 0 + (tp->query_skill(SS_AWARENESS)/10)) //this is a random find (find it with (skill/10)) (max 10%)
			{
				room_ore = random_ore_by_value(0); //random ore selected taking into consideration rarity; if by luck, master_mine_ore is selected, this counts as the start of a vein too
			}
			else if (random(100) < ((ORES[query_master_instance_pointer()->query_master_mine_ore()]["rarity"]/2) + (tp->query_skill(SS_AWARENESS)/10))) //this is the start of a vein (find it with (rarity/2)+(skill/10))
			{
				room_ore = query_master_instance_pointer()->query_master_mine_ore();
			}
			else
			{ //no luck
				room_ore = "none";
			}
		}

    	create_reward(room_ore);

        //If ore was found that matches the mine type, make this next mined room of that ore type,
        //so the vein continues.
	    if (room_ore == query_master_instance_pointer()->query_master_mine_ore())
	    {
	    	instances_room->set_room_ore(query_master_instance_pointer()->query_master_mine_ore());
	    	room_ore = "none";
	    }
	    else
	    {
	    	instances_room->set_room_ore("none");
	    }

        //TODO
	    //query_master_mine_terrain() <- drop certain ammount since it's what you dug out too. (this will be ROCKs, not ores or gems)

		tp->catch_msg("You finish digging a new tunnel.\n");
		tell_room(environment(tp), QCTNAME(tp) + " finishes " +
                    "digging a new tunnel.\n", tp);

	}
	else
	{

        //if room exists and its a temple wall, you cant make the dig, instead inform the player of the wall.
        //also, save the location as mined, so if he tried to mine again, it would be informed of the wall.
        if (roomExists->query_dungeon_type() == "none" || roomExists->query_dungeon_type() == "door")
        {
            //normal
            if (str == "down")
            {
                this_object()->add_exit(file_name(roomExists),
                    str, block_player_down);

                this_object()->add_item(({ "rock" }),
                    "A big rock.\n");

                roomExists->add_item(({ "roof" }),
                    "There's a hole in the roof.\n");
            }
            else
            {
                this_object()->add_exit(file_name(roomExists),
                str, block_player);

                roomExists->add_exit(file_name(this_object()), opositeDirs[str]);
            }

            tell_room(file_name(roomExists), "Suddenly a wall crumbles " +
                        "and a new tunnel appears. Someone is on the other side.\n", tp);

            tp->catch_msg("You dig into a room.\n");
            tell_room(environment(tp), QCTNAME(tp) + " digs " +
                        "into a room.\n", tp);
        }
        else
        {
            //unbreakable
            this_object()->add_exit(file_name(roomExists),
            str, block_player_dungeon);

            tp->catch_msg("You mine into a rock formation with various inscriptions, " +
                        "that seems protected by magic. It will be impossible to continue this way.\n");
            tell_room(environment(tp), QCTNAME(tp) + " mines into a rock formation with various inscriptions, " +
                        "that seems protected by magic.\n", tp);
        }

	}

	someoneIsMining = 0;
	paralyze_mining->stop_paralyze();
}

mapping DIGING_EVENT_ROCK=   ([
                            "msg"   : "You mine a few rocks off.\n",
                            "env"   : " mines a few rocks off.\n",
                            "timer"  : -1,
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
                                        "the sand slides out freely.\n",
                            "env"   : " hits a patch of sand after breaking a rock, " +
                                        "the sand slides out freely.\n",
                            "timer"  : -2,
                            "fatigue" : -1,
                            "percent" : 0
                        ]);

mapping DIGING_EVENT_ROOF=   ([
                            "msg"   : "You hit the wrong rock, since some of the roof " +
                                        "falls and blocks part of what you were mining.\n",
                            "env"   : " hits the wrong rock, since some of the roof " +
                                        "falls and blocks the way.\n",
                            "timer"  : 2,
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


/*	Function name: dig
	Description: 

*/
void
dig(string str, int mining_timer)
{
	object tp = this_player();

	if (mining_timer < 0)
	{
    	add_instance_room(str);
    }
    else if (mining_timer > 25)
    {
        tp->catch_msg("You don't seem to be going nowhere, you stop mining to " +
                    "contemplate what you are doing wrong, perhaps you " +
                    "could use a bit more awareness.\n");
        tell_room(environment(tp), QCTNAME(tp) + " doesn't seem to be going nowhere, then stops mining to " +
                    "contemplate what's wrong.\n", tp);

        someoneIsMining = 0;
        paralyze_mining->stop_paralyze();
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
                someoneIsMining = 0;
                paralyze_mining->stop_paralyze();
                tp->catch_msg("You fall to the ground trying to catch your breath. You are too tired to keep mining.\n");
                tell_room(environment(tp), QCTNAME(tp) + " falls to the ground exhausted of mining.\n", tp);
                return;
            }
        }

        //TODO tweak values, change awareness for mining.
        DIGING_EVENT_ROCK["percent"]            = random(tp->query_skill(SS_AWARENESS) - 10);
        DIGING_EVENT_BIG_ROCK["percent"]        = random(tp->query_skill(SS_AWARENESS) - 50);
        DIGING_EVENT_UNBREAK_ROCK["percent"]    = random(70 - tp->query_skill(SS_AWARENESS));
        DIGING_EVENT_SAND["percent"]            = random(tp->query_skill(SS_AWARENESS) - 20);
        DIGING_EVENT_ROOF["percent"]            = random(50 - tp->query_skill(SS_AWARENESS));        

        string selected = random_by_percent(0, DIGING_EVENTS, "percent");

        tp->catch_msg(DIGING_EVENTS[selected]["msg"]);
        tell_room(environment(tp), QCTNAME(tp) + DIGING_EVENTS[selected]["env"], tp);
        mining_timer = mining_timer + DIGING_EVENTS[selected]["timer"];
        tp->add_fatigue(DIGING_EVENTS[selected]["fatigue"]);

        //TODO tweak values.
    	if (tp->query_skill(SS_AWARENESS) > 90 && room_ore != "none")
    	{
	    	if (random(100) < 10)
	    	{
		    	//and find (?)
		    	create_reward(room_ore);
	    	}
    	}

    	mining_alarm = set_alarm(5.0, 0.0, &dig(str, mining_timer));
    }
}

/*	Function name: do_dig
	Description: 

*/
int
do_dig(string str)
{
	object tp = this_player();
	int time_to_mine = 0;

    if (!str)
    {
    	notify_fail("Dig in what direction?\n");
    	return 0;
   	}

   	if (query_master_instance_pointer()->query_mine_boundaries(x,y,z) == 0)
   	{
   		notify_fail("It would seem this tunnel walls are " +
   			"pretty much made from bedrock. Nothing can break them.\n");
   		return 0;
   	}

    if (this_object()->query_dungeon_type() != "none")
    {
        notify_fail("The walls here seem protected by magic, various " +
            "inscriptions adorn them. It will be impossible to break through.\n");
        return 0;
    }

    object * ob = FIND_STR_IN_OBJECT("miner_pickaxe", this_player());
    if (!sizeof(ob))
    {
        notify_fail("You claw into the rocks with your bare hands, " +
        			"and as soon as you start bleeding, you quickly " +
        			"realize you need a pickaxe to do that.\n");
        return 0;
    }
    if (ob[0]->query_wielded() == 0)
    {
        notify_fail("You must wield the miner pickaxe first.\n");
        return 0;
    }

	if (str == "south" || str == "east" || str == "west" || 
		str == "north" || str == "down")
	{

		if (member_array(str,query_exit()) < 0)
		{
			if (!someoneIsMining)
			{
                if (ob[0]->use_pickaxe() >= 0 || this_player()->query_wiz_level())
                {
                    if (ob[0]->use_pickaxe() < 0 && this_player()->query_wiz_level())
                    {
                        write("Since you are a wizard, you can keep mining without recharging.\n");
                    }

    				tp->catch_msg("You start mining.\n");
    				tell_room(environment(tp), QCTNAME(tp) + " starts " +
    	                    "mining a wall.\n", tp);
    				
    				time_to_mine = 0 + random(ob[0]->check_delay_in_mining());

                    seteuid(getuid());
                    paralyze_mining = clone_object("/std/paralyze");
                    paralyze_mining->set_stop_fun("stop_mining");
                    paralyze_mining->set_stop_verb("stop");
                    paralyze_mining->set_combat_stop(1);
                    paralyze_mining->set_stop_message("You stop mining.\n");
                    paralyze_mining->set_remove_time(300);
                    paralyze_mining->set_fail_message("You are busy mining. You must " +
                        "'stop' to do something else.\n");
                    paralyze_mining->move(this_player(),1);

                    mining_alarm = set_alarm(5.0, 0.0, &dig(str, time_to_mine));

    				someoneIsMining = 1;
                }
                else
                {
                    tp->catch_msg("The pickaxe seems to have run out of juice, it's no longer humming. " +
                        "Try as you might, it's impossible to mine anything; you should <refill> the lava tank " +
                        "near a lava source.\n");
                }                    
			}
			else
			{
				tp->catch_msg("Someone is already mining here, wait till they finish or find another place.\n");
			}
		}
		else
		{
			tp->catch_msg("That direccion is already dug out.\n");
		}
	}
	else
	{
    	notify_fail("There no " + str + " direction, try north, east, etc.\n");
    	return 0;
    }
    return 1;
}


/*	Function name: stop_mining
	Description: stops mining alarms. resets flag "someoneIsMining" so the area can be mined again. this is for use with the paralize object only.

*/
varargs int
stop_mining(mixed arg)
{

    remove_alarm(mining_alarm);

    tell_room(environment(this_player()), QCTNAME(this_player())
      + " stops mining.\n", this_player());

    someoneIsMining = 0;

    return 0;
}
