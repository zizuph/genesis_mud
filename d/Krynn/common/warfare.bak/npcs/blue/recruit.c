inherit "/d/Krynn/common/warfare/npcs/blue/da_member";

void
create_da_monster()
{
    ::create_da_monster();
    set_dragonarmy_rank(0, random(3) );
    arm_me();
}
