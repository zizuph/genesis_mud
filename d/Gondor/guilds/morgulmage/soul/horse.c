/*
* Used to create and move horse to player after delay in nsummon
*/

public void
make_horse(object player)
{
    object horse;

    setuid();
    seteuid(getuid());

    string name = "dark_horse_of_" + player->query_real_name();
    
    horse = clone_object("/d/Gondor/morgul/city/mm_stables/obj/steed");
    horse->move_living("M", ENV(TP));
    horse->set_horse_desc(name);
    tell_room(ENV(horse), "A " + horse->short() + " comes galloping in.\n", ({ player }));
    
    player->catch_msg("With pounding hooves and flying tail, a " +
       horse->short() +" gallops to your side, lowering its head obediently.\n");
    return;
}

/*
* Used to move horse to player after delay in msummon
*/

public void
bring_horse(object horse)
{
    // Make sure not to move if horse has a driver or leader
    if (objectp(horse->query_leader()))
    {
        return;
    }

    if (objectp(horse->query_driver()))
    {
        return;
    }


    horse->move_living("off", ENV(TP));
    return;
}


/*
 * msteed - summon your horse
 */


public int
msteed()
{
    object horse;
    mapping steed_owners = ([ ]);
    string horse_name, player_name, *props, *saved_data;
    int test;

    player_name = QCTNAME(TP);

    // We need to switch euid's in order to access map
    setuid();
    seteuid(getuid());
    steed_owners = restore_map("/d/Gondor/morgul/city/mm_stables/log/steed_owners");

    if (!steed_owners[TP->query_real_name()])
    {
        write("You don't have a horse. Go visit the stable master.\n");
        return 1;
    }

    // Get room properties and do checks to be sure horse is allowed here.
    props = ENV(TP)->query_props();

    // Cheesy test to see if ship is at sea. Help me please.
    // if (ENV(TP)->query_prop(ROOM_I_TYPE) == ROOM_IN_WATER)
    test = member_array("_room_m_no_firewood", props);
    if (test != -1)
    {
        write("Your horse can swim, but not quite that good.\n");
        return 1;
    }

    test = member_array("_room_i_no_allow_steed", props);
    if (test != -1)
    {
        write("Your horse isn't allowed here.\n");
        return 1;
    }

    test = member_array("_room_i_inside", props);
    if (test != -1)
    {
        write("Your horse can't come inside this room. " +
            "Try summoning from outdoors.\n");
        return 1;
    }

    horse_name = "dark_horse_of_" + TP->query_real_name();

    write("You shriek shrilly into the air, summoning your dark steed.\n");
    say(player_name + " shrieks shrilly into the air.\n");

    if (find_living(lower_case(horse_name)))
    {
        horse = find_living(lower_case(horse_name));
        if (ENV(TP) == ENV(horse))
        {
            horse->command("eyebrow");
            return 1;
        }
        set_alarm(8.0, 0.0, &bring_horse(horse));
        return 1;
    }
    set_alarm(8.0, 0.0, &make_horse(TP));
    return 1;
}
