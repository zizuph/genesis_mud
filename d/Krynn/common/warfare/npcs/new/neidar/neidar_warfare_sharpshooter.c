
/* 
 * A neidar Sharpshooter of the warfare system.
 */

inherit "/d/Krynn/common/warfare/npcs/new/std/neidar_base";

int level;
int sublevel = 5; // Sharpshooter

int
random_soldier_type()
{
    int rand = random(10);

    switch(rand)
    {
        case 0..4:
            level = 3; // 50% 'grizzled' (139 stat average)
        break;
        case 5..8:
            level = 4; // 40% 'deadly' (169 stat average) 
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
 