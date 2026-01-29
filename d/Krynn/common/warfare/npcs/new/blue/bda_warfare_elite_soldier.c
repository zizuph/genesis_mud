
/* 
 * An elite blue dragonarmy soldier of the warfare system.
 */

inherit "/d/Krynn/common/warfare/npcs/new/std/dragonarmy_soldier_base";

int level;
int sublevel = 0; // elite soldier

int
random_soldier_type()
{
    int rand = random(10);

    switch(rand)
    {
        case 0..5:
            level = 3; // 60% 'fearsome' (139 stat average)
        break;
        case 6..8:
            level = 4; // 30% 'deadly' (169 stat average) 
        break;
        default:
            level = 5; // 10% 'elite' (189 stat average)
        break;
    }

    return level;
}

public void
create_dragonarmy_soldier()
{
    set_dragonarmy_level(random_soldier_type(), sublevel, "blue");
}
 