
/* 
 * A green dragonarmy high officer of the warfare system.
 */

inherit "/d/Krynn/common/warfare/npcs/new/std/dragonarmy_soldier_base";

int level;
int sublevel = 2; // high officer

int
random_soldier_type()
{
    int rand = random(10);

    switch(rand)
    {
        case 0..1:
            level = 3; // 20% 'fearsome' (139 stat average)
        break;
        case 2..6:
            level = 4; // 50% 'deadly' (169 stat average) 
        break;
        default:
            level = 5; // 30% 'elite' (189 stat average)
        break;
    }

    return level;
}

public void
create_dragonarmy_soldier()
{
    set_dragonarmy_level(random_soldier_type(), sublevel, "green");
}
 