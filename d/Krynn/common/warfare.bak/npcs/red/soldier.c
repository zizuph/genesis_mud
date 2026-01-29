inherit "/d/Krynn/common/warfare/npcs/red/da_member";

void
create_da_monster()
{
    ::create_da_monster();
    set_dragonarmy_rank(1);
    arm_me();
    set_patrol_path(({ &random_da_move() }));
    set_alarm(20.0, 0.0, &start_patrol());  
}
