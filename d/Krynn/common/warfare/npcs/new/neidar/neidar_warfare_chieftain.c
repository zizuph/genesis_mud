
/* 
 * A neidar chieftain of the warfare system.
 */

inherit "/d/Krynn/common/warfare/npcs/new/std/neidar_base";

int level;
int sublevel = 4; // chieftain

int
random_soldier_type()
{
    int rand = random(10);

    switch(rand)
    {
        case 0..1:
            level = 3; // 20% 'grizzled' (139 stat average)
        break;
        case 2..6:
            level = 4; // 50% 'deadly' (169 stat average) 
        break;
        default:
            level = 5; // 30% 'legendary' (189 stat average)
        break;
    }

    return level;
}

public void
create_neidar_soldier()
{
    set_neidar_level(random_soldier_type(), sublevel, "neidar");
}
 