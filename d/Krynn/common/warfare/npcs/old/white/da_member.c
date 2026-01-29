inherit "/d/Ansalon/guild/dragonarmy/npc/da_member";

void
create_da_monster()
{
    if (random(3))
	set_race_name("human");
    else
	set_race_name("goblin");

    set_random_name();

    //set_hunt_enemy(); no hunting for now.

    add_name("_da_member_");
    set_pick_up_team(({"_da_member_", "aurak", "sivak", "bozak", "kapak",
                           "baaz"}));
    set_max_team_size_auto_join(5);

    set_color("white");

    //set_patrol_path(({ &random_da_move() }));
    //set_alarm(20.0, 0.0, &start_patrol());  
    // no patrolling either!!

    set_alarm(10.0, 0.0, &cut_special_skill());
}
