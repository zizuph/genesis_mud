inherit "/d/Krynn/common/warfare/npcs/green/da_member";

void
create_da_monster()
{
    ::create_da_monster();
    set_dragonarmy_rank(0, 3+random(4) );
    arm_me();
}
