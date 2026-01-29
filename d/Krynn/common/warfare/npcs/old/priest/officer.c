inherit "/d/Krynn/common/warfare/npcs/blue/da_member";

void
create_da_monster()
{
    ::create_da_monster();
    set_dragonarmy_rank(2);
    arm_me();

    set_stats(({150+random(30),150+random(30),
	        150+random(30),130+random(15),
		130+random(15),130+random(15)}));
        
    string color = one_of_list(({"blue", "red", "black", "green", "white"}));
    set_color(color);
   
    if (!random(4))
	set_hunt_enemy();

    set_patrol_path(({ &random_da_move() }));
    set_alarm(20.0, 0.0, &start_patrol());  
}
