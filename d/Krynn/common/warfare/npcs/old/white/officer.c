inherit "/d/Krynn/common/warfare/npcs/white/da_member";

void
create_da_monster()
{
    ::create_da_monster();
    set_dragonarmy_rank(2);
    arm_me();

    if (!random(4))
	set_hunt_enemy();

    set_stats(({150+random(30),150+random(30),
	        150+random(30),130+random(15),
		130+random(15),130+random(15)}));

    set_patrol_path(({ &random_da_move() }));
    set_alarm(20.0, 0.0, &start_patrol());  
}
