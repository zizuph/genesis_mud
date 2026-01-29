
/* 
 * A neidar slayer of the warfare system.
 */

inherit "/d/Krynn/common/warfare/npcs/new/std/neidar_base";

int level;
int sublevel = 2; // slayer

int
random_soldier_type()
{
    int rand = random(10);

    switch(rand)
    {
        case 0..5:
            level = 3; // 60% 'grizzled' (139 stat average)
        break;
        case 6..8:
            level = 4; // 30% 'deadly' (169 stat average) 
        break;
        default:
            level = 5; // 10% 'legendary' (189 stat average)
        break;
    }

    return level;
}

public void
create_neidar_soldier()
{
    set_neidar_level(random_soldier_type(), sublevel, "neidar");
}
 