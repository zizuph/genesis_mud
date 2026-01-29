inherit "/d/Krynn/common/warfare/npcs/red/da_member";

void
create_da_monster()
{
    ::create_da_monster();
    set_dragonarmy_rank(2);
    arm_me();

    if (!random(5))
	set_hunt_enemy();

    set_patrol_path(({ &random_da_move() }));
    set_alarm(20.0, 0.0, &start_patrol());  
}
